/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaTween/CppTweener.h>


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();
        void update();

        va::RectangleShape* myRect;
		vaTween::Expo tween;
};

#endif
	
