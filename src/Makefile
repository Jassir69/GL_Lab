CD=cd
RM=rm
RMFLAGS=-f
MKDIR=mkdir
MKDFLAGS=-p
COMP=g++
CCFLAGS=-std=c++17 -Wall -g  # Updated to use C++17 and added general warnings and debug information
LINK=g++
LNFLAGS=$(CCFLAGS)
LIBS=

BUILD=build
EXEDIR=bin
EXE=$(EXEDIR)/AirWatcher
OBJDIR=obj
SRCDIR=.
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CLEAN=clean

all: $(BUILD)

$(BUILD): $(OBJ)
	$(MKDIR) $(MKDFLAGS) $(EXEDIR)
	$(LINK) -o $(EXE) $(OBJ) $(LIBS) $(LNFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(MKDIR) $(MKDFLAGS) $(OBJDIR)
	$(COMP) -o $@ -c $< $(CCFLAGS)

.PHONY: $(CLEAN)
$(CLEAN):
	$(RM) $(RMFLAGS) $(OBJDIR)/* $(EXEDIR)/*
