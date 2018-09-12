/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/11 18:42:35 by rreedy           ###   ########.fr       */
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

typedef unsigned long long t_ull;

char	*ft_uitoabase(t_ull n, int base);
char	*ft_itoabase(long long int n, int base);
char	*ft_ptoa(uintptr_t p);
int		base(char *fmt);
int		cmp(char *fmt, char *type);
char	*parse(char *fmt, va_list ap);
char	*parse2(char *fmt, char *s, va_list ap);
char	*to_type(char *fmt);
char	*clean(char *s, char *sub, char **fmt, size_t *slen);
int		ft_printf(const char *fmt, ...);
char	*crop(char *sub, char *fmt, size_t *sublen);
char	*addflags(char *sub, char *flg, char type);
char	*precision(char *sub, char *flg, char type, int precision);
char	*fill_flags(char *sub, char *fmt, char type);
char	*addzeros(char *sub, char *flg, int p);

#endif
