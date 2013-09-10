C = g++
LIBS = 
OPT = -Wall -pedantic -std=c++0x
OBJDIR = obj
BINDIR = bin
SRCDIR = src
SEPAR = \\
EXE = Test.exe

all: $(BINDIR)$(SEPAR)$(EXE)

run: all
	$(BINDIR)$(SEPAR)$(EXE)

$(BINDIR)$(SEPAR)$(EXE): $(OBJDIR)$(SEPAR)RadixTree.o $(OBJDIR)$(SEPAR)main.o
	$(C) $(LIBS) $^ -o $@
	
	
$(OBJDIR)$(SEPAR)RadixTree.o: $(SRCDIR)$(SEPAR)RadixTree.cpp $(SRCDIR)$(SEPAR)RadixTree.hpp
	$(C) $(OPT) -c $< -o $@
	
$(OBJDIR)$(SEPAR)main.o: $(SRCDIR)$(SEPAR)main.cpp
	$(C) $(OPT) -c $< -o $@