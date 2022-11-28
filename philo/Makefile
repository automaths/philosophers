NAME		=		philo
CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror -g3 -MMD -MP
INC			=		philo.h						\

SRCS		=		main.c 						\
					erroring.c					\
					initing_global.c			\
					initing_mutex.c				\
					initing_philosophers.c 		\
					living.c					\
					living_utils.c				\
					parsing.c					\
					timing.c					\
					utils.c 					\

OBJS		:=		$(addprefix ./objs/,$(SRCS:%.c=%.o))
DEP			=		$(addprefix ./objs/,$(OBJS:%.o=%.d))

all:				$(NAME)

-include $(DEP)

./objs/%.o: 		./%.c
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME):			$(OBJS) $(INC)
					$(CC) $(CFLAGS) -I incl -o $(NAME) $(OBJS)

clean:
					rm -rf objs/
					rm -rf $(NAME)

fclean:				clean

re:					fclean all

.PHONY:				all clean fclean re