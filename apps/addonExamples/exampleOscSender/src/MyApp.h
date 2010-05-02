/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaOsc/Sender.h>


class MyApp : public va::App {
    
    public:
    
        MyApp();
        ~MyApp();
        
        void touchMove( va::Touch& touch );
        void mouseButton( va::Mouse& mouse );
        void widget( va::ButtonWidget& button );
        
        vaOsc::Sender* sender;
        va::ButtonWidget* buttonSend;
};

#endif
    
