##########################################################################
# Author: Jacob Nardone
# File Type: GNU Makefile
# Date Created: 5/10/2022
# Description: VimBell Makefile for Windows systems
##########################################################################

 ###################
#####  Windows  #####
 ###################


#----------------------------------------------------------------#
# name of dir that stores source files
SRCDIR	:= src

# name of dir that stores header files
INCDIR	:= include

# name of dir that stores object files
OBJDIR 	:= objs
DIR-DBG := debug
DIR-RLS := release

# name of final executable
EXEC 		:= VimBell.exe
EXEC-DBG 	:= $(DIR-DBG)/bin/$(EXEC)
EXEC-RLS 	:= $(DIR-RLS)/bin/$(EXEC)

# C compiler
CC := C:/ProgramData/chocolatey/lib/mingw/tools/install/mingw64/bin/g++.exe

# SFML paths
SFML-INCPATH := C:/dev/libs/SFML/include
SFML-LIBPATH := C:/dev/libs/SFML/lib

# compilation flags
CFLAGS	:=  -std=c++17 -Wall \
			-Wno-unused-variable \
			-Wno-unused-private-field \
			-Wno-reorder-ctor \
			-Wno-switch \
			-Wno-reorder \
			-Wno-sign-compare \
			-I$(INCDIR) -I$(SFML-INCPATH)

CFLAGS-DBG := -g $(CFLAGS)
CFLAGS-RLS	:= -DSFML_STATIC $(CFLAGS)



# linker flags
LFLAGS-DBG := -L$(SFML-LIBPATH) \
				-lstdc++fs \
				-lsfml-audio \
				-lsfml-graphics \
				-lsfml-window \
				-lsfml-system \

LFLAGS-RLS	:= -static -L$(SFML-LIBPATH) \
				-lstdc++fs \
				-lsfml-audio-s \
				-lsfml-graphics-s \
				-lsfml-window-s \
				-lsfml-system-s \
				-lopengl32 -lwinmm -lgdi32 -lFLAC -lfreetype -lopenal32 -lvorbisfile -lvorbis -lvorbisenc -logg \
				-mwindows -O2
#----------------------------------------------------------------#

OBJS-DBG 	:= $(patsubst $(SRCDIR)/%.cpp, $(DIR-DBG)/$(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))
OBJS-RLS 	:= $(patsubst $(SRCDIR)/%.cpp, $(DIR-RLS)/$(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))
HEADERS 	:= $(wildcard $(INCDIR)/*.hpp)

.PHONY: debug release portable run-debug run-release run-only clean


### DEBUG

$(EXEC-DBG): $(OBJS-DBG)
	@ echo Linking debug build ...
	@ $(CC) $^ $(LFLAGS-DBG) -o $@
	@ echo Done.
	@ printf "\n"


$(DIR-DBG)/$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@ echo Compiling $< \(debug\) ...
	@ $(CC) $< -c $(CFLAGS-DBG) -o $@




### RELEASE

$(EXEC-RLS): $(OBJS-RLS)
	@ echo Linking release build ...
	@ $(CC) $^ $(LFLAGS-RLS) res/icons/app-icon.res -o $@
	@ echo Done.
	@ printf "\n"


$(DIR-RLS)/$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@ echo Compiling $< \(release\) ...
	@ $(CC) $< -c $(CFLAGS-RLS) -o $@



debug:
	@ make -s $(EXEC-DBG) #-j7


release:
	@ make -s $(EXEC-RLS) #-j7


portable: release
	@ rm -rf $@
	@ mkdir $@
	@ cp -r $(DIR-RLS)/bin/* res $@


run-debug:
	@ make -s debug
	@ $(EXEC-DBG)


run-release:
	@ make -s release
	@ $(EXEC-RLS)


runonly:
	@ $(EXEC-DBG)


clean-debug:
	@ rm -rf $(DIR-DBG)/$(OBJDIR)/* $(EXEC-DBG)


clean-release:
	@ rm -rf $(DIR-RLS)/$(OBJDIR)/* $(EXEC-RLS)
