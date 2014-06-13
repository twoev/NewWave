SUBDIRS = .

lib_LTLIBRARIES = libNewWave.la

libNewWave_la_SOURCES = PixelDefinition.cc    \
                        WaveletCoefficient.cc \
                        WaveletEvent.cc

libNewWave_la_CPPFLAGS  = $(AM_CPPFLAGS)
libNewWave_la_LDFLAGS   = $(AM_LDFLAGS)

if ENABLE_GSL

libNewWave_la_CPPFLAGS  +=  $(GSLCPPFLAGS)
libNewWave_la_LDFLAGS   +=  $(GSLLIBS)
libNewWave_la_SOURCES   +=  GSLEngine.cc

endif

if ENABLE_HEPMC

libNewWave_la_CPPFLAGS  += $(HEPMC_CPPFLAGS)
libNewWave_la_LDFLAGS   += $(HEPMC_LDFLAGS)
libNewWave_la_SOURCES   +=  HepMC_enabled.cc

else

libNewWave_la_SOURCES   +=  HepMC_disabled.cc

endif



