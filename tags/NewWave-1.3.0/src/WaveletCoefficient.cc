#include "NewWave/WaveletCoefficient.hh"
#include "NewWave/Exceptions.hh"
#include "NewWave/FrequencyBand.hh"

namespace NewWave {
  
  WaveletCoefficient::WaveletCoefficient(size_t yLevel,
                                         size_t phiLevel,
                                         size_t key,
                                         bool smoothing,
                                         double yMin, double yMax,
                                         double phiMin, double phiMax,
                                         double value):
  _value(value),
  _yLevel(yLevel), _phiLevel(phiLevel),
  _key(key),
  _isSmoothing(smoothing),
  _yMin(yMin),   _phiMin(phiMin),
  _yMax(yMax), _phiMax(phiMax),
  _haveYCentre(false), _havePhiCentre(false),
  _event(0){}
  
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
  
  bool WaveletCoefficient::isSmoothing()const{
    return _isSmoothing;
  }
  
  double WaveletCoefficient::yMin()const{
    return _yMin;
  }

  double WaveletCoefficient::yMax()const{
    return _yMax;
  }
  
  double WaveletCoefficient::yCentre()const{
    if(_haveYCentre) return _yCentre;
    
    _yCentre = 0.5 *(yMin() + yMax());
    _haveYCentre = true;
    return _yCentre;
  }
  
  double WaveletCoefficient::phiMin()const{
    return _phiMin;
  }
  
  double WaveletCoefficient::phiMax()const{
    return _phiMax;
  }
  
  double WaveletCoefficient::phiCentre()const{
    if(_havePhiCentre) return _phiCentre;
    
    _phiCentre = 0.5 *(phiMin() + phiMax());
    _havePhiCentre = true;
    return _phiCentre;
  }
  
  void WaveletCoefficient::setValue(double val){
    _value = val;
    return;
  }
  
  int WaveletCoefficient::frequencyHash(int nLevels)const{
    return phiLevel() + (nLevels + 1) * yLevel();
  }

  int WaveletCoefficient::frequencyHash()const{
    if(_event ==0) throw NullEvent();
    
    return frequencyHash(_event->pixelDefn().nLevels());
  }
  
  const FrequencyBand &WaveletCoefficient::frequencyBand()const{
    return _event->frequencyBand(*this);
  }
  
}

