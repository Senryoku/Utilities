C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin
DOCDIR = doc
OPT = -Wall -pedantic -g -std=c++0x -I ../DynamicBitset/src/
#OPT = -Wall -pedantic -O2 -std=c++0x
FILES = $(wildcard $(SRCDIR)/*.cpp)
GV = $(wildcard *.gv)
PNG = $(wildcard *.png)
OBJT = $(FILES:.cpp=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJT))
OBJWIN = $(OBJ:/=\\)

COMMONOBJ = $(OBJDIR)/Subset.o

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

all: Subset

run: Subset
ifeq ($(OS), Linux)
	./$(BINDIR)/Subset
endif
ifeq ($(OS), Win)
	$(BINDIR)\Subset.exe
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) -c $^ -o $@
	
Subset : $(COMMONOBJ) $(OBJDIR)/main.o
ifeq ($(OS), Linux)
	$(C) $(LIBS) $^ -o $(BINDIR)/$@
endif
ifeq ($(OS), Win)
	$(C) $(LIBS) $^ -o $(BINDIR)\Subset.exe
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
