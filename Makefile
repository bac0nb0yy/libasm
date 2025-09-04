NAME = libasm.a
PROJECT_NAME = libasm

TEST_FILE_NAME = criterion_test.c
EXECUTABLE_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror
ASM = nasm
ASMFLAGS = -f elf64

SRC_DIR = sources/
OBJ_DIR = objects/
LIB_DIR = library/
INC_DIR = includes/

USER_HOME 				:= $(HOME)
CRITERION_INSTALL_DIR 	:= $(USER_HOME)/Criterion
CLANGD_FILE 			:= .clangd

CRITERION_DIR = $(HOME)/Criterion/include/criterion
CRITERION_FLAGS = -Wl,-rpath=$(HOME)/Criterion/build/src -L$(HOME)/Criterion/build/src -W

RM = rm -rf

ERASE_L = \033[K
CURS_UP = \033[A
SAVE_CURS_POS = \033[s
LOAD_CURS_SAVE = \033[u
BOLD = \033[1m
BLINK = \033[5m

NC = \033[0m

YELLOW = \033[0;33m
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
PURPLE = \033[0;35m
CYAN = \033[0;36m
BLACK = \033[0;30
WHITE = \033[0;37m

BYELLOW = \033[1;33m
BGREEN = \033[1;32m
BBLUE = \033[1;34m
BRED = \033[1;31m
BPURPLE = \033[1;35m
BCYAN = \033[1;36m
BBLACK = \033[1;30m
BWHITE = \033[1;37m

GREEN_BG = \033[48;5;2m

MANDATORY := ft_io \
			 ft_strcmp \
			 ft_strcpy \
			 ft_strdup \
			 ft_strlen \

SRCS_MANDATORY = $(addprefix $(SRC_DIR), $(addsuffix .s, $(MANDATORY)))
OBJS_MANDATORY = $(addprefix $(OBJ_DIR), $(notdir $(SRCS_MANDATORY:.s=.o)))

INCS = includes/libasm.h

TOTAL = $(words $(SRCS_MANDATORY))
FILE_COUNT = 0

BAR_COUNT = 0
BAR_PROGRESS = 0
BAR_SIZE = 64
GRADIENT_G := \033[38;5;160m \
			\033[38;5;196m \
			\033[38;5;202m \
			\033[38;5;208m \
			\033[38;5;214m \
			\033[38;5;220m \
			\033[38;5;226m \
			\033[38;5;190m \
			\033[38;5;154m \
			\033[38;5;118m \
			\033[38;5;82m \
			\033[38;5;46m \

GRAD_G_SIZE := 12
GRAD_G_PROG := 0

GRADIENT_B = \033[38;5;2m \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5; \
			 \033[38;5;

define GET_G_GRADIENT
$(word $(1),$(GRADIENT_G))
endef

all: $(NAME)

$(NAME): $(OBJS_MANDATORY)
	@echo "$(ERASE_L)$(BOLD)\tCompiling:$(NC)"
	@printf "\t█$(GREEN)"
	@for N in $$(seq 1 $(BAR_PROGRESS)); do \
		echo -n █; \
	done
	@printf "$(SAVE_CURS_POS)"
	@$(eval BAR_PROGRESS=$(shell echo $$(($(BAR_PROGRESS) / 2))))
	@for N in $$(seq 1 $(BAR_PROGRESS)); do \
		echo -n "\b"; \
	done
	@printf "\b\b$(NC)$(BLINK)$(BOLD)$(GREEN_BG)DONE"
	@printf "$(LOAD_CURS_SAVE)$(NC)█$(CURS_UP)"
	@printf "\b\b\b\b$(BOLD)%3d%%$(NC)\r" $(PERCENT)
	@echo "\n\n\n[🔘] $(BGREEN)$(PROJECT_NAME) compiled !$(NC)\n"
	@ar rcs $(LIB_DIR)/$@ $^
	@printf "[✨] $(BCYAN)[ %d/%d ]\t$(BWHITE)All files have been compiled ✔️$(NC)\n" $(FILE_COUNT) $(TOTAL)
	@echo "[💠] $(BCYAN)$(PROJECT_NAME)\t$(BWHITE) created ✔️\n$(NC)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.s $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(ASM) $(ASMFLAGS) $< -o $@
	@$(eval FILE_COUNT=$(shell echo $$(($(FILE_COUNT)+1))))
	@$(eval PERCENT:=$(shell echo $$((100*$(FILE_COUNT) /$(TOTAL)))))
	@$(eval BAR_PROGRESS=$(shell echo $$(($(BAR_SIZE)*$(FILE_COUNT)/$(TOTAL)))))
	@$(eval GRAD_G_PROG=$(shell echo $$(($(GRAD_G_SIZE)*$(FILE_COUNT)/$(TOTAL) + 1))))
	@printf "\t$(BWHITE)Compiling: $@%*s...$(NC)$(ERASE_L)\n" $$(($(FILE_COUNT)/$(TOTAL)*33))
	@printf "\t█$(call GET_G_GRADIENT,$(GRAD_G_PROG))"
	@for N in $$(seq 1 $(BAR_PROGRESS)); do \
		echo -n █; \
	done
	@for N in $$(seq 1 $(shell echo $$(($(BAR_SIZE) - $(BAR_PROGRESS))))); do \
		echo -n ░; \
	done
	@printf "$(NC)█$(CURS_UP)"
	@printf "\b\b\b\b$(BOLD)%3d%%$(NC)\r" $(PERCENT)

install:
	@if [ ! -d "$(CRITERION_INSTALL_DIR)" ]; then \
		echo "Installing Meson and Ninja..."; \
		pip3 install --user meson; \
		python3 -m pip install --user ninja; \
		export PATH="$$HOME/.local/bin:$$PATH"; \
		cd $$HOME; \
		echo "Cloning Criterion..."; \
		git clone --recursive https://github.com/Snaipe/Criterion.git; \
		cd Criterion; \
		meson build; \
		ninja -C build; \
	else \
		echo "Criterion already installed at $(CRITERION_INSTALL_DIR)"; \
	fi

	@echo "Generating $(CLANGD_FILE)..."
	@echo "CompileFlags:" > $(CLANGD_FILE)
	@echo "  Add:" >> $(CLANGD_FILE)
	@echo "    - -I./includes" >> $(CLANGD_FILE)
	@echo "    - -I$(CRITERION_INSTALL_DIR)/include" >> $(CLANGD_FILE)
	@echo "    - -L$(CRITERION_INSTALL_DIR)/build/src" >> $(CLANGD_FILE)
	@echo "    - -Wl,-rpath=$(CRITERION_INSTALL_DIR)/build/src" >> $(CLANGD_FILE)
	@echo "    - -lcriterion" >> $(CLANGD_FILE)

	@echo "Installation complete."

uninstall:
	@echo "Removing Criterion installation..."
	@rm -rf $(CRITERION_INSTALL_DIR)
	@echo "Removing $(CLANGD_FILE)..."
	@rm -f $(CLANGD_FILE)
	@echo "Uninstallation complete."

bonus: all

clean:
	@$(RM) $(OBJ_DIR)
	@echo "[🧼] $(BYELLOW)Objects $(YELLOW)files have been cleaned from $(PROJECT_NAME) ✔️$(NC)\n"

fclean: clean
	@$(RM) $(LIB_DIR)/$(NAME)
	@$(RM) $(EXECUTABLE_NAME)
	@echo "[🚮] $(BRED)All $(RED)files have been cleaned ✔️$(NC)\n"

re: clean all

test: $(NAME)
	@$(CC) -o $(EXECUTABLE_NAME) $(TEST_FILE_NAME) -I$(INC_DIR) -I$(CRITERION_DIR) $(CRITERION_FLAGS) -lasm -lc -lcriterion -L$(LIB_DIR) $(CFLAGS) && ./$(EXECUTABLE_NAME)

test42: $(NAME)
	@$(CC) -o $(EXECUTABLE_NAME) $(TEST_FILE_NAME) -I$(INC_DIR) -I$(CRITERION_DIR) $(CRITERION_FLAGS) -lasm -lc -lcriterion -L$(LIB_DIR) $(CFLAGS) -D TEST42=true && ./$(EXECUTABLE_NAME)

.PHONY: bonus all clean fclean re test
