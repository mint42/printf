/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:07:03 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/14 23:11:23 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

# define TESTS 12

static void		jump(int index);
void			display_menu();

void			display_all()
{
	int		i;

	i = 2;
	while (i <= TESTS)
		jump(i++);
}

void		random_tests()
{
	ft_printf("%%s		|%s|\n", 0);
	ft_printf("%%.4s	|%.4s|\n", 0);
	ft_printf("%%u		|%u|\n", 42);
	ft_printf("%%c		|%c|\n", 0);
	ft_printf("%%c		|%c|\n", -0);
	ft_printf("%%d		|%d|\n", -0);
}

void		c()
{
	ft_printf("\n%%c tests\n\n");

	ft_printf("%%c%%c		|%c%c|\n", '4', '2');
	ft_printf("%%c %%c		|%c %c|\n", '4', '2');
	ft_printf("%%5c			|%5c|\n", 0);
	ft_printf("%%10:5c		|%10:5c|\n", 0);
}

void		pP()
{
	int		e;

	e = 18;
	ft_printf("\n%%pP tests\n\n");
	
	ft_printf("%%p		|%p|\n", &e);
	ft_printf("%%p		|%p|\n", 0);
	ft_printf("%%-13p	|%-13p|\n", &e);
}

void		fF()
{
	ft_printf("\n%%f tests\n\n");

	float	n;

	n = -123.4567;
	ft_putstr(ft_ftoa(n, 8));
	ft_putchar('\n');
	ft_putstr(ft_ftoa(5.0505000F, 5));
	ft_putchar('\n');
	ft_putchar('\n');
}

void		CS()
{

	ft_printf("\n%%C tests\n\n");

	ft_printf("%%C			|%C|\n", L'\u03c0');
	ft_printf("%%C			|%C|\n", L'\U0001F47D');
	ft_printf("%%C			|%C|\n", L'\U0001F989');
	ft_printf("%%C			|%C|\n", L'\U0001F95E');
	ft_printf("%%C			|%C|\n", L'我');
	ft_printf("%%C			|%C|\n", 0);

	ft_printf("\n%%S tests\n\n");

	ft_printf("%%S			|%S|\n", L"pi: \u03c0 alien: \U0001F47D owl: \U0001F989");
	ft_printf("%%S			|%S|\n", L"\U0001F47D \u03c0 。 \U0001F989");
	ft_printf("%%S			|%S|\n", L"\U0001F9E1 \U0001F49B \U0001F49A \U0001F499 \U0001F49C \U0001F5A4");
	ft_printf("%%S			|%S|\n", L"\U0001F384 \U0001F381 \U0001F98C \U0001F385");
	ft_printf("%%S			|%S|\n", L"我是一只猫。");
	ft_printf("%%S			|%S|\n", 0);

	ft_printf("\n%%CS precision and width tests\n\n");

	ft_printf("%%-15.10C	|%-15.10C|\n", 0);
	ft_printf("%%-15.10C	|%-15.10C|\n", L'\u03c0');
	ft_printf("%%15.10C		|%15.10C|\n", L'\U0001F989');
	ft_printf("%%15C		|%15C|\n", L'\u03c0');
	ft_printf("%%5C			|%5C|\n", L'\U0001F47D');
	ft_printf("%%3C			|%3C|\n", L'\U0001F47D');
	ft_printf("%%.10C		|%.10C|\n", L'\u03c0');
	ft_printf("%%.0C		|%.0C|\n", L'\U0001F95E');
	ft_printf("\n");
  	ft_printf("%%-15.10S	|%-15.10S|\n", 0);
	ft_printf("%%-15.5S		|%-15.5S|\n", 0);
	ft_printf("%%-15.10S	|%-15.10S|\n", L"\u03c0\u03c0\u03c0\u03c0\u03c0\u03c0\u03c0");
	ft_printf("%%15.5S		|%15.5S|\n", L"\u03c0\u03c0\u03c0\u03c0\u03c0\u03c0\u03c0");
	ft_printf("%%-15.10S	|%-15.10S|\n", L"我是一只猫。");
	ft_printf("%%15.5S		|%15.5S|\n", L"我是一只猫。");
	ft_printf("%%5.15S		|%5.15S|\n", L"我是一只猫。");
	ft_printf("%%5.1S		|%5.1S|\n", L"我是一只猫。");
	ft_printf("%%15S		|%15S|\n", L"\U0001F95E");
	ft_printf("%%5S			|%5S|\n", L"\U0001F95E");
	ft_printf("%%3S			|%3S|\n", L"\U0001F95E");
	ft_printf("%%.10S		|%.10S|\n", L"\U0001F9E1 \U0001F49B \U0001F49A \U0001F499 \U0001F49C \U0001F5A4");
	ft_printf("%%.3S		|%.3S|\n", L"\U0001F9E1 \U0001F49B \U0001F49A \U0001F499 \U0001F49C \U0001F5A4");
	ft_printf("%%.0S		|%.0S|\n", L"\U0001F9E1 \U0001F49B \U0001F49A \U0001F499 \U0001F49C \U0001F5A4");
}

void		bB()
{
	ft_printf("\n%%b tests\n\n");

	ft_printf("%%b			|%b|\n", 42);
	ft_printf("%%(2)b		|%(2)b|\n", 42);	
	ft_printf("%%(4)b		|%(4)b|\n", 42);
	ft_printf("%%(6)b		|%(6)b|\n", 42);
	ft_printf("%%(10)b		|%(10)b|\n", 42);
	ft_printf("%%(12)b		|%(12)b|\n", 42);
	ft_printf("%%(25)b		|%(25)b|\n", 443);
	ft_printf("%%(30)b		|%(30)b|\n", 637574);
	ft_printf("%%(36)b		|%(36)b|\n", 624769209);

	ft_printf("\n%%B tests\n\n");

	ft_printf("%%B			|%B|\n", 42);
	ft_printf("%%(2)B		|%(2)B|\n", 42);
	ft_printf("%%(4)B		|%(4)B|\n", 42);
	ft_printf("%%(6)B		|%(6)B|\n", 42);
	ft_printf("%%(10)B		|%(10)B|\n", 42);
	ft_printf("%%(12)B		|%(12)B|\n", 42);
	ft_printf("%%(25)B		|%(25)B|\n", 443);
	ft_printf("%%(30)B		|%(30)B|\n", 637574);
	ft_printf("%%(36)B		|%(36)B|\n", 624769209);

	ft_printf("\n%%bB precision and width tests\n\n");

	ft_printf("%%-15.10b	|%-15.10b|\n", 42);
	ft_printf("%%-15.10B	|%-15.10B|\n", 42);
	ft_printf("%%15.10b		|%15.10b|\n", 42);
	ft_printf("%%15.10B		|%15.10B|\n", 42);
	ft_printf("%%15b		|%15b|\n", 42);
	ft_printf("%%15B		|%15B|\n", 42);
	ft_printf("%%.10b		|%.10b|\n", 42);
	ft_printf("%%.10B		|%.10B|\n", 42);

	ft_printf("\n%%bB alternate form tests\n\n");

	ft_printf("%%#b			|%#b|\n", 0);
	ft_printf("%%#B			|%#B|\n", 0);
	ft_printf("%%#b			|%#b|\n", 42);
	ft_printf("%%#B			|%#B|\n", 42);
	ft_printf("%%#(2)b		|%#(2)b|\n", 42);
	ft_printf("%%#(2)B		|%#(2)B|\n", 42);
	ft_printf("%%#(8)b		|%#(8)b|\n", 0);
	ft_printf("%%#(8)B		|%#(8)B|\n", 0);
	ft_printf("%%#(8)b		|%#(8)b|\n", 42);
	ft_printf("%%#(8)B		|%#(8)B|\n", 42);
	ft_printf("%%#(16)b		|%#(16)b|\n", 0);
	ft_printf("%%#(16)B		|%#(16)B|\n", 0);
	ft_printf("%%#(16)b		|%#(16)b|\n", 42);
	ft_printf("%%#(16)B		|%#(16)B|\n", 42);
	ft_printf("%%+(10)b		|%+(10)b|\n", 0);
	ft_printf("%%+(10)B		|%+(10)B|\n", 0);
	ft_printf("%%+(10)b		|%+(10)b|\n", 42);
	ft_printf("%%+(10)B		|%+(10)B|\n", 42);
	ft_printf("%%+(10)b		|%+(10)b|\n", -42);
	ft_printf("%%+(10)B		|%+(10)B|\n", -42);
	ft_printf("%% (10)b		|% (10)b|\n", 0);
	ft_printf("%% (10)B		|% (10)B|\n", 0);
	ft_printf("%% (10)b		|% (10)b|\n", 42);
	ft_printf("%% (10)B		|% (10)B|\n", 42);
	ft_printf("%% (10)b		|% (10)b|\n", -42);
	ft_printf("%% (10)B		|% (10)B|\n", -42);

	ft_printf("\n%%bB invalid tests\n\n");

	ft_printf("%%(1)b		|%(1)b|\n", 42);
	ft_printf("%%(1)B		|%(1)B|\n", 42);
	ft_printf("%%(37)b		|%(37)b|\n", 42);
	ft_printf("%%(37)B		|%(37)B|\n", 42);
	ft_printf("%%(6b		|%(6b|\n", 42);
	ft_printf("%%(6B		|%(6B|\n", 42);
	ft_printf("%%6)b		|%6)b|\n", 42);
	ft_printf("%%6)B		|%6)B|\n", 42);
	ft_printf("%%#(6)b		|%#(6)b|\n", 42);
	ft_printf("%%#(6)B		|%#(6)B|\n", 42);
	ft_printf("%%(6)d		|%(6)d|\n", 42);
}

void		justify()
{
	ft_printf("\njustified tests\n\n");
	
	ft_printf("%%#15:5x		|%#15:5x|\n", 42);
	ft_printf("%%-15:5S		|%-15:5S|\n", L"\U0001F989");
	ft_printf("%%^15:5S		|%^15:5S|\n", L"\U0001F989");
	ft_printf("%%15:20.3s	|%15:20.3s|\n", "string");
	ft_printf("%%-15:20.3s	|%-15:20.3s|\n", "string");
	ft_printf("%%-15:(6)b	|%-15:(6)b|\n", 42);
	ft_printf("%%15:(6)b	|%15:(6)b|\n", 42);
	ft_printf("%%-15:5d		|%-15:5d|\n", 42);
	ft_printf("%%+15:5d		|%+15:5d|\n", 42);
	ft_printf("%%+*:*d		|%+*:*d|\n", 15, 5, 42);
	ft_printf("%%#15:*o		|%#15:*o|\n", 5, 42);
}

void		midflag()
{
	ft_printf("\n mid justified tests\n\n");

	ft_printf("%%^16s		|%^16s|\n", "string");
	ft_printf("%%^16.5s		|%^16.5s|\n", "string");
	ft_printf("%%^16.0s		|%^16.0s|\n", "string");
	ft_printf("%%^-16.5s	|%^-16.5s|\n", "string");
	ft_printf("%%^17s		|%^17s|\n", "string");
	ft_printf("%%-^17s		|%-^17s|\n", "string");
	ft_printf("%%^17.5s		|%^17.5s|\n", "string");
	ft_printf("%%-^17.5		|%-^17.5s|\n", "string");
	ft_printf("%%^15S		|%^15S|\n", L"\U0001F989");
	ft_printf("%%-^15S		|%-^15S|\n", L"\U0001F989");
	ft_printf("%%^15S		|%^15S|\n", L"\U0001F989");
}

void		plus_and_space()
{
	ft_printf("\n%%plus and space flags tests\n\n");

	int	i = 3;
	while (i >= -3)
	{
		ft_printf("%%+d			|%+d|\n", i);
		--i;
	}
	ft_printf("\n");
	i = 3;
	while (i >= -3)
	{
		ft_printf("%% d			|% d|\n", i);
		--i;
	}
}

void		leaks()
{
	ft_printf("\nLeaks\n\n");
	
	ft_printf("\n");
	ft_printf("%%\n");
	ft_printf("%d\n", 42);
	ft_printf("%d%d\n", 42, 41);
	ft_printf("%d%d%d\n", 42, 43, 44);
	ft_printf("%ld\n", 2147483647);
	ft_printf("%lld\n", 9223372036854775807);
	ft_printf("%x\n", 505);
	ft_printf("%X\n", 505);
	ft_printf("%p\n", &ft_printf);
	ft_printf("%20.15d\n", 54321);
	ft_printf("%-10d\n", 3);
	ft_printf("% d\n", 3);
	ft_printf("%+d\n", 3);
	ft_printf("%010d\n", 1);
	ft_printf("%hhd\n", 0);
	ft_printf("%jd\n", 9223372036854775807);
	ft_printf("%zd\n", 4294967295);
	ft_printf("thing |%5.8J| thing\n");
	ft_printf("%\n");
	ft_printf("\n");
	ft_printf("%U\n", 4294967295);
	ft_printf("%u\n", 4294967295);
	ft_printf("%o\n", 40);
	ft_printf("%%#08x\n", 42);
	ft_printf("%x\n", 1000);
	ft_printf("%#X\n", 1000);
	ft_printf("%s\n", NULL);
	ft_printf("%S\n", L"ݗݜशব");
	ft_printf("%s%s\n", "test", "test");
	ft_printf("%s%s%s\n", "test", "test", "test");
	ft_printf("%C\n", 15000);
}

void		undefined_behavior()
{
	ft_printf("\nUndefined Behavior tests\n\n");

	ft_printf("%\n");
	ft_printf("% \n");
	ft_printf("% h\n");
	ft_printf("%Z\n");
	ft_printf("% hZ\n");
	ft_printf("%05%\n");
	ft_printf("%-05%\n");
   	ft_printf("% hZ%\n");
	ft_printf("% Z\n", "test");
	ft_printf("% Z \n", "test");
	ft_printf("% Z%s\n", "test");
	ft_printf("%000   %\n", "test");
	ft_printf("%%%\n", "test");
	ft_printf("%%   %\n", "test");
	ft_printf("%ll#x\n", 9223372036854775807);
	ft_printf("%010s is a string\n", "this");
	ft_printf("%-010s is a string\n", "this");
	ft_printf("%05c\n", 42);
	ft_printf("% Z\n", 42);
	ft_printf("%0 d\n", 42);
	ft_printf("%0 d\n", -42);
	ft_printf("% 0d\n", 42);
	ft_printf("% 0d\n", -42);
	ft_printf("%5+d\n", 42);
	ft_printf("%5+d\n", -42);
	ft_printf("%-5+d\n", 42);
	ft_printf("%-0+5d\n", 42);
	ft_printf("%-5+d\n", -42);
	ft_printf("%-0+5d\n", -42);
	ft_printf("%zhd\n", 4294967296);
	ft_printf("%jzd\n", 9223372036854775807);
	ft_printf("%jhd\n", 9223372036854775807);
	ft_printf("%lhl\n", 9223372036854775807);
	ft_printf("%lhlz\n", 9223372036854775807);
	ft_printf("%zj\n", 9223372036854775807);
	ft_printf("%lhh\n", 2147483647);
	ft_printf("%hhld\n", 128);
	ft_printf("@main_ftprintf: %####0000 33..1..#00d\n", 256);
	ft_printf("@main_ftprintf: %####0000 33..1d\n", 256);
	ft_printf("@main_ftprintf: %###-#0000 33...12..#0+0d\n", 256);
}

void		display_menu()
{
	ft_printf("\nPlease Choose a Valid Argument:\n\n");
	ft_printf("1 ->		Check All\n");
	ft_printf("2 ->		Type %%f %%F\n");
	ft_printf("3 ->		Type %%b %%B\n");
	ft_printf("4 ->		Type %%C %%S\n");
	ft_printf("5 ->		Type %%c\n");
	ft_printf("6 ->		Type %%p %%P\n");
	ft_printf("7 ->		Justify\n");
	ft_printf("8 ->		Middle Justify\n");
	ft_printf("9 ->		Plus and Space flags\n");
	ft_printf("10 ->	Leaks\n");
	ft_printf("11 ->	Undefined Behavior\n");
	ft_printf("12 ->	random\n");
}

static void		jump(int index)
{
		
	static void	(*j[])() = 
	{
		display_all,
		fF,
		bB,
		CS,
		c,
		pP,
		justify,
		midflag,
		plus_and_space,
		leaks,
		undefined_behavior,
		random_tests,
	};

	j[index - 1]();
}

int	main(int argc, char **argv)
{
	int		av;
	int		ac;

	av = 0;
	ac = 1;

	if (argc == 1)
		display_menu();
	while (ac < argc)
	{
		av = ft_atoi(argv[ac]);
		if (av == 1)
		{
			jump(1);
			return (0);
		}
		++ac;
	}
	ac = 1;
	while (ac < argc)
	{
		av = ft_atoi(argv[ac]);
		if (av < 1 || av > TESTS)
		{
			ft_printf("\n%d is not a Valid Argument.\n", av);
			display_menu();
			return (0);
		}
		jump(av);
		++ac;
	}
	return (0);
}
