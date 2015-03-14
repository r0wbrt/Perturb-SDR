#ifndef __perturb_simple_simpleAudioCompressor_h__
#define __perturb_simple_simpleAudioCompressor_h__

#define __perturb_include_internal_h__
#include "perturb.h"
namespace perturb
{

template <typename T>
class simpleAudioCompressor
{
  protected:
  T prev;
  T feedback;
  T gain;
  T maxMul;
  public:
  simpleAudioCompressor();  
  T inputSample(std::complex<T> input);
  T getFeedback();
  T setFeedback(T feedback);
  T getGain();
  T setGain(T gain);
  T setMaxMul(T mul);
  T getMaxMul();
  void reset();
};

#ifndef __perturb_simple_simpleAudioCompressor_h__internal


extern template class simpleAudioCompressor<double>;
#endif

};
#endif
