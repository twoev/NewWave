#include "NewWave/NewWave.hh"
#include "NewWave/GSLEngine.hh"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"

#include <string>
#include <fstream>
#include <iostream>

#include <memory>

/// alias for a shared pointer to a HepMC IO_GenEvent
typedef std::shared_ptr<HepMC::IO_GenEvent> ioPtr;

ioPtr inStream(const std::string &inputName);

ioPtr outStream(const std::string &outputName);

////////////////////////////////////////////////////////////////////////
/// Main loop over input HepMC file
int main(int argc, char **argv){
  
  if(argc < 2 || argc > 3){
    std::cout<<"Usage: NewWave-HepMC inputFile <outputFile>"<<std::endl;
    exit(2);
  }
  
  ioPtr input = inStream(argv[1]);
  ioPtr output = (argc==2)? outStream("-") : outStream(argv[2]);
  
  HepMC::GenEvent *event;
  
  // define the dimensions of the pixels for rasterisation
  NewWave::PixelDefinition pixelDefn(128, 3.2);
  // Create an engine for doing the wavelet transform, in this case using GSL
  NewWave::WaveletEngine *waveletEngine = new NewWave::GSLEngine(gsl_wavelet_daubechies, 4, pixelDefn);
  
  *input >> event;
  
  long count =0;
  long eventNumber=0;
  long incr = 1;
  
  while(event){
    ++eventNumber;
    ++count;
    
    if(count == incr){
      count = 0;
      std::cerr<<"NewWave-HepMC event number: "<<eventNumber<<std::endl;
      if(eventNumber==10) incr=10;
      if(eventNumber==100) incr=100;
      if(eventNumber==1000) incr=1000;
    }
    
    // Create a version of the event in the wavelet domain using the earlier pixel definition and wavelet engine.
    NewWave::WaveletEvent<HepMC::GenEvent*> waveletEvent(event, pixelDefn, *waveletEngine);

    // Can denoise the event in the wavelet domain.  Note the conversion factor to 1 GeV from HepMC.
    waveletEvent.denoise(HepMC::Units::conversion_factor(event->momentum_unit(), HepMC::Units::GEV));
    
    HepMC::GenEvent *denoisedevent = waveletEvent.particles();
    
    *output << denoisedevent;
    
    delete denoisedevent;
    delete event;
    
    *input >> event;
  }
  
} // End of main loop


////////////////////////////////////////////////////////////////////////
ioPtr inStream(const std::string &inputName){
  
  HepMC::IO_GenEvent *ptr;
  
  if(inputName=="-"){
    ptr = new HepMC::IO_GenEvent(std::cin);
  }else{
    ptr = new HepMC::IO_GenEvent(inputName, std::ios::in);
  }
  
  return ioPtr(ptr);
}

////////////////////////////////////////////////////////////////////////

ioPtr outStream(const std::string &outputName){
  
  HepMC::IO_GenEvent *ptr;
  
  if(outputName=="-"){
    ptr = new HepMC::IO_GenEvent(std::cout);
  }else{
    ptr = new HepMC::IO_GenEvent(outputName, std::ios::out);
  }
  
  return ioPtr(ptr);
}

