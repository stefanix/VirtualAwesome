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
        
        void widget( va::SliderWidget& slider );
        
        va::ImageShape* imagepng;
        va::ImageShape* imagejpg;
        va::ImageShape* imagebmp;
        
        va::Model* spaceship; 
        va::Model* modelobj; 
        va::Model* model3ds; 
        va::Model* modelstl; 
                
};

#endif
    
