### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3

### PROJECT NAME ###
PROJECT := philo
PROJECT_DIR := ./

### SOURCE DIR ###
SRC_DIR := src
INCLUDES_DIR := -I ./include

### LIBFT DIR ###
FT_DIR := ./libft
LIBFT := $(FT_DIR)/libft.a

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
OBJ := $(OBJ_SRC)

# *************************************************************************** #
#                             MANDATORY SOURCE FILE                           #
# *************************************************************************** #
define SRC_FILE :=
	$(addprefix $(SRC_DIR)/, \
		main.c \
		philo.c \
		init.c
	)
endef


# *************************************************************************** #
#                                SRC COMPILE OBJ                              #
# *************************************************************************** #

# COMPILING SRC_FILE
all : $(PROJECT) $(OBJ)

# COMPILIG OBJ_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) $(SRC_FILE) $(LIBFT) $(OBJ) -o $(PROJECT)

$(LIBFT) :
	@make -C $(FT_DIR)

fclean : clean
	@rm -f $(PROJECT)
	@make fclean -C $(FT_DIR)

#Suppresion des fichiers objet
clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C $(FT_DIR)

re : fclean all