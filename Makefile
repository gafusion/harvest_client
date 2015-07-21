include ${GACODE_ROOT}/shared/install/make.inc.${GACODE_PLATFORM}

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