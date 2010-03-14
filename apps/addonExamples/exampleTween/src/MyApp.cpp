
#include "MyApp.h"



MyApp::MyApp(){
	
    myRect = new va::RectangleShape(50, 20);
    myRect->setPosition(0, 0.5*scene->getHeight(), 0);
    myRect->setColor(1.0, 0.19, 0.14, 1.0);
    scene->addChild(myRect);

}

MyApp::~MyApp(){}


void MyApp::update() {
	static bool bRight = true;
    static int dur = 150;
	float time = scene->getFrameNumber() % dur;
    
    if (time == 0) {
        bRight = !bRight;
    }
    
    float w = scene->getWidth();
    float wrec = myRect->getWidth();
    
    if (bRight) {
        myRect->setX( tween.easeInOut(time, 0, w-wrec, dur) );
    } else {
        myRect->setX( tween.easeInOut(time, w-wrec, -w+wrec, dur) );
	}
}





