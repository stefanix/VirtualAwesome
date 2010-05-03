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

#include <osgDB/FileUtils>
#include <vaOpenal/SoundPlayer.h>

using namespace vaOpenal;


SoundPlayer::SoundPlayer( std::string fileName, bool bIsStream)
	: _bIsStereo(false),
      _buffer(0), 
      _sound(0), 
      _stereoSound(0), 
      _stream(0), 
      _isStreaming(false),
      _bMultiPlay(false),
      _bLoadedOk(false),
      _bPaused(false),
      _pan(0.0f),
      _volume(1.0f),
      _internalFreq(0),
      _speed(1),
      _length(0),
      _duration(0),
      _channelCount(0)
{
	loadNewSound(fileName, bIsStream);
}


SoundPlayer::~SoundPlayer() {
	clean();
}


bool SoundPlayer::loadNewSound( std::string fileName, bool bIsStream ) {
    _bLoadedOk = false;
    fileName = osgDB::findDataFile(fileName);

	clean();

    if(bIsStream) {
        _stream = new Music();

        // Load a stream
        if (!_stream->OpenFromFile(fileName)) {
        	osg::notify(osg::FATAL)<<"SoundPlayer, failed to open stream, "<<fileName<<std::endl;
            return false;
        }

        _internalFreq = _stream->GetSampleRate();
        _duration = _stream->GetDuration();
        _length = static_cast<unsigned int> (_internalFreq * _duration);
        _channelCount = _stream->GetChannelsCount();

        _isStreaming = true;
        _bLoadedOk = true;
        
    } else {
        _buffer = new SoundBuffer();

        // Load a _sound _buffer from a file
        if (!_buffer->LoadFromFile(fileName)) {
        	osg::notify(osg::FATAL)<<"SoundPlayer, failed to open sound, "<<fileName<<std::endl;        
            return false;
        }

        _internalFreq = _buffer->GetSampleRate();
        _duration = _buffer->GetDuration();
        _channelCount = _buffer->GetChannelsCount();
        _length = _buffer->GetSamplesCount(); // length in samples


        if(_channelCount == 2) {
            _bIsStereo = true;
            _stereoSound = new SoundStereo();
            _stereoSound->SetBuffer(*_buffer);
            _bLoadedOk = true;

        } else {
            // create a mono sound instance
            _sound = new Sound();
            _sound->SetBuffer(*_buffer);
            _bLoadedOk = true;
        }

    }

    return _bLoadedOk;
}



void SoundPlayer::clean() {
    if (!_bLoadedOk) {
	    return;
	}

    if (_sound) {
        _sound->Stop();
        delete _sound;
        _sound = NULL;
    }

    if (_stereoSound) {
        _stereoSound->Stop();
        delete _stereoSound;
        _stereoSound = NULL;
    }
    
    if (_stream) {
        _stream->Stop();
        delete _stream;
        _stream = NULL;
    }
    
    if (_multiSounds.size() > 0) {
        std::vector<Sound*>::iterator itr;
        for(itr = _multiSounds.begin(); itr < _multiSounds.end();itr++) {
            (*itr)->Stop();
            delete (*itr);
        }
        _multiSounds.clear();
    }
    
    if(_buffer) {
        delete _buffer;
        _buffer = NULL;
    }
}



bool SoundPlayer::getIsPlaying() {
    Sound::SoundStatus status;
	if (!_bLoadedOk) {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;        
	    return false;
	}

    if(_stream) {
        status = _stream->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
        
    } else if(_stereoSound) {
        status = _stereoSound->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
        
    } else if(_sound) {
        status = _sound->GetStatus();
        if( status == Sound::Playing) {
            return true;
        }
    }

    return false;
}



float SoundPlayer::getSpeed() {
    if(_stream) {
        _speed = _stream->GetPitch();
        
    } else if(_stereoSound) {
        _speed = _sound->GetPitch();
        
    } else if(_sound) {
        _speed = _sound->GetPitch();
        
    } else {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;            
    }

    return _speed;
}



float SoundPlayer::getPan() {
    return _pan;
}



bool SoundPlayer::getLoop() {
    if(_stream) {
        return _stream->GetLoop();
    }

    else if(_stereoSound) {
        return _stereoSound->GetLoop();
    
    } else if(_sound) {
        return _sound->GetLoop();
    
    } else {
        osg::notify(osg::WARN)<<"SoundPlayer, no open sound"<<std::endl;            
    }

    return false;
}



void SoundPlayer::setVolume(float vol) {
	if (vol < 0) {
        _volume = 0;
    } else if (vol >1) {
        _volume = 1;
    } else {
    	_volume = vol;
    }

    if(_stream) {
        _stream->SetVolume(_volume*100.0f);
        
    } else if(_stereoSound) {
        _stereoSound->SetVolume(_volume*100.0f);
    
    } else if(_sound) {
        _sound->SetVolume(_volume*100.0f);
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
    
    if(_sound) {
        _sound->SetPlayingOffset(pct);
    }
    
    if(_stereoSound) {
        _stereoSound->SetPlayingOffset(pct);
    }

    else if(_stream) {
        osg::notify(osg::WARN)<<"SoundPlayer, cannot position a stream"<<std::endl;            
    }
}



float SoundPlayer::getPosition() {
    if(_stream) {
        return _stream->GetPlayingOffset();

    } else if(_stereoSound){
        return _stereoSound->GetPlayingOffset();
    
    } else if(_sound) {
        return _sound->GetPlayingOffset();
    
    } else {
    	 return 0;
    }
}



void SoundPlayer::setPan(float pan) {
	if (pan < -1) {
        _pan = -1;
    } else if (pan >1) {
        _pan = 1;
    } else {
    	_pan = pan;
    }

    if(_stream) {
        _stream->SetPosition(_pan,0,0);
    
    } else if(_stereoSound) {
        _stereoSound->SetPan(_pan);
    
    } else if(_sound) {
        _sound->SetPosition(_pan,0,0);
    }
}



void SoundPlayer::setPaused(bool bP) {
    Sound::SoundStatus status;
    _bPaused = bP;

    if(_stream) {
        status = _stream->GetStatus();
        if(_bPaused) {
            _stream->Pause();
        } else {
            if (status == Sound::Paused) {
                _stream->Play();
            }
        }
    
    } else if(_stereoSound) {
        status = _stereoSound->GetStatus();
        if(_bPaused) {
            _stereoSound->Pause();
        } else {
            if (status == Sound::Paused) {
                _stereoSound->Play();
            }
        }
    
    } else if(_sound) {
        status = _sound->GetStatus();
        if(_bPaused) {
            _sound->Pause();
        } else {
            if (status == Sound::Paused) {
                _sound->Play();
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

    if(_stream) {
        _stream->SetPitch(spd);
    
    } else if(_stereoSound) {
        _stereoSound->SetPitch(spd);
    
    } else if(_sound) {
        _sound->SetPitch(spd);
    }
}



void SoundPlayer::setLoop(bool bLp) {
    if(_stream) {
        _stream->SetLoop(bLp);
    
    } else if(_stereoSound) {
        _stereoSound->SetLoop(bLp);
    
    } else if(_sound) {
        _sound->SetLoop(bLp);
    }

}



void SoundPlayer::setMultiPlay(bool bMp) {
    if(_bIsStereo) {
        osg::notify(osg::WARN)<<"SoundPlayer, setMultiPlay() not yet implemented for stereo sounds"<<std::endl;            
    } else if (_isStreaming) {
        osg::notify(osg::WARN)<<"SoundPlayer, setMultiPlay() does not work with streams"<<std::endl;            
    } else {
        _bMultiPlay = bMp;
    }
}



void SoundPlayer::play() {
    if(_stream) {
        _stream->Play();
    
    } else if(_stereoSound) {
        _stereoSound->Play();
    
    } else if(_sound) {
        if(_bMultiPlay) {
            bool hasPlayed = false;
            Sound::SoundStatus status = _sound->GetStatus();
            if( status == Sound::Playing) {
                std::vector<Sound*>::iterator itr;
                for(itr = _multiSounds.begin(); itr != _multiSounds.end();itr++) {
                    status = (*itr)->GetStatus();
                    if(status != Sound::Playing) {
                        (*itr)->Play();
                        hasPlayed = true;
                        break;
                    }
                }
                
                if(!hasPlayed) {
                    _multiSounds.push_back(new Sound(*_sound));
                    _multiSounds.back()->Play();
                }

            } else {
                _sound->Play();
            }
        
        } else {
            _sound->Play();
        }
    }
}



void SoundPlayer::stop() {
    if(_stream) {
        _stream->Stop();
    
    } else if(_stereoSound) {
        _stereoSound->Stop();
    
    } else if(_sound) {
        _sound->Stop();
    }
}


