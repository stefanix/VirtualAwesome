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

#ifndef VAOPENAL_SOUNDSTEREO
#define VAOPENAL_SOUNDSTEREO

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <osg/Vec3>
#include <vaOpenal/Resource.h>
#include <vaOpenal/AudioResource.h>
#include <cstdlib>

#include <vaOpenal/Sound.h>

namespace vaOpenal {

class SoundBuffer;
class Sound;

////////////////////////////////////////////////////////////
/// SoundStereo defines the properties of stereo sounds
/// basically a wrapper for 2 Sound ojbects
////////////////////////////////////////////////////////////
class SoundStereo
{
public :

    ////////////////////////////////////////////////////////////
    /// Enumeration of the sound states
    ////////////////////////////////////////////////////////////
    enum SoundStatus
    {
        Stopped, ///< Sound is not playing
        Paused,  ///< Sound is paused
        Playing  ///< Sound is playing
    };

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ///
    ////////////////////////////////////////////////////////////
    SoundStereo();

    ////////////////////////////////////////////////////////////
    /// Construct the sound from its parameters
    ///
    /// \param Buffer :   Sound buffer to play (NULL by default)
    /// \param Loop :     Loop flag (false by default)
    /// \param Pitch :    Value of the pitch (1 by default)
    /// \param Volume :   Volume (100 by default)
    /// \param Left position : Left position (-1, 0, 0 by default)
    /// \param Right position : Right Position (1, 0, 0 by default)
    ///
    ////////////////////////////////////////////////////////////
    SoundStereo(const SoundBuffer& Buffer, bool Loop = false, float Pitch = 1.f, float Volume = 100.f, const osg::Vec3f& LeftPosition = osg::Vec3f(-1, 0, 0), const osg::Vec3f& RightPosition = osg::Vec3f(-1, 0, 0));

    ////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    /// \param Copy : Instance to copy
    ///
    ////////////////////////////////////////////////////////////
    SoundStereo(const SoundStereo& Copy);

    ////////////////////////////////////////////////////////////
    /// Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SoundStereo();

    ////////////////////////////////////////////////////////////
    /// Play the sound
    ///
    ////////////////////////////////////////////////////////////
    void Play();

    ////////////////////////////////////////////////////////////
    /// Pause the sound
    ///
    ////////////////////////////////////////////////////////////
    void Pause();

    ////////////////////////////////////////////////////////////
    /// Stop the sound
    ///
    ////////////////////////////////////////////////////////////
    void Stop();

    ////////////////////////////////////////////////////////////
    /// Set the source buffer
    ///
    /// \param Buffer : New sound buffer to bind to the sound
    ///
    ////////////////////////////////////////////////////////////
    void SetBuffer(const SoundBuffer& Buffer);

    ////////////////////////////////////////////////////////////
    /// Set the sound loop state.
    /// This parameter is disabled by default
    ///
    /// \param Loop : True to play in loop, false to play once
    ///
    ////////////////////////////////////////////////////////////
    void SetLoop(bool Loop);

    ////////////////////////////////////////////////////////////
    /// Set the sound pitch.
    /// The default pitch is 1
    ///
    /// \param Pitch : New pitch
    ///
    ////////////////////////////////////////////////////////////
    void SetPitch(float Pitch);

    ////////////////////////////////////////////////////////////
    /// Set the sound volume.
    /// The default volume is 100
    ///
    /// \param Volume : Volume (in range [0, 100])
    ///
    ////////////////////////////////////////////////////////////
    void SetVolume(float Volume);

    ////////////////////////////////////////////////////////////
    /// Set the sound 2D pan.
    /// The default pan is 0
    ///
    /// \param Volume : Volume (in range [0, 100])
    ///
    ////////////////////////////////////////////////////////////
    void SetPan(float pan);

    ////////////////////////////////////////////////////////////
    /// Set the left channel position (take 3 values).
    /// The default position is (-1, 0, 0)
    ///
    /// \param X, Y, Z : Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    void SetLeftPosition(float X, float Y, float Z);

    ////////////////////////////////////////////////////////////
    /// Set the right channel position (take 3 values).
    /// The default position is (1, 0, 0)
    ///
    /// \param X, Y, Z : Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    void SetRightPosition(float X, float Y, float Z);

    ////////////////////////////////////////////////////////////
    /// Set the left channel position (take a 3D vector).
    /// The default position is (-1, 0, 0)
    ///
    /// \param Position : Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    void SetLeftPosition(const osg::Vec3f& Position);

    ////////////////////////////////////////////////////////////
    /// Set the right channel position (take a 3D vector).
    /// The default position is (1, 0, 0)
    ///
    /// \param Position : Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    void SetRightPosition(const osg::Vec3f& Position);

    ////////////////////////////////////////////////////////////
    /// Make the sound's position relative to the listener's
    /// position, or absolute.
    /// The default value is false (absolute)
    ///
    /// \param Relative : True to set the position relative, false to set it absolute
    ///
    ////////////////////////////////////////////////////////////
    void SetRelativeToListener(bool Relative);

    ////////////////////////////////////////////////////////////
    /// Set the minimum distance - closer than this distance,
    /// the listener will hear the sound at its maximum volume.
    /// The default minimum distance is 1.0
    ///
    /// \param MinDistance : New minimum distance for the sound
    ///
    ////////////////////////////////////////////////////////////
    void SetMinDistance(float MinDistance);

    ////////////////////////////////////////////////////////////
    /// Set the attenuation factor - the higher the attenuation, the
    /// more the sound will be attenuated with distance from listener.
    /// The default attenuation factor 1.0
    ///
    /// \param Attenuation : New attenuation factor for the sound
    ///
    ////////////////////////////////////////////////////////////
    void SetAttenuation(float Attenuation);

    ////////////////////////////////////////////////////////////
    /// Set the current playing position of the sound
    ///
    /// \param TimeOffset : New playing position, expressed in seconds
    ///
    ////////////////////////////////////////////////////////////
    void SetPlayingOffset(float TimeOffset);

    ////////////////////////////////////////////////////////////
    /// Get the left source buffer
    ///
    /// \return Sound buffer bound to the sound (can be NULL)
    ///
    ////////////////////////////////////////////////////////////
    const SoundBuffer* GetLeftBuffer() const;

    ////////////////////////////////////////////////////////////
    /// Get the right source buffer
    ///
    /// \return Sound buffer bound to the sound (can be NULL)
    ///
    ////////////////////////////////////////////////////////////
    const SoundBuffer* GetRightBuffer() const;

    ////////////////////////////////////////////////////////////
    /// Tell whether or not the sound is looping
    ///
    /// \return True if the sound is looping, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    bool GetLoop() const;

    ////////////////////////////////////////////////////////////
    /// Get the pitch
    ///
    /// \return Pitch value
    ///
    ////////////////////////////////////////////////////////////
    float GetPitch() const;

    ////////////////////////////////////////////////////////////
    /// Get the volume
    ///
    /// \return Volume value (in range [1, 100])
    ///
    ////////////////////////////////////////////////////////////
    float GetVolume() const;

    ////////////////////////////////////////////////////////////
    /// Get the pan
    ///
    /// \return 2D panning value (in range [-1, 1])
    ///
    ////////////////////////////////////////////////////////////
    float GetPan() const;

    ////////////////////////////////////////////////////////////
    /// Get the left channel position
    ///
    /// \return Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    osg::Vec3f GetLeftPosition() const;

    ////////////////////////////////////////////////////////////
    /// Get the right channel position
    ///
    /// \return Position of the sound in the world
    ///
    ////////////////////////////////////////////////////////////
    osg::Vec3f GetRightPosition() const;

    ////////////////////////////////////////////////////////////
    /// Tell if the sound's position is relative to the listener's
    /// position, or if it's absolute
    ///
    /// \return True if the position is relative, false if it's absolute
    ///
    ////////////////////////////////////////////////////////////
    bool IsRelativeToListener() const;

    ////////////////////////////////////////////////////////////
    /// Get the minimum distance
    ///
    /// \return Minimum distance for the sound
    ///
    ////////////////////////////////////////////////////////////
    float GetMinDistance() const;

    ////////////////////////////////////////////////////////////
    /// Get the attenuation factor
    ///
    /// \return Attenuation factor of the sound
    ///
    ////////////////////////////////////////////////////////////
    float GetAttenuation() const;

    ////////////////////////////////////////////////////////////
    /// Get the status of the sound (stopped, paused, playing)
    ///
    /// \return Current status of the sound
    ///
    ////////////////////////////////////////////////////////////
    Sound::SoundStatus GetStatus() const;

    ////////////////////////////////////////////////////////////
    /// Get the current playing position of the sound
    ///
    /// \return Current playing position, expressed in seconds
    ///
    ////////////////////////////////////////////////////////////
    float GetPlayingOffset() const;

    ////////////////////////////////////////////////////////////
    /// Assign the sound to an Effect Slot
    ///
    /// \param uiSlotID : ID of the aux. effect slot to be used
    ///
    ////////////////////////////////////////////////////////////
    void AssignEffectSlot(unsigned int uiEffectSlot, unsigned int uiSlotID);

    ////////////////////////////////////////////////////////////
    /// Remove the sound from an Effect Slot
    ///
    /// \param uiSlotID : ID of the aux. effect slot to be removed from
    ///
    ////////////////////////////////////////////////////////////
    void RemoveEffectSlot(unsigned int uiSlotID);

    ////////////////////////////////////////////////////////////
    /// Assignment operator
    ///
    /// \param Other : Instance to assign
    ///
    /// \return Reference to the sound
    ///
    ////////////////////////////////////////////////////////////
    SoundStereo& operator =(const SoundStereo& Other);

private :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Sound  leftChannel;
    Sound  rightChannel;
    float     m_pan;
    float     m_volume;

};


}
#endif
