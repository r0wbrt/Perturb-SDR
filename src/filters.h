#include "perturb.h"
#include <vector>

namespace perturb 
{
  template <class T>
  class filters
  {
    public:
      int hilbertFilter(int c, int nc, std::vector<T>& filter);
      int sincFilter(int c, int nc, double b, std::vector<T>& filter);
      int raisedCosineFilter(int c, int nc, double q, double b, std::vector<T>& filter);
      int rootRaisedCosineFilter(int c, int nc, int symbolLength, double q,  double b, std::vector<T>& filter);
      int boxCarFilter(int n, std::vector<T>& filter);
      
  };

};
