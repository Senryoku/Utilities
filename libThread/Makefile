#Corrige certains problèmes avec le PATH de windows... Commenter si autre système.
SHELL=C:/Windows/System32/cmd.exe

C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin
EXE = ThreadTest
OPT = -Wall -pedantic -g
FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJT = $(FILES:.cpp=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJT))
OBJWIN = $(OBJ:/=\\)

COMMONOBJ = $(OBJDIR)/Thread.o

ifeq ($(SHELL), sh.exe) 
OS := Win
else
ifeq ($(SHELL), C:/Windows/System32/cmd.exe)
OS := Win
else
OS := $(shell uname)
endif
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

all: $(ThreadTest).exe

run: $(ThreadTest).exe
ifeq ($(OS), Linux)
	./$(BINDIR)/$(ThreadTest).exe
endif
ifeq ($(OS), Win)
	$(BINDIR)\$(ThreadTest).exe
endif

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) -c $^ -o $@
	
$(ThreadTest) : $(COMMONOBJ) $(OBJDIR)/$(ThreadTest).o
ifeq ($(OS), Linux)
	$(C) $^ $(LIBS) -o $(BINDIR)/$@.exe
endif
ifeq ($(OS), Win)
	$(C) $^ $(LIBS) -o $(BINDIR)\$@.exe
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
