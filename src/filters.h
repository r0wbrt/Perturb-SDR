namespace perturb 
{
  template <class T>
  class filters
  {
    public:
      int hilbertFilter(int c, int nc, std::vector<T>& filter);
      int sincFilter(int c, int nc, double b, std::vector<T>& filter);
      int raisedCosineFilter(int n, int T, double Beta, std::vector<T>& filter);
      int raisedCosineFilter_Length(int n, int T, double Beta);
  };

};
