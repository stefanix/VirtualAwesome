/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <osgDB/WriteFile>
#include <vaMultipad/Multipad.h>
#include <va/GestureWidget.h>


class MyApp : public va::App {
    
    public:
    
        MyApp();
        ~MyApp();

        void widget( va::ToggleWidget& toggle );
        
        va::GestureWidget* panel1;
        va::ToggleWidget* toggle1;
        va::ToggleWidget* toggle2;
        va::ToggleWidget* toggle3;

};

#endif
    
