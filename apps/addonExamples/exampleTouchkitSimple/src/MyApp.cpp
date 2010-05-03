
#include "MyApp.h"



MyApp::MyApp(){
    scene->enableTouchVisuals();

    tracker = new vaTouchkit::Tracker(320,240);
    tracker->addEventHandler(scene);
    tracker->setPosition(100, scene->getHeight()-580, 0);
    scene->addChild(tracker);

    bool bLiveVideo = true;
    if (bLiveVideo) {
        //tracker->listDevices();
        tracker->selectDevice(0);
	} else {
    	// run tracking from jpeg sequence
        // parameters are: name of first image, number of digits
        // for the incementing number, first frame, last frame
        //
        //tracker->selectJpegs("touchkit-fingers/touchkit-fingers 0001.jpg", 4, 1, 2300);
        tracker->selectJpegs("touchkit-drag/touchkit-drag 0001.jpg", 4, 1, 1014);
        //tracker->selectJpegs("touchkit-pinch/touchkit-pinch 0001.jpg", 4, 1, 1100);
        //tracker->selectJpegs("touchkit-pinchrotate/touchkit-pinchrotate 001.jpg", 3, 1, 860);
	}
}

MyApp::~MyApp(){}


void MyApp::keyPress( va::Key& key ){
	if (key.getKey() == 's') {
    	// toggle setup mode
        tracker->setSetupMode(!tracker->getSetupMode());
    } else if (key.getKey() == '?') {
    	// toggle rendering stats
        scene->toggleStats();
    }

}


