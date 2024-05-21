NAME 	= philo

# Configuration
CFLAGS	= -Wall -Werror -Wextra -g
CFLAGS += -fsanitize=adders -g
RM		= rm -rf
SRCDIR	= src/

# Source Files
SRC =	main.c table_settings.c mutexes.c \
		utils_1.c utils_2.c \

OBJ		= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR	= obj

# Colors
# Colors
RESET = \033[0m
YELLOW = \33[1;43m
BLUE=\033[1;44m
RED=\033[0;31m
PURPLE=\033[45m
CORAL=\033[38;2;255;127;80m

# Objectives
all: $(OBJDIR) $(NAME)
	@echo "\n$(PURPLE)✨ Compilation for Philosophers done ✨ $(RESET)\n\n"


# Cleaning
clean:

fclean: clean

re: fclean all

.PHONY: all libft libmlx clean fclean re