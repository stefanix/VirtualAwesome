/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaNetwork/Main.h>


class MyApp : public va::App {
    
    public:
    
        MyApp();
        ~MyApp();

        void update();
        void widget( va::ButtonWidget& button );
        
        vaNetwork::TCPServer server;
        
        va::PanelWidget* panel;
        va::TextShape* textbox;

};

#endif
    
