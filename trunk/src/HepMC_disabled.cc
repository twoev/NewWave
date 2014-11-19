#include "NewWave/WaveletEvent.hh"

#include "NewWave/Exceptions.hh"

namespace NewWave{

  template<>
  HepMC::GenEvent* const &WaveletEvent<HepMC::GenEvent *>::particles()const{
    
    throw NotCompiledException("HepMC");
  }
  
  template<>
  void WaveletEvent<HepMC::GenEvent*>::_init(HepMC::GenEvent* const &input){
    throw NotCompiledException("HepMC");
  }
  
}
