
#include "MyApp.h"



MyApp::MyApp(){
    
    receiver = new vaOsc::Receiver(4242);
    receiver->addOscHandler(this);
    std::cout << "listening for osc on port 4242" << std::endl;
    
    panel = new va::PanelWidget(600,140);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,140);
    textbox->setText("No OSC message received yet.");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
}

MyApp::~MyApp(){}


void MyApp::oscReceive( vaOsc::Message message ) {
    // check for mouse moved message
    if ( message.getAddress() == "/mouse/position" ) {
        textbox->setText("mouse positionX: ");
        textbox->appendText(message.getArgAsInt(0));
        textbox->appendText(" positionY: ");
        textbox->appendText(message.getArgAsInt(1));        
    }
    // check for mouse button message
    else if ( message.getAddress() == "/mouse/button" ) {
        textbox->setText("mouse button: ");
        textbox->appendText(message.getArgAsInt(0));
    }
    // unrecognized message
    else {
        textbox->setText("");
        textbox->appendText(message.getAddress());
        textbox->appendText(": ");
        for ( int i=0; i<message.getNumArgs(); i++ ) {
            textbox->appendText(message.getArgTypeName(i));
            textbox->appendText(":");
            if( message.getArgType(i) == vaOsc::TYPE_INT ) {
                textbox->appendText(message.getArgAsInt(i));
            } else if( message.getArgType(i) == vaOsc::TYPE_FLOAT ) {
                textbox->appendText(message.getArgAsFloat(i));
            } else if( message.getArgType(i) == vaOsc::TYPE_STRING ) {
                textbox->appendText(message.getArgAsString(i));
            } else {
                textbox->appendText("unknown");
            }
            textbox->appendText(", ");
        }            
    }
}


