# --- create shared object lib_iri.so ---
# ifor -fPIC -c *.for
# ld -shared -o ~/MY_LD/lib.so *.o
#
# --- to create executable from shared object using .c as main driven ---
# icc -c c_plot.c
# icc -o iri_so ~/MY_LD/lib_iri.so c_plot.o -lifcore

# specify the Fortran compiler and flag here
FC = ifort
FLAGS =
PIC_FLAGS = -fPIC 

# specify source codes
sources = iritest.for irisub.for irifun.for iritec.for iridreg.for igrf.for cira.for iriflip.for
objects = $(sources:.for=.o)

# rule to create the shared object
executable = run_so
LDFLAGS = -shared   # linking flags
TARGET_LIB = ~/MY_LD/lib_iri.so
$(executable): $(objects)
	ld $(LDFLAGS) $(objects) -o $(TARGET_LIB)

# rule to compile source files
%.o: %.for
	$(FC) $(PIC_FLAGS) $(FLAGS) -c $<

# Clean target
clean:
	rm -f $(objects) $(executable)

