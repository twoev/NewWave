#include "NewWave/RasterisedEvent.hh"
#include "NewWave/WaveletEvent.hh"

#include "HepMC/GenEvent.h"

namespace NewWave {
  
  template<>
  RasterisedEvent<HepMC::GenEvent*>::RasterisedEvent(HepMC::GenEvent* const &event,
                                                     const PixelDefinition &pixelDefn):
  _pixelDefn(pixelDefn),
  _pixels(pixelDefn.makeEmptyPixelArray()){
    
    _input = event;
    for(HepMC::GenEvent::particle_const_iterator p=event->particles_begin();
        p != event->particles_end(); ++p){
      if((*p)->status() != 1) continue;
      
      double pz = (*p)->momentum().pz();
      double e = (*p)->momentum().e();
      
      double rapidity = 0.5 * log((e + pz) / (e-pz));
      if(_pixelDefn.covers(rapidity, (*p)->momentum().phi())){
        addParticle(rapidity, (*p)->momentum().phi(), (*p)->momentum().perp());
      }
    }
    
  }

  template<>
  HepMC::GenEvent* const &WaveletEvent<HepMC::GenEvent *>::particles()const{
   
    return _originalEvent.inputParticles();
  }
  
  
  
}

