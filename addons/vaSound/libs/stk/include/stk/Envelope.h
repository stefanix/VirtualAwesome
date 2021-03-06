#ifndef STK_ENVELOPE_H
#define STK_ENVELOPE_H

#include <stk/Generator.h>

namespace stk {

/***************************************************/
/*! \class Envelope
    \brief STK linear line envelope class.

    This class implements a simple linear line envelope generator
    which is capable of ramping to an arbitrary target value by a
    specified \e rate.  It also responds to simple \e keyOn and \e
    keyOff messages, ramping to 1.0 on keyOn and to 0.0 on keyOff.

    by Perry R. Cook and Gary P. Scavone, 1995 - 2010.
*/
/***************************************************/

class Envelope : public Generator
{
 public:

  //! Default constructor.
  Envelope( void );

  //! Class destructor.
  ~Envelope( void );

  //! Assignment operator.
  Envelope& operator= ( const Envelope& e );

  //! Set target = 1.
  void keyOn( void ) { this->setTarget( 1.0 ); };

  //! Set target = 0.
  void keyOff( void ) { this->setTarget( 0.0 ); };

  //! Set the \e rate.
  void setRate( StkFloat rate );

  //! Set the \e rate based on a time duration.
  void setTime( StkFloat time );

  //! Set the target value.
  void setTarget( StkFloat target );

  //! Set current and target values to \e value.
  void setValue( StkFloat value );

  //! Return the current envelope \e state (0 = at target, 1 otherwise).
  int getState( void ) const { return state_; };

  //! Return the last computed output value.
  StkFloat lastOut( void ) const { return lastFrame_[0]; };

  //! Compute and return one output sample.
  StkFloat tick( void );

  //! Fill a channel of the StkFrames object with computed outputs.
  /*!
    The \c channel argument must be less than the number of
    channels in the StkFrames argument (the first channel is specified
    by 0).  However, range checking is only performed if _STK_DEBUG_
    is defined during compilation, in which case an out-of-range value
    will trigger an StkError exception.
  */
  StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );

 protected:

  void sampleRateChanged( StkFloat newRate, StkFloat oldRate );

  StkFloat value_;
  StkFloat target_;
  StkFloat rate_;
  int state_;
};

inline void Envelope :: setRate( StkFloat rate )
{
#if defined(_STK_DEBUG_)
  if ( rate < 0.0 ) {
    errorString_ << "Envelope::setRate: negative rates not allowed ... correcting!";
    handleError( StkError::WARNING );
    rate_ = -rate;
  }
  else
#endif
    rate_ = rate;
}

inline void Envelope :: setTime( StkFloat time )
{
#if defined(_STK_DEBUG_)
  if ( time < 0.0 ) {
    errorString_ << "Envelope::setTime: negative times not allowed ... correcting!";
    handleError( StkError::WARNING );
    rate_ = 1.0 / ( -time * Stk::sampleRate() );
  }
  else
#endif
    rate_ = 1.0 / ( time * Stk::sampleRate() );
}

inline void Envelope :: setTarget( StkFloat target )
{
  target_ = target;
  if ( value_ != target_ ) state_ = 1;
}

inline void Envelope :: setValue( StkFloat value )
{
  state_ = 0;
  target_ = value;
  value_ = value;
}

inline StkFloat Envelope :: tick( void )
{
  if ( state_ ) {
    if ( target_ > value_ ) {
      value_ += rate_;
      if ( value_ >= target_ ) {
        value_ = target_;
        state_ = 0;
      }
    }
    else {
      value_ -= rate_;
      if ( value_ <= target_ ) {
        value_ = target_;
        state_ = 0;
      }
    }
    lastFrame_[0] = value_;
  }

  return value_;
}

inline StkFrames& Envelope :: tick( StkFrames& frames, unsigned int channel )
{
#if defined(_STK_DEBUG_)
  if ( channel >= frames.channels() ) {
    errorString_ << "Envelope::tick(): channel and StkFrames arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  StkFloat *samples = &frames[channel];
  unsigned int hop = frames.channels();
  for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
    *samples = tick();

  return frames;
}

} // stk namespace

#endif
