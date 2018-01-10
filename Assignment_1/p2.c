#include <stdio.h>
#include <omp.h>

int func(int ID)
{
	printf("Hello World %d\n", ID);
}

int main()
{
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		func(ID);
	}
	return 0;
}  