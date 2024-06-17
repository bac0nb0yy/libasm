# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
ASM = nasm
ASMFLAGS = -f elf64

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INC_DIR = includes

# Files
NAME = libasm.a
SRCS = $(wildcard $(SRC_DIR)/*/*.s)
SRCS_BONUS = $(wildcard $(SRC_DIR)/bonus/*/*.s)
OBJS = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRCS_BONUS))
INC = $(wildcard $(INC_DIR)/*.h)
TEST = tester.c

all: $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(LIB_DIR)/$(NAME) $^

$(NAME): $(OBJS)
	ar rcs $(LIB_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s $(INC)
	@mkdir -p $(@D)
	@$(ASM) $(ASMFLAGS) $< -o $@

test: $(NAME) $(TEST)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o check $(TEST) -L$(LIB_DIR) -lasm -lc && ./check

malloc_test: $(NAME) $(TEST)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o check $(TEST) -L$(LIB_DIR) -lasm -lc && (ulimit -v 3800 && ./check)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(LIB_DIR)/$(NAME)
	@rm -f check

re: fclean all

.PHONY: all clean fclean re
