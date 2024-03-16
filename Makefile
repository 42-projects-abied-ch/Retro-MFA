NAME			= 	retromfa	

SRCDIR			=	srcs
SRCS			=	\
					$(SRCDIR)/mlx_utils.c \
					$(SRCDIR)/exit.c \
					$(SRCDIR)/draw.c \
					$(SRCDIR)/main_display.c \
					$(SRCDIR)/display.c \
					$(SRCDIR)/handler.c \

OBJDIR			=	$(SRCDIR)/objs
OBJS			=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o) 
DEPS			=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.d)

#-------FLAGS------------------------- CC				= 	cc
FLAGS			= 	-Wall -Wextra -Werror  -MD -MP -Ofast -march=native -O3 -g 
LIBS			= 	-lmlx -lXext -lX11 -lm -lXfixes
INCLUDE			=	-I ./inc
RM				= 	rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Linking..."
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)  

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling..."
	@mkdir -p $(dir $@)
	@$(CC) -c $(FLAGS) $(INCLUDE) $< -o $@ 
	
clean:
	@$(RM) $(OBJDIR)
	@echo "Cleaned"

fclean:
	@$(RM) $(OBJDIR) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus
