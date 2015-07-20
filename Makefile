include ${GACODE_ROOT}/shared/install/make.inc.${GACODE_PLATFORM}

LLIB=GADB_lib

EXEC = clientC \
       clientF

OBJECTS = send2DB.o \
          gadb_clientC.o \
          gadb_clientF.o

.SUFFIXES : .o .c

lib: send2DB.o Makefile
	$(ARCH) $(LLIB).a send2DB.o

.c.o : *.c Makefile
	$(CC) $(CFLAGS) -c $<

gadb_clientF.o : gadb_clientF.f90 Makefile
	$(FC) $(FFLAGS) -c $<

all: $(OBJECTS) Makefile
	$(CC) $(CFLAGS) -o clientC send2DB.o gadb_clientC.o
	$(FC) $(FFLAGS) -o clientF send2DB.o gadb_clientF.o

clean:
	rm -f *.o $(LLIB).a $(EXEC)

gacode_install: all
	cp -f Makefile send2DB.c send2DB.h ${GACODE_ROOT}/shared/gadb/