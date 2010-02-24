/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://code.google.com/p/virtualawesome/wiki/EventHandlers
*/

#ifndef VA_MYAPP
#define VA_MYAPP

#include <va/Main.h>
#include <vaTouchkit/Tracker.h>


class MyApp : public va::App {
	
	public:
    
    	MyApp();
    	~MyApp();	      
        
        void keyPress( va::Key& key );
        
        vaTouchkit::Tracker* tracker;

};	

#endif
	
