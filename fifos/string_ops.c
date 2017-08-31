#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


#define SIZE 100
#define SIZE_HALF ((SIZE)/2+1)

/*Functions given with the practice*/

//----------------------------------------------------------------------

void split (char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF])
{
	int a;

	a = strlen (all) / 2;

	strncpy(half1, all ,a);
	half1[a] = '\0';

	strcpy (half2, all+a);
}

//----------------------------------------------------------------------

void concatenate (char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF])
{
	printf("hi, it is the concatenate function\n");
	printf("half1 is: %s\n", half1);
	printf("half2 is: %s\n", half2);
	strcpy(all , half1);
	strcat(all , half2);
	printf("the final strinf is: %s\n", all);
}

//----------------------------------------------------------------------

