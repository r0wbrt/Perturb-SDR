#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "perturb.h"
#include "simple/simpleFrequencyLocker.h"


#define paramCheck(A, b, c) do { assert(A.getGain() == b); assert(A.getFeedback() == c); } while(1==0)
#define outputCheck(A, b, c, d)  do { double k = fabs(b -  sfl.inputSample(std::complex<double>c, std::complex<double>d)); assert(k < 10E-2); } while(1==0)


int main()
{
  perturb::simpleFrequencyLocker<double> sfl;
  double test = 0;
  paramCheck(sfl, .6, 0);
  outputCheck(sfl, 0.942477, (1,0), (0,1));

  sfl.reset();
  paramCheck(sfl, .6, 0.0);

  outputCheck(sfl, 0.942477, (0,0), (0,1));
  outputCheck(sfl, 1.8846, (0,0), (0, -1));
  outputCheck(sfl, 0.942477, (0,0), (1, 0));

  sfl.setFeedback(.1);
  paramCheck(sfl, .6, 0.1);
  outputCheck(sfl, 0.942477+0.15705, (0,0), (0, 1));

  sfl.setGain(.3);
  paramCheck(sfl, .3, 0.1);
  outputCheck(sfl, 0.47115 + .1*1.099527, (0,0), (-1, 0));



  sfl.setFeedback(0.0);
  sfl.setGain(.6);
  paramCheck(sfl, .6, 0.0);
  sfl.reset();
  paramCheck(sfl, .6, 0.0);

  outputCheck(sfl, -0.942477, (0,1), (0,0));
  outputCheck(sfl, -1.8846, (0,-1), (0, 0));
  outputCheck(sfl, -0.942477, (1,0), (0, 0));

  sfl.setFeedback(.1);
  paramCheck(sfl, .6, 0.1);
  outputCheck(sfl, -(0.942477+0.15705), (0,1), (0, 0));

  sfl.setGain(.3);
  paramCheck(sfl, .3, 0.1);
  outputCheck(sfl, -(0.47115 + .1*1.099527), (-1,0), (0, 0));

  sfl.setFeedback(0.0);
  sfl.setGain(.6);
  paramCheck(sfl, .6, 0.0);
  sfl.reset();
  paramCheck(sfl, .6, 0.0);

  //0.707106781  

  

  




  return 0;
}
