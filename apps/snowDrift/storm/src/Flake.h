
#ifndef _FLAKE_
#define _FLAKE_

#include <vector>
#include <va/Shape.h>
#include <va/VertexShape.h>

class Storm;


class Flake : public va::Shape {

    public:

        Flake( Storm* storm );        
        
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        
        void run();
    
    protected:
    	Storm* _storm;
        
        osg::Vec3 _loc;
        osg::Vec3 _vel;
        osg::Vec3 _acc;
        float _r;
        float _maxsteer;
        float _maxvelocity;
        
        osg::ref_ptr<va::VertexShape> _trail;
        
        osg::Vec3 separate();
        osg::Vec3 align();
        osg::Vec3 cohesion();
        osg::Vec3 steer( const osg::Vec3& target, bool slowdown );
        
    
};


#endif