/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaOsc/Receiver.h>
#include <vaOsc/EventHandlers.h>
#include <vaOsc/Message.h>


class MyApp : public va::App, public vaOsc::OscHandler {
    
    public:
    
        MyApp();
        ~MyApp();
                
        void oscReceive( vaOsc::Message message );
        
        vaOsc::Receiver* receiver;
        
        va::PanelWidget* panel;
        va::TextShape* textbox;

};

#endif
    
