IDIR =../Include
CXX = g++
CXXFLAGS=-I$(IDIR) -g -D_TEST -ftest-coverage -fprofile-arcs

ODIR=../obj
LDIR=../lib

LIBS= -lgtest -lpthread -lgtest_main --coverage -lgcov -lncurses -lmenu -lform -Wno-write-strings

_DEPS= GrafoInterface.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= Main.o GrafoInterface.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBS)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	cppcheck --enable=warning Main.c Grafo.c ../Include/GrafoInterface.h

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
