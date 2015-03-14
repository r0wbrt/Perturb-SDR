#define __perturb_simple_simplePhaseLocker_h__internal
#include "simple/simplePhaseLocker.h"

namespace perturb {

template <>
double simplePhaseLocker<double>::domainBoundDx(double arg)
{
  double ret = arg;

    if(ret < -3.14159)
      ret += 2*3.14159;
    else if(ret > 3.14159)
      ret -= 2*3.14159;
  return ret;

}



template <>
void simplePhaseLocker<double>::reset()
{
      this->prevRet = 0;
}


template <>
simplePhaseLocker<double>::simplePhaseLocker()
{
  this->reset();
  this->gain = .6;
  this->feedback = 0.0;
}

template <>
double simplePhaseLocker<double>::inputSample(std::complex<double> lo, std::complex<double> ref)
{
  double refArg, loArg, err;

  loArg = arg(lo);
  refArg = arg(ref);
  
  err = refArg - loArg;
  err = this->domainBoundDx(err);


  this->prevRet =  err*this->gain + this->prevRet*this->feedback;

  return this->prevRet;
}







template <>
double simplePhaseLocker<double>::setFeedback(double feedback)
{
  this->feedback = feedback;
  return feedback;
}
template <>
double  simplePhaseLocker<double>::getFeedback()
{
  return this->feedback;
}
template <>
double simplePhaseLocker<double>::setGain(double gain)
{
  this->gain = gain;
  return gain;
}
template <>
 double simplePhaseLocker<double>::getGain()
{
  return this->gain;
}

};
