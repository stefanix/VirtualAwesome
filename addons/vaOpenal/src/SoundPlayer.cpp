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

#include <vaOpenal/SoundPlayer.h>

using namespace vaOpenal;


/*
void SoundStopAll()
{
    Listener::StopAllSounds();
    Listener::StopAllStreams();
}

void SoundSetVolume(float vol)
{

    vol = ofClamp(vol,0,1);
    Listener::SetGlobalVolume(vol*100);
}
*/



SoundPlayer::SoundPlayer()
	: buffer(0), 
      sound(0), 
      stereoSound(0), 
      stream(0), 
      bIsStereo(false),
      isStreaming(false),
      bMultiPlay(false),
      bLoop(false),
      bLoadedOk(false),
      bPaused(false),
      pan(0.0f),
      volume(1.0f),
      internalFreq(0),
      speed(1),
      length(0),
      duration(0),
      channelCount(0)
{}



bool SoundPlayer::loadSound( std::string fileName, bool bIsStream ) {
    bLoadedOk = false;
	// fileName = ofToDataPath(fileName);

	unloadSound();

    if(bIsStream) {
        stream = new Music();

        // Load a stream
        if (!stream->OpenFromFile(fileName)) {
        	osg::notify(osg::FATAL)<<"SoundPlayer, failed to open stream, "<<fileName<<std::endl;
            return false;
        }

        internalFreq = stream->GetSampleRate();
        duration = stream->GetDuration();
        length = static_cast<unsigned int> (internalFreq * duration);
        channelCount = stream->GetChannelsCount();

        isStreaming = true;
        bLoadedOk = true;
        
    } else {
        buffer = new SoundBuffer();

        // Load a sound buffer from a file
        if (!buffer->LoadFromFile(fileName)) {
        	osg::notify(osg::FATAL)<<"SoundPlayer, failed to open sound, "<<fileName<<std::endl;        
            return false;
        }

        internalFreq = buffer->GetSampleRate();
        duration = buffer->GetDuration();
        channelCount = buffer->GetChannelsCount();
        length = buffer->GetSamplesCount(); // length in samples


        if(channelCount == 2) {
            bIsStereo = true;
            stereoSound = new SoundStereo();
            stereoSound->SetBuffer(*buffer);
            bLoadedOk = true;

        } else {
            // create a mono sound instance
            sound = new Sound();
            sound->SetBuffer(*buffer);
            bLoadedOk = true;
        }

    }

    return bLoadedOk;
}



void SoundPlayer::unloadSound() {
    if (!bLoadedOk) {
	    return;
	}

    if (sound) {
        sound->Stop();
        delete sound;
        sound = NULL;
    }

    if (stereoSound) {
        stereoSound->Stop();
        delete stereoSound;
        stereoSound = NULL;
    }
    
    if (stream) {
        stream->Stop();
        delete stream;
        stream = NULL;
    }
    
    if (multiSounds.size() > 0) {
        std::vector<Sound*>::iterator itr;
        for(itr = multiSounds.begin(); itr < multiSounds.end();itr++) {
            (*itr)->Stop();
            delete (*itr);
        }
        multiSounds.clear();
    }
    
    if(buffer) {
        delete buffer;
        buffer = NULL;
    }
}



bool SoundPlayer::getIsPlaying() {
    Sound::SoundStatus status;
	if (!bLoadedOk) {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;        
	    return false;
	}

    if(stream) {
        status = stream->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
        
    } else if(stereoSound) {
        status = stereoSound->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
        
    } else if(sound) {
        status = sound->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
    }

    return false;
}



float SoundPlayer::getSpeed() {
    if(stream) {
        speed = stream->GetPitch();
        
    } else if(stereoSound) {
        speed = sound->GetPitch();
        
    } else if(sound) {
        speed = sound->GetPitch();
        
    } else {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;            
    }

    return speed;
}



float SoundPlayer::getPan() {
    return pan;
}



bool SoundPlayer::getLoop() {
    if(stream) {
        return stream->GetLoop();
    }

    else if(stereoSound) {
        return stereoSound->GetLoop();
    
    } else if(sound) {
        return sound->GetLoop();
    
    } else {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;            
    }

    return false;
}



void SoundPlayer::setVolume(float vol) {
	if (vol < 0) {
        volume = 0;
    } else if (vol >1) {
        volume = 1;
    } else {
    	volume = vol;
    }

    if(stream) {
        stream->SetVolume(volume*100.0f);
        
    } else if(stereoSound) {
        stereoSound->SetVolume(volume*100.0f);
    
    } else if(sound) {
        sound->SetVolume(volume*100.0f);
    }
}



void SoundPlayer::setPosition(float pct) {
	if (pct < 0) {
        pct = 0;
    } else if (pct >1) {
        pct = 1;
    } else {
    	pct = pct;
    }
    
    if(sound) {
        sound->SetPlayingOffset(pct);
    }
    
    if(stereoSound) {
        stereoSound->SetPlayingOffset(pct);
    }

    else if(stream) {
        osg::notify(osg::WARN)<<"SoundPlayer, cannot position a stream"<<std::endl;            
    }
}



float SoundPlayer::getPosition() {
    if(stream) {
        return stream->GetPlayingOffset();

    } else if(stereoSound){
        return stereoSound->GetPlayingOffset();
    
    } else if(sound) {
        return sound->GetPlayingOffset();
    
    } else {
    	 return 0;
    }
}



void SoundPlayer::setPan(float _pan) {
	if (_pan < -1) {
        pan = -1;
    } else if (_pan >1) {
        pan = 1;
    } else {
    	pan = _pan;
    }

    if(stream) {
        stream->SetPosition(pan,0,0);
    
    } else if(stereoSound) {
        stereoSound->SetPan(pan);
    
    } else if(sound) {
        sound->SetPosition(pan,0,0);
    }
}



void SoundPlayer::setPaused(bool bP) {
    Sound::SoundStatus status;
    bPaused = bP;

    if(stream) {
        status = stream->GetStatus();
        if(bPaused) {
            stream->Pause();
        } else {
            if (status == Sound::Paused) {
                stream->Play();
            }
        }
    
    } else if(stereoSound) {
        status = stereoSound->GetStatus();
        if(bPaused) {
            stereoSound->Pause();
        } else {
            if (status == Sound::Paused) {
                stereoSound->Play();
            }
        }
    
    } else if(sound) {
        status = sound->GetStatus();
        if(bPaused) {
            sound->Pause();
        } else {
            if (status == Sound::Paused) {
                sound->Play();
            }
        }
    }
}



void SoundPlayer::setSpeed(float spd) {
	if (spd < 0) {
        spd = 0;
    } else if (spd >128) {
        spd = 128;
    } else {
    	spd = spd;
    }

    if(spd < 0) {
        osg::notify(osg::WARN)<<"SoundPlayer, cannot set negative speed"<<std::endl;                
    }

    if(stream) {
        stream->SetPitch(spd);
    
    } else if(stereoSound) {
        stereoSound->SetPitch(spd);
    
    } else if(sound) {
        sound->SetPitch(spd);
    }
}



void SoundPlayer::setLoop(bool bLp) {
    if(stream) {
        stream->SetLoop(bLp);
    
    } else if(stereoSound) {
        stereoSound->SetLoop(bLp);
    
    } else if(sound) {
        sound->SetLoop(bLp);
    }

}



void SoundPlayer::setMultiPlay(bool bMp) {
    if(bIsStereo) {
        osg::notify(osg::WARN)<<"SoundPlayer, setMultiPlay() not yet implemented for stereo sounds"<<std::endl;            
    } else if (isStreaming) {
        osg::notify(osg::WARN)<<"SoundPlayer, setMultiPlay() does not work with streams"<<std::endl;            
    } else {
        bMultiPlay = bMp;
    }
}



void SoundPlayer::play() {
    if(stream) {
        stream->Play();
    
    } else if(stereoSound) {
        stereoSound->Play();
    
    } else if(sound) {
        if(bMultiPlay) {
            bool hasPlayed = false;
            Sound::SoundStatus status = sound->GetStatus();
            if( status == Sound::Playing) {
                std::vector<Sound*>::iterator itr;
                for(itr = multiSounds.begin(); itr < multiSounds.end();itr++) {
                    status = (*itr)->GetStatus();
                    if(status != Sound::Playing) {
                        (*itr)->Play();
                        hasPlayed = true;
                        itr = multiSounds.end();
                    }
                }
                
                if(!hasPlayed) {
                    multiSounds.push_back(new Sound(*sound));
                    multiSounds.back()->Play();
                }

            } else {
                sound->Play();
            }
        
        } else {
            sound->Play();
        }
    }
}



void SoundPlayer::stop() {
    if(stream) {
        stream->Stop();
    
    } else if(stereoSound) {
        stereoSound->Stop();
    
    } else if(sound) {
        sound->Stop();
    }
}


