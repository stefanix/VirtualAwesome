/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>


class MyApp : public va::App {
    
    public:
    
        MyApp();
        ~MyApp();
        
        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        void widget( va::Slider2DWidget& slider );
        void widget( va::ToggleWidget& toggle );
        
        va::PanelWidget* panel1;
        va::SliderWidget* slider1;
        va::SliderWidget* slider2;
        va::Slider2DWidget* slider3;
        va::PanelWidget* panel2;
        va::TextShape* textbox1;
        va::ToggleWidget* toggle1;

};

#endif
    
