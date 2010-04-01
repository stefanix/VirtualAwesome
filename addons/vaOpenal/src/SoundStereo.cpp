////////////////////////////////////////////////////////////
//
// ofxOpenALPlayer
// Copyright (C) 2009 Pierre Proske (pierre@digitalstar.net)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vaOpenal/SoundStereo.h>
#include <vaOpenal/Sound.h>
#include <vaOpenal/Listener.h>
#include <vaOpenal/SoundBuffer.h>

using namespace vaOpenal;


////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
SoundStereo::SoundStereo() : m_pan(0), m_volume(100)
{

}


////////////////////////////////////////////////////////////
/// Construct the sound from its parameters
////////////////////////////////////////////////////////////
SoundStereo::SoundStereo(const SoundBuffer& Buffer, bool Loop, float Pitch, float Volume, const osg::Vec3f& LeftPosition, const osg::Vec3f& RightPosition)
{

    const Int16* buf = Buffer.GetSamples();
    int newLength = Buffer.GetSamplesCount()/2;
    Int16* buf1 = new Int16[newLength];
    Int16* buf2 = new Int16[newLength];

    for(int i = 0;i < newLength;i++)
    {
        buf1[i] = *buf++;
        buf2[i] = *buf++;
    }

    SoundBuffer* leftBuffer = new SoundBuffer();
    SoundBuffer* rightBuffer = new SoundBuffer();
    leftBuffer->LoadFromSamples(buf1,newLength,Buffer.GetChannelsCount()/2,Buffer.GetSampleRate());
    rightBuffer->LoadFromSamples(buf2,newLength,Buffer.GetChannelsCount()/2,Buffer.GetSampleRate());

    // Create a stereo sound instance
    //leftChannel = new Sound();
    //rightChannel = new Sound();
    leftChannel.SetBuffer(*leftBuffer);
    rightChannel.SetBuffer(*rightBuffer);

    SetLoop(Loop);
    SetPitch(Pitch);
    SetVolume(Volume);
    SetLeftPosition(LeftPosition);
    SetRightPosition(RightPosition);

    delete [] buf1;
    delete [] buf2;
}


////////////////////////////////////////////////////////////
/// Copy constructor
////////////////////////////////////////////////////////////
SoundStereo::SoundStereo(const SoundStereo& Copy)
{
    //leftChannel = new Sound;
    leftChannel.SetBuffer(*Copy.GetLeftBuffer());
    //rightChannel = new Sound;
    rightChannel.SetBuffer(*Copy.GetRightBuffer());
    SetPan(Copy.m_pan);
    SetVolume(Copy.m_volume);
    SetLoop(Copy.GetLoop());
    SetLeftPosition(Copy.GetLeftPosition());
    SetRightPosition(Copy.GetRightPosition());
    SetMinDistance(Copy.GetMinDistance());
    SetAttenuation(Copy.GetAttenuation());
}


////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
SoundStereo::~SoundStereo()
{
//    if(leftChannel) {
//        delete leftChannel;
//    }
//    if(rightChannel) {
//        delete rightChannel;
//    }
}


////////////////////////////////////////////////////////////
/// Play the sound
////////////////////////////////////////////////////////////
void SoundStereo::Play()
{
    leftChannel.Play();
    rightChannel.Play();
}


////////////////////////////////////////////////////////////
/// Pause the sound
////////////////////////////////////////////////////////////
void SoundStereo::Pause()
{
    leftChannel.Pause();
    rightChannel.Pause();
}


////////////////////////////////////////////////////////////
/// Stop the sound
////////////////////////////////////////////////////////////
void SoundStereo::Stop()
{
    leftChannel.Stop();
    rightChannel.Stop();
}


////////////////////////////////////////////////////////////
/// Set the source buffer
////////////////////////////////////////////////////////////
void SoundStereo::SetBuffer(const SoundBuffer& Buffer)
{
    // extract stereo channels
    const Int16* buf = Buffer.GetSamples();
    int newLength = Buffer.GetSamplesCount()/2;
    Int16* buf1 = new Int16[newLength];
    Int16* buf2 = new Int16[newLength];

    for(int i = 0;i < newLength;i++)
    {
        buf1[i] = *buf++;
        buf2[i] = *buf++;
    }

    SoundBuffer* leftBuffer = new SoundBuffer();
    SoundBuffer* rightBuffer = new SoundBuffer();
    leftBuffer->LoadFromSamples(buf1,newLength,Buffer.GetChannelsCount()/2,Buffer.GetSampleRate());
    rightBuffer->LoadFromSamples(buf2,newLength,Buffer.GetChannelsCount()/2,Buffer.GetSampleRate());

    // Create a stereo sound instance
//    leftChannel = new Sound();
//    rightChannel = new Sound();
    leftChannel.SetBuffer(*leftBuffer);
    rightChannel.SetBuffer(*rightBuffer);

    leftChannel.SetPosition(-1,0,0);
    rightChannel.SetPosition(1,0,0);

    delete [] buf1;
    delete [] buf2;

}


////////////////////////////////////////////////////////////
/// Set the sound loop state
////////////////////////////////////////////////////////////
void SoundStereo::SetLoop(bool Loop)
{
    leftChannel.SetLoop(Loop);
    rightChannel.SetLoop(Loop);
}


////////////////////////////////////////////////////////////
/// Set the sound pitch
////////////////////////////////////////////////////////////
void SoundStereo::SetPitch(float Pitch)
{
    leftChannel.SetPitch(Pitch);
    rightChannel.SetPitch(Pitch);
}


////////////////////////////////////////////////////////////
/// Set the sound volume
////////////////////////////////////////////////////////////
void SoundStereo::SetVolume(float Volume)
{
    m_volume = Volume;
    leftChannel.SetVolume((1.0f - m_pan)*Volume);
    rightChannel.SetVolume(m_pan*Volume);
}

////////////////////////////////////////////////////////////
/// Set the 2D sound panning
/// Takes values from -1 to +1
////////////////////////////////////////////////////////////
void SoundStereo::SetPan(float pan)
{
    m_pan = pan;
    float p = (pan + 1.0f)/2.0f;
    leftChannel.SetVolume((1.0f - p)*2*m_volume);
    rightChannel.SetVolume(p*2*m_volume);
}

////////////////////////////////////////////////////////////
/// Set the right channel position (take 3 values).
/// The default position is (-1, 0, 0)
////////////////////////////////////////////////////////////
void SoundStereo::SetLeftPosition(float x, float y, float z)
{
    leftChannel.SetPosition(osg::Vec3f(x,y,z));
}

////////////////////////////////////////////////////////////
/// Set the left channel position (take 3 values).
/// The default position is (1, 0, 0)
////////////////////////////////////////////////////////////
void SoundStereo::SetRightPosition(float x, float y, float z)
{
    rightChannel.SetPosition(osg::Vec3f(x,y,z));
}


////////////////////////////////////////////////////////////
/// Set the left channel position (take a 3D vector).
/// The default position is (0, 0, 0)
////////////////////////////////////////////////////////////
void SoundStereo::SetLeftPosition(const osg::Vec3f& Position)
{
    leftChannel.SetPosition(Position);
}

////////////////////////////////////////////////////////////
/// Set the right channel position (take a 3D vector).
/// The default position is (0, 0, 0)
////////////////////////////////////////////////////////////
void SoundStereo::SetRightPosition(const osg::Vec3f& Position)
{
    rightChannel.SetPosition(Position);
}


////////////////////////////////////////////////////////////
/// Make the sound's position relative to the listener's
/// position, or absolute.
/// The default value is false (absolute)
////////////////////////////////////////////////////////////
void SoundStereo::SetRelativeToListener(bool Relative)
{
    leftChannel.SetRelativeToListener(Relative);
    rightChannel.SetRelativeToListener(Relative);
}


////////////////////////////////////////////////////////////
/// Set the minimum distance - closer than this distance,
/// the listener will hear the sound at its maximum volume.
/// The default minimum distance is 1.0
////////////////////////////////////////////////////////////
void SoundStereo::SetMinDistance(float MinDistance)
{
    leftChannel.SetMinDistance(MinDistance);
    rightChannel.SetMinDistance(MinDistance);
}


////////////////////////////////////////////////////////////
/// Set the attenuation factor - the higher the attenuation, the
/// more the sound will be attenuated with distance from listener.
/// The default attenuation factor 1.0
////////////////////////////////////////////////////////////
void SoundStereo::SetAttenuation(float Attenuation)
{
    leftChannel.SetAttenuation(Attenuation);
    rightChannel.SetAttenuation(Attenuation);
}


////////////////////////////////////////////////////////////
/// Set the current playing position of the sound
////////////////////////////////////////////////////////////
void SoundStereo::SetPlayingOffset(float TimeOffset)
{
    leftChannel.SetPlayingOffset(TimeOffset);
    rightChannel.SetPlayingOffset(TimeOffset);
}


////////////////////////////////////////////////////////////
/// Get the right source buffer
////////////////////////////////////////////////////////////
const SoundBuffer* SoundStereo::GetLeftBuffer() const
{
    return leftChannel.GetBuffer();
}

////////////////////////////////////////////////////////////
/// Get the right source buffer
////////////////////////////////////////////////////////////
const SoundBuffer* SoundStereo::GetRightBuffer() const
{
    return rightChannel.GetBuffer();
}

////////////////////////////////////////////////////////////
/// Tell whether or not the sound is looping
////////////////////////////////////////////////////////////
bool SoundStereo::GetLoop() const
{
    return leftChannel.GetLoop();
}


////////////////////////////////////////////////////////////
/// Get the pitch
////////////////////////////////////////////////////////////
float SoundStereo::GetPitch() const
{
    return leftChannel.GetPitch();
}

////////////////////////////////////////////////////////////
/// Get the volume
////////////////////////////////////////////////////////////
float SoundStereo::GetVolume() const
{
    return m_volume;
}

////////////////////////////////////////////////////////////
/// Get the pan
////////////////////////////////////////////////////////////
float SoundStereo::GetPan() const
{
    return m_pan;
}

////////////////////////////////////////////////////////////
/// Get the right channel position
////////////////////////////////////////////////////////////
osg::Vec3f SoundStereo::GetLeftPosition() const
{
    return leftChannel.GetPosition();
}

////////////////////////////////////////////////////////////
/// Get the right channel position
////////////////////////////////////////////////////////////
osg::Vec3f SoundStereo::GetRightPosition() const
{
    return rightChannel.GetPosition();
}

////////////////////////////////////////////////////////////
/// Tell if the sound's position is relative to the listener's
/// position, or if it's absolute
////////////////////////////////////////////////////////////
bool SoundStereo::IsRelativeToListener() const
{
    return leftChannel.IsRelativeToListener();
}


////////////////////////////////////////////////////////////
/// Get the minimum distance
////////////////////////////////////////////////////////////
float SoundStereo::GetMinDistance() const
{
    return leftChannel.GetMinDistance();
}


////////////////////////////////////////////////////////////
/// Get the attenuation factor
////////////////////////////////////////////////////////////
float SoundStereo::GetAttenuation() const
{
    return leftChannel.GetAttenuation();
}


////////////////////////////////////////////////////////////
/// Get the current playing position of the sound
////////////////////////////////////////////////////////////
float SoundStereo::GetPlayingOffset() const
{
    return leftChannel.GetPlayingOffset();
}


////////////////////////////////////////////////////////////
/// Get the status of the sound (stopped, paused, playing)
////////////////////////////////////////////////////////////
Sound::SoundStatus SoundStereo::GetStatus() const
{
    return leftChannel.GetStatus();
}

////////////////////////////////////////////////////////////
/// Assign the sound to an Effect Slot
////////////////////////////////////////////////////////////
void SoundStereo::AssignEffectSlot(unsigned int uiEffectSlot, unsigned int uiSlotID)
{

}

////////////////////////////////////////////////////////////
/// Remove the sound from an Effect Slot
////////////////////////////////////////////////////////////
void SoundStereo::RemoveEffectSlot(unsigned int uiSlotID)
{

}

////////////////////////////////////////////////////////////
/// Assignment operator
////////////////////////////////////////////////////////////
SoundStereo& SoundStereo::operator =(const SoundStereo& Other)
{
    SoundStereo Temp(Other);

//    std::swap(mySource, Temp.mySource);
//    std::swap(myBuffer, Temp.myBuffer);

    return *this;
}

