/*
	fifo1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "string_ops.h"



#define SIZE 100
#define HALF_SIZE ((SIZE)/2+1)

//~IO

int main(int argc, char * argv[])
{
	if(argc!=4)
	{
		printf("Incorrect number of parameters\n");
		return -1;
	}
	
	
	//ORDER MATTERS
	int	writeEnd1 = open(argv[2], O_WRONLY);
	int	writeEnd2 = open(argv[3], O_WRONLY);	
	int readEnd1 = open(argv[1],O_RDONLY);
	
	//VARIABLES
	char buff [SIZE];
	char part1 [HALF_SIZE];
	char part2 [HALF_SIZE];
	int r;
	
	printf("Enter lines of text. Ctrl + D to exit.\n");
	for(;;)
	{
	//WRITE PHASE
		if(fgets (buff , SIZE , stdin)) // read from keyboard
		{
			//first slpit message
			split(buff , part1 , part2);
			
			//Check for errors, if any -> abort
			if(write (writeEnd1, part1 , 1 + strlen(part1)) < 0)
				break;
			if(write (writeEnd2, part2 , 1 + strlen(part2)) < 0)
				break;
		printf("Sending %d bytes through pipe %s.\n", (int)strlen(part1)+1 , argv[2]);
		printf("Sending %d bytes through pipe %s.\n", (int)strlen(part2)+1 , argv[3]);		
		
		}
		else//End of File
		{
			close(writeEnd1);
			close(writeEnd2);
		}
	//READ PHASE
		
		r = read (readEnd1 , buff , SIZE);
		
		if(r < 0) //ERROR -> Abort
			break;
		else if(r==0)
			return 0; //PIPE CLOSED -> finish
		
		printf("Received %d bytes through pipe %s.\n", (int)strlen(buff)+1 , argv[1]);
		fputs (buff , stdout); // SHOW WHAT WAS RECEIVED FROM CHILD
	}
	
	//FINISHING
	perror("IoMux");
	return -1;
	

}
