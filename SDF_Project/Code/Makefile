FMTDIR=/home/geetha/packages/SFML-2.5.1
INCLUDEDIR=$(FMTDIR)/include
LIBDIR=$(FMTDIR)
CC=g++
# CFLAGS=-c -g -Wall -Werror -pedantic -pedantic-errors -I $(INCLUDEDIR)
CFLAGS=-c -g -I $(INCLUDEDIR)
LIBFLAGS=-lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

SRCS=start.cpp BoardCode.cpp diceRoller.cpp community_chest.cpp chance.cpp playing_cards.cpp main.cpp 
OBJS=$(addsuffix .o,$(basename $(SRCS))) 
EXE=monopoly
.PHONY	: clean all

all : $(EXE)

$(EXE)	: $(OBJS)
		$(CC) -o $@ -L $(LIBDIR) $(OBJS) $(LIBFLAGS)


$(OBJS)	:	%.o	: %.cpp
		$(CC) $(CFLAGS) $<


clean :
	rm $(OBJS) $(EXE)