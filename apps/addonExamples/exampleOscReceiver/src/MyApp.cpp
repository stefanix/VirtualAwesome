
#include "MyApp.h"



MyApp::MyApp(){
    
    receiver = new vaOsc::Receiver(4242);
    std::cout << "listening for osc on port 4242" << std::endl;
    
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


void MyApp::update() {
	while( receiver->hasWaitingMessages() ) {
		vaOsc::Message m = receiver->getNextMessage();
        
		// check for mouse moved message
		if ( m.getAddress() == "/mouse/position" ) {
			// both the arguments are int32's
			//mouseX = m.getArgAsInt32( 0 );
			//mouseY = m.getArgAsInt32( 1 );
		}
		// check for mouse button message
		else if ( m.getAddress() == "/mouse/button" ) {
			// the single argument is a string
			//mouseButtonState = m.getArgAsString( 0 ) ;
            
		} else {
			// unrecognized message: display on the bottom of the screen
            textbox->setText("");
            textbox->appendText(m.getAddress());
            textbox->appendText(": ");
			for ( int i=0; i<m.getNumArgs(); i++ ) {
				// get the argument type
				textbox->appendText(m.getArgTypeName(i));
				textbox->appendText(":");
				// display the argument - make sure we get the right type
				if( m.getArgType( i ) == vaOsc::TYPE_INT32 )
					textbox->appendText(m.getArgAsInt32(i));
				else if( m.getArgType( i ) == vaOsc::TYPE_FLOAT )
					textbox->appendText(m.getArgAsFloat(i));
				else if( m.getArgType( i ) == vaOsc::TYPE_STRING )
					textbox->appendText(m.getArgAsString(i));
				else
					textbox->appendText("unknown");
			}            
		}
	}
}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getName() == "send") {  //match by name
    
    }
}



