#include "NewWave/NewWave.hh"
#include "NewWave/GSLEngine.hh"

#include "HepMC/GenEvent.h"
#include "HepMC/IO_GenEvent.h"

#include <string>
#include <iostream>

int main(int argc, char **argv){
  
  if(argc < 2 || argc > 3){
    std::cout<<"Usage: NewWave-HepMC inputFile <outputFile>"<<std::endl;
    exit(2);
  }
  
  std::string inputFile(argv[1]);
  
  NewWave::PixelDefinition pixelDefn(128, 3.2);
  NewWave::WaveletEngine *waveletEngine = new NewWave::GSLEngine(gsl_wavelet_daubechies, 4, pixelDefn);

  
  HepMC::IO_GenEvent input(inputFile, std::ios::in);
  HepMC::GenEvent *event;
  input >> event;
  
  long count =0;
  long eventNumber=0;
  long incr = 1;
  
  while(event){
    ++eventNumber;
    ++count;
    
    if(count == incr){
      count = 0;
      std::cout<<"NewWave-HepMC event number: "<<eventNumber<<std::endl;
      if(eventNumber==10) incr=10;
      if(eventNumber==100) incr=100;
      if(eventNumber==1000) incr=1000;
    }
    
    NewWave::WaveletEvent<HepMC::GenEvent*> waveletEvent(event, pixelDefn, *waveletEngine);

    waveletEvent.denoise(HepMC::Units::conversion_factor(event->momentum_unit(), HepMC::Units::GEV));
    
    
    delete event;
    input >> event;
  }
  
}
