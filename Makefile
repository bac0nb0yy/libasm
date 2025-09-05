# Project settings
NAME        = libasm.a
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

# Deps
DEPS_DIR       := $(CURDIR)/deps
NINJA_DIR      := $(DEPS_DIR)/ninja
MESON_DIR      := $(DEPS_DIR)/meson
BIN_DIR        := $(CURDIR)/.local/bin

CRITERION_DIR  := $(CURDIR)/Criterion
CRITERION_INC 	= $(CRITERION_DIR)/include
CRITERION_LIB 	= $(CRITERION_DIR)/build/src

CLANGD_FILE   	= .clangd

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
all: $(LIB_DIR)$(NAME)

$(LIB_DIR)$(NAME): $(OBJS)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.s $(INC_DIR)/libasm.h
	@mkdir -p $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

# Tests
$(EXEC): $(TESTS) $(LIB_DIR)$(NAME)
	$(CC) -o $@ $(TESTS) \
		-I$(TEST_INC) -I$(INC_DIR) -I$(CRITERION_INC) \
		-L$(LIB_DIR) -lasm \
		-L$(CRITERION_LIB) -Wl,-rpath=$(CRITERION_LIB) \
		-lcriterion $(CFLAGS)

test: deps $(EXEC)
	./$(EXEC)

# Criterion installation
deps:
	@mkdir -p $(DEPS_DIR) $(BIN_DIR)

	@if ! command -v $(BIN_DIR)/ninja >/dev/null 2>&1; then \
		echo "[🔨] Installing Ninja from source..."; \
		cd $(DEPS_DIR); \
		git clone https://github.com/ninja-build/ninja.git || true; \
		cd ninja; \
		git fetch --all; \
		git checkout v1.10.2; \
		cmake -B build-cmake -S .; \
		cmake --build build-cmake; \
		cp build-cmake/ninja $(BIN_DIR)/ninja; \
	else \
		echo "[✅] Ninja already built."; \
	fi

	@if ! command -v $(BIN_DIR)/meson >/dev/null 2>&1; then \
		echo "[🔨] Installing Meson from source..."; \
		cd $(DEPS_DIR); \
		git clone https://github.com/mesonbuild/meson.git || true; \
		cd meson; \
		git fetch --all; \
		git checkout 0.59.4; \
		ln -sf $(MESON_DIR)/meson.py $(BIN_DIR)/meson; \
		chmod +x $(BIN_DIR)/meson; \
	else \
		echo "[✅] Meson already built."; \
	fi

	@if [ ! -d "$(CRITERION_DIR)" ]; then \
		echo "[📦] Installing Criterion from source..."; \
		export PATH="$(BIN_DIR):$$PATH"; \
		git clone --recursive https://github.com/Snaipe/Criterion.git $(CRITERION_DIR); \
		cd $(CRITERION_DIR); \
		git checkout v2.4.2; \
		git submodule update --init --recursive; \
		$(BIN_DIR)/meson setup build; \
		$(BIN_DIR)/ninja -C build; \
	else \
		echo "[✅] Criterion already built."; \
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
	@echo "[🧹] Removing Ninja and Meson source..."
	@$(RM) $(NINJA_DIR) $(MESON_DIR)
	@echo "[🧹] Removing local bin..."
	@$(RM) $(BIN_DIR)/ninja $(BIN_DIR)/meson
	@$(RM) $(DEPS_DIR)
	@echo "[✅] Uninstallation complete."

# Defaults rules
clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(LIB_DIR) $(EXEC) $(DEPS_DIR)

re: fclean all

bonus: all

.PHONY: all bonus clean fclean re test deps uninstall
