// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

#include "NewWave/NewWave.hh"
#include "NewWave/GSLEngine.hh"


namespace Rivet {


  class NewWave_Example : public Analysis {
  public:

    NewWave_Example()
      : Analysis("NewWave_Example"),
        _pixelDefn(NewWave::PixelDefinition(128, 3.2))
    {    }


  public:

    /// Book histograms and initialise projections before the run
    void init() {

      FinalState fs(-3.2, 3.2);
      addProjection(fs, "Particles");
      addProjection(FastJets(fs, FastJets::CAM, 1.2), "CAM12");
      
      _h_jetMass = bookHisto1D("JetMass", 200, 0., 200.*GeV);
      _h_denoisedJetMass = bookHisto1D("Denoised_JetMass", 200, 0., 200.*GeV);
      
      _waveletEngine = new NewWave::GSLEngine(gsl_wavelet_daubechies, 4, _pixelDefn);
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();

      const Particles &particles=applyProjection<FinalState>(event, "Particles").particles();
      NewWave::RasterisedEvent rasterised(particles, _pixelDefn);
      NewWave::WaveletEvent waveletEvent(rasterised, *_waveletEngine);
      
      waveletEvent.denoise(1.*GeV);
      
    }


    /// Normalise histograms etc., after the run
    void finalize() {


    }


  private:

    // This holds the definition of the pixel sizes and ranges.  Defined once at the start of the run
    NewWave::PixelDefinition _pixelDefn;
    
    // This holds the wavelet engine that does the transform
    // Since we don't know what this is, it is a pointer to the
    // WaveletEngine base class
    NewWave::WaveletEngine *_waveletEngine;
    
    Histo1DPtr _h_jetMass;
    Histo1DPtr _h_denoisedJetMass;

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(NewWave_Example);

}
