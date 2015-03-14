#ifndef __perturb_filters_boxCarFilter_h__
#define __perturb_filters_boxCarFilter_h__

#define __perturb_include_internal_h__
#include "perturb.h"
#include <deque>
#include <assert.h>

namespace perturb {
  template <typename T>
  class boxCarFilter: public firFilter<T>
  {
    int numberOfTaps;
    std::complex<T> filterSum;
    std::deque<std::complex<T> > signalBuffer;
    public:
    

    int getNumberOfTaps()
    {
      return this->numberOfTaps;
    }

    void pushSample(std::complex<T> sample)
    {
      std::complex<T> s = sample / (T) this->numberOfTaps;
      this->signalBuffer.push_front(s);
      this->filterSum += this->signalBuffer.front();
      this->filterSum -= this->signalBuffer.back();
      this->signalBuffer.pop_back();
      
    }

    void reset()
    {
      this->filterSum = 0;
      this->signalBuffer.clear();
      for(int i = 0; i < this->numberOfTaps; i++)
      {
        this->signalBuffer.push_front(0);
      }
    }

    std::complex<T> getOutput()
    {
      return this->filterSum;
    }

    boxCarFilter(int length)
    {
      #ifdef __perturb_ERROR_CHECKS
        assert(length > 0);
      #endif
      this->numberOfTaps = length;
      this->reset();
    }

    int resizeFilter(int length)
    {

      #ifdef __perturb_ERROR_CHECKS
        assert(length > 0);
      #endif

      this->signalBuffer.resize(length, 0);
      int l = this->signalBuffer.size();
      this->filterSum = 0;
      for(int i = 0;i < l; i++)
      {
        this->signalBuffer[i] = this->signalBuffer[i] * ((T) this->numberOfTaps / (T) length);
        this->filterSum += this->signalBuffer[i];
      }
      this->numberOfTaps = length;
      return length;
    }
  };
};
#endif


