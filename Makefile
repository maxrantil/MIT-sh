MAKEFLAGS	+= --no-print-directory

NAME		=	MIT-sh
CC			=	gcc

SOURCES 	= 	srcs
OBJECTS 	= 	objs
INCLUDES	= 	includes

H_FILES 	= 	sh

FILES 		= 	main \
				constructors \
				fork1 \
				gettoken \
				nullterminate \
				panic \
				parseblock \
				parsecmd \
				parseexec \
				parseline \
				parsepipe \
				parseredir \
				peek \
				runcmd \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
C_PATHS 	= 	$(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS 	= 	$(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))


HEADERS		=	-I$(INCLUDES)/


all: $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(LEAK_CHECK)

$(OBJECTS):
	@mkdir -p $(OBJECTS)

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

