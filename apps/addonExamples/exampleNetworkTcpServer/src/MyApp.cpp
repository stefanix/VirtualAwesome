
#include "MyApp.h"



MyApp::MyApp(){
    
	server.tcpListen(4242);
    server.addNetworkHandler(this);
    std::cout << "listening for TCP on port 4242" << std::endl;
    
    panel = new va::PanelWidget(600,240);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,240);
    textbox->setText("No client connected yet.");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
}

MyApp::~MyApp(){}


void MyApp::update() {

}


void MyApp::networkConnect( vaNetwork::Host host ) {
	std::cout << "connected" << std::endl;
    textbox->appendText("connected by: ");
    textbox->appendText(host.getHostString());
    textbox->appendText("\n");
}

void MyApp::networkDisconnect( vaNetwork::Host host ) {
    textbox->appendText("disconnected by: ");
    textbox->appendText(host.getHostString());
    textbox->appendText("\n");
}

void MyApp::networkReceive( vaNetwork::Message message ) {
    textbox->appendText(message.getText());
    textbox->appendText("\n");}
        

