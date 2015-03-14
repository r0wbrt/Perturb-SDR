/*
 * DATE     3/5/2015
 * AUTHOR   Robert C. Taylor
 * PURPOSE  To test the boxCarFilter fir filter.
 */

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "perturb.h"
#include "filters/boxCarFilter.h"


#define output(b) sqrt(std::norm(b.getOutput()))


int main() 
{
  perturb::boxCarFilter<double> boxCar(10);
  
  assert(boxCar.getNumberOfTaps()==10);
  assert(output(boxCar)==0);
  
  for(int i = 0; i < 10; i++)
  {
    boxCar.pushSample(1);
  }

  double k = fabs(1- output(boxCar));
  assert(k < 10E-2);

  boxCar.resizeFilter(12);

  double l = fabs(0.8333-output(boxCar));
  assert(boxCar.getNumberOfTaps()==12);
  assert(l < 10E-2);

  boxCar.pushSample(1);

  double m = fabs(0.916-output(boxCar));
  assert(m < 10E-2);

  boxCar.pushSample(2);
  boxCar.resizeFilter(5);
  double n = fabs(1.2 - output(boxCar));
  assert(boxCar.getNumberOfTaps()==5);
  assert(n < 10E-2);
 
  boxCar.reset();
  assert(boxCar.getNumberOfTaps()==5);
  assert(output(boxCar) == 0);
  boxCar.pushSample(.25);
  double o = fabs(.05 - output(boxCar));
  assert(o < 10E-2);

  boxCar.pushSample(3);  // 1.6
  assert(fabs(.6 - output(boxCar)) < 10E-2);
  boxCar.pushSample(4); //2.2
  assert(fabs(1.4 - output(boxCar)) < 10E-2);
  boxCar.pushSample(5); //3
  assert(fabs(2.4 - output(boxCar)) < 10E-2);
  boxCar.pushSample(6);  // 4
  assert(fabs(3.6 - output(boxCar)) < 10E-2);
  boxCar.pushSample(7);  //5
  assert(fabs(5.0 - output(boxCar)) < 10E-2);
  boxCar.pushSample(8);  //6
  assert(fabs(6.0 - output(boxCar)) < 10E-2);
  boxCar.pushSample(20);  //6
  assert(fabs(9.2 - output(boxCar)) < 10E-2);

  boxCar.resizeFilter(5);
  double p = fabs(9.2 - output(boxCar));
  assert(boxCar.getNumberOfTaps()==5);
  assert(n < 10E-2);

  boxCar.resizeFilter(4);
  double  q = fabs(10.25 - output(boxCar));
  assert(boxCar.getNumberOfTaps()==4);
  assert(q < 10E-2);


  return 0;
}
