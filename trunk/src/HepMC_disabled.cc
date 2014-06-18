#include "NewWave/RasterisedEvent.hh"
#include "NewWave/WaveletEvent.hh"

#include "NewWave/Exceptions.hh"

namespace NewWave{
  
  template<>
  RasterisedEvent<HepMC::GenEvent*>::RasterisedEvent(HepMC::GenEvent* const &event,
                                                     const PixelDefinition &pixelDefn):
  _pixelDefn(pixelDefn),
  _pixels(pixelDefn.makeEmptyPixelArray()){
    throw NotCompiledException("HepMC");
  }
  
  template<>
  HepMC::GenEvent* const &WaveletEvent<HepMC::GenEvent *>::particles()const{
    
    throw NotCompiledException("HepMC");
  }
  
}
