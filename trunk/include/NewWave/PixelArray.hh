#ifndef NEWWAVE_PIXEL_ARRAY_HH
#define NEWWAVE_PIXEL_ARRAY_HH

#include <cassert>
#include <vector>

namespace NewWave{
  using std::vector;
  
  class PixelRow{
    
  public:
    
    PixelRow(){
      
    }
    
    PixelRow(size_t length): _data(length, 0.), _isEmpty(length, true){
      
    }
    
    void push_back(double pixel){
      _data.push_back(pixel);
      _isEmpty.push_back(false);
      return;
    }
    
    const double & at(size_t index) const {return _data.at(index);}
    double & at(size_t index) {return _data.at(index);}
    
    void clear(){
      _data.clear();
      _isEmpty.clear();
      return;
    }
    
    size_t size()const {return _data.size();}
    
    vector<double>::const_iterator begin()const{ return _data.begin();}
    vector<double>::const_iterator end()const{ return _data.end();}
    
    friend PixelRow operator / (PixelRow left, const PixelRow &right);
    
  private:
    
    vector<double> _data;
    vector<bool> _isEmpty;
    
  };
  
  /// Divide each pixel in a row by another row
  /**
   *  The PixelRow contains a vector<double> of pixel values, plus an
   *  additional vector<bool> recording whether each pixel has been
   *  filled.  This allows the divide by zero error to be avoided
   *  because those pixels that have not been filled can be ignored
   */
  inline PixelRow operator / (PixelRow left, const PixelRow &right){
   
    assert(left._data.size() == right._data.size());
    
    for(size_t ii=0; ii != left._data.size(); ++ii){
      if(left._isEmpty[ii]) continue;
      left._data[ii] /= right._data[ii];
    }
    
    return left;
  }
  
  typedef vector<PixelRow> PixelArray;
}

#endif
