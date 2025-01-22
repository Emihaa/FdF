CC = cc 
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -fsanitize=undefined -fsanitize=leak
#remember I am not allowed to use -fsanitize=address when submitting program
LIBMLX = ./MLX42
LIBFT = ./libft
NAME = fdf

HEADERS = -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm 
SRC = rsc/fdf.c rsc/map_control.c rsc/color_utils.c rsc/keyhooks.c rsc/draw.c rsc/initialize.c \
rsc/color_utils_invert.c rsc/colors.c rsc/map_tasks.c rsc/draw_line.c

OBJS = $(SRC:.c=.o)

all: $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(NAME)

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

$(LIBMLX)/build/libmlx42.a: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

%.o: %.c fdf.h
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re