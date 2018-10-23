/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/10/20 19:34:19 by rreedy           ###   ########.fr       */
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

typedef struct	s_sub
{
	char		*s;
	size_t		len;
	char		*flags;
	int			p;
	int			w;
	char		mod;
	char		type;
}				t_sub;

//typedef unsigned long long t_ull;

int				ft_printf(const char *fmt, ...);
int				ft_sprintf(char **s, const char *fmt, ...);
int				ft_printfd(int fd, const char *fmt, ...);

t_sub			makesub(char *fmt, va_list ap, int init);
int				check_flags(char **flag, char *sub, char type, int width);
void			delsub(char **s, char **flags);
char			*fill_flags(char *fmt, char **flag);
char			*fill_pw(char *fmt, va_list ap, int *precision, int *width);
void			fill_type(char *fmt, char *mod, char *type);

char			*parse(t_sub sub, va_list ap);
char			*parse_clcsls(t_sub sub, char *s, va_list ap);
char			*parse_di(t_sub sub, char *s, va_list ap, int base);
char			*parse_ouxbigx(t_sub sub, char *s, va_list ap, int base);
char			*parse_ldlolu(t_sub sub, char *s, va_list ap, int base);

char			*vatostr(const char *s);
int				get_base(char type);
char			*ft_uitoabase(unsigned long long int n, int base);
char			*ft_itoabase(long long int n, int base);
char			*ft_ptoa(uintptr_t p);

char			*clean(char *s, t_sub sub, char **fmt, size_t *slen);
char			*crop(t_sub sub, size_t *sublen);
char			*addflags(t_sub sub);
char			*addzeros(t_sub sub, int p);
char			*precision(t_sub sub);

int				get_utf8_bytes(wchar_t *str);
void			utf8_inc(char **str);
char			*conv_utf8_c(wchar_t c);
char			*conv_utf8(wchar_t *str);

#endif
