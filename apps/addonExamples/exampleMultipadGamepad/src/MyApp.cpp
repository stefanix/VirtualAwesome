
#include "MyApp.h"



MyApp::MyApp(){

    scene->hideCursor();
    
    
    // setup multitouch gamepad
    //
    gamepad = new vaMultipad::GamepadWidget(300);
    gamepad->setPosition(0.5*scene->getWidth()-150,50);
    gamepad->addEventHandler(this);
    scene->addChild(gamepad);
    
    spaceshipContainer = new va::Node();
    spaceshipContainer->setPosition(0.5*scene->getWidth(),scene->getHeight()-300,0); 
    spaceshipContainer->addRotationX(0.5);   
    scene->addChild(spaceshipContainer);    
    
    spaceship = new va::Model();
    spaceship->loadModel("spaceship.osg");
    spaceship->addRotationX(1.3);  // adjust orientation
    spaceship->addRotationZ(2.6);  // adjust orientation
    spaceship->setScale(20);
    spaceshipContainer->addChild(spaceship);    
 
}

MyApp::~MyApp(){}


void MyApp::widget( vaMultipad::GamepadWidget& gamepad ) {
    if (gamepad.isStick1Event()) {
    	//not smoothed, direct
		//spaceship->setX(gamepad.getStick1()[0]*400);
		//spaceship->setY(gamepad.getStick1()[1]*200);
        
        //0.8 to 0.2 smoothed
		spaceship->setX(0.8*spaceship->getX()+0.2*(gamepad.getStick1()[0]*400));
		spaceship->setY(0.8*spaceship->getY()+0.2*(gamepad.getStick1()[1]*200));
    }
    
    if (gamepad.isStick2Event()) {
        spaceshipContainer->resetRotation();
        spaceshipContainer->addRotationZ(-gamepad.getStick2()[0]);
        spaceshipContainer->addRotationX(0.5-gamepad.getStick2()[1]);
    }
}


