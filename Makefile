##########################################################################
# Author: Jacob Nardone
# File Type: GNU Makefile
# Date Created: 5/10/2022
# Description: Flexible C makefile for ranging project file structures.
##########################################################################


#----------------------------------------------------------------#
# name of dir that stores source files
SRCDIR	:= src
# name of dir that stores header files
INCDIR	:= include
# name of dir that stores object files
OBJDIR 	:= objs
# name of final executable
EXEC 	:= bin\VimBell.exe
# C compiler
CC		:= g++
# compilation flags
CFLAGS	:= -std=c++17 -Wall \
			-Wno-unused-variable \
			-Wno-unused-private-field \
			-Wno-reorder-ctor \
			-Wno-switch \
			-Wno-reorder \
			-Wno-sign-compare \
			-g \
			-I$(INCDIR) -IC:\dev\libs\SFML\include
# linking flags (libraries)
SFML-LIBPATH	:= C:\dev\libs\SFML\lib
LFLAGS			:= -L$(SFML-LIBPATH) -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
LFLAGS-RLS			:= -L$(SFML-LIBPATH) -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -mwindows -O2
#----------------------------------------------------------------#

OBJS 		:= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))
HEADERS 	:= $(wildcard $(INCDIR)/*.hpp)

.PHONY: build run portable release clean


build:
	@ make -s $(EXEC) -j7

$(EXEC): $(OBJS)
	@ echo Linking dev build ...
	@ $(CC) $^ $(LFLAGS) -o $@
	@ echo Done.
	@ printf "\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@ echo Compiling $< ...
	@ $(CC) $< -c $(CFLAGS) -o $@

run:
	@ make -s build
	@ $(EXEC)

runonly:
	@ $(EXEC)

release: $(OBJS)
	@ echo Linking release build ...
	@ $(CC) $^ $(LFLAGS-RLS) -o $(EXEC)
	@ echo Done.
	@ printf "\n"

portable: release
	@ mkdir -p $@
	@ cp $(EXEC) $@
	@ cp -R res $@

clean:
	@ rm -rf $(EXEC) $(OBJDIR)

$(OBJDIR):
	mkdir -p $@


