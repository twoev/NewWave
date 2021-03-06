#include "NewWave/WaveletEvent.hh"
#include "HepMC/GenEvent.h"

namespace NewWave {
  
  template<>
  void WaveletEvent<HepMC::GenEvent*>::_init(HepMC::GenEvent* const &input){
    _originalParticles = input;
    
    for(HepMC::GenEvent::particle_const_iterator p=input->particles_begin();
        p != input->particles_end(); ++p){
      if((*p)->status() != 1) continue;
      
      double pz = (*p)->momentum().pz();
      double e = (*p)->momentum().e();
      
      double rapidity = 0.5 * log((e + pz) / (e-pz));
      if(_pixelDefn.covers(rapidity, (*p)->momentum().phi())){
        _addParticle(rapidity, (*p)->momentum().phi(), (*p)->momentum().perp());
      }
    }
    
    return;
  }
  
  
  HepMC::FourVector operator *(double r, HepMC::FourVector right){
    right.setPx(r*right.px());
    right.setPy(r*right.py());
    right.setPz(r*right.pz());
    right.setE(r*right.e());

    return right;
  }
  
  HepMC::FourVector operator *(HepMC::FourVector left, double r){
    return r*left;
  }
  
  template<>
  HepMC::GenEvent* const &WaveletEvent<HepMC::GenEvent *>::particles()const{
   
    if(!_doInvert) return _modifiedParticles;
    
    _ratio = pixels() / _originalPixels ;
    
    _modifiedParticles = new HepMC::GenEvent(*(_originalParticles));
    
    vector<HepMC::GenParticle *> toUpdate;
    
    for(HepMC::GenEvent::particle_const_iterator p=_modifiedParticles->particles_begin();
        p != _modifiedParticles->particles_end(); ++p){
    
      if((*p)->status() != 1) continue;
    
      (*p)->set_status(10);
      
      double pz = (*p)->momentum().pz();
      double e = (*p)->momentum().e();
      double rapidity = 0.5 * log((e + pz) / (e-pz));
      if(_pixelDefn.covers(rapidity, (*p)->momentum().phi())){
        
        size_t ybin   = _pixelDefn.yPixelIndex(rapidity);
        size_t phiBin = _pixelDefn.phiPixelIndex((*p)->momentum().phi());
        double ratio = _ratio.at(ybin).at(phiBin);
        if(ratio > 0){
        
          HepMC::GenVertex *vx = new HepMC::GenVertex();
          vx->add_particle_in(*p);
          HepMC::GenParticle *pOut = new HepMC::GenParticle(ratio*(*p)->momentum(),
                                                            (*p)->pdg_id(),
                                                            10,
                                                            (*p)->flow(),
                                                            (*p)->polarization());
          
          pOut->set_generated_mass(ratio * (*p)->generated_mass());
          
          toUpdate.push_back(pOut);
          vx->add_particle_out(pOut);
          _modifiedParticles->add_vertex(vx);
        }
      }
    }
    
    for(auto p: toUpdate){
      p->set_status(1);
    }
    
    _doInvert = false;
    
    return _modifiedParticles;
  }
  
}

