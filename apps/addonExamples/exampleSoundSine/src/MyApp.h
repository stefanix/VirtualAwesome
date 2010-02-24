/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaSound/EventHandlers.h>
#include <vaSound/Sound.h>
#include <stk/SineWave.h>


class MyApp : public va::App, public vaSound::SoundHandler {
	
	public:
    
    	MyApp();
    	~MyApp();

        void update();
        void soundRequest( vaSound::SoundBuffer& buffer );
        void widget( va::ButtonWidget& button );        
        void widget( va::SliderWidget& slider );
        
        vaSound::Sound* sound;
        stk::SineWave* sine1;
        stk::SineWave* sine2;
                
        float pan;
        bool bNoise;
        va::ButtonWidget* button1;        
        va::SliderWidget* sliderPan;
        va::SliderWidget* sliderFrq;

};

#endif
	
