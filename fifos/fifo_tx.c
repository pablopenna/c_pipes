/*
	fifo_tx.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h> 

#include "string_ops.h"



#define SIZE 100
#define HALF_SIZE ((SIZE)/2+1)

//~CAPS
int main(int argc, char *argv[])
{
//check for the number of the arguments
	if(argc != 3)
	{
		printf("Incorrect number of arguments.\n");
		return -1;
	}
	//PIPES
	int readEnd1 = open(argv[1], O_RDONLY);
 	int writeEnd1 = open(argv[2], O_WRONLY);
	
	
	//VARIABLES
	int i, r;
	char buff[SIZE];
	
	srand ((unsigned)getpid() ^ (unsigned)time(NULL));
	
	for(;;)
	{	
		//READING PHASE
		r = read(readEnd1, buff , SIZE); //RECEIVE STRING
		
		if(r<0)
			break;//if error -> abort
		else if(r==0)
		{
			close(writeEnd1);
			return 0;//If reading Pipe closed -> finish writing as well 
		}
		printf("Received %d bytes through pipe %s.\n", (int)strlen(buff)+1 , argv[1]);
		printf("Text before coonversion: %s\n", buff);
		//CHANGE CASE 
		for(i=0 ; buff[i] ; i++)
			if (rand() > RAND_MAX/2)
				if(buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= ('a' - 'A');
		printf("Text after coonversion: %s\n", buff);
	
		//WRITING PHASE -> WRITE THE CHANGES
		if(write(writeEnd1, buff , strlen(buff) + 1) < 0)
		{
			break;
		}
		printf("Sending %d bytes through pipe %s.\n", (int)strlen(buff)+1 , argv[2]);
	}
	
	perror("Tx");
	return -1;
}

