#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>


#define SIZE 100
#define SIZE_HALF ((SIZE)/2+1)

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
/*
int caps (int readend , int writeend) // conversion to caps
{
	int i, r;
	char buff[SIZE];

	srand ((unsigned)getpid() ^ (unsigned)time(NULL));

	for(;;)
	{
		//READ
		r = read (readend , buff , SIZE); // receive string

		if(r<0)		// if error abort
			break;	
		
		else if(r==0)
		{
			close (writeend);
			return 0;
		}
		
		for(i=0;buff[i];i++)//converto some letter to capitals
			if(rand() > RAND_MAX/2)
				if(buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= ('a' - 'A');
		//send back
		//WRITE
		if(write (writeend , buff , 1+strlen(buff)) < 0)
			break;

	}
	
	perror ("caps");
	return -1;

}

//----------------------------------------------------------------------

int sendData (int writeend, char buff [SIZE]) // input
{
	
	if(write(writeend , buff , 1+strlen(buff))<0)
	{
		printf("SALIENDO\n");	
		return -1;
	}
	else
	{
		int weight = (strlen(buff) + 1)*sizeof(char);
		printf("%d bytes sent\n", weight);
		close(writeend);
		return 0;
	}

}

//----------------------------------------------------------------------

int receiveData (int readend, char * buff2) // ouput
{
	int r;
	char buff[SIZE];
	

	r = read(readend , buff , SIZE);

	if(r<0) // if error abort
	{
		printf("SALIENDO\n");
		return -1;
	}
	else if (r==0)// if pipe was closed
	{
		printf("BIEN RCV\n");
		strcpy(buff2,buff);
		return 0;	// finish ok
	}
	printf("The data received is:");
	fputs(buff , stdout);//show what the child returned
	printf("\n");
	int weight = (strlen(buff) + 1)*sizeof(char);
	printf("%d bytes received\n", weight);
	strcpy(buff2,buff);
	return -1;
}	

//----------------------------------------------------------------------

int caps2 (char * str) // conversion to caps
{
	int i;
	
	char buff[SIZE];
	strcpy(buff, str);
	
	srand ((unsigned)getpid() ^ (unsigned)time(NULL));


	for(i=0;buff[i];i++)//convert some letter to capitals
		if(rand() > RAND_MAX/2)
			if(buff[i] >= 'a' && buff[i] <= 'z')
				buff[i] -= ('a' - 'A');
	
	strcpy(str,buff);

	return 0;
}*/
