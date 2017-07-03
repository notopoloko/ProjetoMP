IDIR =../Include
CXX=g++
CXXFLAGS=-I$(IDIR) -g -D_TEST -ftest-coverage -fprofile-arcs

ODIR=../OBJ
LDIR=../LIB

LIBS= -lgtest -lpthread -lgtest_main -lcurses --coverage -lgcov

_DEPS= Grafo.h
DEPS= $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o RedeSocial.o
OBJ= $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
