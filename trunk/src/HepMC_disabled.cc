#include "NewWave/RasterisedEvent.hh"
#include "NewWave/Exceptions.hh"

namespace NewWave{
  
  RasterisedEvent::RasterisedEvent(const HepMC::GenEvent *event,
                                   const PixelDefinition &pixelDefn):
  _pixelDefn(pixelDefn),
  _pixels(pixelDefn.makeEmptyPixelArray()){
    throw NotCompiledException("HepMC");
  }
  
}
