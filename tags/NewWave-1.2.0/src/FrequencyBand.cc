#include "NewWave/FrequencyBand.hh"
#include "NewWave/Exceptions.hh"
#include <cmath>

namespace NewWave{
  
  FrequencyBand::FrequencyBand(int yLevel, int phiLevel):_yLevel(yLevel), _phiLevel(phiLevel), _rms(-1.){
    int nY = (_yLevel==0)? 1: pow(2, _yLevel-1);
    int nPhi = (_phiLevel==0)? 1: pow(2, _phiLevel-1);
    _nCoeffs = nY * nPhi;
  }
  
  const WaveletCoefficients & FrequencyBand::coefficients()const{
    if(_coefficients.size() != _nCoeffs) throw InvalidFrequencyBand();
    return _coefficients;
  }
  
  void FrequencyBand::addCoefficient(const WaveletCoefficient &coeff){
    if(_coefficients.size() == _nCoeffs) throw InvalidFrequencyBand();
    if(coeff.yLevel() != _yLevel || coeff.phiLevel() != _phiLevel) throw WrongCoefficient(coeff.yLevel(), coeff.phiLevel(), _yLevel, _phiLevel);
    _coefficients.push_back(coeff);
    return;
  }
  
  double FrequencyBand::rms()const{
    
    if(_rms > 0.) return _rms;
    
    _rms=0.;
    
    for(const auto &c: coefficients()){
      _rms += c.value() * c.value();
    }
    
    _rms /= ((double)_nCoeffs);
    _rms = sqrt(_rms);
    
    return _rms;
  }
  
  int FrequencyBand::yLevel()const{
    return _yLevel;
  }
  
  int FrequencyBand::phiLevel()const{
    return _phiLevel;
  }
  
}
