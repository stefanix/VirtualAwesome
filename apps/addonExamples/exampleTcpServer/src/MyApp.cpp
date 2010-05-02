
#include "MyApp.h"



MyApp::MyApp(){
    
    server.setup(4242);
    
    
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
    for (int i=0; i<server.getNumClients(); i++) {
        server.TCPConnections[i];
    }

}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getName() == "send") {  //match by name
        server.sendToAll("hello");
    }
}



