/*
* Copyright 2009 NOR_/D Labs <http://labs.nortd.com>
*
* This file is part of VirtualAwesome.
* VirtualAwesome is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation, either version 3 of
* the License, or (at your option) any later version. For details
* see <http://www.gnu.org/licenses/>.
*
* * *
*
*/

#include <vaSound/Sound.h>
#include <stk/Stk.h>

using namespace vaSound;


Sound::Sound() {
    init(2, 0, 44100, 256, 4);
}

Sound::Sound( int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers ) {
    init(nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
}



void Sound::init( int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers ) {

    stk::Stk::setSampleRate( sampleRate );
    stk::Stk::showWarnings( true );
    //stk::Stk::setRawwavePath( "/Users/noema/Downloads/stk-4.4.2/rawwaves/" );

	_sampleRate = sampleRate;
    _bufferSize = bufferSize;
    _nBuffers = nBuffers;

	_nInputChannels = nInputs;
	_nOutputChannels = nOutputs;
	
	int rval = 1;
	while (rval<bufferSize) { rval<<=1; }  // get next pow2
    bufferSize = rval;                     // must be pow2

	try {
		_audio = new RtAudio();
	} catch (RtError &error) {
		error.printMessage();
		//std::exit(EXIT_FAILURE); // need case here
	}


	RtAudio::StreamParameters* outputParameters = NULL;
	if (_nOutputChannels > 0) {
		outputParameters = new RtAudio::StreamParameters();
		outputParameters->deviceId = _audio->getDefaultOutputDevice();
		outputParameters->nChannels = _nOutputChannels;
	}

	RtAudio::StreamParameters* inputParameters = NULL;
	if (_nInputChannels > 0) {
		inputParameters = new RtAudio::StreamParameters;
		inputParameters->deviceId = _audio->getDefaultInputDevice();
		inputParameters->nChannels = _nInputChannels;
	}

	unsigned int bufferFrames = (unsigned int)bufferSize;

	RtAudio::StreamOptions options;
	options.flags = RTAUDIO_SCHEDULE_REALTIME;
	options.numberOfBuffers = nBuffers;
	options.priority = 1;

	try {
		_audio->openStream( outputParameters, inputParameters, 
		                    RTAUDIO_FLOAT32, sampleRate, 
		                    &bufferFrames, &callback, 
		                    this, &options );
		// Reminder: make sure stk::StkFloat is actually defined as float
		//           otherwise if double use RTAUDIO_FLOAT64
		
		_audio->startStream();
	} catch (RtError &error) {
		error.printMessage();
	}
}



Sound::~Sound() {
	try {
    	_audio->stopStream();
    	_audio->closeStream();
  	} catch (RtError &error) {
   		error.printMessage();
 	}
 	
    delete _audio;
}



void Sound::setEventHandler( SoundHandler* handler ) {
    _soundHandler = handler;
}



void Sound::listDevices() {
	RtAudio* audioTemp = 0;
	try {
		audioTemp = new RtAudio();
	} catch (RtError &error) {
		error.printMessage();
	}
 	int devices = audioTemp->getDeviceCount();
	RtAudio::DeviceInfo info;
	for (int i=0; i< devices; i++) {
		try {
			info = audioTemp->getDeviceInfo(i);
		} catch (RtError &error) {
			error.printMessage();
			break;
		}
		std::cout << "device = " << i << " (" << info.name << ")\n";
		if (info.isDefaultInput) std::cout << "----* default ----* \n";
		std::cout << "maximum output channels = " << info.outputChannels << "\n";
		std::cout << "maximum input channels = " << info.inputChannels << "\n";
		std::cout << "-----------------------------------------\n";

	}
	delete audioTemp;
}



int Sound::callback( void* outputBuffer, void* inputBuffer, 
                     unsigned int bufferSize, double streamTime, 
                     RtAudioStreamStatus status, void* data ) {

	if ( status ) std::cout << "Stream over/underflow detected." << std::endl;

	// 	rtAudio uses a system by which the audio
	// 	can be of different formats
	// 	char, float, etc.
	// 	we choose float
	float * fPtrOut = (float *)outputBuffer;
	float * fPtrIn = (float *)inputBuffer;
	// [zach] memset output to zero before output call
	// this is because of how rtAudio works: duplex w/ one callback
	// you need to cut in the middle. if the simpleApp
	// doesn't produce audio, we pass silence instead of duplex...

    // Get the instance of Sound that set up this callback
    Sound* instance = (Sound*)data;

	if (instance->_nInputChannels > 0) {
        instance->_bufferArg._buffer = fPtrIn;
        instance->_bufferArg._bufferSize = bufferSize;
        instance->_bufferArg._nChannels = instance->_nInputChannels;
		instance->_soundHandler->soundReceive(instance->_bufferArg);
		memset(fPtrIn, 0, bufferSize * instance->_nInputChannels * sizeof(float));
	}


	if (instance->_nOutputChannels > 0) {
        instance->_bufferArg._buffer = fPtrOut;
        instance->_bufferArg._bufferSize = bufferSize;
        instance->_bufferArg._nChannels = instance->_nOutputChannels;	    
		instance->_soundHandler->soundRequest(instance->_bufferArg);
	}

	return 0;
}

