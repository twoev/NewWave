#ifndef NEWWAVE_RASTERISED_EVENT_HH
#define NEWWAVE_RASTERISED_EVENT_HH

#include "NewWave/PixelDefinition.hh"

namespace HepMC{
  class GenEvent;
}

namespace NewWave {
  
  /// A rasterised representation of the event
  template<typename T>
  class RasterisedEvent{
    
  public:
    /// Generic Templated constructor on anything that could be a list of particles
    /**
     *  Templated constructor on anything that is a list of particles possesing
     *  a momentum method.  This would work with e.g. Rivet's Particle class
     *
     *  \param inputParticles a vector of input Particle types
     *  \param pixelDefn The defintion of the pixel array
     */
    RasterisedEvent(const T &inputParticles,
                    const PixelDefinition &pixelDefn):
    _pixelDefn(pixelDefn),
    _pixels(pixelDefn.makeEmptyPixelArray()){
      
      for(auto p: inputParticles){
//      for(typename T::const_iterator p = inputParticles.begin();
//          p != inputParticles.end(); ++p){
        addParticle(p);
      }
    }
    
    /// Constructor from an existing array of pixels
    /**
     *  \param pixelArray A 2-D array of pixel values
     *  \param pixelDefn The definition of the pixel dimensions
     */
    RasterisedEvent(const PixelArray &pixelArray,
                    const PixelDefinition &pixelDefn):
            _pixelDefn(pixelDefn),
            _pixels(pixelArray){}
    
    /// Constructor from a HepMC GenEvent
    /**
     *  Constructor from a HepMC::GenEvent. Requires compiling against HepMC
     *
     *  \param event The HepMC GenEvent
     *  \param pixelDefn The definition of the pixel array
     */
    RasterisedEvent(const HepMC::GenEvent *event,
                    const PixelDefinition &pixelDefn):
    _pixelDefn(pixelDefn),
    _pixels(pixelDefn.makeEmptyPixelArray()){
      _input = event;
      fillFromHepMC(event);
    }
    
    const T &inputParticles()const{return _input;}
    
    
    /// Return the array of pixel values
    /**
     *  \return the array of pixel values for this event
     */
    const PixelArray &pixels()const{return _pixels;}
    
    /// Return the pixel array definition
    /**
     *  \return the definition in \f$\phi\f$ and rapidity
     */
    const PixelDefinition &pixelDefinition()const{return _pixelDefn;}
    
  private:
    
    PixelDefinition _pixelDefn;
    PixelArray _pixels;
    
    T _input;
    
    void fillFromHepMC(const HepMC::GenEvent *event);
    
    void addParticle(double rapidity, double phi, double pT){
      size_t ybin   = _pixelDefn.yPixelIndex(rapidity);
      size_t phiBin = _pixelDefn.phiPixelIndex(phi);
      _pixels[ybin][phiBin] += pT;
    }
    
    template<typename P>
    void addParticle(const P &particle){
      addParticle(particle.momentum().rapidity(),
                  particle.momentum().phi(),
                  particle.momentum().pT());
    }
    
  };
}

#endif
