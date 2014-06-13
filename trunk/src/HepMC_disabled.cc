#include "NewWave/RasterisedEvent.hh"
#include "NewWave/Exceptions.hh"

namespace NewWave{
  
  template<typename T>
  void RasterisedEvent<T>::fillFromHepMC(const HepMC::GenEvent *event){
    throw NotCompiledException("HepMC");
  }
  
}
