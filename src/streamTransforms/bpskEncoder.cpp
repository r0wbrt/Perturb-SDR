#define __perturb_bpskEncoder_h__DOUBLE_INTERNAL
#include "bpskEncoder.h"

namespace perturb
{

  template <>
  bpskEncoder<double>::bpskEncoder()
  {
    this->state = false;
    this->amplitude = 1.0;
  }


  template <>
  bool bpskEncoder<double>::inputByte(int byte, bool differential)
  {
    bool dec;
    if(byte&0x01 == 1)
      dec = true;
    else
      dec = false;

    if(differential == true && dec == true)
      this->state = !this->state;
    else if(differential == false) {
      this->state = dec;
    }

    return true;
  }


  template <>
  bool bpskEncoder<double>::inputByte(int byte)
  {
    return this->inputByte(byte, false);
  }





  template <>
  std::complex<double> bpskEncoder<double>::doEncode()
  {
    if(this->state == true)
      return std::complex<double>(-amplitude,0);
    else
      return std::complex<double>(amplitude,0);
  }

  template <>
  void bpskEncoder<double>::reset()
  {
    this->state = false;
    this->amplitude = 1.0;  
  }

  template <>
 void bpskEncoder<double>::encoderReset()
  {
      /*NOOP*/
  }


  template <>
  void bpskEncoder<double>::setAmplitude(double amplitude)
  {
    this->amplitude = amplitude;
  }


  template <>
  double bpskEncoder<double>::getAmplitude()
  {
    return this->amplitude;
  }

};
