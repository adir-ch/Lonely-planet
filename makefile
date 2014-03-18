
#######################################################################
# Simple makefile 
#
# Makefile 
#######################################################################

CC=g++
AR=/usr/bin/ar
RL=/urs/bin/ranlib
LD=/usr/bin/ld

SRCDIR := .
INCDIR := .
OBJDIR := .

SRC :=  $(SRCDIR)/html_generator.cpp
	

EXE := html_generator

OBJ := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

CFLAGS := -c $(addprefix -I, $(INCDIR)) -O2 -Wall

DBGFLAGS := -g3 -rdynamic -DPROFILER #-pg

LDFLAGS := \

SIMPLE_LDFLAGS := -lpthread 

all: $(EXE)

debug: $(EXED)  

build: clean all
install: clean all

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
		$(CC) $(CFLAGS) -MD -o $@ $<
		@cp $(OBJDIR)/$*.d $(OBJDIR)/$*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $(OBJDIR)/$*.d >> $(OBJDIR)/$*.P; \
		rm -f $(OBJDIR)/$*.d


$(EXE) : $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLGS) $(LDFLAGS)


# compile for debug + profiler
$(EXED) : $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) $(DBGFLAGS)

clean:
	rm -f $(EXE) $(MAP) $(OBJ) $(OBJ:.o=.P) *~

-include $(OBJ:.o=.P)


