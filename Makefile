NAME = endgame

SRCS = src/main.c

INC = inc/header.h

HEADBIN = header.h

SRCS = src/main.c \
		src/inits.c \
		src/input.c \
		src/cleanup.c \
		src/logic.c \
		src/draw.c \

SRCSBIN = main.c \
		inits.c \
		input.c \
		cleanup.c \
		logic.c \
		draw.c \

CFLAGS = -std=c11 
#-std=c11 -Wall -Wextra -Werror -Wpedantic

DFLAGS = -fsanitize=address -g

FFLAGS = -I ./Frameworks/SDL2.framework/Versions/A/Header \
-F ./Frameworks -framework SDL2 -rpath ./frameworks \
-I ./Frameworks/SDL2_image.framework/Versions/A/Header \
-F ./Frameworks -framework SDL2_image -rpath ./frameworks \
-I ./Frameworks/SDL2_mixer.framework/Versions/A/Header \
-F ./Frameworks -framework SDL2_mixer -rpath ./frameworks \


all: install uninstall
dbg: debug uninstall

#@gcc $(SRCSBIN) $(CFLAGS) $(NAME) $(SRCSBIN)
#@cp $(INC) .

install:
	@cp $(SRCS) .
	@cp $(INC) .
	@clang $(CFLAGS) $(FFLAGS) -o $(NAME) $(SRCSBIN)
	#@gcc $(SRCSBIN) $(CFLAGS) 

uninstall: 
	@rm -rf $(SRCSBIN)
	@rm -rf $(HEADBIN)

debug:
	@cp $(SRCS) .
	@cp $(INC) .
	@clang $(CFLAGS) $(FFLAGS) $(DFLAGS) -o $(NAME) $(SRCSBIN)

clean: uninstall
	@rm -rf $(NAME)	
	
reinstall:
	@rm -rf $(SRCSBIN)
	@rm -rf $(HEADBIN)

	@cp $(SRCS) .
	@cp $(INC) .
	@gcc $(SRCSBIN) $(CFLAGS) 

	@rm -rf $(SRCSBIN)
	@rm -rf $(HEADBIN)

