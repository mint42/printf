/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:16:12 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/09 00:15:30 by rreedy           ###   ########.fr       */
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

# define VALID_FMTS "cCsSpPdDiIbBoOuUxX%lLhHjz1234567890.+- #*()"
# define VALID_TYPE "cCsSpPdDiIbBoOuUxX%"
# define VALID_MODS "lLhHjz"

# define S sub->s
# define FLAG sub->flags
# define TYPE sub->type
# define BASE sub->base
# define PRECISION sub->p
# define WIDTH sub->w
# define JUSTIFICATION sub->j
# define LENGTH sub->len

typedef struct	s_sub
{
	char		*s;
	int			flags;
	int			type;
	int			base;
	int			p;
	int			w;
	int			j;
	size_t		len;
}				t_sub;

int				ft_printf(const char *fmt, ...);
int				ft_sprintf(char **s, const char *fmt, ...);
int				ft_printfd(int fd, const char *fmt, ...);

t_sub			makesub(char **fmt, va_list ap, int init);
int				check_flags(char **fmt, t_sub *sub);
char			*get_flags(char *fmt, t_sub *sub);
char			*get_pw(char *fmt, t_sub *sub, va_list ap);
char			*get_type(char *fmt, t_sub *sub);

char			*parse(t_sub sub, va_list ap);
char			*parse_cs(t_sub sub, char *s, va_list ap);
char			*parse_di(t_sub sub, char *s, va_list ap, int base);
char			*parse_boux(t_sub sub, char *s, va_list ap, int base);

char			*clean(char *s, t_sub sub, char **fmt, size_t *slen);
char			*crop(t_sub sub, size_t *sublen);
char			*addflags(t_sub sub);
char			*addzeros(t_sub sub, int p);
char			*precision(t_sub sub);

#endif
