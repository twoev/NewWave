#include "NewWave/WaveletEvent.hh"

#include <cmath>

namespace NewWave {
  
  WaveletEvent::WaveletEvent(const RasterisedEvent &event,
                             const WaveletEngine &engine):
  _originalEvent(event),
  _rasterisedEvent(event),
  _engine(engine),
  _doInvert(false){}
  
  WaveletCoefficients &WaveletEvent::_coefficients()const{
    if(_coeffs.size() != 0) return _coeffs;
    _coeffs = _engine.transform(_rasterisedEvent.pixels());
    return _coeffs;
  }
  
  const WaveletCoefficients &WaveletEvent::coefficients()const{
    return _coefficients();
  }
  
  const RasterisedEvent &WaveletEvent::originalEvent()const{
    return _originalEvent;
  }
  
  const RasterisedEvent &WaveletEvent::rasterisedEvent()const{
    if(!_doInvert) return _rasterisedEvent;
    
    const PixelArray &pixels = _engine.inverseTransform(coefficients());
    _rasterisedEvent = RasterisedEvent(pixels, _rasterisedEvent.pixelDefinition());
    _doInvert = false;
    return _rasterisedEvent;
  }
  
  void WaveletEvent::denoise(double noiseThreshold){
    for(WaveletCoefficient &coeff: _coefficients()){
      if(fabs(coeff.value()) < noiseThreshold){
        coeff.setValue(0.);
        _doInvert = true;
      }
    }
  }
  
}

