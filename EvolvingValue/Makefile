C = g++
OBJDIR = obj
SRCDIR = src
BINDIR = bin

OPT = -std=c++0x

all: obj exe

exe : $(OBJDIR)/test.o
	$(C) $^ -o bin\test.exe
	
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(C) $(OPT) $< -c -o $@

run: all
	$(BINDIR)\test.exe
	
.PHONY : clean

clean:
	rmdir $(OBJDIR) /S/Q
	mkdir $(OBJDIR)
	rmdir $(BINDIR) /S/Q
	mkdir $(BINDIR)