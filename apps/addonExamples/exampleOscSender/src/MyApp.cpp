
#include "MyApp.h"



MyApp::MyApp(){
    
    sender = new vaOsc::Sender("127.0.0.1", 4242);
    
    
    // setup some widgets
    //
    panel = new va::PanelWidget(300,140);
    panel->setPivot(150,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(300,140);
    textbox->setName("Latest Received Network Message");
    textbox->setText("No message received yet.");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
    va::ButtonWidget* buttonSend = new va::ButtonWidget(200,40);
    buttonSend->setName("send");
    buttonSend->setLabel("Send 'hello' to all.");
    buttonSend->setPivot(100,25,0);
    buttonSend->setPosition(150,-40);
    buttonSend->addEventHandler(this);
    panel->addChild(buttonSend);    
}

MyApp::~MyApp(){}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getName() == "send") {  //match by name
		vaOsc::Message m;
		m.setAddress( "/test" );
		m.addIntArg( 1 );
		m.addFloatArg( 3.5f );
		m.addStringArg( "hello" );
		m.addFloatArg( (float)scene->getSimulationTime() );
		sender->sendMessage( m );
    }
}



