#ifndef NEWWAVE_RASTERISED_EVENT_HH
#define NEWWAVE_RASTERISED_EVENT_HH

#include "NewWave/PixelDefinition.hh"

namespace HepMC{
  class GenEvent;
}

namespace NewWave {
  
  /// A rasterised representation of the event
  
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
    template<typename T>
    RasterisedEvent(const vector<T> &inputParticles,
                    const PixelDefinition &pixelDefn):
    _pixelDefn(pixelDefn),
    _pixels(pixelDefn.makeEmptyPixelArray()){
      
      for(const T &p: inputParticles){
        addParticle(p);
      }
    }
    
    /// Constructor from an existing array of pixels
    /**
     *  \param pixelArray A 2-D array of pixel values
     *  \param pixelDefn The definition of the pixel dimensions
     */
    RasterisedEvent(const PixelArray &pixelArray,
                    const PixelDefinition &pixelDefn);
    
    /// Constructor from a HepMC GenEvent
    /**
     *  Constructor from a HepMC::GenEvent. Requires compiling against HepMC
     *
     *  \param event The HepMC GenEvent
     *  \param pixelDefn The definition of the pixel array
     */
    RasterisedEvent(const HepMC::GenEvent *event,
                    const PixelDefinition &pixelDefn);
    
    /// Return the array of pixel values
    /**
     *  \return the array of pixel values for this event
     */
    const PixelArray &pixels()const;
    
    /// Return the pixel array definition
    /**
     *  \return the definition in \f$\phi\f$ and rapidity
     */
    const PixelDefinition &pixelDefinition()const;
    
  private:
    
    PixelDefinition _pixelDefn;
    PixelArray _pixels;
    
    void addParticle(double rapidity, double phi, double pT);
    
    template<typename T>
    void addParticle(const T &particle){
      addParticle(particle.momentum().rapidity(),
                  particle.momentum().phi(),
                  particle.momentum().pT());
    }
    
  };
}

#endif
