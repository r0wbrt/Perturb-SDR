#ifndef __perturb_bpskEncoder_h__
#define __perturb_bpskEncoder_h__

#define __perturb_include_internal_h__
#include "perturb.h"

namespace perturb
{
  template <typename T>
  class bpskEncoder
  {
    protected:
      bool state;
      T amplitude;
      
    public:
      bpskEncoder();
      bool inputByte(int byte);
      bool inputByte(int byte, bool differential);
      std::complex<T> doEncode();
      void reset();
      void encoderReset();
      void setAmplitude(T amplitude);
      T getAmplitude();

  };

#ifndef __perturb_bpskEncoder_h__DOUBLE_INTERNAL
  extern template class bpskEncoder <double>;
#endif

};

#endif
