#include "NewWave/WaveletEvent.hh"

#include <cmath>

namespace NewWave {
  
  
  template<typename T>
  const WaveletCoefficients &WaveletEvent<T>::coefficients()const{
    return _coefficients();
  }
  
}

