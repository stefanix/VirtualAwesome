
#include "MyApp.h"



MyApp::MyApp(){
    
    receiver = new vaOsc::Receiver(4242);
    receiver->addOscHandler(this);
    std::cout << "listening for osc on port 4242" << std::endl;
    
    // setup some widgets
    //
    panel = new va::PanelWidget(600,140);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,140);
    textbox->setName("Latest Received Network Message");
    textbox->setText("No message received yet.");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
}

MyApp::~MyApp(){}


void MyApp::oscReceive( vaOsc::Message message ) {
    // check for mouse moved message
    if ( message.getAddress() == "/mouse/position" ) {
        // both the arguments are int32's
        //mouseX = message.getArgAsInt32( 0 );
        //mouseY = message.getArgAsInt32( 1 );
    }
    // check for mouse button message
    else if ( message.getAddress() == "/mouse/button" ) {
        // the single argument is a string
        //mouseButtonState = message.getArgAsString( 0 ) ;
        
    } else {
        // unrecognized message: display on the bottom of the screen
        textbox->setText("");
        textbox->appendText(message.getAddress());
        textbox->appendText(": ");
        for ( int i=0; i<message.getNumArgs(); i++ ) {
            // get the argument type
            textbox->appendText(message.getArgTypeName(i));
            textbox->appendText(":");
            // display the argument - make sure we get the right type
            if( message.getArgType( i ) == vaOsc::TYPE_INT32 )
                textbox->appendText(message.getArgAsInt32(i));
            else if( message.getArgType( i ) == vaOsc::TYPE_FLOAT )
                textbox->appendText(message.getArgAsFloat(i));
            else if( message.getArgType( i ) == vaOsc::TYPE_STRING )
                textbox->appendText(message.getArgAsString(i));
            else
                textbox->appendText("unknown");
        }            
    }
}


