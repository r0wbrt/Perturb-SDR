#ifndef __perturb_simple_simplePhaseLocker_h__
#define __perturb_simple_simplePhaseLocker_h__

#define __perturb_include_internal_h__
#include "perturb.h"

namespace perturb
{

template <typename T> 
class simplePhaseLocker
{
  protected:
    T gain;
    T feedback;
    T prevRet;

   T domainBoundDx(T arg);
  public:
    simplePhaseLocker();
    T inputSample(std::complex<T> lo, std::complex<T> ref);
    void reset();
    T setFeedback(T feedback);
    T getFeedback();
    T setGain(T gain);
    T getGain();
};

#ifndef __perturb_simple_simplePhaseLocker_h__internal

extern template class simplePhaseLocker<double>;

#endif

};
#endif
