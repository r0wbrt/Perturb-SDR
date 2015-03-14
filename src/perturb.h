#ifndef __perturb_perturb_h__
#define __perturb_perturb_h__

#include <stdint.h>
#include <vector>
#include <math.h>
#include <numeric>
#include <complex>

#ifdef __perturb_include_internal_h__
#include "perturb_internal.h"
#endif

namespace perturb
{

  #define PI 3.14159265359

  template <typename type>
  class sink 
  {
    public:
      virtual type getMin() = 0;
      virtual type getMax() = 0;
      virtual int getRate() = 0;
      virtual bool operator()(std::complex<type> input) = 0;
      virtual void close() = 0;
  };

  template <typename type>
  class source
  {
    public:
      virtual type getMin() = 0;
      virtual type getMax() = 0;
      virtual int getRate() = 0;
      virtual bool operator()(std::complex<type>& output) = 0;
      virtual void close() = 0;
  };


  class frequencyEstimator
  {
    protected:
      double last;
      double freq;
      int n;
    public:
      double inputSample(std::complex<double> input);
      double getFrequency();
      void reset();
  };

  class phaseEstimator
  {
    protected:
    double phase;
    int n;
    public:
      double inputSample(std::complex<double> input, std::complex<double> lo);
      double getPhaseOffset();
      void reset();
  };

  template <typename T>
  class firFilter
  {
    public:
      virtual int getNumberOfTaps() = 0;
      virtual void pushSample(std::complex<T> sample) = 0;
      virtual void reset() = 0;
      virtual std::complex<T> getOutput() = 0;
  };

  template <typename T>
  class frequencyLocker
  {
    public:
      virtual T inputSample(std::complex<T> lo, std::complex<T> ref) = 0;
      virtual void reset() = 0;
  };

  template <typename T>
  class phaseLockedLoop
  {
    public:
      virtual T inputSample(std::complex<T> lo, std::complex<T> ref) = 0;
      virtual void reset() = 0;
  };

};

#endif
