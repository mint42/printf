#include "ft_printf.h"

char	*clean(const char *format, char *str, int start)
{
	int		end;
	int		i;
	
	end = start;
	str = stresize(&str, 0, ft_strlen(format) + ft_strlen(str) - end - start);
	while (i <= start)
	{
		str[i + start] = str[i];
		str[i] = format[i];
		++i;
	}
	while (format[end])
	{
		str[i + start + end] = format[end];
		++end;
	}
	return (str);
}

char	*parse(char *format, char *str, ...)
{
	str = correspondingstring.table[]();
	str = addsign(str, format);
	str = cutandpad(str, format);
	return (str);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	char		*str;

	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (!(char *)format = ft_strchr(format + i, '%'))
			break;
		str = clean(format, parse(format, str ...), i);
		++i;
	}
	write(1, str, numtoprint(str));
	va_end(ap);
	return (numtoprint(str));
}
