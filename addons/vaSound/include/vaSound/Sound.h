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

#ifndef VASOUND_SOUND
#define VASOUND_SOUND

#include <stk/RtAudio.h>
#include <vaSound/EventHandlers.h>

namespace vaSound {


class Sound {
    public:

		Sound();
        Sound( int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers );
        void init( int nOutputs, int nInputs, int sampleRate, int bufferSize, int nBuffers );
        ~Sound();
        
        void setEventHandler( SoundHandler* handler );
        void listDevices();
        
        static int callback( void* outputBuffer, void* inputBuffer, 
                             unsigned int bufferSize, double streamTime, 
                             RtAudioStreamStatus status, void* data ); 
        
        
    private:
        RtAudio* _audio;
        int _nInputChannels;
        int _nOutputChannels;
        int _sampleRate;
        int _bufferSize;
        int _nBuffers;
        SoundHandler* _soundHandler;
        SoundBuffer _bufferArg;
    
};


}
#endif

