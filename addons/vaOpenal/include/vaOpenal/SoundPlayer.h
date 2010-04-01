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

#ifndef VAOPENAL_SOUNDPLAYER
#define VAOPENAL_SOUNDPLAYER

#include <osg/Notify>
#include <vaOpenal/Listener.h>
#include <vaOpenal/Sound.h>
#include <vaOpenal/SoundStereo.h>
#include <vaOpenal/SoundBuffer.h>
#include <vaOpenal/Music.h>

namespace vaOpenal {


class SoundPlayer {
	public:

        SoundPlayer();
        SoundPlayer( std::string fileName, bool stream=false );
        virtual ~SoundPlayer();
        
        void play();
        void stop();

        void setVolume( float vol );
        void setPan( float pan );
        void setSpeed( float spd );
        void setPaused( bool bP );
        void setLoop( bool bLp );
        void setMultiPlay( bool bMp );
        void setPosition( float pct ); // 0 = start, 1 = end;

        float getPosition();
        bool getIsPlaying();
        float getSpeed();
        float getPan();
        bool getLoop();
        

	protected:
    
        bool _bIsStereo;            // (currently ignored for streams)
        SoundBuffer* _buffer;       //loaded samples for sounds/streams
        Sound* _sound;              // mono sound sample
        SoundStereo* _stereoSound;  // stereo sound sample
        Music* _stream;             // audio stream
        std::vector<Sound*>  _multiSounds;

        bool _isStreaming;
        bool _bMultiPlay;
        bool _bLoadedOk;
        bool _bPaused;
        float _pan;                 // -1 to 1
        float _volume;              // 0 - 1
        float _internalFreq;
        float _speed;               // 0 to 128, 1 is 100%
        unsigned int _length;       // in samples;
        float _duration;            //in seconds
        int _channelCount;          // 1 or 2
        
        bool loadNewSound( std::string fileName, bool stream );
        void clean();        
};


}
#endif
