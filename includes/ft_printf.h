/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/30 15:40:21 by rreedy           ###   ########.fr       */
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
# include "../libft/includes/libft.h"

typedef unsigned long long t_ull;

char	*ft_uitoabase(t_ull n, int base);
char	*ft_itoabase(long long int n, int base);
int		base(char *fmt);
int		cmp(char *fmt, char *type);
char	*parse(char *fmt, va_list ap);
char	*parse2(char *fmt, char *s, va_list ap);
char	*to_type(char *fmt);
char	*clean(char *s, char *sub, char **fmt, size_t *len);
int		ft_printf(const char *fmt, ...);
char	*crop(char *s, char *fmt);
char	*flag(char *s, char *flags, char type);
char	*precision(char *s, char type, int precision);
char	*fill_flags(char *s, char *fmt, char type);
char	*addzeros(char *s);

#endif
