#include "ex1_q1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	List* polygonsList = makeEmptyList();

	char command[MAX_COMMAND + 1]; // plus '\0'

	while(1)
	{
		int ignored = scanf("%s", command);
		if(run_ex1_q1(command, polygonsList))
			break;
	}
	
	freeList(polygonsList);
}