NAME = fractol

# Compiler and flags (g3 debug with LLDB)
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -g3

# Directories
SRC_DIR = src
INC_DIR = includes
LIBFT_DIR = lib/libft
MLX_DIR = minilibx-linux

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/fractals.c \
       $(SRC_DIR)/fractal_newton.c \
       $(SRC_DIR)/fractal_flower.c \
			 $(SRC_DIR)/colors.c \
			 $(SRC_DIR)/colors_utils.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/coordinates.c \
       $(SRC_DIR)/events.c \
       $(SRC_DIR)/event_utils.c \
       $(SRC_DIR)/mouse_events.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/ui_utils.c \
       $(SRC_DIR)/ui_draw.c \
       $(SRC_DIR)/parse_args.c \
       $(SRC_DIR)/parse_utils.c \
       $(SRC_DIR)/print_usage.c

# Object files
OBJS = $(SRCS:.c=.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

# Include and library flags
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default target
all: $(NAME)

# Build the executable
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

# Compile object files
%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# Build MiniLibX
$(MLX):
	@echo "$(GREEN)Building MiniLibX...$(RESET)"
	@make -C $(MLX_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Test the program with different fractals
test: $(NAME)
	@echo "$(GREEN)Testing Mandelbrot set...$(RESET)"
	@./$(NAME) mandelbrot &
	@sleep 2
	@echo "$(GREEN)Testing Julia set...$(RESET)"
	@./$(NAME) julia -0.7 0.27015 &
	@sleep 2
	@echo "$(GREEN)Testing Newton fractal...$(RESET)"
	@./$(NAME) newton &

# Norm check
norm:
	@echo "$(GREEN)Checking norm...$(RESET)"
	@norminette $(SRCS) $(INC_DIR)/*.h

# Phony targets
.PHONY: all clean fclean re test norm
