static void		ft_nbrcpy_p(long nb, int precision, char *str)
{
	int	len;
	int	i;
	int	mult;

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
