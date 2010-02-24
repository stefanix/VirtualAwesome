/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include "Storm.h"


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();
        
        void touchMove( va::Touch& touch );
        
        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        
        va::PanelWidget* panel1;
        va::SliderWidget* slider1;

};

#endif
	
