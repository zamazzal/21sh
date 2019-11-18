make -C libft
gcc -Wall -Wextra -Werror main.c -I includes -I libft libft/libft.a srcs/*/* -o 21sh -ltermcap
make -C libft fclean
