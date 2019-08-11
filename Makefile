NAME = endgame

INC = inc/header.h

HEADBIN = header.h

SRCS = src/Hello_main.c \

SRCSBIN = Hello_main.c \


CFLAGS = -I ./Frameworks/SDL2.framework/Versions/A/Header -F ./Frameworks -framework SDL2 -rpath ./frameworks

#-std=c11 -Wall -Wextra -Werror -Wpedantic

all: install uninstall 

#@gcc $(SRCSBIN) $(CFLAGS) $(NAME) $(SRCSBIN)

install:
	@cp $(SRCS) .
	@cp $(INC) .
	@gcc $(SRCSBIN) $(CFLAGS) 

uninstall: 
	@rm -rf $(SRCSBIN)
	@rm -rf $(HEADBIN)

clean: uninstall
	@rm -rf $(NAME)	
	
reinstall:
	@cp $(SRCS) .
	@cp $(INC) .
	@gcc $(SRCSBIN) $(CFLAGS) 

	@rm -rf $(SRCSBIN)
	@rm -rf $(HEADBIN)

