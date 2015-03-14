#include <iostream>
#include <complex>
#include <math.h>

std::complex<double> genWave()
{
  static double pi = 0;
  static double acc = 2.85599;
 // acc += 10E-3;
  pi += acc;
  if(pi > 6.283185)
  {
    pi -= 6.283185;
  }

  if(pi < 0)
    pi += 6.283185;

//std::cout << pi << std::endl;
  std::complex<double> ret(cos(pi), sin(pi));
  return ret;
  
}

std::complex<double> loWave(double k, double phase)
{
  static double pi = 0;
  static double acc = 0;

  if(phase > 3.14159)
    phase = 3.14159;
  else if(phase < -3.14159)
    phase = -3.14159;

  acc += k;
  
  if(acc > 3.14159)
    acc = 3.14159;
  else if(acc < -3.14159)
    acc = -3.14159;

  pi += acc + phase;

  
  if(pi < 0)
    pi += 6.283185;

  if(pi > 6.283185)
    pi -= 6.283185;

//std::cout << pi << std::endl;
  std::complex<double> ret(cos(pi), sin(pi));

  return ret;

}


int main()
{
 
  double pastA = 0;
  double pastL = 0; 
  double k = 0;
  double l = 0;
  bool frequencyLocked = false;
  for(int i = 0; i < 130; i++)
  {


    double alienW = arg(genWave());
    double alienWdx = (alienW - pastA);
    pastA = alienW;
    if(alienWdx < -3.14159)
      alienWdx += 2*3.14159;
    else if(alienWdx > 3.14159)
      alienWdx -= 2*3.14159;

    double low = arg(loWave(k, l));
    double lowdx = (low - pastL);
    pastL = low;

    if(lowdx < -3.14159)
      lowdx += 2*3.14159;
    else if(lowdx > 3.14159)
      lowdx -= 2*3.14159;

    double err = (alienWdx - lowdx);
    double perr = (pastA - low);  




    if(perr < -3.14159)
      perr += 2*3.14159;
    else if(perr > 3.14159)
      perr -= 2*3.14159;

    

    std::cout << i << " " << ", " << err << ", " << perr << std::endl;



    if(frequencyLocked == true)
    {
     // k = err*.01 + k*.99;
      l = perr*.6;
      
    } else {
      l = 0;
      k = (err)*.6;
      if(fabs(k) < 10E-4 && i > 10)
      {
       // std::cout << "Locked!" << std::endl;
        frequencyLocked = true;
        k = 0;
      }
    }
    

    
  }



  return 0;
}
