
#include "MyApp.h"



MyApp::MyApp(){
    
    server = new vaNetwork::HttpRpcServer();
	server->listen(4242);
    server->addNetworkHandler(this);
    scene->addUpdateHandler(server);
    
    panel = new va::PanelWidget(600,240);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,240);
    textbox->setText("Listening on port 4242. Clients are saying:\n");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
}

MyApp::~MyApp(){
	delete server;
}


void MyApp::networkConnect( std::string ip, int port ) {
    textbox->appendText("connected by: ");
    textbox->appendText(ip).appendText(":").appendText(port);
    textbox->appendText("\n");
}

void MyApp::networkDisconnect( std::string ip, int port ) {
    textbox->appendText("disconnected by: ");
    textbox->appendText(ip).appendText(":").appendText(port);
    textbox->appendText("\n");
}

void MyApp::networkReceive( vaNetwork::Message message ) {
	std::cout << message.getText() << std::endl;
    textbox->appendText(message.getText()).appendText("\n");
    server->setRemoteHost(message.getIp(), message.getPort());
    server->send("hi, to you too!");
}
        

