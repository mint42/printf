#include "ft_printf.h"
#include "libft.h"

int	main()
{

	ft_printf("\nfloat tests\n\n");
	
	float	n;

	n = -123.4567;
	ft_putstr(ft_ftoa(n, 8));
	ft_putchar('\n');
	ft_putchar('\n');

/*

	ft_printf("\nb tests\n\n");

	ft_printf("%%b			|%b|\n", 42);
	ft_printf("%%(2)b		|%(2)b|\n", 42);
	ft_printf("%%(4)b		|%(4)b|\n", 42);
	ft_printf("%%(6)b		|%(6)b|\n", 42);
	ft_printf("%%(10)b		|%(10)b|\n", 42);
	ft_printf("%%(12)b		|%(12)b|\n", 42);
	ft_printf("%%(20)b		|%(20)b|\n", 42);
	ft_printf("%%(36)b		|%(36)b|\n", 42);

	ft_printf("\nB tests\n\n");

	ft_printf("%%B			|%B|\n", 42);
	ft_printf("%%(2)B		|%(2)B|\n", 42);
	ft_printf("%%(4)B		|%(4)B|\n", 42);
	ft_printf("%%(6)B		|%(6)B|\n", 42);
	ft_printf("%%(10)B		|%(10)B|\n", 42);
	ft_printf("%%(12)B		|%(12)B|\n", 42);
	ft_printf("%%(20)B		|%(20)B|\n", 42);
	ft_printf("%%(36)B		|%(36)B|\n", 42);

	ft_printf("\nbB precision and width tests\n\n");

	ft_printf("%%-15.10b	|%-15.10b|\n", 42);
	ft_printf("%%-15.10B	|%-15.10B|\n", 42);
	ft_printf("%%15.10b		|%15.10b|\n", 42);
	ft_printf("%%15.10B		|%15.10B|\n", 42);
	ft_printf("%%15b		|%15b|\n", 42);
	ft_printf("%%15B		|%15B|\n", 42);
	ft_printf("%%.10b		|%.10b|\n", 42);
	ft_printf("%%.10B		|%.10B|\n", 42);

	ft_printf("\nbB alternate form tests\n\n");

	ft_printf("%%#b			|%#b|\n", 0);
	ft_printf("%%#B			|%#B|\n", 0);
	ft_printf("%%#b			|%#b|\n", 42);
	ft_printf("%%#B			|%#B|\n", 42);
	ft_printf("%%#(2)b		|%#(2)b|\n", 42);
	ft_printf("%%#(2)B		|%#(2)B|\n", 42);

	ft_printf("\nbB invalid tests\n\n");

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


	ft_printf("\njustified tests\n\n");
	
	ft_printf("%%#15:5x		|%#15:5x|\n", 42);
	ft_printf("%%15:20.3s	|%15:20.3s|\n", "string");
	ft_printf("%%-15:20.3s	|%-15:20.3s|\n", "string");
	ft_printf("%%-15:(6)b	|%-15:(6)b|\n", 42);
	ft_printf("%%15:(6)b	|%15:(6)b|\n", 42);
	ft_printf("%%-15:5d		|%-15:5d|\n", 42);
	ft_printf("%%+15:5d		|%+15:5d|\n", 42);
	ft_printf("%%+*:*d		|%+*:*d|\n", 15, 5, 42);
	ft_printf("%%#15:*o		|%#15:*o|\n", 5, 42);


	ft_printf("\n+d tests\n\n");

	int	i = 3;
	while (i >= -3)
	{
		ft_printf("%%+d			|%+d|\n", i);
		--i;
	}
*/

	return (0);
}
