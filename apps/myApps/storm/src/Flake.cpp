
#include "Flake.h"
#include "Storm.h"


Flake::Flake( Storm* storm ) {
	_storm = storm;

    _trail = new va::VertexShape();
    _trail->setMode(GL_TRIANGLE_STRIP);
    addChild(_trail);
    
    setPosition(va::random(600,700), va::random(600,700),0);    
    _loc = getPosition();
    _vel.set(va::random(0.001,0.01), va::random(0.001,0.01),0);    
	
    // adding 40 vertices
	for (unsigned int i=0; i<20; ++i) {
        _trail->addVertex(i, 0, 0);
        _trail->addVertex(i, 10, 0);
    }

    // adding 40 vertex colors
	for (unsigned int i=0; i<20; ++i) {
        _trail->addVertexColor(0, 0, 0, 1-(i/20.0f));
        _trail->addVertexColor(0, 0, 0, 1-(i/20.0f));
    }
        
    disableDepthTest();
    disableLighting();
    enableBlending();
    
    _maxvelocity = 10.0;
    _maxsteer = 3.0;
    _r = 10;
}


void Flake::setColor( float r, float g, float b, float a ) {
    setColor(osg::Vec4(r,g,b,a));
}
    
void Flake::setColor( const osg::Vec4& color ) {
    _trail->setColor(color);
}



void Flake::run() {

	// calculate steering vectors, Craig-Reynold-style.
    osg::Vec3 sep = separate();
    osg::Vec3 ali = align();
    osg::Vec3 coh = cohesion();
    // arbitrarily weight these forces
    sep *= 0.1;
    ali *= 0.04;
    coh *= 0.06;
    // add the force vectors to acceleration
    _acc += sep + ali + coh;
                
    // update location
    //
    _vel += _acc;
    //limit _vel
    float lenVel = _vel.length();
    if (lenVel>_maxvelocity && lenVel!=0) {
        _vel *= _maxvelocity/lenVel;
    }
    _loc += _vel;
    _acc.set(0,0,0);  //reset
        

	// borders
    //
    if (_loc.x() < _storm->bounds.xMin()-_r) {_vel.x() *= -1;}
    if (_loc.y() < _storm->bounds.yMin()-_r) {_vel.y() *= -1;}
    if (_loc.x() > _storm->bounds.xMax()+_r) {_vel.x() *= -1;}
    if (_loc.y() > _storm->bounds.yMax()+_r) {_vel.y() *= -1;}
    
    
    /*
	for (unsigned int i=39; i>2; i-=2) {
    	_trail->setVertex( i, _trail->getVertex(i-2) );
    	_trail->setVertex( i-1, _trail->getVertex(i-3) );
    }

	//std::cout << _loc.x() << std::endl;
        
    _trail->setVertex(0, osg::Vec3(_loc.x(), _loc.y()-5, _loc.z()) );   
    _trail->setVertex(1, osg::Vec3(_loc.x(), _loc.y()+5, _loc.z()) );
    */
    
    setPosition(_loc);
    setRotation( atan2(_vel.y()-_vel.x(),_vel.x()+_vel.y())+va::PI_4, 0,0,1);   
}



osg::Vec3 Flake::separate() {
	// for every flake, calc vector to steer away from nearby flakes 
    float desiredseparation = 20.0;
    osg::Vec3 steer = osg::Vec3(0,0,0);
    int count = 0;
    for (unsigned int i=0 ; i<_storm->flakes.size(); i++) {
    	Flake* other = _storm->flakes[i];
        float d = (_loc-(other->_loc)).length();  //distance
        if (d>0 && d<desiredseparation) {
            osg::Vec3 diff = _loc - other->_loc;  // away from neighbor
            diff.normalize();
            diff /= d;                            // weight by distance
            steer += diff;
            count++;
        }
    }
    
    if (count > 0) {
    	// average vector length
        steer /= (float)count;
    }

    if (steer.length() > 0) {
        // Implement Reynolds: Steering = Desired - Velocity
        steer.normalize();
        steer *= _maxvelocity;
        steer -= _vel;
        //limit steer
        float len = steer.length();
        if (len>_maxsteer && len!=0) {
            steer *= _maxsteer/len;
        }        
    }
    return steer;
}



osg::Vec3 Flake::align() {
	// for every flake, calc vector to align with nearby flakes
    
    float neighbordist = 25.0;
    osg::Vec3 steer = osg::Vec3(0,0,0);
    int count = 0;
    for (unsigned int i=0; i<_storm->flakes.size(); i++) {
		Flake* other = _storm->flakes[i];
        float d = (_loc-(other->_loc)).length();  //distance
        if ((d > 0) && (d < neighbordist)) {
            steer += other->_vel;
            count++;
        }
    }
    if (count > 0) {
      steer /= (float)count;
    }

    // As long as the vector is greater than 0
    if (steer.length() > 0) {
        // Implement Reynolds: Steering = Desired - Velocity
        steer.normalize();
        steer *= _maxvelocity;
        steer -= _vel;
        //limit steer
        float len = steer.length();
        if (len>_maxsteer && len!=0) {
            steer *= _maxsteer/len;
        }
    }
    return steer;
}



osg::Vec3 Flake::cohesion() {
	// for every flake, calc vector to steer to the center of nearby flakes
    
    float neighbordist = 100.0;
    osg::Vec3 sum = osg::Vec3(0,0,0);
    int count = 0;
    for (unsigned int i=0; i<_storm->flakes.size(); i++) {
		Flake* other = _storm->flakes[i];
        float d = (_loc-(other->_loc)).length();  //distance
      	if ((d > 0) && (d < neighbordist)) {
        	sum += other->_loc; // Add location
        	count++;
        }
    }
    if (count > 0) {
      sum /= (float)count;
      return steer(sum,false);  // Steer towards the location
    }
    return sum;
}



osg::Vec3 Flake::steer( const osg::Vec3& target, bool slowdown ){
    // A method that calculates a steering vector towards a target
    // Takes a second argument, if true, it slows down as it approaches the target

    osg::Vec3 steer;  // The steering vector
    osg::Vec3 desired = target - _loc;  // A vector pointing from the location to the target
    float d = desired.length(); // Distance from the target is the magnitude of the vector
    // If the distance is greater than 0, calc steering (otherwise return zero vector)
    if (d > 0) {
        // Normalize desired
        desired.normalize();
        // Two options for desired vector magnitude (1 -- based on distance, 2 -- _maxvelocity)
        if ((slowdown) && (d < 100.0)) {
        	desired *= _maxvelocity*(d/100.0); // This damping is somewhat arbitrary
        } else {
        	desired *= _maxvelocity;
        }
        // Steering = Desired minus Velocity
        steer = desired - _vel;
        
        //limit steer
        float len = steer.length();
        if (len>_maxsteer && len!=0) {
            steer *= _maxsteer/len;
        }        
    } else {
        steer = osg::Vec3(0,0,0);
    }
    return steer;
}

