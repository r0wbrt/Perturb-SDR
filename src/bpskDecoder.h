#ifndef __perturb_bpskDecoder_h__
#define __perturb_bpskDecoder_h__

#define __perturb_include_internal_h__
#include "perturb.h"
#include <deque>

namespace perturb
{
  template <typename T>
  class bpskDecoder
  {
    protected:
      T phaseError;
      T amplitudeError;
      T amplitudeMean;
      bool changed;
      std::deque<T> phaseVector;
      std::vector<bool> dataVector;
      int index;
    public:
      bpskDecoder();

      void inputSample(std::complex<T> sample);
      void inputSample(std::complex<T> prevSymbolSample, std::complex<T> currentSymbolSample);
      bool doDecode();
      void resetDecoder();   
      void clearData();
      std::vector<bool> outputData();
      void reset();

      int getNumberOfSamples();
      T getAmplitudeError();
      T getPhaseError();
      bool isChanged();
   
  };
#ifndef __perturb_bpskDecoder_h__DOUBLE_INTERNAL
  extern template class bpskDecoder <double>;
#endif
};


#endif
