#include "NewWave/WaveletCoefficient.hh"

namespace NewWave {
  
  WaveletCoefficient::WaveletCoefficient(size_t yLevel,
                                         size_t phiLevel,
                                         size_t key,
                                         double value):
  _value(value),
  _yLevel(yLevel), _phiLevel(phiLevel),
  _key(key){}
  
  double WaveletCoefficient::value()const{
    return _value;
  }
  
  size_t WaveletCoefficient::key()const{
    return _key;
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

