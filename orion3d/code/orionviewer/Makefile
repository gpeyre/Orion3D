# Rakan El-Khalil
# rfe3@columbia.edu 
##################################################################

PROGRAM     = OrionViewer

##################################################################

TOOLKIT_DIR	= /usr/X11R6
SRC_DIR		= ../orion3d

##################################################################

DEBUG		= -D_DEBUG -g
LLDLIBS		= -L$(TOOLKIT_DIR)/lib -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm
DEFINES		= -D_UNIX_

CXX     	= g++
CXXFLAGS	= -O2 -Wall -I$(SRC_DIR) $(DEFINES) #$(DEBUG)
CC		= $(CXX)
CFLAGS		= $(CXXFLAGS)

##################################################################

all : $(PROGRAM)

clean:
	rm -f a.out *~ core *.o

cleanAll:
	rm -f a.out *~ core *.o $(PROGRAM)

##################################################################

OVWR_DEP	= OrionViewer.cpp
O3D_LIB		= ../orion3d/orion3d.a

##################################################################

OrionViewer: $(OVWR_DEP)
	$(RM) $@
	$(CXX) $(CXXFLAGS) $(LLDLIBS) $@.cpp -o $@ $(O3D_LIB)

#take care of cpp files
.SUFFIXES: .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
