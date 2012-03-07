#============================================================================
#  Name:
#    $(TARGET).MAK
#
#  Description:
#    Makefile to build the $(TARGET) downloadable module.
#
#   The following nmake targets are available in this makefile:
#
#     all           - make .elf and .mod image files (default)
#     clean         - delete object directory and image files
#     filename.o    - make object file
#
#   The above targets can be made with the following command:
#
#     nmake /f $(TARGET).mak [target]
#
#  Assumptions:
#    1. The environment variable ADSHOME is set to the root directory of the
#       arm tools.
#    2. The version of ADS is 1.2 or above.
#
#  Notes:
#    None.
#
#
#        Copyright ?2000-2003 QUALCOMM Incorporated.
#               All Rights Reserved.
#            QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#============================================================================
ARM_HOME       =$(ARMHOME)
BREW_HOME      =$(BREWDIR)
TARGET         = box2d
OBJS	         =  \
		 b2Settings.o \
		 b2CircleShape.o \
		 b2StackAllocator.o \
		 b2BlockAllocator.o \
		 b2Timer.o \
		 b2Draw.o \
		 b2Math.o \
		 b2WorldCallbacks.o \
		 b2Rope.o \
		 b2WeldJoint.o \
		 b2WheelJoint.o \
		 b2TimeOfImpact.o \
		 b2RopeJoint.o \
		 b2RevoluteJoint.o \
		 b2PulleyJoint.o \
		 b2PrismaticJoint.o \
		 b2PolygonShape.o \
		 b2MouseJoint.o \
		 b2GearJoint.o \
		 b2EdgeShape.o \
		 b2DistanceJoint.o \
		 b2Distance.o \
		 b2CollidePolygon.o \
		 b2CollideEdge.o \
		 b2CollideCircle.o \
		 b2ChainShape.o \
		 b2Body.o \
		 b2BroadPhase.o \
		 b2Collision.o \
		 b2ContactManager.o \
		 b2DynamicTree.o \
		 b2Fixture.o \
		 b2Joint.o \
		 b2FrictionJoint.o \
		 b2Island.o \
                 b2ContactSolver.o \
		 b2PolygonContact.o \
		 b2PolygonAndCircleContact.o \
		 b2EdgeAndPolygonContact.o \
		 b2EdgeAndCircleContact.o \
		 b2Contact.o \
		 b2CircleContact.o \
		 b2ChainAndPolygonContact.o \
		 b2ChainAndCircleContact.o \
		 pre.o \
                 b2World.o  
APP_INCLUDES   = -I . -I "$(BREWDIR)\inc"

APP_LIB = #

#-------------------------------------------------------------------------------
# Target file name and type definitions
#-------------------------------------------------------------------------------

EXETYPE    = a                # Target image file format
MODULE     =                 # Downloadable module extension

#-------------------------------------------------------------------------------
# Target compile time symbol definitions
#-------------------------------------------------------------------------------

DYNAPP          = -DDYNAMIC_APP


#-------------------------------------------------------------------------------
# Software tool and environment definitions
#-------------------------------------------------------------------------------

SUPPORT_DIR    = $(BREW_HOME)\src
SUPPORT_INCDIR = $(BREW_HOME)\inc

ARMBIN = $(ARM_HOME)\bin        # ARM ADS application directory
ARMINC = $(ARM_HOME)\include    # ARM ADS include file directory
ARMLIB = $(ARM_HOME)\lib        # ARM ADS library directory

ARMCC   = $(ARMBIN)\armcc       # ARM ADS ARM 32-bit inst. set ANSI C compiler
ARMCPP   = $(ARMBIN)\armcpp     # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
THUMBCC    = $(ARMBIN)\tcc      # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
THUMBCPP   = $(ARMBIN)\tcpp     # ARM ADS ARM 32-bit inst. set ANSI CPP compiler
LD      = $(ARMBIN)\armar       # ARM ADS linker

OBJ_CMD    = -o                 # Command line option to specify output filename

#-------------------------------------------------------------------------------
# Processor architecture options
#-------------------------------------------------------------------------------

CPU = -cpu ARM7EJ-S            # ARM7TDMI target processor

#-------------------------------------------------------------------------------
# ARM Procedure Call Standard (APCS) options
#-------------------------------------------------------------------------------

ROPI     = ropi                 # Read-Only(code) Position independence
INTERWRK = interwork            # Allow ARM-Thumb interworking

APCS = -apcs /$(ROPI)/$(INTERWRK)/norwpi

#-------------------------------------------------------------------------------
# Additional compile time error checking options
#-------------------------------------------------------------------------------

CHK = -fa                       # Check for data flow anomolies

#-------------------------------------------------------------------------------
# Compiler output options
#-------------------------------------------------------------------------------

OUT = -c                        # Object file output only

#-------------------------------------------------------------------------------
# Compiler/assembler debug options
#-------------------------------------------------------------------------------

DBG = #-g                        # Enable debug

#-------------------------------------------------------------------------------
# Compiler optimization options
#-------------------------------------------------------------------------------

OPT = -Ospace  -O2               # Full compiler optimization for space

#-------------------------------------------------------------------------------
# Compiler code generation options
#-------------------------------------------------------------------------------

END = -littleend                # Compile for little endian memory architecture
ZA  = -zo                       # LDR may only access 32-bit aligned addresses

CODE = $(END) $(ZA)


#-------------------------------------------------------------------------------
# Include file search path options
#-------------------------------------------------------------------------------

INC = -I. -I$(SUPPORT_INCDIR) $(APP_INCLUDES)


#-------------------------------------------------------------------------------
# Compiler pragma emulation options
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
# Linker options
#-------------------------------------------------------------------------------

LINK_CMD = -r                    #Command line option to specify output file
                                 #on linking

ROPILINK = -ropi                 #Link image as Read-Only Position Independent

LINK_ORDER = 

#-------------------------------------------------------------------------------
# HEXTOOL options
#-------------------------------------------------------------------------------

BINFORMAT = -bin


#-------------------------------------------------------------------------------
# Compiler flag definitions
#-------------------------------------------------------------------------------

CFLAGS0 = $(OUT) $(DYNAPP) $(CPU) $(APCS) $(CODE) $(CHK) $(DBG)
CFLAGS  = $(CFLAGS0) $(OPT)

#-------------------------------------------------------------------------------
# Linker flag definitions
#-------------------------------------------------------------------------------

# the -entry flag is not really needed, but it keeps the linker from reporting
# warning L6305W (no entry point).  The address
LFLAGS = -r

#----------------------------------------------------------------------------
# Default target
#----------------------------------------------------------------------------

all :  $(TARGET).$(EXETYPE)

#----------------------------------------------------------------------------
# Clean target
#----------------------------------------------------------------------------

# The object subdirectory, target image file, and target hex file are deleted.

clean :
        @echo ---------------------------------------------------------------
        @echo CLEAN
        -del /f $(OBJS)
        -del /f ..\..\sxmsample\$(TARGET).$(EXETYPE)
        @echo ---------------------------------------------------------------

#============================================================================
#                           DEFAULT SUFFIX RULES
#============================================================================

# The following are the default suffix rules used to compile all objects that
# are not specifically included in one of the module specific rules defined
# in the next section.

# The following macros are used to specify the output object file, MSG_FILE
# symbol definition and input source file on the compile line in the rules
# defined below.

SRC_CPP_FILE = $(@F:.o=.cpp)      # Input source file specification
SRC_C_FILE   = $(@F:.o=.c)      # Input source file specification
OBJ_FILE = $(OBJ_CMD) $(@F)   # Output object file specification

.SUFFIXES :
.SUFFIXES : .o .dep .c .cpp

#--------------------------------------------------------------------------
# C code inference rules
#----------------------------------------------------------------------------

.c.o:
        @echo ---------------------------------------------------------------
        @echo OBJECT $(@F)
        $(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE) $(SRC_C_FILE)
        @echo ---------------------------------------------------------------

.c.mix:
        @echo ---------------------------------------------------------------
        @echo OBJECT $(@F)
        $(ARMCC) -S -fs $(CFLAGS) $(INC) $(OBJ_FILE) $<
        @echo ---------------------------------------------------------------

.cpp.o:
        @echo ---------------------------------------------------------------
        @echo OBJECT $(@F)
        $(ARMCPP) $(CFLAGS) $(INC) $(OBJ_FILE) $(SRC_CPP_FILE)
        @echo ---------------------------------------------------------------

#{$(SUPPORT_DIR)}.c.o:
#        @echo ---------------------------------------------------------------
#        @echo OBJECT $(@F)
#        $(ARMCC) $(CFLAGS) $(INC) $(OBJ_FILE) $(SUPPORT_DIR)\$(SRC_C_FILE)
#        @echo ---------------------------------------------------------------


#===============================================================================
#                           MODULE SPECIFIC RULES
#===============================================================================

APP_OBJS = $(OBJS)

RULE7 = .
{$(RULE7)}.cpp.o:
	@echo ---------------------------------------------------------------
	@echo OBJECT $(@F)
	$(ARMCPP) $(CFLAGS) $(INC) $(OBJ_FILE)  $(RULE7)\$(SRC_CPP_FILE)
#	$(THUMBCPP) $(CFLAGS) $(INC) $(OBJ_FILE)  $(RULE7)\$(SRC_CPP_FILE)
	@echo ---------------------------------------------------------------

#----------------------------------------------------------------------------
# Lib file targets
#----------------------------------------------------------------------------

 
$(TARGET).$(EXETYPE) : $(APP_OBJS)
        @echo ---------------------------------------------------------------
        @echo TARGET $@
        $(LD) $(LINK_CMD)  .\$(TARGET).$(EXETYPE) $(APP_OBJS) $(APP_LIB) $(LINK_ORDER)
