##
## Makefile for Makefile in /home/jansen_a//svn/abstractvm
## 
## Made by arthur jansen
## Login   <jansen_a@epitech.net>
## 
## Started on  Mon Feb 11 18:45:02 2013 arthur jansen
## Last update Fri Feb 15 15:05:35 2013 nicolas charlas
##

NAME =	abstractVM

CC =	g++

TILDE=	*~

RM=	rm -f

SRCS = 	AbstractVM.cpp \
	Lexer.cpp \
	ListOperands.cpp \
	main.cpp \
	Overunderflow.cpp \
	Parser.cpp

OBJS =  $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -Wall -Wextra -Werror

clean:
	$(RM) $(OBJS)
	$(RM) $(TILDE)

fclean:
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:	fclean all

rec:	fclean all clean
