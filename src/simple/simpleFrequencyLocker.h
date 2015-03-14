#ifndef __perturb_simple_simpleFrequencyLocker_h__
#define __perturb_simple_simpleFrequencyLocker_h__

#define __perturb_include_internal_h__
#include "perturb.h"

namespace perturb
{

template <typename T> 
class simpleFrequencyLocker
{
  protected:
    T gain;
    T feedback;
    T loArgLast;
    T refArgLast;
    T prevRet;

   T domainBoundDx(T arg);
  public:
    simpleFrequencyLocker();
    T inputSample(std::complex<T> lo, std::complex<T> ref);
    void reset();
    T setFeedback(T feedback);
    T getFeedback();
    T setGain(T gain);
    T getGain();
};

#ifndef __perturb_simple_simpleFreqeuncyLocker_h__internal

extern template class simpleFrequencyLocker<double>;

#endif

};

#endif
