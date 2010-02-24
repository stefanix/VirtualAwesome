
#ifndef _STORM_
#define _STORM_

#include <va/Node.h>

class Flake;


class Storm : public va::Node {

    public:

        Storm();        
        void update();
        
        void setBounds( float xMin, float yMin, float zMin, float xMax, float yMax, float zMax );
        
    
    protected:
    	friend class Flake;
    	std::vector<Flake*> flakes;
        osg::BoundingBox bounds;
        
        void seedRandom();
        void seedRandom( long seed );
        float random( float min, float max );
        
    
};


#endif