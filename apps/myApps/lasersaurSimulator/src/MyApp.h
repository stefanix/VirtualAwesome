/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include "HttpRpcServer.h"


class MyApp : public va::App, public vaNetwork::NetworkHandler {
    
    public:
    
        MyApp();
        ~MyApp();
        
        void networkConnect( std::string ip, int port );
        void networkDisconnect( std::string ip, int port );
        void networkReceive( vaNetwork::Message message );   
        
        vaNetwork::HttpRpcServer* server;
        
        va::PanelWidget* panel;
        va::TextShape* textbox;

};

#endif
    
