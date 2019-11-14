make -C libft
gcc -Wall -Wextra -Werror main.c -I . -I libft libft/libft.a srcs/*/* -o 21sh -ltermcap
