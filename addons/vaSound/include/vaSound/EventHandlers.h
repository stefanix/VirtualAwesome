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

#ifndef VASOUND_EVENTHANDLERS
#define VASOUND_EVENTHANDLERS

namespace vaSound {


class SoundBuffer {
    public:
                                
        SoundBuffer()
          : _buffer(NULL),
            _bufferSize(0),
            _nChannels(0.0)
        {}
        
        float* getBuffer() {return _buffer;}
        int getBufferSize() {return _bufferSize;}
        int getNumChannels() {return _nChannels;}

    public:
        float* _buffer;
        int _bufferSize;
        int _nChannels;
};


class SoundHandler {
    public:
        virtual ~SoundHandler() {}
        virtual void soundReceive( SoundBuffer& buffer ) {}
        virtual void soundRequest( SoundBuffer& buffer ) {}        
};


}
#endif

