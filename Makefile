# Project settings
NAME        = libasm.a
PROJECT     = libasm
EXEC        = checker

# Compiler & Assembler
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
ASM         = nasm
ASMFLAGS    = -f elf64

# Directories
SRC_DIR     = sources/
OBJ_DIR     = objects/
LIB_DIR     = library/
INC_DIR     = includes/

# Criterion
USER_HOME   	:= $(HOME)
CRITERION_DIR 	= $(USER_HOME)/Criterion
CLANGD_FILE   	= .clangd
CRITERION_INC 	= $(CRITERION_DIR)/include
CRITERION_LIB 	= $(CRITERION_DIR)/build/src

# Sources
MANDATORY   := ft_io ft_strcmp ft_strcpy ft_strdup ft_strlen
SRCS        = $(addprefix $(SRC_DIR), $(addsuffix .s, $(MANDATORY)))
OBJS        = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.s=.o)))

# Tests
TEST_INC    = tests_includes/
TEST_DIR    = tests_sources
TESTS       = \
    $(TEST_DIR)/tests_utils.c \
    $(TEST_DIR)/test_strlen.c \
    $(TEST_DIR)/test_strcpy.c \
    $(TEST_DIR)/test_strcmp.c \
    $(TEST_DIR)/test_write.c \
    $(TEST_DIR)/test_read.c \
    $(TEST_DIR)/test_strdup.c

# Tools
RM          = rm -rf

# Default rule
all: install $(LIB_DIR)/$(NAME)

$(LIB_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.s $(INC_DIR)/libasm.h
	@mkdir -p $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

# Tests
$(EXEC): $(TESTS) $(LIB_DIR)/$(NAME)
	$(CC) -o $@ $(TESTS) \
		-I$(TEST_INC) -I$(INC_DIR) -I$(CRITERION_INC) \
		-L$(LIB_DIR) -lasm \
		-L$(CRITERION_LIB) -Wl,-rpath=$(CRITERION_LIB) \
		-lcriterion $(CFLAGS)

test: install $(EXEC)
	./$(EXEC)

# Criterion installation
install:
	@if ! command -v meson >/dev/null 2>&1 || ! command -v ninja >/dev/null 2>&1; then \
		echo "Installing Meson and Ninja..."; \
		python3 -m pip install --user --upgrade pip; \
		python3 -m pip install --user meson ninja; \
	else \
		echo "Meson and Ninja already installed."; \
	fi

	@if [ ! -d "$(CRITERION_DIR)" ]; then \
		echo "Installing Criterion..."; \
		export PATH="$$HOME/.local/bin:$$PATH"; \
		cd $$HOME; \
		git clone --recursive https://github.com/Snaipe/Criterion.git; \
		cd Criterion; \
		meson setup build; \
		ninja -C build; \
	else \
		echo "Criterion already installed."; \
	fi

	@if [ ! -f "$(TEST_DIR)/$(CLANGD_FILE)" ]; then \
		echo "Generating $(CLANGD_FILE)..."; \
		echo "CompileFlags:" > $(TEST_DIR)/$(CLANGD_FILE); \
		echo "  Add:" >> $(TEST_DIR)/$(CLANGD_FILE); \
		echo "    - -I../$(INC_DIR)" >> $(TEST_DIR)/$(CLANGD_FILE); \
		echo "    - -I../$(TEST_INC)" >> $(TEST_DIR)/$(CLANGD_FILE); \
		echo "    - -I$(CRITERION_INC)" >> $(TEST_DIR)/$(CLANGD_FILE); \
	fi

uninstall:
	@echo "[🧹] Removing Criterion repository..."
	@$(RM) $(CRITERION_DIR)
	@echo "[🧹] Removing .clangd..."
	@$(RM) $(TEST_DIR)/$(CLANGD_FILE)
	@echo "[🧹] Uninstalling Python packages (meson, ninja)..."
	@python3 -m pip uninstall -y meson ninja
	@echo "[✅] Uninstallation complete."

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(LIB_DIR) $(EXEC)

re: fclean all

bonus: all

.PHONY: all bonus clean fclean re test install uninstall
