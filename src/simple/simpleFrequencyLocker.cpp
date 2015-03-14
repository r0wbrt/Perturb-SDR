#define __perturb_simple_simpleFreqeuncyLocker_h__internal
#include "simple/simpleFrequencyLocker.h"


namespace perturb 
{
template <>
double simpleFrequencyLocker<double>::domainBoundDx(double arg)
{
  double ret = arg;

    if(ret < -3.14159)
      ret += 2*3.14159;
    else if(ret > 3.14159)
      ret -= 2*3.14159;
  return ret;

}

template <>
void simpleFrequencyLocker<double>::reset()
{
  
      this->loArgLast = 0;
      this->refArgLast = 0;
      this->prevRet = 0;
}


template <>
simpleFrequencyLocker<double>::simpleFrequencyLocker()
{
  this->reset();
  this->gain = .6;
  this->feedback = 0.0;
}

template <>
double simpleFrequencyLocker<double>::inputSample(std::complex<double> lo, std::complex<double> ref)
{
  double dxrefArg, dxloArg, refArg, loArg, err;

  loArg = arg(lo);
  refArg = arg(ref);
  dxrefArg = refArg - this->refArgLast;
  dxloArg = loArg - this->loArgLast;

  dxrefArg = this->domainBoundDx(dxrefArg);
  dxloArg = this->domainBoundDx(dxloArg);

  err = dxrefArg - dxloArg;
  err = this->domainBoundDx(err);

  this->refArgLast = refArg;
  this->loArgLast = loArg;

  this->prevRet =  err*this->gain + this->prevRet*this->feedback;

  return this->prevRet;
}


template <>
double simpleFrequencyLocker<double>::setFeedback(double feedback)
{
  this->feedback = feedback;
  return feedback;
}
template <>
double  simpleFrequencyLocker<double>::getFeedback()
{
  return this->feedback;
}
template <>
double simpleFrequencyLocker<double>::setGain(double gain)
{
  this->gain = gain;
  return gain;
}
template <>

 double simpleFrequencyLocker<double>::getGain()
{
  return this->gain;
}

};
