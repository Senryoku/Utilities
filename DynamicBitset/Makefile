C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin
DOCDIR = doc
OPT = -Wall -pedantic -g -std=c++0x
#OPT = -Wall -pedantic -O2 -std=c++0x
FILES = $(wildcard $(SRCDIR)/*.cpp)
GV = $(wildcard *.gv)
PNG = $(wildcard *.png)
OBJT = $(FILES:.cpp=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJT))
OBJWIN = $(OBJ:/=\\)

COMMONOBJ = $(OBJDIR)/DynamicBitset.o

ifeq ($(SHELL), sh.exe)
OS := Win
else
OS := $(shell uname)
endif

ifeq ($(OS), Linux)
RM = rm
LIBS := 
endif
ifeq ($(OS), Darwin)
RM = rm
LIBS := 
endif
ifeq ($(OS), Win)
RM = del
LIBS := 
endif

all: DynamicBitset

run: DynamicBitset
ifeq ($(OS), Linux)
	./$(BINDIR)/DynamicBitset
endif
ifeq ($(OS), Win)
	$(BINDIR)\DynamicBitset.exe
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) -c $^ -o $@
	
DynamicBitset : $(COMMONOBJ) $(OBJDIR)/main.o
ifeq ($(OS), Linux)
	$(C) $(LIBS) $^ -o $(BINDIR)/$@
endif
ifeq ($(OS), Win)
	$(C) $(LIBS) $^ -o $(BINDIR)\DynamicBitset.exe
endif

clean:
ifeq ($(OS), Linux)
	$(RM) $(OBJDIR)/*.o
	$(RM) $(BINDIR)/*
endif
ifeq ($(OS), Win)
	rmdir $(OBJDIR) /S/Q
	mkdir $(OBJDIR)
	rmdir $(BINDIR) /S/Q
	mkdir $(BINDIR)
endif
