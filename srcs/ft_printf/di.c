/*
** HEADER di
*/

#include "ft_printf.h"

static void		zeros_di(t_sub *sub)
{
	int		i;

	i = ((FLAGS & 0x2) && PREC == -1) ? 1 : 0;
	while (S && S[i] == ' ')
		S[i++] = '0';
	if (i && (S[i] == '-' || S[i] == '+'))
	{
		S[0] = S[i];
		S[i] = '0';
	}
}

static void		precision_di(t_sub *sub)
{
	if (S[0] != '-' && (size_t)PREC > ft_strlen(S))
		S = ft_shift(&(S), PREC - ft_strlen(S), PREC);
	else if (S[0] == '-' && (size_t)PREC >= ft_strlen(S))
		S = ft_shift(&(S), PREC - ft_strlen(S) + 1, PREC + 1);
	zeros_di(sub);
}

static void		flags_di(t_sub *sub)
{
	S = ft_shift(&(S), 1, ft_strlen(S) + 1);
	if (FLAGS & 0x4)
		S[0] = '+';
}

static void		width_di(t_sub *sub)
{
	if ((size_t)JUST > (size_t)WIDTH - LEN)
		JUST = WIDTH - LEN;
	if (!(FLAGS & 0x30))
		JUST = WIDTH - JUST - LEN;
	else if ((FLAGS & 0x30) == 0x30)
		JUST = (WIDTH - LEN) / 2;
	else if (FLAGS & 0x20)
		JUST = ((WIDTH - LEN) / 2) + (((WIDTH - LEN) % 2) ? 1 : 0);
	S = ft_shift(&(S), JUST, WIDTH);
	LEN = ft_strlen(S);
}

/*
**	add to checks the possibility of base 10 with b haveing +
**	also take out last if from checks and do it individually
*/

char	*crop_di(t_sub *sub)
{
	if (ft_strequ(S, "0") && (FLAGS & 0x4))
		FLAGS = FLAGS ^ 0x6;
	if (PREC >= 0)
		precision_di(sub);
	if ((FLAGS & 0x6) && (S[0] != '-'))
		flags_di(sub);
	LEN = ft_strlen(S);
	if ((size_t)WIDTH > LEN)
		width_di(sub);
	if (FLAGS & 0x8)
		zeros_di(sub);
	return (S);
}
