#include "NewWave/RasterisedEvent.hh"

#include "HepMC/GenEvent.h"

namespace NewWave {
  
  template<typename T>
  void RasterisedEvent<T>::fillFromHepMC(const HepMC::GenEvent *event){
    for(HepMC::GenEvent::particle_const_iterator p=event->particles_begin();
        p != event->particles_end(); ++p){
      if((*p)->status() != 1) continue;
      
      double pz = (*p)->momentum().pz();
      double e = (*p)->momentum().e();
      
      double rapidity = 0.5 * log((e + pz) / (e-pz));
      
      addParticle(rapidity, (*p)->momentum().phi(), (*p)->momentum().perp());
    }
    
  }
  
}

