/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftosn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 04:19:45 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/03 21:04:51 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		nbrcpy_p(long nb, int precision, char *str)
{
	long int	mult;
	int			len;
	int			i;

	len = ft_numlen(nb);
	if (precision > len)
		precision = len;
	i = 0;
	mult = ft_pow(10, len - 1);
	while (i < precision)
	{
		str[i] = ((nb / mult) % 10) * (nb < 0 ? -1 : 1) + '0';
		++i;
		mult /= 10;
	}
}

static t_fp		get_parts(double n, int precision)
{
	t_fp	f;

	f.len_f = 0;
	f.lead_zeros = 0;
	f.trail_zeros = 0;
	while (n >= (1UL << 63))
	{
		n = n / 10;
		++(f.trail_zeros);
	}
	f.integer = (f.trail_zeros) ? ft_round(n) : (long)n;
	f.len_i = ft_numlen(f.integer);
	while (n && f.len_f < precision && (f.len_f + SIGFIGS_I) < 17)
	{
		n = n * 10;
		if ((long)n || (SIGFIGS_F == precision - 1 && ft_round(n)))
			++(f.len_f);
		else
			++(f.lead_zeros);
	}
	f.fraction = ft_round(n) - (f.integer * (long)ft_pow(10, f.len_f));
	return (f);
}

static char		*make_string_pos(t_fp f, int sign, int precision)
{
	char	*s;
	char	*cur;

	s = ft_strinit('0', sign + 3 + (precision ? (precision + 1) : 0) +
		((ft_numlen(SIGFIGS_I - 1) < 2) ? 2 : ft_numlen(SIGFIGS_I - 1)));
	cur = s;
	if (sign)
		s[0] = '-';
	nbrcpy_p(f.integer, 1, cur + sign);
	if (precision)
	{
		s[sign + 1] = '.';
		cur = cur + sign + 2;
		nbrcpy_p(f.integer % (long)ft_pow(10, f.len_i - 1), precision, cur);
	}
	if (precision > (SIGFIGS_I - 1 + f.lead_zeros))
	{
		if (f.integer % (long)ft_pow(10, f.len_i - 1))
			cur = cur + ft_numlen(f.integer) - 1;
		nbrcpy_p(f.fraction, f.len_f - 1, cur);
	}
	ft_strncpy(s + sign + ((precision) ? precision + 1 : 0) + 1, "e+", 2);
	cur = s + ft_strlen(s) - ft_numlen(SIGFIGS_I - 1);
	nbrcpy_p(SIGFIGS_I - 1, ft_numlen(SIGFIGS_I - 1), cur);
	return (s);
}

static char		*make_string_neg(t_fp f, int sign, int precision)
{
	char	*s;
	char	*cur;

	s = ft_strinit('0', sign + 3 + ((precision) ? precision + 1 : 0) +
		((ft_numlen(f.lead_zeros + 1) < 2) ? 2 : ft_numlen(f.lead_zeros + 1)));
	cur = s;
	if (sign)
		cur[0] = '-';
	nbrcpy_p(f.fraction / (long)ft_pow(10, f.len_f - 1), 1, cur + sign);
	if (precision)
	{
		cur[sign + 1] = '.';
		cur = cur + sign + 2;
		nbrcpy_p(f.fraction % (long)ft_pow(10, f.len_f - 1), precision, cur);
	}
	ft_strncpy(s + sign + ((precision) ? precision + 1 : 0) + 1, "e-", 2);
	cur = s + ft_strlen(s) - ft_numlen(f.lead_zeros + 1);
	nbrcpy_p(f.lead_zeros + 1, ft_numlen(f.lead_zeros + 1), cur);
	return (s);
}

char			*ft_ftosn(double n, int precision)
{
	t_double	doub;
	t_fp		f;
	int			sign;
	int			exponent;
	long		significand;

	doub.d = n;
	sign = (doub.l >> 63) & 1;
	exponent = ((doub.l >> 52) & 0x7ff);
	significand = (doub.l & 0x000fffffffffffff);
	if (exponent == 0x7ff)
	{
		if (significand)
			return (ft_strdup("nan"));
		else
			return (ft_strdup((sign) ? "-inf" : "inf"));
	}
	f = get_parts(n, precision);
	if (!n || f.integer > 0 || f.integer < 0)
		return (make_string_pos(f, sign, precision));
	return (make_string_neg(f, sign, precision));
}
