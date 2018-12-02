/* HEADER */

#include "libft.h"
#include "ft_printf.h"

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
