#include "NewWave/WaveletEvent.hh"

#include <cmath>

namespace NewWave {
  
  template<typename T>
  WaveletCoefficients &WaveletEvent<T>::_coefficients()const{
    if(_coeffs.size() != 0) return _coeffs;
    _coeffs = _engine.transform(_rasterisedEvent.pixels());
    return _coeffs;
  }
  
  template<typename T>
  const WaveletCoefficients &WaveletEvent<T>::coefficients()const{
    return _coefficients();
  }
  
  template<typename T>
  void WaveletEvent<T>::denoise(double noiseThreshold){
    for(WaveletCoefficient &coeff: _coefficients()){
      if(fabs(coeff.value()) < noiseThreshold){
        coeff.setValue(0.);
        _doInvert = true;
      }
    }
  }
  
}

