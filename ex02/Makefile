 NAME	= PmergeMe

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS	=	main.cpp \
			PmergeMe.cpp

OBJS	= $(SRCS:.cpp=.o)

CXX	= @c++

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98 -g3

SAN	= -fsanitize=address

RM	= @rm -rf

CURRENT_DATE	:= $(shell date +"%Y-%m-%d %H:%M:%S")

all	: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS)  $(OBJS) -o $(NAME)
	@echo "$(MAGENTA)Make Done$(DEF_COLOR)"

clean : 
	$(RM) $(OBJS) 
	@echo "$(BLUE)OBJS CLEAR MY FRIEND!$(DEF_COLOR)"

fclean : 
	$(RM) $(NAME) $(OBJS)
	@echo "$(MAGENTA)¯|_(ツ)_/¯ I'M SO PROUD OF U!$(DEF_COLOR)"

re :	fclean all

ex :	re clean
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑ALL FINE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"
	@echo "$(PURPLE)testing : shuf -i 1-3000 -n 3000$(DEF_COLOR)"
	@./PmergeMe `shuf -i 1-3000 -n 3000 | tr "\n" " "`

git	:	fclean
	@$(RM) */a.out a.out
	@git add . > /dev/null 2>&1
	@@msg=$${MSG:-"$(CURRENT_DATE)"}; git commit -m "$(USER) $$msg" > /dev/null 2>&1 
	@git push > /dev/null 2>&1
	@echo "$(GREEN)(•̀ᴗ•́)و ̑̑GIT UPDATE!(•̀ᴗ•́)و ̑̑$(DEF_COLOR)"

val : re clean
	@echo "$(YELLOW)testing with valgrind: shuf -i 1-3000 -n 3000$(DEF_COLOR)"
	@valgrind -s --leak-check=full --show-leak-kinds=all  ./PmergeMe `shuf -i 1-3000 -n 3000 | tr "\n" " "`
