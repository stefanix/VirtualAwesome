/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaOpenal/SoundPlayer.h>


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();

		void update();
        
        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        
        vaOpenal::SoundPlayer* swosh;
        vaOpenal::SoundPlayer* sonar;
        vaOpenal::SoundPlayer* beat;
                
        va::SliderWidget* sliderFreq;
        va::SliderWidget* sliderVol;
};

#endif
	
