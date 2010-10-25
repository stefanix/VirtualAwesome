/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaNetwork/Main.h>


class MyApp : public va::App, public vaNetwork::NetworkHandler {
    
    public:
    
        MyApp();
        ~MyApp();
        
        void update();
        void networkConnect( vaNetwork::Host host );
        void networkDisconnect( vaNetwork::Host host );
        void networkReceive( vaNetwork::Message message );   
        
        vaNetwork::EndPoint server;
        
        va::PanelWidget* panel;
        va::TextShape* textbox;

};

#endif
    
