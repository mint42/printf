/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/14 08:46:59 by rreedy           ###   ########.fr       */
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
	char		type;
}				t_sub;

typedef unsigned long long t_ull;

int				ft_printf(const char *fmt, ...);

t_sub			makesub(char *fmt, va_list ap, int init);
void			delsub(char **s, char **flags);
char			*fill_flags(char *sub, char *fmt, char type);
void			fill_pw(char *fmt, va_list ap, int *precision, int *width);
char			*to_type(char *fmt);

int				base(char *fmt);
int				cmp(char *fmt, char *type);
char			*parse(char *fmt, va_list ap);
char			*parse2(char *fmt, char *s, va_list ap);

char			*vatostr(const char *s);
char			*ft_uitoabase(t_ull n, int base);
char			*ft_itoabase(long long int n, int base);
char			*ft_ptoa(uintptr_t p);

char			*clean(char *s, t_sub sub, char **fmt, size_t *slen);
char			*crop(t_sub sub, size_t *sublen);
char			*addflags(char *sub, char *flg, char type);
char			*addzeros(char *sub, char *flg, int p);
char			*precision(char *sub, char *flg, char type, int precision);

#endif
