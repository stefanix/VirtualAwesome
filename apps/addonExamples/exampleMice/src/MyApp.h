/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaMice/Mice.h>


class MyApp : public va::App {
    
    public:
    
        MyApp();
        ~MyApp();

        void update();

        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        void widget( va::ToggleWidget& toggle );
        
        vaMice::Mice* mice;
        
        va::SliderWidget* sliderR;
        va::SliderWidget* sliderG;
        va::SliderWidget* sliderB;
                        
        va::PanelWidget* panel1;
        va::PanelWidget* panel2;
        va::TextShape* textbox1;
        va::ToggleWidget* toggle1;

};

#endif
    
