/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();      
        
        void keyPress( va::Key& key );
        void keyRelease( va::Key& key );
        
        virtual void touchDown( va::Touch& touch );
        virtual void touchMove( va::Touch& touch );
        virtual void touchUp( va::Touch& touch );
        
        void mouseButton( va::Mouse& mouse );
        void mouseScroll( va::Mouse& mouse );
        
        va::RectangleShape* rect;
        va::TextShape* text;

};

#endif
	
