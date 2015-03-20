#include "perturb.h"
#include "filters.h"

namespace perturb 
{
  template <>
  int filters<double>::hilbertFilter(int c, int nc, std::vector<double>& filter)
  {
    int j = 0;
    filter.clear();
    filter.reserve(c+nc+1);
    for(int i = 0; i < nc; i++)
    {
      int s = nc - i;
      double coef;
      if(s % 2 == 1)
      {
        coef = -2.0 / (PI*(double) s); 
      } else {
        coef = 0.0;
      }
      filter.push_back(coef);
      j++;
    }
    filter.push_back(0.0);
    j++;
    for(int i = 0; i < nc; i++)
    {
      int s = i;
      double coef;
      if(s % 2 == 1)
      {
        coef = 2.0 / (PI*(double) s); 
      } else {
        coef = 0.0;
      }
      filter.push_back(coef);
      j++;
    }

    return j;

  }

  template <>
  int filters<double>::sincFilter(int c, int nc, double b, std::vector<double>& filter)
  { 
    int j = 0;
    filter.clear();
    filter.reserve(c+nc+1);
    for(int i = 0; i < nc; i++)
    {
      double coef = sin(2.0*PI*b*(nc - i)) / (PI*(nc-i));
      filter.push_back(coef);
      j++;
    }
    filter.push_back(1.0);
    j++;
    for(int i = 0; i < c; i++)
    {
      double coef = sin(2.0*PI*b*(i+1)) / (PI*(i+1));
      filter.push_back(coef);
      j++;
    }

    return j;
  }

  // q = symbolLength / sampleRate
  template <>
  int filters<double>::raisedCosineFilter(int c, int nc, double q, double b, std::vector<double>& filter)
  {
    int j = 0;
    filter.clear();
    filter.reserve(c+nc+1);
    for(int i = 0; i < nc; i++)
    {
      double s = nc - i;
      double k = PI*s*q;
      double l = 2.0*b*s*q;
      double sinc = sin(k)/k;
      double coef = (sinc*cos(b*k)) / (1.0 - l*l);
      filter.push_back(coef);
      j++;
    }
    filter.push_back(1.0);
    j++;

    for(int i = 0; i < c; i++)
    {
      double s = i;
      double k = PI*s*q;
      double l = 2.0*b*s*q;
      double sinc = sin(k)/k;
      double coef = (sinc*cos(b*k)) / (1.0 - l*l);
      filter.push_back(coef);
      j++;
    }
  
    return j;
  }

  template <>
  int filters<double>::rootRaisedCosineFilter(int c, int nc, int symbolLength, double q,  double b, std::vector<double>& filter)
  {
    int j = 0;
    double ts = 1.0 / sqrt(1.0 / (double) symbolLength );
    filter.clear();
    filter.reserve(c+nc+1);
    for(int i = 0; i < nc; i++)
    {
      double s = nc - i;
      double a = sin(PI*q*s*(1.0 - b));
      double b = 4.0*b*q*s*cos(PI*q*s*(1+b));
      double d = 4.0*b*q*s;
      double c = PI*q*s*(1.0 - d*d);
      double coef = (ts*(a+b)) / c;
      filter.push_back(coef);
      j++;
      
    }
    filter.push_back(ts*(1 - b + ((4.0*b) / PI)));
    j++;
    for(int i = 0; i < nc; i++)
    {
      double s = i;
      double a = sin(PI*q*s*(1.0 - b));
      double b = 4.0*b*q*s*cos(PI*q*s*(1+b));
      double d = 4.0*b*q*s;
      double c = PI*q*s*(1.0 - d*d);
      double coef = (ts*(a+b)) / c;
      filter.push_back(coef);
      j++; 
    }
  }

  template <>
  int filters<double>::boxCarFilter(int n, std::vector<double>& filter)
  {
    int j = 0;
    filter.clear();
    filter.reserve(n);
    for(int i = 0; i < n; i++)
    {
      filter.push_back(1.0);
      j++;
    }
    return j;
  }


};
