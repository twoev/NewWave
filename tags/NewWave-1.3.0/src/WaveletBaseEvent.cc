#include "NewWave/WaveletBaseEvent.hh"
#include "NewWave/WaveletCoefficient.hh"

namespace NewWave{
  
  void WaveletBaseEvent::setEvent(WaveletCoefficient &coeff)const{
    coeff._event = this;
    return;
  }
  
}
