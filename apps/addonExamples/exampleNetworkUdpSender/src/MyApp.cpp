
#include "MyApp.h"



MyApp::MyApp(){
    
    sender = new vaNetwork::AwesomeSocket();
    sender->setRemoteHost("127.0.0.1", 4242);
    
    panel = new va::PanelWidget(600,240);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,240);
    textbox->setText("Press button to send UDP message to 127.0.0.1:4242");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
    button1 = new va::ButtonWidget(200,40);
    button1->setLabel("Send \"hi!\"");
    button1->setPosition(0,-50,0);
    button1->addEventHandler(this);
    panel->addChild(button1);    
}

MyApp::~MyApp(){
	delete sender;
}


void MyApp::widget( va::ButtonWidget& button ) {
	if (&button == button1) {
     	sender->send("hi!");
    }
}