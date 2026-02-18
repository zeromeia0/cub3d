NAME = cub3d

SRCDIR = .
OBJDIR = objs
MLXDIR = ../.minilibx-linux
MAP_DIR = maps
EXTRA = ./extra

CC = cc
CFLAGS = -Iinc -Wall -Wextra -Werror -g
MLX_FLAGS = -L . -lmlx -lXext -lX11
INCLUDES = -I$(MLXDIR) -I$(GNL_DIR) -I. -I$(MAP_DIR)

# ================= SOURCES =================

SRC_BASE = \
	src/main.c \
	src/enemies/basic_enemy.c \
	src/enemies/enemy_utils1.c \
	src/enemies/enemy_utils2.c \
	src/enemies/enemy_utils3.c \
	src/exit_door/winning_exit.c \
	src/exit_door/winnin_helper.c \
	src/frees/freedom.c \
	src/frees/freedom2.c \
	src/frees/freedom3.c \
	src/game_loop/game_loop_helper.c \
	src/game_loop/window_management.c \
	src/inits/struct_new.c \
	src/inits/struct_new_utils1.c \
	src/inits/struct_new_utils2.c \
	src/inits/struct_new_utils3.c \
	src/inits/struct_new_utils4.c \
	src/inits/struct_new_utils5.c \
	src/inits/struct_new_utils6.c \
	src/inits/struct_new_utils7.c \
	src/key_inputs/keyboard_utils.c \
	src/key_inputs/keyboard_utils2.c \
	src/key_inputs/keyboard_utils3.c \
	src/minimap/minimap.c \
	src/minimap/minimap_utils.c \
	src/minimap/minimap_utils2.c \
	src/music/songs.c \
	src/music/songs_helper.c \
	src/parsing/parser.c \
	src/parsing/construct_map.c \
	src/parsing/header_validation.c \
	src/parsing/header_validation2.c \
	src/parsing/map_validation.c \
	src/parsing/rgb_validation.c \
	src/player/collision.c \
	src/player/mouse_movement.c \
	src/player/player_movement.c \
	src/player/player_movement2.c \
	src/player/player_position.c \
	src/render_raycast/dda_utils1.c \
	src/render_raycast/dda_utils2.c \
	src/render_raycast/picasso1.c \
	src/render_raycast/picasso2.c \
	src/render_raycast/picasso3.c \
	src/render_raycast/raycast.c \
	src/utils/get_next_line.c \
	src/utils/lib_utils1.c \
	src/utils/lib_utils2.c \
	src/utils/lib_utils3.c \
	src/utils/lib_utils4.c \
	src/utils/lib_utils5.c \
	src/utils/lib_utils6.c \
	src/utils/lib_utils7.c \
	src/utils/lib_utils8.c \
	src/utils/lib_utils9.c \
	src/utils/print_stuff.c \
	src/utils/vignette_utils.c \
	src/utils/vignette_utils2.c \

SRC = $(SRC_BASE)

SRC_EXTRA = \
	$(EXTRA)/enemy.c \
	$(EXTRA)/AStar/AStar.c

# ================ OBJECTS ==================

OBJS = $(SRC:../%.c=$(OBJDIR)/%.o)
# OBJS = $(OBJS:./%.c=$(OBJDIR)/%.o)

# ================= RULES ===================

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -lm -lXfixes -o $(NAME)

$(OBJDIR)/%.o: ../%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: ./%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============== EXTRA =====================


extra:
	@echo "[Creating extra directory]"
	@mkdir -p $(EXTRA)
	@echo "[Done]"
	@echo "[Copying ./.nightmare/enemy.txt]"
	@if [ -f ./.nightmare/enemy.txt ]; then \
		cp ./.nightmare/enemy.txt $(EXTRA)/enemy.c; \
	fi
	@echo "[Done]"
	@echo "[Injecting enemy logic into game_loop_helper.c]"
	@if ! grep -q "update_enemy(gen, i);" src/game_loop/game_loop_helper.c; then \
		sed -i '25i\		if ((gen->enemy[i].type == ENEMY_CTHULHU || gen->enemy[i].type == ENEMY_GHOST) && gen->flags->terror_mode)' src/game_loop/game_loop_helper.c; \
		sed -i '26i\			update_enemy(gen, i);' src/game_loop/game_loop_helper.c; \
	fi
	@echo "[Done]"
	@echo "[Injecting mlx include into general.h]"
	@	sed -i '17i\# include "../extra/AStar/AStar.h"' ./inc/general.h;
	@echo "[Done]"
	@echo "[Injecting AStar include]"
	@if ! grep -q 'AStar.h' inc/general.h; then \
		sed -i '17i\# include "../extra/AStar/AStar.h"' inc/general.h; \
	fi
	@echo "[Done]"
	@echo "cloning AStar repository"
	@if [ ! -d "$(EXTRA)/AStar" ]; then \
		git clone https://github.com/BigZaphod/AStar.git $(EXTRA)/AStar; \
	fi
	@echo "[Done]"
	@echo "Compiling now"
	@$(MAKE) SRC="$(SRC_BASE) $(SRC_EXTRA)" CFLAGS="-Iinc"


lib:
	git clone git@github.com:42paris/minilibx-linux.git
	cd minilibx-linux && make && cp libmlx.a ../ && cp mlx.h ../inc && cd .. && rm -rf minilibx-linux
	@if ! grep -q '# include "mlx.h"' ./inc/general.h; then \
		sed -i '15i\# include "mlx.h"' ./inc/general.h; \
	fi
# ============== CLEAN ======================

clean:
	@rm -rf $(OBJDIR)

fclean:
	@echo "Removing minilibx if it exists"
	@rm -rf minilibx-linux
	@echo "[Done]"
	@echo "Removing libmlx.a"
	@rm -rf libmlx.a
	@echo "[Done]"
	@echo "Removing AStar and extra logic..."
	@rm -rf ./extra/AStar
	@rm -rf ./extra/enemy.c
	@sed -i '/ENEMY_SKELETON/d' ./src/game_loop/game_loop_helper.c
	@sed -i '/update_enemy(gen, i);/d' ./src/game_loop/game_loop_helper.c
	@sed -i '/gen->enemy\[i\].type == ENEMY_CTHULHU .* ENEMY_GHOST).*terror_mode/d' ./src/game_loop/game_loop_helper.c
	@if grep -q 'AStar/AStar.h' ./inc/general.h; then \
		sed -i '/AStar\/AStar.h/d' ./inc/general.h; \
	fi
	@if grep -q '# include "mlx.h"' ./inc/general.h; then \
		sed -i '/# include "mlx.h"/d' ./inc/general.h; \
	fi
	@rm -rf extra
	@echo "Deleting extra directory"
	@rm -rf inc/mlx.h
	@echo "Removing mlx.h from inc"
	@$(MAKE) clean
	@rm -f $(NAME)



re: fclean lib all

# ============== TOOLS ======================

deb:
	lldb ./$(NAME) maps/testing.cub

val:
	valgrind --leak-check=full --track-fds=yes \
	--show-leak-kinds=all --track-origins=yes \
	./$(NAME) maps/map.cub

run: re
	@./$(NAME) maps/testing.cub

norm:
	@norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) \
	| awk '/c: Error/ { c++; if (c % 2 == 1) printf "\033[1;35m%s\033[0m\n", $$0; else printf "\033[1;36m%s\033[0m\n", $$0 }'
	@echo "Amount of errors: " && norminette $(shell find . -type f \( -name "*.c" -o -name "*.h" \)) | grep "Error" | wc -l

.PHONY: all clean fclean re extra run norm
