IDIR =../include
CXX = g++
CXXFLAGS=-I$(IDIR) -g -D_TEST -ftest-coverage -fprofile-arcs

ODIR=obj
LDIR=../lib

LIBS= -lgtest -lpthread -lgtest_main -lcurses --coverage -lgcov -lncurses -Wno-write-strings

_DEPS= Grafo.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= Main.o Grafo.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBS)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
