
#include "MyApp.h"



MyApp::MyApp(){
	
    scene->hideCursor();
    scene->enableTouchVisuals();
    
            
    // setup multiple mouse input
    //
    mice = new vaMice::Mice();
    mice->addEventHandler(scene);
    
    
    // setup some widgets
    //
    va::ButtonWidget* button1 = new va::ButtonWidget(140,40);
    button1->setLabel("Black");
    button1->setPosition(500,600);
    button1->setPosition(scene->getWidth()-750,30);
    button1->addEventHandler(this);
    scene->addChild(button1);

    sliderR = new va::SliderWidget(300,40);
    sliderR->setLabel("Red");
    sliderR->setPosition(scene->getWidth()-500,20);
    sliderR->addRotationZ(va::PI/4);
    sliderR->setValueMin(0.0f);
    sliderR->setValueMax(1.0f);
    sliderR->addEventHandler(this);
    scene->addChild(sliderR); 

    sliderG = new va::SliderWidget(300,40);
    sliderG->setLabel("Green");
    sliderG->setPosition(scene->getWidth()-400,20);
    sliderG->addRotationZ(va::PI/4);
    sliderG->setValueMin(0.0f);
    sliderG->setValueMax(1.0f);
    sliderG->addEventHandler(this);
    scene->addChild(sliderG); 

    sliderB = new va::SliderWidget(300,40);
    sliderB->setLabel("Blue");
    sliderB->setPosition(scene->getWidth()-300,20);
    sliderB->addRotationZ(va::PI/4);
    sliderB->setValueMin(0.0f);
    sliderB->setValueMax(1.0f);
    sliderB->addEventHandler(this);
    scene->addChild(sliderB); 
    
    panel1 = new va::PanelWidget(300,200);
    panel1->setLabel("Empty Panel");
    panel1->setPosition(200,500);
    panel1->setPivot(150,100,0);
    scene->addChild(panel1);
    
    panel2 = new va::PanelWidget(300,160);
    panel2->setPivot(150,80,0);
    panel2->setPosition(700,500,0);
    scene->addChild(panel2);
    
    textbox1 = new va::TextShape(300,160);
    textbox1->setName("MyTextfield");
    textbox1->setText("This example is written for multiple mouse devices. Attach as many of them to your computer and use them simultanously. This is particularly useful when designing interfaces for multiple users or for testing multitouch interaction.");
    textbox1->setPadding(20.0f);
    panel2->addChild(textbox1);
    
    toggle1 = new va::ToggleWidget(180,40);
    toggle1->setLabel("Make Text Red");
    toggle1->setPosition(0,-50);
    toggle1->addEventHandler(this);
    panel2->addChild(toggle1);
    
    // set an initial background color through the sliders
    sliderR->setValue(0.3f);
    sliderB->setValue(0.1f);
    sliderG->setValue(0.0f);
    
}

MyApp::~MyApp(){
    delete mice;
    scene->showCursor();
}


void MyApp::update(){
    mice->update();
}

void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getLabel() == "Black") {
        sliderR->setValue(0.0f);
        sliderG->setValue(0.0f);
        sliderB->setValue(0.0f);
    }
}
void MyApp::widget( va::SliderWidget& slider ) {
	scene->setBackgroundColor( sliderR->getValue(), 
                               sliderG->getValue(), 
                               sliderB->getValue() );
}
void MyApp::widget( va::ToggleWidget& toggle ) {
    if (&toggle == toggle1) {
        if( toggle.getValue() ) {
            textbox1->setColor(1.0f, 0.0f, 0.0f, 1.0f);
        } else {
            textbox1->setColor(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
}



