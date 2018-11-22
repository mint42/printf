/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/11/21 22:55:03 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <wchar.h>
# include <stdint.h>
# include <limits.h>
# include "libft.h"

# define VALID_FMTS "cCsSpPdDiIbBoOuUxX%lLhHjz1234567890.+- #*"
# define VALID_TYPE "cCsSpPdDiIbBoOuUxX%"
# define VALID_MODS "lLhHjz"


typedef struct	s_sub
{
	char		*s;
	char		*flags;
	char		mod;
	char		type;
	int			base;
	int			p;
	int			w;
	size_t		len;
}				t_sub;

int				ft_printf(const char *fmt, ...);
int				ft_sprintf(char **s, const char *fmt, ...);
int				ft_printfd(int fd, const char *fmt, ...);

t_sub			makesub(char **fmt, va_list ap, int init);
char			*fill_flags(char *fmt, char **flag);
char			*fill_pw(char *fmt, va_list ap, int *precision, int *width);
char			*fill_type(char *fmt, char *mod, char *type, int *base);
int				check_flags(char **flag, char *sub, char type, int width);

char			*parse(t_sub sub, va_list ap);
char			*parse_cs(t_sub sub, char *s, va_list ap);
char			*parse_di(t_sub sub, char *s, va_list ap, int base);
char			*parse_boux(t_sub sub, char *s, va_list ap, int base);
//char			*parse_ldlolu(t_sub sub, char *s, va_list ap, int base);

//char			*vatostr(const char *s);
char			*ft_uitoabase(unsigned long long int n, int base);
char			*ft_itoabase(long long int n, int base);
//char			*ft_ptoa(uintptr_t p);

char			*clean(char *s, t_sub sub, char **fmt, size_t *slen);
char			*crop(t_sub sub, size_t *sublen);
char			*addflags(t_sub sub);
char			*addzeros(t_sub sub, int p);
char			*precision(t_sub sub);

void			utf8_inc(char **str);
char			*conv_utf8_c(wchar_t c);
char			*conv_utf8(wchar_t *str);
int				get_utf8_bytes(wchar_t *str);

#endif
