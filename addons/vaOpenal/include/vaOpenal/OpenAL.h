////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
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

#ifndef VAOPENAL_OPENAL
#define VAOPENAL_OPENAL

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <va/Constants.h>

#if defined(TARGET_OSX)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
//#include <OpenAL/alext.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
//#include <AL/alext.h>
#endif

#include <iostream>
#include <string>

#ifndef ALC_EXT_EFX

/**
 * Source definitions to be used with alSource functions.
 * These values must be unique and not conflict with other
 * al source values.
 */
#define AL_DIRECT_FILTER                                   0x20005
#define AL_AUXILIARY_SEND_FILTER                           0x20006
#define AL_AIR_ABSORPTION_FACTOR                           0x20007
#define AL_ROOM_ROLLOFF_FACTOR                             0x20008
#define AL_CONE_OUTER_GAINHF                               0x20009
#define AL_DIRECT_FILTER_GAINHF_AUTO                       0x2000A
#define AL_AUXILIARY_SEND_FILTER_GAIN_AUTO                 0x2000B
#define AL_AUXILIARY_SEND_FILTER_GAINHF_AUTO               0x2000C

/**
 * Auxiliary Slot object definitions to be used with alAuxiliaryEffectSlot functions.
 */
#define AL_EFFECTSLOT_EFFECT                               0x0001
#define AL_EFFECTSLOT_GAIN                                 0x0002
#define AL_EFFECTSLOT_AUXILIARY_SEND_AUTO                  0x0003

/**
 * Value to be used as an Auxiliary Slot ID to disable a source send..
 */
#define AL_EFFECTSLOT_NULL                                 0x0000

/* Effect type */
#define AL_EFFECT_FIRST_PARAMETER                          0x0000
#define AL_EFFECT_LAST_PARAMETER                           0x8000
#define AL_EFFECT_TYPE                                     0x8001

/* Effect type definitions to be used with AL_EFFECT_TYPE. */
#define AL_EFFECT_NULL                                     0x0000  /* Can also be used as an Effect Object ID */
#define AL_EFFECT_REVERB                                   0x0001
#define AL_EFFECT_CHORUS                                   0x0002
#define AL_EFFECT_DISTORTION                               0x0003
#define AL_EFFECT_ECHO                                     0x0004
#define AL_EFFECT_FLANGER                                  0x0005
#define AL_EFFECT_FREQUENCY_SHIFTER                        0x0006
#define AL_EFFECT_VOCAL_MORPHER                            0x0007
#define AL_EFFECT_PITCH_SHIFTER                            0x0008
#define AL_EFFECT_RING_MODULATOR                           0x0009
#define AL_EFFECT_AUTOWAH                                  0x000A
#define AL_EFFECT_COMPRESSOR                               0x000B
#define AL_EFFECT_EQUALIZER                                0x000C
#define AL_EFFECT_EAXREVERB                                0x8000

/* Echo Parameters */
#define AL_ECHO_DELAY                                      0x0001
#define AL_ECHO_LRDELAY                                    0x0002
#define AL_ECHO_DAMPING                                    0x0003
#define AL_ECHO_FEEDBACK                                   0x0004
#define AL_ECHO_SPREAD                                     0x0005

/* Reverb Parameters */
#define AL_REVERB_DENSITY                                  0x0001
#define AL_REVERB_DIFFUSION                                0x0002
#define AL_REVERB_GAIN                                     0x0003
#define AL_REVERB_GAINHF                                   0x0004
#define AL_REVERB_DECAY_TIME                               0x0005
#define AL_REVERB_DECAY_HFRATIO                            0x0006
#define AL_REVERB_REFLECTIONS_GAIN                         0x0007
#define AL_REVERB_REFLECTIONS_DELAY                        0x0008
#define AL_REVERB_LATE_REVERB_GAIN                         0x0009
#define AL_REVERB_LATE_REVERB_DELAY                        0x000A
#define AL_REVERB_AIR_ABSORPTION_GAINHF                    0x000B
#define AL_REVERB_ROOM_ROLLOFF_FACTOR                      0x000C
#define AL_REVERB_DECAY_HFLIMIT                            0x000D

/* AL EAXReverb effect parameters. */
#define AL_EAXREVERB_DENSITY                               0x0001
#define AL_EAXREVERB_DIFFUSION                             0x0002
#define AL_EAXREVERB_GAIN                                  0x0003
#define AL_EAXREVERB_GAINHF                                0x0004
#define AL_EAXREVERB_GAINLF                                0x0005
#define AL_EAXREVERB_DECAY_TIME                            0x0006
#define AL_EAXREVERB_DECAY_HFRATIO                         0x0007
#define AL_EAXREVERB_DECAY_LFRATIO                         0x0008
#define AL_EAXREVERB_REFLECTIONS_GAIN                      0x0009
#define AL_EAXREVERB_REFLECTIONS_DELAY                     0x000A
#define AL_EAXREVERB_REFLECTIONS_PAN                       0x000B
#define AL_EAXREVERB_LATE_REVERB_GAIN                      0x000C
#define AL_EAXREVERB_LATE_REVERB_DELAY                     0x000D
#define AL_EAXREVERB_LATE_REVERB_PAN                       0x000E
#define AL_EAXREVERB_ECHO_TIME                             0x000F
#define AL_EAXREVERB_ECHO_DEPTH                            0x0010
#define AL_EAXREVERB_MODULATION_TIME                       0x0011
#define AL_EAXREVERB_MODULATION_DEPTH                      0x0012
#define AL_EAXREVERB_AIR_ABSORPTION_GAINHF                 0x0013
#define AL_EAXREVERB_HFREFERENCE                           0x0014
#define AL_EAXREVERB_LFREFERENCE                           0x0015
#define AL_EAXREVERB_ROOM_ROLLOFF_FACTOR                   0x0016
#define AL_EAXREVERB_DECAY_HFLIMIT                         0x0017

/**
 * Context definitions to be used with alcCreateContext.
 * These values must be unique and not conflict with other
 * al context values.
 */
#define ALC_EFX_MAJOR_VERSION                              0x20001
#define ALC_EFX_MINOR_VERSION                              0x20002
#define ALC_MAX_AUXILIARY_SENDS                            0x20003




/**
 * Listener definitions to be used with alListener functions.
 * These values must be unique and not conflict with other
 * al listener values.
 */
#define AL_METERS_PER_UNIT                                 0x20004

/**
 * Filter object definitions to be used with alFilter functions.
 */

/* Lowpass parameters. */
#define AL_LOWPASS_GAIN                                    0x0001
#define AL_LOWPASS_GAINHF                                  0x0002

/* Highpass Parameters */
#define AL_HIGHPASS_GAIN                                   0x0001
#define AL_HIGHPASS_GAINLF                                 0x0002

/* Bandpass Parameters */
#define AL_BANDPASS_GAIN                                   0x0001
#define AL_BANDPASS_GAINLF                                 0x0002
#define AL_BANDPASS_GAINHF                                 0x0003

/* Filter type */
#define AL_FILTER_FIRST_PARAMETER                          0x0000
#define AL_FILTER_LAST_PARAMETER                           0x8000
#define AL_FILTER_TYPE                                     0x8001

/* Filter type definitions to be used with AL_FILTER_TYPE. */
#define AL_FILTER_NULL                                     0x0000  /* Can also be used as a Filter Object ID */
#define	AL_FILTER_LOWPASS                                  0x0001
#define AL_FILTER_HIGHPASS                                 0x0002
#define AL_FILTER_BANDPASS                                 0x0003

#endif

namespace vaOpenal {

////////////////////////////////////////////////////////////
/// Let's define a macro to quickly check every OpenAL
/// API calls
///
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

    // If in debug mode, perform a test on every call
    #define ALCheck(Func) ((Func), ALCheckError(__FILE__, __LINE__))

#else

    // Else, we don't add any overhead
    #define ALCheck(Func) (Func)

#endif


////////////////////////////////////////////////////////////
/// Check last OpenAL error
///
////////////////////////////////////////////////////////////
inline void ALCheckError(const std::string& File, unsigned int Line)
{
    // Get the last error
    ALenum ErrorCode = alGetError();

    if (ErrorCode != AL_NO_ERROR)
    {
        std::string Error, Desc;

        // Decode the error code
        switch (ErrorCode)
        {
            case AL_INVALID_NAME :
            {
                Error = "AL_INVALID_NAME";
                Desc  = "an unacceptable name has been specified";
                break;
            }

            case AL_INVALID_ENUM :
            {
                Error = "AL_INVALID_ENUM";
                Desc  = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case AL_INVALID_VALUE :
            {
                Error = "AL_INVALID_VALUE";
                Desc  = "a numeric argument is out of range";
                break;
            }

            case AL_INVALID_OPERATION :
            {
                Error = "AL_INVALID_OPERATION";
                Desc  = "the specified operation is not allowed in the current state";
                break;
            }

            case AL_OUT_OF_MEMORY :
            {
                Error = "AL_OUT_OF_MEMORY";
                Desc  = "there is not enough memory left to execute the command";
                break;
            }
        }

        // Log the error
        std::cerr << "An internal OpenAL call failed in "
                  << File.substr(File.find_last_of("\\/") + 1) << " (" << Line << ") : "
                  << Error << ", " << Desc
                  << std::endl;
    }
}


}
#endif
