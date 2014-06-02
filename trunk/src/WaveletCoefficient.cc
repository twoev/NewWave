#include "NewWave/WaveletCoefficient.hh"

namespace NewWave {
  
  WaveletCoefficient::WaveletCoefficient(size_t yLevel,
                                         size_t phiLevel,
                                         double value):
  _value(value), _yLevel(yLevel), _phiLevel(phiLevel){}
  
  double WaveletCoefficient::value()const{
    return _value;
  }
  
  size_t WaveletCoefficient::yLevel()const{
    return _yLevel;
  }
  
  size_t WaveletCoefficient::phiLevel()const{
    return _phiLevel;
  }
  
  void WaveletCoefficient::setValue(double val){
    _value = val;
    return;
  }
  
}

