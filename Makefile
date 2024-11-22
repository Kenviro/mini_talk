NAME1 = client
NAME2 = server
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC_CLIENT = client.c
SRC_SERVER = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

HEADERS = mini_talk.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(LIBFT_DIR)

all: $(LIBFT) $(NAME1) $(NAME2)

$(NAME1): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME1)

$(NAME2): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME2)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME1) $(NAME2)

re: fclean all