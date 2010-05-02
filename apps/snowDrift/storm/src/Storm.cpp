
#include "Storm.h"
#include "Flake.h"


Storm::Storm() {

	//bounds.set(0,0,0, 800,800,0);
    
	for (unsigned int i=0; i<100; ++i) {
        Flake* flake = new Flake(this);
        flakes.push_back(flake);
        addChild(flake);
    }
        
    enableUpdateCallback();
    disableDepthTest();
    disableLighting();
    enableBlending();
    
    va::seedRandom();
    
}


void Storm::update() {
	for (unsigned int i=0; i<flakes.size(); ++i) {
        flakes[i]->run();
    }    
}


void Storm::setBounds( float xMin, float yMin, float zMin, float xMax, float yMax, float zMax ){
	bounds.set(xMin, yMin, zMin, xMax, yMax, zMax);
}

