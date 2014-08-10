AC_PREREQ(2.59)

AC_INIT( [NewWave], [1.0.0], [jmonk@cern.ch], [NewWave])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([src/WaveletCoefficient.cc])
AC_CONFIG_HEADERS([config/config.h])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST(LT_OBJDIR)
AC_LANG(C++)

AC_LANG(C++)
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AM_PROG_CC_C_O

## Doxygen

DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([NewWave],, [doc])

# lib suffix differs on OS X
AC_DEFINE_DYNAMIC_LIBS

# Do we have and LCG tag, AFS area.
# Can user-define the LCG tag for annoying cases (CENT OS!)

AC_ARG_WITH([LCGTag],
  [AC_HELP_STRING([--with-LCGTag], [Specify the LCG tag (default=auto detect)])],
  [auto_lcg=no], [auto_lcg=yes])

AS_IF([test x$auto_lcg == xno],
    [LCG_TAG=$with_LCGTag],
    [LCG_TAG=no]
    )

AC_SEARCH_LCG

## GNU Scientific Library

AC_ARG_WITH([gsl],
  [AC_HELP_STRING([--with-gsl], [enable the GNU Scientific Library (GSL) (default enabled) and give the GSL install location])],
  )
  
AS_IF([test x$with_gsl != xno],
    [AC_SEARCH_GSL([enable_gsl=yes],
      [AS_IF( [test x$with_gsl = x], [enable_gsl=no],[AC_MSG_ERROR([GSL requested but not found!!])])])],
    [enable_gsl=no])

if test x$enable_gsl = xyes; then
  AC_MSG_NOTICE([Building with GSL])
else
    
  AC_MSG_NOTICE([*** Not building with GSL - GSL wavelets will be disabled!! ***])
fi

AM_CONDITIONAL(ENABLE_GSL, [test x$enable_gsl = xyes])

## HepMC

AC_ARG_WITH([HepMC],
  [AC_HELP_STRING([--with-HepMC], [enable HepMC and give the installation location (=no to disable)])],
  )

AS_IF([test x$with_HepMC != xno],
    [AC_SEARCH_HEPMC([enable_HepMC=yes],
      [AS_IF( [test x$with_HepMC = x], [enable_HepMC=no], [AC_MSG_ERROR([HepMC package requested but not found!!])])])],
    [enable_HepMC=no])

if test x$enable_HepMC = xyes; then
  AC_MSG_NOTICE([Building with HepMC])
else
  AC_MSG_NOTICE([*** Not building with HepMC - use with HepMC events will be disabled!! ***])
fi

AM_CONDITIONAL(ENABLE_HEPMC, [test x$enable_HepMC = xyes])

AM_CXXFLAGS="$AM_CXXFLAGS -Wall -O2"
AM_CPPFLAGS="$AM_CPPFLAGS -Wall -O2 -I\$(top_builddir)/ -I\$(top_builddir)/include $BOOST_CPPFLAGS"
AC_SUBST(AM_CXXFLAGS)
AC_SUBST(AM_CPPFLAGS)

AC_CONFIG_FILES([ Makefile
                  doc/Makefile
                  src/Makefile
                  include/Makefile
                  include/NewWave/Makefile ])

AC_OUTPUT
