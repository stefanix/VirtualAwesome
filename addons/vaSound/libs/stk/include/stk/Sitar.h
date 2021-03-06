#ifndef STK_SITAR_H
#define STK_SITAR_H

#include <stk/Instrmnt.h>
#include <stk/DelayA.h>
#include <stk/OneZero.h>
#include <stk/Noise.h>
#include <stk/ADSR.h>
#include <cmath>

namespace stk {

/***************************************************/
/*! \class Sitar
    \brief STK sitar string model class.

    This class implements a sitar plucked string
    physical model based on the Karplus-Strong
    algorithm.

    This is a digital waveguide model, making its
    use possibly subject to patents held by
    Stanford University, Yamaha, and others.
    There exist at least two patents, assigned to
    Stanford, bearing the names of Karplus and/or
    Strong.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2010.
*/
/***************************************************/

class Sitar : public Instrmnt
{
 public:
  //! Class constructor, taking the lowest desired playing frequency.
  Sitar( StkFloat lowestFrequency = 20 );

  //! Class destructor.
  ~Sitar( void );

  //! Reset and clear all internal state.
  void clear( void );

  //! Set instrument parameters for a particular frequency.
  void setFrequency( StkFloat frequency );

  //! Pluck the string with the given amplitude using the current frequency.
  void pluck( StkFloat amplitude );

  //! Start a note with the given frequency and amplitude.
  void noteOn( StkFloat frequency, StkFloat amplitude );

  //! Stop a note with the given amplitude (speed of decay).
  void noteOff( StkFloat amplitude );

  //! Compute and return one output sample.
  StkFloat tick( unsigned int channel = 0 );

 protected:

  DelayA  delayLine_;
  OneZero loopFilter_;
  Noise   noise_;
  ADSR    envelope_;

  StkFloat loopGain_;
  StkFloat amGain_;
  StkFloat delay_;
  StkFloat targetDelay_;

};

inline StkFloat Sitar :: tick( unsigned int )
{
  if ( fabs(targetDelay_ - delay_) > 0.001 ) {
    if ( targetDelay_ < delay_ )
      delay_ *= 0.99999;
    else
      delay_ *= 1.00001;
    delayLine_.setDelay( delay_ );
  }

  lastFrame_[0] = delayLine_.tick( loopFilter_.tick( delayLine_.lastOut() * loopGain_ ) + 
                                (amGain_ * envelope_.tick() * noise_.tick()));
  
  return lastFrame_[0];
}

} // stk namespace

#endif

