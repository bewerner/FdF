NAME		=	fdf
LIBFT		=	libft/libft.a
MLX42		=	MLX42/build/libmlx42.a
SRC	=	fdf.c init_fdf.c init_png.c init_mesh.c init_skybox.c \
				put_skybox.c put_pixel.c put_dot.c put_mesh.c put_face.c \
				put_line.c color_math.c vector_math.c put_sky_tri.c \
				cleanup.c set_vert_colors.c init_hooks.c main_loop.c \
				key_hook.c project_mesh.c cursor_hook.c validate_value.c
OBJ			=	$(patsubst %.c, obj/%.o, $(SRC))
CFLAGS		=	-Wall -Wextra -Werror -Ofast -flto
LDFLAGS		=	-lm -ldl -lglfw -flto
CC			=	cc
COL_GREEN	= 	\033[32m
COL_RED		=	\033[31m
COL_YELLOW	= 	\033[38;2;214;189;28m
COL_PINK	= 	\033[95m
COL_DEFAULT	= 	\033[0m

.SILENT:

ifeq ($(shell uname -r | grep -oi microsoft), microsoft)
 CFLAGS += -DCURSOR_SETTABLE=0
endif

all: $(MLX42) $(NAME)

$(NAME): $(OBJ)
	echo "$(COL_YELLOW)Building FdF...$(COL_DEFAULT)"
	$(MAKE) -C libft > /dev/null
	$(CC) $(OBJ) $(LIBFT) $(MLX42) -o $(NAME) $(LDFLAGS)
	echo "\n$(COL_GREEN)Successfully built FdF!$(COL_DEFAULT)"
	echo "\n$(COL_YELLOW)Try it out with $(COL_PINK)./fdf assets/maps/fdf/42.fdf $(COL_YELLOW)\
	or any of the presets:$(COL_DEFAULT)\n"
	echo "$(COL_PINK)make ft$(COL_DEFAULT)"
	echo "$(COL_PINK)make alien      make foggy       make crater$(COL_DEFAULT)"
	echo "$(COL_PINK)make mud        make pebbles     make cobblestone$(COL_DEFAULT)"
	echo "\n$(COL_YELLOW)Please have a look at the $(COL_PINK)[$(COL_GREEN)README.md$(COL_PINK)]\
	$(COL_YELLOW) to learn about all of the controls!$(COL_DEFAULT)\n"

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX42):
	echo "$(COL_YELLOW)Cloning MLX42...$(COL_DEFAULT)"
	git clone https://github.com/codam-coding-college/MLX42.git > /dev/null
	echo "$(COL_YELLOW)Switching to latest known-to-work branch...$(COL_DEFAULT)"
	cd MLX42 && git checkout ca0f163 || > /dev/null
	echo "$(COL_YELLOW)Building MLX42...$(COL_DEFAULT)"
	cmake -B MLX42/build -S MLX42 > /dev/null && make -C MLX42/build -j4 > /dev/null ||\
	(echo "\n$(COL_RED)Looks like an ERROR has occured!$(COL_DEFAULT)\n$(COL_YELLOW)Please refer to the \
	$(COL_PINK)MLX42 GitHub $(COL_YELLOW)page to find out about	dependencies and instructions.\n\
	$(COL_PINK)https://github.com/codam-coding-college/MLX42$(COL_DEFAULT)\n" && rm -rf MLX42)

clean:
	$(MAKE) -C libft clean > /dev/null
	rm -rf obj
	echo "$(COL_GREEN)Object files have been removed.$(COL_DEFAULT)"

fclean: clean
	$(MAKE) -C libft fclean > /dev/null
	rm -rf $(NAME) MLX42
	@echo "$(COL_GREEN)MLX42 and FdF executables have been removed.$(COL_DEFAULT)"

re: fclean all

ft: all
	echo "./fdf assets/maps/fdf/42.fdf"
	./fdf assets/maps/fdf/42.fdf

alien: all
	echo "./fdf assets/maps/terrain/alien_height_1k.png assets/maps/terrain/alien_color_1k.png"
	./fdf assets/maps/terrain/alien_height_1k.png assets/maps/terrain/alien_color_1k.png

foggy: all
	echo "./fdf assets/maps/terrain/foggy_height_1k.png assets/maps/terrain/foggy_color_1k.png"
	./fdf assets/maps/terrain/foggy_height_1k.png assets/maps/terrain/foggy_color_1k.png

crater: all
	echo "./fdf assets/maps/terrain/crater_height_1k.png assets/maps/terrain/crater_color_1k.png"
	./fdf assets/maps/terrain/crater_height_1k.png assets/maps/terrain/crater_color_1k.png

cobblestone: all
	echo "./fdf assets/maps/materials/cobblestone_height_1k.png assets/maps/materials/cobblestone_color_1k.png"
	./fdf assets/maps/materials/cobblestone_height_1k.png assets/maps/materials/cobblestone_color_1k.png

mud: all
	echo "./fdf assets/maps/materials/mud_height_1k.png assets/maps/materials/mud_color_1k.png"
	./fdf assets/maps/materials/mud_height_1k.png assets/maps/materials/mud_color_1k.png

pebbles: all
	echo "./fdf assets/maps/materials/pebbles_height_1k.png assets/maps/materials/pebbles_color_1k.png"
	./fdf assets/maps/materials/pebbles_height_1k.png assets/maps/materials/pebbles_color_1k.png

.PHONY: all clean fclean re ft alien foggy crater cobblestone mud pebbles
