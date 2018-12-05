/* HEADER */

#include "libft.h"
#include "ft_printf.h"

/*
char	*ft_ftoa(float n, int precision)
{
	char	*s;
	char	*cur;
	int		len;

	len = ft_numlen((long long int)n);
	s = ft_strinit(' ', len + precision + 1);
	cur = s;
	cur[len] = '.';
	ft_strncpy(s, ft_itoabase((long long int)n, 10), len);
	if (n < 0)
		n = n * -1;
	n = n - (long long int)n;
	cur = cur + len + 1;
	while (precision--)
	{
		n = n * 10;
		*cur = (int)n + 48;
		n = n - (int)n;
		++cur;
	}
	return (s);
}
*/
char	*ft_ftoa(double n, int precision)
{
	int		sign;
	int		exponent;
	int		intpart;
	int		decimalpart;
	long	significand;
	int		b;

	b = 2;
	sign = (n >> 63) ? -1 : 1;
	exponent = (n >> 52) & (0 << 53);
	exponent = (exponent) - DOUBLE_EXPONENT_BIAS (1023) (+ 1);
	significand = n & (0x000 << 64);
//	significand = n & (0x1 << 53);
	intpart = (exponent >= 0) ? n << (52 - exponent) : 0;
	decimalpart = 
	

	

}
