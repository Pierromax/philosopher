### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3

### PROJECT NAME ###
PROJECT := philo
PROJECT_DIR := ./

### SOURCE DIR ###
SRC_DIR := src
INCLUDES_DIR := -I ./include

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
		init.c	\
		utils.c	
	)
endef


# *************************************************************************** #
#                                SRC COMPILE OBJ                              #
# *************************************************************************** #

# COMPILING SRC_FILE
all : $(PROJECT) $(OBJ)

$(PROJECT) : 
	@$(CC) $(CFLAGS) $(INCLUDES_DIR) $(SRC_FILE) $(LIBFT) $(OBJ) -o $(PROJECT)

# COMPILIG OBJ_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	@rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	@rm -rf $(OBJ_DIR)

re : fclean all