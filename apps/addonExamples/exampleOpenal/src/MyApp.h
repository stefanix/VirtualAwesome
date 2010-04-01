/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <osgDB/WriteFile>
#include <vaOpenal/SoundPlayer.h>


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();

		void update();
        
        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        void widget( va::ToggleWidget& toggle );
        
        vaOpenal::SoundPlayer* sound;
        vaOpenal::SoundPlayer* music;
                
        va::PanelWidget* panel1;
        va::SliderWidget* slider1;
        va::SliderWidget* slider2;
        va::PanelWidget* panel2;
        va::TextShape* textbox1;
        va::ToggleWidget* toggle1;

};

#endif
	
