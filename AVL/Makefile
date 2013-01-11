C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin
OPT = -Wall -pedantic -g
FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJT = $(FILES:.cpp=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJT))
OBJWIN = $(OBJ:/=\\)

COMMONOBJ = 

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

all: AVL

run: AVL
ifeq ($(OS), Linux)
	./$(BINDIR)/AVL
	dot -Tpng "Graph.gv" -o "Graph.png"
endif
ifeq ($(OS), Win)
	$(BINDIR)\AVL.exe
	dot -Tpng "Graph.gv" -o "Graph.png"
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) -c $^ -o $@
	
AVL : clean $(COMMONOBJ) $(OBJDIR)/main.o
ifeq ($(OS), Linux)
	$(C) $(LIBS) $(OBJDIR)/main.o -o $(BINDIR)/$@
endif
ifeq ($(OS), Win)
	$(C) $(LIBS) $(OBJDIR)/main.o -o $(BINDIR)\AVL.exe
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
