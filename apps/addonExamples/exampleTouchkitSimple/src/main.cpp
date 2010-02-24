
#include <va/Main.h>
#include "MyApp.h"


int main() {
    osg::ref_ptr<MyApp> app = new MyApp();
    return app->run();
}
