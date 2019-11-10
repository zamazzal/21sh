make -C libft
gcc -Wall -Wextra -Werror ctrld.c main.c -I includes -I libft libft/libft.a srcs/*/* -o 21sh -ltermcap
