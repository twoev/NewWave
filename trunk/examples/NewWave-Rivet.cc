// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Projections/FastJets.hh"

#include "NewWave/NewWave.hh"
#include "NewWave/GSLEngine.hh"


namespace Rivet {

  /// Example Rivet analysis using NewWave
  class NewWave_Example : public Analysis {
  public:

    NewWave_Example()
      : Analysis("NewWave_Example"),
        _pixelDefn(NewWave::PixelDefinition(128, 3.2)),
        _uncachedJetProjection(FastJets::CAM, 1.2)
    {    }


  public:

    /// Book histograms and initialise projections before the run
    void init() {

      FinalState fs(-4., 4.);
      addProjection(fs, "Particles");
      addProjection(FastJets(fs, FastJets::CAM, 1.2), "CAM12");
      
      _h_jetMass = bookHisto1D("JetMass", 200, 0., 200.*GeV);
      _h_denoisedJetMass = bookHisto1D("Denoised_JetMass", 200, 0., 200.*GeV);
      
      _waveletEngine = new NewWave::GSLEngine(gsl_wavelet_daubechies, 4, _pixelDefn);
    }


    /// Perform the per-event analysis
    void analyze(const Event& event) {
      const double weight = event.weight();

      Jets jets = applyProjection<FastJets>(event, "CAM12").jetsByPt(150.*GeV);

      // this saves doing the wavelet transform if we have no high pT jets
      // If there is a lot of pile up then the cut of 180 GeV may need to be lowered
      if(jets.size()==0) vetoEvent;
      
      for(const Jet &jet: jets){
        if(fabs(jet.momentum().rapidity()) < 2. &&
           jet.momentum().perp() > 300.*GeV){
          _h_jetMass->fill(jet.momentum().mass(), weight);
        }
      }
      
      const Particles &particles=applyProjection<FinalState>(event, "Particles").particles();
      NewWave::WaveletEvent<Particles> waveletEvent(particles, _pixelDefn, *_waveletEngine);
      
      waveletEvent.denoise(1.*GeV);
      
      const Particles &denoisedParticles = waveletEvent.particles();
      
      _uncachedJetProjection.calc(denoisedParticles);
      const Jets &filteredJets = _uncachedJetProjection.jetsByPt(300.*GeV);
      
      for(const Jet &jet: filteredJets){
        if(fabs(jet.momentum().rapidity()) < 2.){
          _h_denoisedJetMass->fill(jet.momentum().mass(), weight);
        }
      }
      
    }


    /// Normalise histograms etc., after the run
    void finalize() {

      scale(_h_jetMass, crossSection() / sumOfWeights());
      scale(_h_denoisedJetMass, crossSection() / sumOfWeights());

    }


  private:

    // This holds the definition of the pixel sizes and ranges.  Defined once at the start of the run
    NewWave::PixelDefinition _pixelDefn;
    
    // This holds the wavelet engine that does the transform
    // Since we don't know what this is, it is a pointer to the
    // WaveletEngine base class
    NewWave::WaveletEngine *_waveletEngine;
    
    // Fastjets projection not booked through the projection system
    // This runs on the local copy of the modified particles
    FastJets _uncachedJetProjection;
    
    Histo1DPtr _h_jetMass;
    Histo1DPtr _h_denoisedJetMass;

  };



  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(NewWave_Example);

}
