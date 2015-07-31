# The GACODE_ROOT environmental variable should point to the root directory where GACODE is installed.
# Environment variable GACODE_PLATFORM should be set to one of the following systems:
#   ALCF_BGP ALCF_CETUS BABBAGE BANACH CAOS CARVER CMODWS DELPHI
#   DROP EDISON_CRAY EDISON_INTEL FT GFORTRAN_CORE2 GFORTRAN_OSX
#   GFORTRAN_OSX_64 GFORTRAN_OSX_BELLI GFORTRAN_OSX_MACPORTS
#   GFORTRAN_OSX_TECHX GFORTRAN_PENRYN GFORTRAN_TECHX HOPPER_CRAY
#   HOPPER_INTEL HPC_ITER IFORT_CORE2 IFORT_PENRYN JAC LINDGREN
#   LOHAN LOKI LOKI_SCRATCH METIUS NEWT OSX_MOUNTAINLION PACER
#   PGFORTRAN_OSX PG_OPT64 PG_OPT64_FFTW PG_OPT64_MUMPS PPPL
#   PPPL_PATHSCALE RANGER SATURN TITAN_CRAY VENUS

ifdef GACODE_ROOT
	include ${GACODE_ROOT}/shared/install/make.inc.${GACODE_PLATFORM}
else
	CC=cc
	CFLAGS=
	FC=gfortran
	FFLAGS=
	ARCH=ar cr
endif

LLIB=harvest_lib

EXEC = lib clientC clientF

OBJECTS = harvest_lib.o harvest_clientC.o harvest_clientF.o

lib: harvest_lib.o Makefile
	$(ARCH) $(LLIB).a harvest_lib.o

clientC : lib harvest_client.c
	$(CC) $(CFLAGS) -o clientC harvest_lib.o harvest_client.c

clientF : lib harvest_client.f90
	$(FC) $(FFLAGS) -o clientF harvest_lib.o harvest_client.f90

all: $(EXEC)

clean:
	rm -f *.o $(LLIB).a $(EXEC)

gacode_install: all
	mkdir ${GACODE_ROOT}/shared/harvest_client
	cp -f Makefile harvest_lib.c harvest_lib.h ${GACODE_ROOT}/shared/harvest_client/