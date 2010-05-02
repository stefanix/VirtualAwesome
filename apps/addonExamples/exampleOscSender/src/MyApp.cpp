
#include "MyApp.h"



MyApp::MyApp(){
    
    sender = new vaOsc::Sender("127.0.0.1", 4242);
    
    buttonSend = new va::ButtonWidget(250,40);
    buttonSend->setLabel("Send message to port 4242.");
    buttonSend->setPivot(125,25,0);
    buttonSend->setPosition(0.5*scene->getWidth(),500,0);
    buttonSend->addEventHandler(this);
    scene->addChild(buttonSend);    
}

MyApp::~MyApp(){}


void MyApp::touchMove( va::Touch& touch ) {
    vaOsc::Message m;
    m.setAddress( "/mouse/position" );
    m.addIntArg(touch.getX());
    m.addIntArg(touch.getY());
    sender->sendMessage( m );   
}

void MyApp::mouseButton( va::Mouse& mouse ) {
    vaOsc::Message m;
    m.setAddress( "/mouse/button" );
    m.addIntArg(mouse.getButtonDirection());
    sender->sendMessage( m );
}

void MyApp::widget( va::ButtonWidget& button ) {
    if (&button == buttonSend) {
        vaOsc::Message m;
        m.setAddress( "/someAddress" );
        m.addIntArg( 23 );
        m.addFloatArg( 4.3f );
        m.addStringArg( "someString" );
        m.addFloatArg( scene->getSimulationTime() );
        sender->sendMessage( m );
    }
}



