
#include "MyApp.h"



MyApp::MyApp(){

    sound = new vaSound::Sound();  //default is stereo out at 44100Hz
    sound->setEventHandler(this);
    
    pan = 0.5f;
    bNoise = false;
    sine1 = new stk::SineWave();
    sine2 = new stk::SineWave();
    sine1->setFrequency(1200.0);    
    sine2->setFrequency(150.0);  
    
    button1 = new va::ButtonWidget(200,40);
    button1->setLabel("Noise");
    button1->setPivot(100,20,0);
    button1->setPosition(0.5*scene->getWidth(),280);
    button1->addEventHandler(this);
    scene->addChild(button1); 
        
    sliderPan = new va::SliderWidget(300,40);
    sliderPan->setLabel("Pan");
    sliderPan->setPivot(150,20,0);
    sliderPan->setPosition(0.5*scene->getWidth(),400);
    sliderPan->setValueMin(0);
    sliderPan->setValueMax(1);
    sliderPan->setValue(pan);
    sliderPan->addEventHandler(this);
    scene->addChild(sliderPan);

    sliderFrq = new va::SliderWidget(300,40);
    sliderFrq->setLabel("Frequency");
    sliderFrq->setPivot(150,20,0);    
    sliderFrq->setPosition(0.5*scene->getWidth(),340);
    sliderFrq->setValueMin(50);
    sliderFrq->setValueMax(2000);
    sliderFrq->setValue(1025);
    sliderFrq->addEventHandler(this);
    scene->addChild(sliderFrq);
               
}

MyApp::~MyApp() {
    delete sound;
    delete sine1;
    delete sine2;
    // button1, sliderFrq, sliderPan 
    // are reference-counted and deleted
    // with the scene if not retained elsewhere
}


void MyApp::update() {}


void MyApp::soundRequest( vaSound::SoundBuffer& buffer ) {    
    register float* output = buffer.getBuffer();
    int bufferSize = buffer.getBufferSize();
    int nChannels = buffer.getNumChannels();
    
    if (bNoise){
        for (int i = 0; i < bufferSize; i++){
            const float random = std::rand()/float(RAND_MAX);
            // write to two interleaves output channels
            // panning accordingly
            output[i*nChannels  ] = random * (1 - pan);
            output[i*nChannels+1] = random * pan;
        }
    } else {
        for (int i=0; i<bufferSize; i++) {
            // write to two interleaves output channels
            // summing up the two sines and paning accordingly
            output[i*nChannels  ] = (0.5*sine1->tick() + 0.5*sine2->tick()) * (1 - pan);    
            output[i*nChannels+1] = (0.5*sine1->lastOut() + 0.5*sine2->lastOut()) * pan;  
        }
    }
}


void MyApp::widget( va::ButtonWidget& button ) {
    if (&button == button1) {
        if (!bNoise) {
            bNoise = true;
            button1->setLabel("Sine");
        } else {
            bNoise = false;
            button1->setLabel("Noise");
        }
    }
}


void MyApp::widget( va::SliderWidget& slider ) {
    if (&slider == sliderPan) {
        pan = sliderPan->getValue();
    } else if (&slider == sliderFrq) {
        sine1->setFrequency(sliderFrq->getValue());  
    }
}




