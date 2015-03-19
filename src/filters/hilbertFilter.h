#ifndef __perturb_filters_hilbertFilter_h__
#define __perturb_filters_hilbertFilter_h__


#include "perturb.h"
#include <deque>
#include <assert.h>

namespace perturb {
  template <typename T>
  class RealHilbertFilter: public firFilter<T>
  {
    protected:
    std::deque<T> signalBuffer;
    std::deque<T> firCoef;
    int numberOfTaps;
    void genCoef()
    {
      this->firCoef.clear();
      int num = this->numberOfTaps;
      for(int i = 1; i <= num; i++)
      {
        firCoef.push_back(2 / (PI * (2*i-1)));
      }  
    }
    void resetSignalBuffer()
    {
      this->signalBuffer.clear();
      for(int i = 0; i < (numberOfTaps*4 - 1); i++)
      {
       this->signalBuffer.push_back(0); 
      }
    }
    public:
    hilbertFilter(int numberOfTaps)
    {
      this->numberOfTaps = numberOfTaps;
      this->resetSignalBuffer();
      this->genCoef();
    }
    int getNumberOfTaps()
    {
      return (this->numberOfTaps*4 - 1);
    }
    void pushSample(std::complex<T> sample)
    {
      this->signalBuffer.pop_front();
      this->signalBuffer.push_back(sample.real());
    }
    void reset();
    std::complex<T> getOutput()
    {
      T imag = 0;
      T real = this->signalBuffer[2*this->numberOfTaps];
      for(int i = 1; i <= this->numberOfTaps; i++)
      {
        T a = this->signalBuffer[2*(this->numberOfTaps  - i)];
        T b = this->signalBuffer[2*(this->numberOfTaps  + i - 1)];
        imag += this->firCoef[i] * (a-b);
      }
      return std::complex<T> (real, imag);
    }

    std::complex<T> getCoef(int i)
    {
    }
  };
};
#endif


