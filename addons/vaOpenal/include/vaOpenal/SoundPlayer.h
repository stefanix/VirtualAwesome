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
        virtual ~SoundPlayer() {};

        bool    loadSound( std::string fileName, bool stream=false );
        void    unloadSound();
        void    play();
        void    stop();

        void    setVolume( float vol );
        void    setPan( float vol );
        void    setSpeed( float spd );
        void    setPaused( bool bP );
        void    setLoop( bool bLp );
        void    setMultiPlay( bool bMp );
        void    setPosition( float pct ); // 0 = start, 1 = end;

        float   getPosition();
        bool    getIsPlaying();
        float   getSpeed();
        float   getPan();
        bool    getLoop();


        SoundBuffer* buffer;       //loaded samples for sounds/streams
        Sound* sound;              // mono sound sample
        SoundStereo* stereoSound;  // stereo sound sample
        Music* stream;             // audio stream
        std::vector<Sound*>  multiSounds;
        bool bIsStereo;            // (currently ignored for streams)

        bool isStreaming;
        bool bMultiPlay;
        bool bLoop;
        bool bLoadedOk;
        bool bPaused;
        float pan; // -1 to 1
        float volume; // 0 - 1
        float internalFreq;
        float speed; // -n to n, 1 = normal, -1 backwards
        unsigned int length; // in samples;
        float duration; //in seconds
        int channelCount; // 1 or 2
};


}
#endif
