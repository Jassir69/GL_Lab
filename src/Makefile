COMP=g++
CCFLAGS=-std=c++17 -Wall -g
LINK=$(COMP)
LNFLAGS=$(CCFLAGS)
LIBS=

EXE=AirWatcher
SRCDIR=.
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJDIR=obj
OBJ=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CLEAN=clean

all: $(EXE)

$(EXE): $(OBJ)
	$(LINK) -o $(EXE) $(OBJ) $(LIBS) $(LNFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(COMP) -o $@ -c $< $(CCFLAGS)

.PHONY: $(CLEAN)
$(CLEAN):
	rm -f $(OBJDIR)/* $(EXE)
