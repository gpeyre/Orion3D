# Rakan El-Khalil
# rfe3@columbia.edu 
##################################################################

PROGRAM     = orion3d.a

##################################################################

AR= ar rc
AR2= ranlib

DEBUG		= -D_DEBUG -g
DEFINES		= -D_UNIX_

##################################################################

CXX     	= g++
CXXFLAGS	= -O2 -Wall $(DEFINES) #$(DEBUG)
CC		= $(CXX)
CFLAGS		= $(CXXFLAGS)

##################################################################

all : $(PROGRAM)

clean:
	rm -f a.out *~ core *.o

cleanAll:
	rm -f a.out *~ core *.o $(PROGRAM)

##################################################################

OR_OBJ		= 	OR_Action.o OR_Annexes.o OR_BSP.o OR_Camera.o\
			OR_Endian_Conv.o OR_Fog.o\
			OR_Force.o OR_GLExtensions.o OR_Gizmo.o\
			OR_HierarchyTree.o\
			OR_InputOutput.o OR_IsoSurface.o OR_IsoSurfaceTab.o\
			OR_Light.o OR_MathsSurface.o OR_MathsSurface_Def.o\
			OR_Mesh.o OR_MetaManager.o OR_Node.o OR_Nurbs.o\
			OR_Object.o OR_Particules.o OR_Plan.o OR_Portals.o\
			OR_Primitives.o\
			OR_Shader.o OR_Std_Template.o OR_SurfaceTeslator.o\
			OR_TexFont.o OR_Texture.o OR_Viewport.o TexFont.o\
			orion3d.o

GETTSCTIME_OBJ  = gettsctime.o
O3DLIB_OBJ	= $(OR_OBJ) $(GETTSCTIME_OBJ)

##################################################################

orion3d.a: $(O3DLIB_OBJ)
	$(RM) $@
	$(AR) $@ $(O3DLIB_OBJ)
	$(AR2) $@

#take care of cpp files
.SUFFIXES: .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
