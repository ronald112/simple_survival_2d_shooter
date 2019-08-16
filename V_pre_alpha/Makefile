NAME = endgame

SRCS = src/main.c

INC = inc/header.h

HEADBIN = header.h

SRCS = src/Hello_main.c \
		src/init_SDL.c \
		src/do_input.c \
		src/prepare_scene.c \
		src/cleanup.c \
		src/load_Texture.c \
		src/blit.c \
		src/do_key_down.c \
		src/do_key_up.c \
		src/get_angle.c \
		src/blit_rotated.c \
		src/do_entities.c \
		src/init_player.c \


SRCSBIN = Hello_main.c \
		init_SDL.c \
		do_input.c \
		prepare_scene.c \
		cleanup.c \
		load_Texture.c \
		blit.c \
		do_key_down.c \
		do_key_up.c \
		get_angle.c \
		blit_rotated.c \
		do_entities.c \
		init_player.c \

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
dbg: debug clean

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

