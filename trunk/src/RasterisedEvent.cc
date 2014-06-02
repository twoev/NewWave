#include "NewWave/RasterisedEvent.hh"

namespace NewWave {
  
  RasterisedEvent::RasterisedEvent(const PixelArray &pixelArray,
                                   const PixelDefinition &pixelDefn):
  _pixelDefn(pixelDefn),
  _pixels(pixelArray){}
  
  void RasterisedEvent::addParticle(double rapidity, double phi, double pT){
    size_t ybin   = _pixelDefn.yPixelIndex(rapidity);
    size_t phiBin = _pixelDefn.phiPixelIndex(phi);
    _pixels[ybin][phiBin] += pT;
  }
  
  const PixelArray &RasterisedEvent::pixels()const{
    return _pixels;
  }
  
  const PixelDefinition &RasterisedEvent::pixelDefinition()const{
    return _pixelDefn;
  }
  
}

