NAME 	= philo

# Configuration
CFLAGS	= -Wall -Werror -Wextra -pthread -g3 #-fsanitize=address
RM		= rm -rf
SRCDIR	= src/
OBJDIR	= obj/
HEADER	= ./include/philo.h
PHILO = philo

# Source Files
SRCFILES =	main.c table_setting.c mutexes.c \
			utils_general.c utils_free_and_destroy.c \
			utils_dinner.c dinner.c check_philoc.c \

SRCOBJ	= $(SRCFILES:%.c=$(OBJDIR)%.o)

# Colors
RESET = \033[0m
YELLOW = \33[1;43m
BLUE=\033[1;44m
RED=\033[0;31m
PURPLE=\033[45m
CORAL=\033[38;2;255;127;80m

.PHONY: all clean fclean re

# Objectives
all: $(PHILO)

$(PHILO): $(SRCOBJ)
	cc $(CFLAGS) $(SRCOBJ) -o $(PHILO)
	@echo "\n$(PURPLE)✨ Compilation for Philosophers done ✨ $(RESET)\n\n"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p obj
	@cc -c $(CFLAGS) -o $@ $<

# Cleaning
clean:
	$(RM) $(SRCOBJ)
	$(RM) -r $(OBJDIR)
	@echo "\n$(CORAL)🧹    Removed all .o files and its directory   🧹$(RESET)\n\n"

fclean: clean
	@$(RM) $(PHILO)
	@echo "$(RED) 🗑️     Cleaned up remaining files   🗑️$(RESET)\n\n"

re: fclean all

run: $(NAME)
	valgrind --leak-check=full -s ./$(NAME)