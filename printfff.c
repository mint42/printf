#include <stdio.h>

int		main()
{
	printf("Adjust: Left, Width : 5, Space\n%- 5i\n", 1234567);
	printf("Adjust: Left, Width : 5, Plus\n%-+5i\n", 1234567);
	printf("Adjust: Left, Width : 5, Negative\n%- 5i\n", -1234567);
	printf("Adjust: Right, Width : 5, Space\n% 5i\n", 1234567);
	printf("Adjust: Right, Width : 5, Plus\n%+5i\n", 1234567);
	printf("Adjust: Right, Width : 5, Negative\n% 5i\n", -1234567);
	printf("Adjust: Left, Width : 15, Space\n%- 15i\n", 1234567);
	printf("Adjust: Left, Width : 15, Plus\n%-+15i\n", 1234567);
	printf("Adjust: Left, Width : 15, Negative\n%- 15i\n", -1234567);
	printf("Adjust: Right, Width : 15, Space\n% 15i\n", 1234567);
	printf("Adjust: Right, Width : 15, Plus\n%+15i\n", 1234567);
	printf("Adjust: Right, Width : 15, Negative\n% 15i\n", -1234567);
	printf("Adjust: Right, Width : 15, Space\n%15i\n", 1234567);
	printf("Adjust: Right, Width : 15, Plus\n%15i\n", 1234567);
	printf("Adjust: Right, Width : 15, Negative\n%15i\n", -1234567);
	return (0);
}
