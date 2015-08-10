#include "NewWave/WaveletCoefficient.hh"
#include "NewWave/Exceptions.hh"
#include "NewWave/FrequencyBand.hh"

namespace NewWave {
  
  WaveletCoefficient::WaveletCoefficient(size_t yLevel,
                                         size_t phiLevel,
                                         size_t key,
                                         double value):
  _value(value),
  _yLevel(yLevel), _phiLevel(phiLevel),
  _key(key),
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

