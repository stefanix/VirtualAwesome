/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaSound/EventHandlers.h>
#include <vaSound/Sound.h>
#include <stk/Saxofony.h>


class MyApp : public va::App, public vaSound::SoundHandler {
    
    public:
    
        MyApp();
        ~MyApp();

        void update();
        void soundRequest( vaSound::SoundBuffer& buffer );
        void widget( va::ButtonWidget& button );        
        void widget( va::SliderWidget& slider );
        
        vaSound::Sound* sound;
        stk::Saxofony* instrument;
        
        bool bNoteOn;
        va::ButtonWidget* button1;        
        va::SliderWidget* sliderFrq;
        
};

#endif
    
