NAME 	= philo

# Configuration
CFLAGS	= -Wall -Werror -Wextra -pthread -g3 #-fsanitize=address
RM		= rm -rf
SRCDIR	= src/
OBJDIR	= obj/
HEADER	= ./include/philo.h
PHILO = philo

# Source Files
SRCFILES =	main.c \
			input_check.c input_init.c \
			table_setting.c dinner.c synchronization.c \
			utils_free.c utils_print.c utils_time.c \

SRCOBJ	= $(SRCFILES:%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

# Objectives
all: $(PHILO)

$(PHILO): $(SRCOBJ)
	cc $(CFLAGS) $(SRCOBJ) -o $(PHILO)
	@echo "\n$(PURPLE)✨ Compilation for Philosophers done ✨ $(RESET)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p obj
	@cc -c $(CFLAGS) -o $@ $<

# Cleaning
clean:
	$(RM) $(SRCOBJ)
	$(RM) -r $(OBJDIR)
	@echo "\n$(CORAL)🧹    Removed all .o files and its directory   🧹$(RESET)"

fclean: clean
	@$(RM) $(PHILO)
	@echo "$(RED) 🗑️     Cleaned up remaining files   🗑️$(RESET)\n"

re: fclean all

run: $(NAME)
	valgrind --leak-check=full -s ./$(NAME)