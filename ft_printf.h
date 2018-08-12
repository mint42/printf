#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <wchar.h>
# include <stdint.h>
# include "./libft/libft.h"

typedef unsigned long long t_ull;

int		ft_printf(const char *format, ...);

#endif
