/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <osgDB/WriteFile>
#include <vaMultipad/Multipad.h>
#include <vaMultipad/GamepadWidget.h>


class MyApp : public va::App, public vaMultipad::GamepadHandler {
    
    public:
    
        MyApp();
        ~MyApp();

        void widget( vaMultipad::GamepadWidget& gamepad );
        
        vaMultipad::GamepadWidget* gamepad;
        
        va::Node* spaceshipContainer;
        va::Model* spaceship;

};

#endif
    
