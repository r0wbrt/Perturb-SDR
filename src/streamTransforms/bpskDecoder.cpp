#define __perturb_bpskDecoder_h__DOUBLE_INTERNAL
#include "bpskDecoder.h"

#include <iostream>
namespace perturb
{

  template <>
  bpskDecoder<double>::bpskDecoder()
  {
    this->phaseError = 0;
    this->amplitudeError = 0;
    this->amplitudeMean = 0;
    this->changed = false;
    this->dataVector.clear();
    this->phaseVector.clear();
    this->index = 0;
  }

  template <>
  void bpskDecoder<double>::inputSample(std::complex<double> sample)
  {
    double a = std::arg(sample);
    this->amplitudeMean += norm(sample);
    this->phaseVector.push_back(a);
    this->index++;
  }

  template <>
  void bpskDecoder<double>::inputSample(std::complex<double> prevSymbolSample, std::complex<double> currentSymbolSample)
  {
    double a = std::arg(currentSymbolSample / prevSymbolSample);
    this->amplitudeMean += norm(currentSymbolSample);
    this->phaseVector.push_back(a);
    this->index++;
  }

  template <>
  bool bpskDecoder<double>::doDecode()
  {
    if(this->index == 0)
      return false;

    this->changed = true;
    this->amplitudeError = (this->amplitudeMean / this->index ) - 1.0;
    double psum = 0.0;
    bool dec = false;
    std::deque<double>::iterator it;
    std::deque<double>::iterator it_end;
    it = this->phaseVector.begin();
    it_end = this->phaseVector.end();
    while(it!=it_end)
    {
      psum += fabs(*it++);
    }
    psum = psum / (double) this->index;

    if(psum < PI/2)
      dec = false;
    else 
      dec = true;

    this->dataVector.push_back(dec);
    it = this->phaseVector.begin();
    it_end = this->phaseVector.end();
    psum = 0.0;
    if(dec==true)
    {
      while(it!=it_end)
      {
        double p = *it++;
        if(p < 0)
        {
          psum += (PI - fabs(p));
        } else {
          psum -= (PI - fabs(p));
        }
      }  
    } else {

      while(it!=it_end)
      {
        double p = *it++;
        if(p < 0)
        {
          psum -= (fabs(p) - 0.0);
        } else {
          psum += (fabs(p) - 0.0);
        }
      }
    }
    this->phaseError = psum / (double) this->index; 
    return true;  
  }

  template <>
  void bpskDecoder<double>::resetDecoder()
  {
    this->amplitudeMean = 0;
    this->phaseVector.clear();
    this->index = 0;
  }

  template <>
  void bpskDecoder<double>::clearData()
  {
    this->dataVector.clear();
  }

  template <>
  std::vector<bool> bpskDecoder<double>::outputData()
  {
    return this->dataVector;
  }

  template <>
  void bpskDecoder<double>::reset()
  {
    this->phaseError = 0;
    this->amplitudeError = 0;
    this->amplitudeMean = 0;
    this->changed = false;
    this->dataVector.clear();
    this->phaseVector.clear();
    this->index = 0;
  }

  template <>
  int bpskDecoder<double>::getNumberOfSamples()
  {
    return this->index;
  }

  template <>
  double bpskDecoder<double>::getAmplitudeError()
  {
    this->changed = false;
    return this->amplitudeError;
  }

  template <>
  double bpskDecoder<double>::getPhaseError()
  {
    this->changed = false;
    return this->phaseError;
  }

  template <>
  bool bpskDecoder<double>::isChanged()
  {
    return this->changed;
  }

};
