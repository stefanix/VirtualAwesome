
#include "MyApp.h"



MyApp::MyApp(){
    
    receiver = new vaNetwork::AwesomeSocket();
	receiver->udpListen(4242);
    receiver->addNetworkHandler(this);
    scene->addUpdateHandler(receiver);
    
    panel = new va::PanelWidget(600,240);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,240);
    textbox->setText("Listening on port 4242. Senders are saying:\n");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
}

MyApp::~MyApp(){
	delete receiver;
}


void MyApp::networkReceive( vaNetwork::Message message ) {
    textbox->appendText(message.getText());
    textbox->appendText("\n");
    //receiver->setRemoteHost(message.getIp(), message.getPort())
    //receiver->send("hi, to you too!");
}
        

