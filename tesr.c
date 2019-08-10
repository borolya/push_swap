#include <stdio.h>

int main()
{
	long int n;
	char *pnbr;

	pnbr = (char*)&n;
	*pnbr = 0;
	*(pnbr + 1) = 0;
	*(pnbr + 2) = 0;
	*(pnbr + 3) = 0;
	*(pnbr + 4) = 0;
    *(pnbr + 5) = 0;
    *(pnbr + 6) = 0;
    *(pnbr + 7) = 0;
	printf("%ld", n);

}
