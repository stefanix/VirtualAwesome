/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaOsc/Receiver.h>
#include <vaOsc/EventHandlers.h>


class MyApp : public va::App, public vaOsc::OscHandler {
	
	public:
    
    	MyApp();
    	~MyApp();
        
		void update();        
        void widget( va::ButtonWidget& button );
        
        vaOsc::Receiver* receiver;
        
        va::PanelWidget* panel;
        va::TextShape* textbox;

};

#endif
	
