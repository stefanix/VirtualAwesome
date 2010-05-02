/* * *
* MyApp can handle many events: mouse, key, pen, touch ...
* http://labs.nortd.com/va/docs/reference#allHandlers
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
    
