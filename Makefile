##########################################################################
# Author: Jacob Nardone
# File Type: GNU Makefile
# Date Created: 4/9/2021
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
EXEC 		:= jBell
# C compiler
CC			:= g++
# compilation flags
CFLAGS	:= -std=c++17 -Wc++17-extensions -Wall -I$(INCDIR) -I/Users/Jacob/dev/libs/sfml/include
# linking flags (libraries)
SFML-LIBPATH	:= /Users/Jacob/dev/libs/sfml/lib 
LFLAGS			:= -L$(SFML-LIBPATH) -rpath $(SFML-LIBPATH) -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system
LFLAGS-RLS			:= -L$(SFML-LIBPATH) -rpath $(SFML-LIBPATH) -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -mwindows -O2
#----------------------------------------------------------------#

OBJS 		:= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))
HEADERS 	:= $(wildcard $(INCDIR)/*.hpp)


$(EXEC): $(OBJS)
	@echo Linking dev build ...
	@$(CC) $^ $(LFLAGS) -o $@
	@echo Done.
	@printf "\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	@echo Compiling $< ...
	@$(CC) $< -c $(CFLAGS) -o $@

run:
	@ make run2 -j7

run2: $(EXEC)
	@ ./$(EXEC)

release: $(OBJS)
	@echo Linking release build ...
	@$(CC) $^ $(LFLAGS-RLS) -o $(EXEC)
	@echo Done.
	@printf "\n"

portable: release
	@ mkdir -p $@
	@ cp $(EXEC) $@
	@ cp -R res $@

clean:
	@ rm -rf $(EXEC) $(OBJDIR)

$(OBJDIR):
	mkdir -p $@

.PHONY: run clean portable release

