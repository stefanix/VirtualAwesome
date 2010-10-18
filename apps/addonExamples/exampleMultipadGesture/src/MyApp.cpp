
#include "MyApp.h"



MyApp::MyApp(){

    scene->enableTouchVisuals();
    scene->hideCursor();
    
    
    // setup multitouch pad
    //
    vaMultipad::Multipad* pad = vaMultipad::getMultipad();
    pad->addEventHandler(scene);
    
    
    // setup some widgets
    //
    panel1 = new va::GestureWidget(600,400);
    panel1->setPivot(300,200,0);
    panel1->setPosition(0.5*scene->getWidth(),0.5*scene->getHeight(),0);
    scene->addChild(panel1);
    
    toggle1 = new va::ToggleWidget(180,40);
    toggle1->setLabel("Make Text Red");
    toggle1->setPosition(0,-50);
    toggle1->addEventHandler(this);
    panel1->addChild(toggle1);  
}

MyApp::~MyApp(){}



void MyApp::touchDown( va::Touch& touch ){

}

void MyApp::touchMove( va::Touch& touch ){}

void MyApp::touchUp( va::Touch& touch ){

}


void MyApp::widget( va::ToggleWidget& toggle ) {
    if (&toggle == toggle1) {    //match by pointer

    }
}



