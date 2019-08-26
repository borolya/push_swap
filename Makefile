CC = cc -Wall -Wextra -Werror -g
SRC_CHECKER = checker_main.c \
			common_do.c \
			common_tools.c

SRC_PUSH_SWAP = push_swap_main.c \
				push_swap_stay_three_elem.c \
				push_swap_take_min_cost.c \
				push_swap_move_to_place.c \
				common_do.c \
				common_tools.c

INCLUDES = -I ./libft/includes \
			-I .
			
OBJ_LIST_CHECKER = $(SRC_CHECKER:.c=.o)
OBJ_LIST_PUSH_SWAP = $(SRC_PUSH_SWAP:.c=.o)
OBJ_DIR = obj/
OBJ_CHECKER = $(addprefix $(OBJ_DIR), $(OBJ_LIST_CHECKER))
OBJ_PUSH_SWAP = $(addprefix $(OBJ_DIR), $(OBJ_LIST_PUSH_SWAP))
LIB = libft/libft.a\

all: checker push_swap

checker: $(LIB) $(OBJ_DIR) $(OBJ_CHECKER)
	$(CC) -o checker $(OBJ_CHECKER) $(INCLUDES) -L ./libft/ -lft

push_swap: $(LIB) $(OBJ_DIR) $(OBJ_PUSH_SWAP)
	$(CC) -o push_swap $(OBJ_PUSH_SWAP) $(INCLUDES) -L ./libft/ -lft

$(LIB):
	make -C ./libft
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)common%.o: common%.c common.h
	$(CC) -c $< $(INCLUDES)  -o $@
$(OBJ_DIR)checker%.o: checker%.c checker.h common.h
	$(CC) -c $< $(INCLUDES)  -o $@
$(OBJ_DIR)push_swap%.o: push_swap%.c push_swap.h common.h
	$(CC) -c $< $(INCLUDES)  -o $@	
clean:
	make -C libft fclean
	rm -rf $(OBJ_DIR)
fclean: clean
	make -C libft fclean
	rm -rf checker
	rm -rf push_swap
re: fclean all