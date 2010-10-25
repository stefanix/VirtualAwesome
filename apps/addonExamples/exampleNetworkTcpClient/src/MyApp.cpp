
#include "MyApp.h"



MyApp::MyApp(){
    
    client = new vaNetwork::AwesomeSocket();
	client->tcpConnect("127.0.0.1", 4242);
    client->addNetworkHandler(this);
    scene->addUpdateHandler(client);
    
    panel = new va::PanelWidget(600,240);
    panel->setPivot(300,70,0);
    panel->setPosition(0.5*scene->getWidth(),500,0);
    scene->addChild(panel);
    
    textbox = new va::TextShape(600,240);
    textbox->setText("Connected to 127.0.0.1:4242. Server is saying:\n");
    textbox->setPadding(20.0f);
    panel->addChild(textbox);
    
    button1 = new va::ButtonWidget(200,40);
    button1->setLabel("Send \"hi!\"");
    button1->setPosition(0,-50,0);
    button1->addEventHandler(this);
    panel->addChild(button1);
    
}

MyApp::~MyApp(){
	delete client;
}


void MyApp::widget( va::ButtonWidget& button ) {
	if (&button == button1) {
     	client->send("hi!");   
    }
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
    textbox->appendText(message.getText());
    textbox->appendText("\n");
}
        

