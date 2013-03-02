#Corrige certains problèmes avec le PATH de windows... Commenter si autre système.
SHELL=C:/Windows/System32/cmd.exe

C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin
OPT = -Wall -pedantic -g
FILES = $(wildcard $(SRCDIR)/*.cpp)
OBJT = $(FILES:.cpp=.o)
OBJ = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJT))
OBJWIN = $(OBJ:/=\\)

COMMONOBJ = $(OBJDIR)/Socket.o

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
LIBS := -lws2_32 -lsfml-system
endif

all: Socket

run: Socket
ifeq ($(OS), Linux)
	./$(BINDIR)/Socket
endif
ifeq ($(OS), Win)
	$(BINDIR)\Socket.exe
endif

runClient: Client
ifeq ($(OS), Linux)
	./$(BINDIR)/Client
endif
ifeq ($(OS), Win)
	$(BINDIR)\Client.exe
endif


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) -c $^ -o $@
	
Socket : $(COMMONOBJ) $(OBJDIR)/main.o
ifeq ($(OS), Linux)
	$(C) $^ $(LIBS) -o $(BINDIR)/$@
endif
ifeq ($(OS), Win)
	$(C) $^ $(LIBS) -o $(BINDIR)\$@.exe
endif	

Client : $(COMMONOBJ) $(OBJDIR)/client.o
ifeq ($(OS), Linux)
	$(C) $^ $(LIBS) -o $(BINDIR)/$@
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
