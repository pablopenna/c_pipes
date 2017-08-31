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

int main(int argc, char *argv[])
{

	if(argc!=4)
	{
		printf("Incorrect number of arguments");
		return -1;
	}
	
	//PIPES
	int readEnd1 = open(argv[1], O_RDONLY);
	int readEnd2 = open(argv[2], O_RDONLY);
	int writeEnd1 = open(argv[3], O_WRONLY);
	
	//VARIABLES
	char buff [SIZE];
	char part1 [HALF_SIZE];
	char part2 [HALF_SIZE];
	
	int r1, r2 , w1;
	
	for(;;)
	{
		r1 = read(readEnd1 , part1 , HALF_SIZE);
		
		if(r1 < 0)//ERROR READING -> EXIT
			break;
		else if(r1 == 0)// READPIPE 1 CLOSED -> CLOSE READPIPE 2
		{
			close(readEnd2);
			return 0;
		}
		
		r2 = read(readEnd2 , part2 , HALF_SIZE);
		
		if(r2 < 0)//ERROR READING -> EXIT
			break;
		else if(r2 == 0)// READPIPE 1 CLOSED -> CLOSE READPIPE 2
		{
			close(readEnd1);
			return 0;
		}
		printf("Received %d bytes through pipe %s.\n", (int)strlen(part1)+1 , argv[1]);
		printf("Received %d bytes through pipe %s.\n", (int)strlen(part2)+1 , argv[2]);
		//here we've got the two halves, so lets join them
		concatenate(buff , part1 , part2);
		
		w1 = write(writeEnd1 , buff , strlen(buff) + 1);
		
		if(w1 < 0)//check for errors
		{
			printf("Malfunctioning when writing at IoMux from Demux.\n");
			break;
		}
		printf("Sending %d bytes through pipe %s.\n", (int)strlen(buff)+1 , argv[3]);
	}
	perror("Demux");
	return -1;
}
