/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftosn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 04:19:45 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/02 22:45:26 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static void		ft_nbrcpy_p(long n, int precision, char *s)
{
	if (precision > 1)
	{
		if (n >= 10 || n <= -10)
			ft_nbrcpy_p(n / 10, precision - 1, s - 1);
		else
			ft_nbrcpy_p(0, precision - 1, s - 1);
	}
	*s = ((n % 10) * (n < 0 ? -1 : 1)) + '0';
}
*/
void	ft_nbrcpy_p(long nb, int precision, char *str)
{
	if (precision > (int)ft_numlen(nb))
	{
		*(str + precision - 1) = '0';
		ft_nbrcpy_p(nb, precision - 1, str);
	}
	else
	{
		if (nb >= 10 && precision > 0)
			ft_nbrcpy_p(nb / 10, precision - 1, str);
		*(str + precision - 1) = (nb % 10) + '0';
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
	while (SIGFIGS_F < precision && (f.len_f + SIGFIGS_I) < 17)
	{
		n = n * 10;
		if ((long)n || (SIGFIGS_F == precision - 1 && ft_round(n)))
			++(f.len_f);
		else
			++(f.lead_zeros);
	}
	f.fraction = ft_round(n);
//	f.len_i = f.len_i + sign;
	return (f);
}

static char		*make_string_pos(t_fp f, int sign, int precision)
{
	char	*s;
	char	*cur;
//	// (possible sign)(first sigfig)(dot -> if precision)(rest of number)(e)(+)(exponent -> min of 2)
	s = ft_strinit('0', sign + 3 + (precision ? (precision + 1) : 0) + ((ft_numlen(SIGFIGS_I - 1) < 2) ? 2 : ft_numlen(SIGFIGS_I - 1)));
	cur = s;
	if (sign)
		cur[0] = '-';
//	// copy first digit into string
	ft_nbrcpy_p(f.integer / ft_pow(10, f.len_i - 1), 1, cur + sign);
//	// f.integer is now the number excluding the first digit
//	// f.integer = f.integer % ft_pow(10, f.len_i - 1);
//	// move cur
	if (precision)
	{
		cur[sign + 1] = '.';
		cur = cur + sign + 2;
		ft_nbrcpy_p(f.integer % ft_pow(10, f.len_i - 1), precision, cur);
	}
		// if you can, add the fractional part
	if (precision > (SIGFIGS_I - 1 + f.lead_zeros))
	{
	   cur = cur + ft_numlen(f.integer % ft_pow(10, f.len_i - 1));
	   ft_nbrcpy_p(f.fraction, precision, cur);
	}
//		cur = cur + sign + precision;
//	// copy rest of integer part into string
//	ft_nbrcpy_p(f.integer % ft_pow(10, f.len_i - 1), precision, cur); 
//	// if you can, add the fractional part
//	if (precision > (SIGFIGS_I - 1 + f.lead_zeros))
//		ft_nbrcpy_p(f.fraction, precision - SIGFIGS_I - 1 + f.lead_zeros, s + 4 + sign + SIGFIGS_I + f.lead_zeros);
//	// add the exponent
	s[sign + (precision ? precision + 1 : 0) + 1] = 'e';
	s[sign + (precision ? precision + 1 : 0) + 2] = '+';
	cur = s + ft_strlen(s) - ft_numlen(SIGFIGS_I - 1);
	ft_nbrcpy_p(SIGFIGS_I - 1, ft_numlen(SIGFIGS_I - 1), cur);
	return (s);
}

static char		*make_string_neg(t_fp f, int sign, int precision)
{
	char	*s;

	s = ft_strinit('0', precision + sign + 5 + ft_numlen(f.lead_zeros + 1));
	if (sign)
		*s = '-';
	if (precision)
		s[sign + 1] = '.';
	s[sign + 2] = '+';
	s[sign + 3] = 'e';
	s[sign + 5 + precision] = '-';
	ft_nbrcpy_p(f.fraction, precision, s + sign + 5 + f.lead_zeros);
	ft_nbrcpy_p(f.lead_zeros + 1, ft_numlen(f.lead_zeros + 1), s + precision + 5);
	return (s);
}

/*
static char		*make_string(t_fp f, int sign, int precision)
{
	char	*s;
	int		i;

	i = (sign) ? 1 : 0;

	s = ft_strinit('0', SIGFIGS_I + 1 + precision);
	if (sign)
	{
		*s = '-';
		ft_nbrcpy_p(f.integer, f.len_i - 1, s + f.len_i - 1);
	}
	else
		ft_nbrcpy_p(f.integer, f.len_i, s + f.len_i - 1);
	if (precision)
		s[SIGFIGS_I] = '.';
	if (f.trail_zeros)
		ft_nbrcpy_p(0, f.trail_zeros, s + SIGFIGS_I - 1);
	if (f.lead_zeros)
		ft_nbrcpy_p(0, f.lead_zeros, s + SIGFIGS_I + f.lead_zeros);
	if (f.len_f)
		ft_nbrcpy_p(f.fraction, f.len_f, s + SIGFIGS_I + SIGFIGS_F);
	if (precision > SIGFIGS_F)
		ft_nbrcpy_p(0, precision - SIGFIGS_F, s + SIGFIGS_I + precision);
	return (s);
}
*/

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
	//f = get_parts(n, sign, precision);
	f = get_parts(n, precision);
	if (f.integer > 0 || f.integer < 0)
		return (make_string_pos(f, sign, precision));
	return (make_string_neg(f, sign, precision));
}
