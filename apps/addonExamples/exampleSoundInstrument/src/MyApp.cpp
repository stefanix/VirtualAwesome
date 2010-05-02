
#include "MyApp.h"



MyApp::MyApp(){
    
    sound = new vaSound::Sound();  //default is stereo out at 44100Hz
    sound->setEventHandler(this);
    
    bNoteOn = true;
    instrument = new stk::Saxofony(100.0);
    instrument->noteOn(500.0f, 0.5); 
    
    button1 = new va::ButtonWidget(200,40);
    button1->setLabel("Note Off");
    button1->setPivot(100,20,0);
    button1->setPosition(0.5*scene->getWidth(),340);
    button1->addEventHandler(this);
    scene->addChild(button1);     
        
    sliderFrq = new va::SliderWidget(300,40);
    sliderFrq->setLabel("Frequency");
    sliderFrq->setPivot(150,20,0);
    sliderFrq->setPosition(0.5*scene->getWidth(),400);
    sliderFrq->setValueMin(100.0f);
    sliderFrq->setValueMax(900.0f);
    sliderFrq->setValue(500.0f);
    sliderFrq->addEventHandler(this);
    scene->addChild(sliderFrq);    
    
    
}

MyApp::~MyApp() {
    delete sound;
    delete instrument;
}


void MyApp::update() {}


void MyApp::soundRequest( vaSound::SoundBuffer& buffer ) {    
    register float* output = buffer.getBuffer();
    int bufferSize = buffer.getBufferSize();
    int nChannels = buffer.getNumChannels();
    
    for (int i=0; i<bufferSize; i++) {
        output[i*nChannels  ] = instrument->tick();    
        output[i*nChannels+1] = instrument->lastOut();    
    }
}


void MyApp::widget( va::ButtonWidget& button ) {
    if (&button == button1) {
        if (!bNoteOn) {
            bNoteOn = true;
            instrument->noteOn(sliderFrq->getValue(), 0.5);
            button1->setLabel("Note Off");
        } else {
            bNoteOn = false;
            instrument->noteOff(0.9);
            button1->setLabel("Note On");
        }
    }
}

void MyApp::widget( va::SliderWidget& slider ) {
    instrument->setFrequency(sliderFrq->getValue());    
}




