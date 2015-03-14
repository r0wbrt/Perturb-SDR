#define __perturb_bpskDecoder_h__DOUBLE_INTERNAL
#include "bpskDecoder.h"

template <>
perturb::bpskDecoder<double>::bpskDecoder()
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
void perturb::bpskDecoder<double>::inputSample(std::complex<double> sample)
{
  double a = arg(sample);
  this->amplitudeMean += norm(sample);
  this->phaseVector.pushBack(a);
  this->index++;
}

template <>
void perturb::bpskDecoder<double>::inputSample(std::complex<double> prevSymbolSample, std::complex<double> currentSymbolSample)
{
  double a = arg(currentSymbolSample / prevSymbolSample);
  this->amplitudeMean += norm(currentSymbolSample);
  this->phaseVector.pushBack(a);
  this->index++;
}

template <>
bool perturb::bpskDecoder<double>::doDecode()
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

  this->dataVec.pushBack(dec);
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
void perturb::bpskDecoder<double>::resetDecoder()
{
  this->amplitudeMean = 0;
  this->phaseVector.clear();
  this->index = 0;
}

template <>
void perturb::bpskDecoder<double>::clearData()
{
  this->dataVector.clear();
}

template <>
std::vector<bool> perturb::bpskDecoder<double>::outputData()
{
  return this->dataVector;
}

template <>
void perturb::bpskDecoder<double>::reset()
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
int perturb::bpskDecoder<double>::getNumberOfSamples()
{
  return this->index;
}

template <>
double perturb::bpskDecoder<double>::getAmplitudeError()
{
  this->changed = false;
  return this->amplitudeError;
}

template <>
double perturb::bpskDecoder<double>::getPhaseError()
{
  this->changed = false;
  return this->phaseError;
}

template <>
bool perturb::bpskDecoder<double>::isChanged()
{
  return this->changed;
}

