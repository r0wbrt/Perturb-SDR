#define __perturb_simple_simpleAudioCompressor_h__internal
#include "simple/simpleAudioCompressor.h"


namespace perturb
{

template<>
 simpleAudioCompressor<double>::simpleAudioCompressor()
{
  this->gain =.3;
  this->feedback = .7;
  this->prev = 0.0;
  this->maxMul = 20.0;
}
  
template<>
double  simpleAudioCompressor<double>::inputSample(std::complex<double> input)
{
  double k = sqrt(norm(input));
  double l;
  if(k!=0)
  {
     l = ( (this->gain*.5) / k );
  } else {
    l = 0;
  } 
  double m = l*this->gain+this->prev*this->feedback;  

  if(m > this->maxMul)
  {
    this->prev = this->maxMul;
  } else {
    this->prev = m;
  }

  return this->prev;
}

template<>
double  simpleAudioCompressor<double>::getFeedback()
{
  return this->feedback;
}

template<>
double  simpleAudioCompressor<double>::setFeedback(double feedback)
{
  this->feedback = feedback;
  return this->feedback;
}

template<>
double  simpleAudioCompressor<double>::getGain()
{
  return this->gain;
}

template<>
double  simpleAudioCompressor<double>::setGain(double gain)
{
  this->gain = gain;
  return this->gain;
}

template<>
void  simpleAudioCompressor<double>::reset()
{
  this->prev = 0;
}

template <>
double simpleAudioCompressor<double>::setMaxMul(double mul)
{
  this->maxMul = mul;
  return this->maxMul;
}

template<>
double simpleAudioCompressor<double>::getMaxMul()
{
  return this->maxMul;
}

};
