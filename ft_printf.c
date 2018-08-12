#include "ft_printf.h"

static char *to_type(char *fmt)
{
	while (!ft_isalpha(*fmt))
		++fmt;
	if (*fmt == 'l' || *fmt == 'h' || *fmt == 'j' || *fmt == 'z')
		++fmt;
	if (*fmt == 'l' || *fmt == 'h')
		++fmt;
	return (fmt);
}

static char	*ft_uitoabase(t_ull n, int base)
{
	unsigned int	i;
	t_ull			pow;
	char			*str;
	int				toupper;

	i = 0;
	pow = 1;
	toupper = (base > 20 && (base -= 20)) ? 1 : 0;
	while (pow - 1 < n && ++i)
		pow = pow * base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'A' - 10 : '0');
		n = n / base;
	}
	return ((toupper) ? ft_strupper(str) : str);
}

static char	*ft_itoabase(long long int n, int base)
{
	int				i;
	long long int	pow;
	int				s;
	char			*str;

	i = 0;
	pow = 1;
	s = (base == 10 && n < 0) ? 1 : 0;
	if (s)
		++i;
	n = (n < 0) ? n * -1 : n;
	while (pow - 1 < n && ++i)
		pow = pow * base;
	str = ft_strnew(i + s);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'A' - 10 : '0');
		n = n / base;
	}
	if (s)
		str[0] = '-';
	return (str);
}

static char	*clean(char *s, char *sub, char *fmt)
{
	int		d;

	d = ft_strlend(fmt, '%');
	if (!s && !sub && *fmt != '%')
		return (ft_strncpy(ft_strnew(d), fmt, d));
	if (s && !sub && *fmt != '%' && ft_strchr(fmt, '%'))
		return (s);
	if (s && sub)
		s = ft_stresize(&s, 0, ft_strlen(s) + ft_strlen(sub));
	else if (!s && sub)
		s = ft_strnew(ft_strlen(sub));
	s = ft_strcat(s, sub);
	fmt = to_type(fmt) + 1;
	s = ft_stresize(&s, 0, ft_strlen(s) + ft_strlend(fmt, '%'));
	return (ft_strncat(s, fmt, ft_strlend(fmt, '%')));
}

static int		base(char *fmt)
{
	fmt = to_type(fmt);
	if (*fmt == 'o' || *fmt == 'O')
		return (!ft_isupper(*fmt) ? 6 : 26);
	if (*fmt == 'x' || *fmt == 'X')
		return (!ft_isupper(*fmt) ? 8 : 28);
	if (*fmt == 'u' || *fmt == 'U')
		return (!ft_isupper(*fmt) ? 10 : 30);
	return (0);
}

static int		cmp(char *fmt, char *type)
{
	++fmt;
	if (*fmt == '%' && *type == '%')
		return (1);
	while (fmt && !ft_isalpha(*fmt))
		++fmt;
	while (type && *type != ',' && *type == *fmt)
	{
		++type;
		++fmt;
	}
	if (*type != ',')
		return (0);
	while (*type++)
		if (*fmt == *type)
			return (1);
	return (0);
}

static char	*parse2(char *fmt, char *s, va_list ap)
{
	if (cmp(fmt,",ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base(fmt));
//	else if (cmp(fmt, "hh,ouUxX"))
//		s = ft_uctoa(va_arg(ap, unsigned char), base(fmt));
	else if (cmp(fmt, "h,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, int), base(fmt));
	else if (cmp(fmt, "l,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base(fmt));
	else if (cmp(fmt, "ll,ouUxX"))
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base(fmt));
	else if (cmp(fmt, "j,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, uintmax_t), base(fmt));
	else if (cmp(fmt, "z,ouUxX"))
		s = ft_itoabase((long long int)va_arg(ap, size_t), base(fmt));	
	else if (cmp(fmt, ",c"))
		s = ft_ctoa(va_arg(ap, int));
//	else if (cmp(fmt, "l,c") || cmp(fmt, ",C"))
//		s = va_arg(ap, wint_t);
	else if (cmp(fmt, ",s"))
		s = ft_strdup(va_arg(ap, char *));
//	else if (cmp(fmt, "l,s") || cmp(fmt, "S"))
//		s = va_arg(ap, wint_t *);
	else if (cmp(fmt, ",p"))
		s = ft_strdup((char *)va_arg(ap, void *));
	return (s);
}

static char	*parse(char *fmt, va_list ap)
{
	char	*s;
	s = 0;
	if (cmp(fmt, "%"))
		s = ft_strdup("%");
	else if (cmp(fmt, ",di"))
		s = ft_itoabase((long long int)va_arg(ap, int), 10);
	else if (cmp(fmt, "hh,di"))
		s = ft_ctoa(va_arg(ap, int));
	else if (cmp(fmt, "h,di"))
		s = ft_itoabase((long long int)va_arg(ap, int), 10);
	else if (cmp(fmt, "l,di"))
		s = ft_itoabase ((long long int)va_arg(ap, long int), 10);
	else if (cmp(fmt, "ll,di"))
		s = ft_itoabase((long long int)va_arg(ap, long long int), 10);
	else if (cmp(fmt, "j,di"))
		s = ft_itoabase((long long int)va_arg(ap, intmax_t), 10);
	else if (cmp(fmt, "z,di"))
		s = ft_itoabase((long long int)va_arg(ap, size_t), 10);
	if (!s)
		s = parse2(fmt, s, ap);
//	s = addsign(s, fmt);
//	s = cutandpad(s, fmt);
	return (s);
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*cur;
	char		*s;

	cur = (char *)fmt;
	va_start(ap, fmt);
	s = clean(0, 0, (char *)fmt);
	while (cur && *cur)
	{
		if (!(cur = ft_strchr(cur, '%')))
		{
			s = clean(s, 0, (char *)fmt);
			break;
		}
		s = clean(s, parse(cur, ap), cur);
		++cur;
	}
	ft_putstr(s);
	va_end(ap);
	return (0);
}

/******************************************************************************
//	
//		di             ouUxX                   c           s             p
//
//	no	int            unsigned int            int         char*         void*
//  hh	char           unsigned char
//  h	short int      unsigned short int
//  l	long int       unsigned long int       wint_t      wint_t*
//  ll	long long int  unsigned long long int
//  j	intmax_t       uintmax_t
//  z	size_t         size_t
//
****************************************************************************/		


int		main()
{
//	int		i = 12345;
	unsigned long int longboi= 3688522574;
//	int		c = 75;
	
	ft_printf("FT_PRINTF:\nunsigned long int: %lu\n\n", longboi);
	printf("PRINTF:\nunsigned long int: %lu\n\n", longboi);
	return (0);
}
