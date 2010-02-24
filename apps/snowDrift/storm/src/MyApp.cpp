
#include "MyApp.h"


MyApp::MyApp(){

	scene->setBackgroundColor(1,1,1);

    panel1 = new va::PanelWidget(300,200);
    panel1->setLabel("MyPanel");
    panel1->setPosition(200,500);
    panel1->setPivot(150,100,0);
    scene->addChild(panel1);

    va::ButtonWidget* button1 = new va::ButtonWidget(200,40);
    button1->setName("Reset");
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
    
    Storm* storm = new Storm();
    //storm->setPosition(700,100,0);
    storm->setBounds(0,0,0, scene->getWidth(),scene->getHeight(), 0);
    scene->addChild(storm);
    
}

MyApp::~MyApp(){}



void MyApp::touchMove( va::Touch& touch ){
	//touch.getX();
}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getName() == "Reset") {  //match by name
        slider1->setValue(0.0f);
    }
}
void MyApp::widget( va::SliderWidget& slider ) {
    if (&slider == slider1) {        //match by pointer
        //
    }
}




