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

static char	*ft_uitoabase(t_ull value, int base)
{
	unsigned int	i;
	unsigned int	pow;
	char			*str;
	int				toupper;

	i = 0;
	pow = 1;
	toupper = (base > 20 && (base -= 20)) ? 1 : 0;
	while (pow - 1 < value && ++i)
		pow = pow * base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i] = (value % base) + (value % base > 9 ? 'A' - 10 : 'O');
		value = value / base;
	}
	return ((toupper) ? ft_strupper(str) : str);
}

static char	*ft_itoabase(long long int value, int base)
{
	int		i;
	int		pow;
	int		sign;
	char	*str;

	i = 0;
	pow = 1;
	sign = (base == 10 && value < 0) ? 1 : 0;
	value = (value < 0) ? value * -1 : value;
	while (pow - 1 < value && ++i)
		pow = pow * base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i + sign] = (value % base) + (value % base > 9 ? 'A' - 10 : 'O');
		value = value / base;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

static char	*clean(char *s, char *sub, char *fmt)
{
	char	*cur;

	if (!sub && *fmt != '%' && ft_strchr(fmt, '%') && s)
		return (s);
	if (sub)
	{
		s = ft_stresize(&s, 0, ft_strlen(s) + ft_strlen(sub));
		cur = s + ft_strlen(s);
		while (sub && *sub)
			*cur++ = *sub++;
		*cur = '\0';
	}
	fmt = (*fmt == '%') ? to_type(fmt) + 1 : fmt;
	s = ft_stresize(&s, 0, ft_strlend(fmt, '%'));
	cur = s + ft_strlen(s);
	while (fmt && *fmt != '%')
		*cur++ = *fmt++;
	*cur = '\0';
	return (s);

//	i = 0;
//	end = start;
//	while (!ft_isalpha(*cur))
//		++cur;
//	if (*cur == 'l' || *cur == 'h' || *cur == 'j' || *cur == 'z')
//		++cur;
//	if (*cur == 'l' || *cur == 'h')
//		++cur;
//	++cur;
//	str = ft_stresize(&str, 0, ft_strlen(fmt) + ft_strlen(str) - end - start);
//	while (i <= start)
//	{
//		str[i + start] = str[i];
//		str[i] = fmt[i];
//		++i;
//	}
//	while (fmt[end])
//	{
//		str[i + start + end] = fmt[end];
//		++end;
//	}
//	str[i + start + end] = '\0';
//	return (str);
}

static int		base(char *fmt)
{
	fmt = to_type(fmt);
	if (*fmt == 'o' || *fmt == 'O')
		return (!ft_isupper(*fmt) ? 26 : 6);
	if (*fmt == 'x' || *fmt == 'X')
		return (!ft_isupper(*fmt) ? 28 : 8);
	if (*fmt == 'u' || *fmt == 'U')
		return (!ft_isupper(*fmt) ? 30 : 10);
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
	{
		s = ft_strdup("%");
	}
	else if (cmp(fmt, ",di"))
	{
		s = ft_itoabase((long long int)va_arg(ap, int), 10);
	}	
	else if (cmp(fmt, "hh,di"))
	{
		s = ft_ctoa(va_arg(ap, int));
	}
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
	printf("test\n");
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
	s = 0;	
	while (cur && *cur)
		if (!(cur = ft_strchr(cur, '%')))
		{
			s = clean(s, 0, (char *)fmt);
			break;
		}
		s = clean(s, parse(cur, ap), cur);
		++cur;
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
	int		i = 12345;
	char 	*str = "this is a string";
	
	ft_printf("FT_PRINTF:\nint: %d\nstring: %s\n\n", i, str);
	printf("PRINTF:\nint: %d\nstring: %s\n\n", i, str);
	return (0);
}
