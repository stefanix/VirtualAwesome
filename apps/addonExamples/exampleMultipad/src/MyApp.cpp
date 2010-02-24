
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
    panel1 = new va::PanelWidget(300,200);
    panel1->setLabel("MyPanel");
    panel1->setPosition(200,500);
    panel1->setPivot(150,100,0);
    scene->addChild(panel1);

    va::ButtonWidget* button1 = new va::ButtonWidget(200,40);
    button1->setLabel("Reset Rotation");
    button1->setPivot(100,25,0);
    button1->setPosition(150,50);
    button1->addEventHandler(this);
    panel1->addChild(button1);

    slider1 = new va::SliderWidget(240,40);
    slider1->setLabel("Rotation");
    slider1->setPosition(30,100);
    slider1->setValueMin(-va::PI);
    slider1->setValueMax(va::PI);
    slider1->addEventHandler(this);
    panel1->addChild(slider1); 

    slider2 = new va::SliderWidget(400,40);
    slider2->setLabel("Scale");
    slider2->setPivot(200,20,0);
    slider2->setPosition(450,500);
    slider2->addRotationZ(va::PI/2);
    slider2->setValueMin(0.0f);
    slider2->setValueMax(2.0f);
    slider2->addEventHandler(this);
    scene->addChild(slider2); 

    panel2 = new va::PanelWidget(300,140);
    panel2->setPivot(150,70,0);
    panel2->setPosition(700,500,0);
    scene->addChild(panel2);
    
    textbox1 = new va::TextShape(300,140);
    textbox1->setName("MyTextfield");
    textbox1->setText("This example is written for multitouch pads typically found in Apple notebooks. The regular mouse pointer is deactivated and each touch on the pad becomes a pointer of its own. ");
    textbox1->setPadding(20.0f);
    panel2->addChild(textbox1);
    
    toggle1 = new va::ToggleWidget(180,40);
    toggle1->setLabel("Make Text Red");
    toggle1->setPosition(0,-50);
    toggle1->addEventHandler(this);
    panel2->addChild(toggle1);  
}

MyApp::~MyApp(){}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getLabel() == "Reset Rotation") {  //match by label
        slider1->setValue(0.0f);
    }
}
void MyApp::widget( va::SliderWidget& slider ) {
    if (&slider == slider1) {        //match by pointer
        panel2->resetRotation();
        panel2->addRotationZ(-slider.getValue());
    } else if (&slider == slider2) {
        panel1->setScale(slider.getValue());  
        panel2->setScale(slider.getValue());    
    }
}
void MyApp::widget( va::ToggleWidget& toggle ) {
    if (&toggle == toggle1) {    //match by pointer
        if( toggle.getValue() ) {
            textbox1->setColor(1.0f, 0.0f, 0.0f, 1.0f);
        } else {
            textbox1->setColor(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
}



