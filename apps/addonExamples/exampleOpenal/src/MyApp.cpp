
#include "MyApp.h"



MyApp::MyApp(){
    
    //long sound, stream
    beat = new vaOpenal::SoundPlayer("savannadrum.ogg",true);
    beat->setLoop(true);
    beat->play();

	//stereo sound
    swosh = new vaOpenal::SoundPlayer("swosh_stereo.wav");
	swosh->setVolume(0.8f); 

    //mono sound and multiplay
    //can be triggered multiple times simultaneously
    //works only with mono sounds
    sonar = new vaOpenal::SoundPlayer("sonar_mono.aiff");
    sonar->setMultiPlay(true);    

    
    // setup some widgets
    //
    float widthHalf = 0.5*scene->getWidth();
    
    sliderFreq = new va::SliderWidget(300,40);
    sliderFreq->setLabel("Speed");
    sliderFreq->setPivot(150,20,0);    
    sliderFreq->setPosition(widthHalf,500);
    sliderFreq->setValueMin(0.5);
    sliderFreq->setValueMax(1.5);
    sliderFreq->setValue(1.0);
    sliderFreq->addEventHandler(this);
    scene->addChild(sliderFreq); 

    sliderVol = new va::SliderWidget(300,40);
    sliderVol->setLabel("Volume");
    sliderVol->setPivot(150,20,0);
    sliderVol->setPosition(widthHalf,440);
    sliderVol->setValueMin(0.0);
    sliderVol->setValueMax(1.0);
    sliderVol->addEventHandler(this);
    sliderVol->setValue(0.5);    
    scene->addChild(sliderVol); 
    
    va::ButtonWidget* buttonSwosh = new va::ButtonWidget(200,40);
    buttonSwosh->setLabel("Swosh!");
    buttonSwosh->setPivot(100,25,0);
    buttonSwosh->setPosition(widthHalf,380);
    buttonSwosh->addEventHandler(this);
    scene->addChild(buttonSwosh);

    va::ButtonWidget* buttonSonar = new va::ButtonWidget(200,40);
    buttonSonar->setLabel("Ping!");
    buttonSonar->setPivot(100,25,0);
    buttonSonar->setPosition(widthHalf,320);
    buttonSonar->addEventHandler(this);
    scene->addChild(buttonSonar);    
}

MyApp::~MyApp(){}

void MyApp::update() {}


void MyApp::widget( va::ButtonWidget& button ) {
    if (button.getLabel() == "Swosh!") {  //match by label
        swosh->play();
    } else if (button.getLabel() == "Ping!") {
        sonar->play();
    }
}
void MyApp::widget( va::SliderWidget& slider ) {
    if (&slider == sliderFreq) {        //match by pointer
		beat->setSpeed(slider.getValue());
    } else if (&slider == sliderVol) {
		beat->setVolume(slider.getValue());
    }
}




