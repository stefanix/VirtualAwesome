
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
    panel1->setPosition(0.5*scene->getWidth(),0.6*scene->getHeight(),0);
    scene->addChild(panel1);
    
    toggle1 = new va::ToggleWidget(280,40);
    toggle1->setLabel("recognize DRAG gesture");
    toggle1->setValue(true);
    toggle1->setPosition(0,-50);
    toggle1->addEventHandler(this);
    panel1->addChild(toggle1);  

    toggle2 = new va::ToggleWidget(280,40);
    toggle2->setLabel("recognize SCALE gesture");
    toggle2->setValue(true);
    toggle2->setPosition(0,-100);
    toggle2->addEventHandler(this);
    panel1->addChild(toggle2);  
    
    toggle3 = new va::ToggleWidget(280,40);
    toggle3->setLabel("recognize ROTATION gesture");
    toggle3->setValue(true);
    toggle3->setPosition(0,-150);
    toggle3->addEventHandler(this);
    panel1->addChild(toggle3);  
}

MyApp::~MyApp(){}



void MyApp::widget( va::ToggleWidget& toggle ) {
    if (&toggle == toggle1) {
        if (toggle1->getValue()) {
            panel1->enableTwoTouchMove();
        } else {
            panel1->disableTwoTouchMove();
        }
    } else if (&toggle == toggle2) {
        if (toggle2->getValue()) {
            panel1->enableTwoTouchScale();
        } else {
            panel1->disableTwoTouchScale();
        }
    } else if (&toggle == toggle3) {
        if (toggle3->getValue()) {
            panel1->enableTwoTouchRotate();
        } else {
            panel1->disableTwoTouchRotate();
        }
    }
}



