/*
	processes_echo_caps.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#include "string_ops.h"

#define SIZE 100
#define HALF_SIZE ((SIZE)/2+1)

int main()
{
	int i;
	int pid;
	/*
		father -> child 1 -> 	->	 ->	child 4 -> father
			   -> child 2 -> child 3 -> 	
	

	father -> I/O mux
	c1 , c2 , c3 -> Caps Tx
	c4 -> Demux

	*/
	int f_to_c1[2];//father to child 1
	int f_to_c2[2];//father to child 2
	int c2_to_c3[2];//child 2 to child 3
	int c1_to_c4[2];//child 1 to child 4
	int c3_to_c4[2];//child 3 to child 4
	int c4_to_f[2];//child 4 to father
	
	//Create all pipes
	if(pipe(f_to_c1))
	{
		perror("pipe\n");
		return -1;
	}
	if(pipe(f_to_c2))
	{
		perror("pipe\n");
		return -1;
	}
	if(pipe(c2_to_c3))
	{
		perror("pipe\n");
		return -1;
	}
	if(pipe(c1_to_c4))
	{
		perror("pipe\n");
		return -1;
	}
	if(pipe(c3_to_c4))
	{
		perror("pipe\n");
		return -1;
	}
	if(pipe(c4_to_f))
	{
		perror("pipe\n");
		return -1;
	}


	for(i=1;i<=4;i++)
	{
		pid=fork();

		if(pid==0)
			break;
	
	}
	
	if(pid==0)
	{
		switch(i)
		{
		
			case 1: //CHILD1
			{
				//	printf("Hi im %d\n",i);
					close(f_to_c1[1]);
					close(c1_to_c4[0]);
					
					char c1str [HALF_SIZE];
					
					//VARIABLES
					int i, r;
	
					srand ((unsigned)getpid() ^ (unsigned)time(NULL));
	
					for(;;)
					{	
						//READING PHASE
						r = read(f_to_c1[0], c1str , HALF_SIZE); //RECEIVE STRING
		
						if(r<0)
							break;//if error -> abort
						else if(r==0)
						{
							close(c1_to_c4[1]);
							return 0;//Reading Pipe closed -> finish writing as well 
						}
						printf("Received %d bytes through pipe f_to_c1.\n", (int)strlen(c1str)+1);
						printf("Text before conversion: %s\n", c1str);
						//CHANGE CASE
						for(i=0 ; c1str[i] ; i++)
							if (rand() > RAND_MAX/2)
								if(c1str[i] >= 'a' && c1str[i] <= 'z')
									c1str[i] -= ('a' - 'A');
						printf("Text after coonversion: %s\n", c1str);
	
						//WRITING PHASE -> WRITE THE CHANGES
						if(write(c1_to_c4[1], c1str , strlen(c1str) + 1) < 0)
						{
							break;
						}
						printf("Sending %d bytes through pipe c1_to_c4.\n", (int)strlen(c1str)+1);
					}
	
					perror("C1");
					return -1;
			}

			case 2: //CHILD2
			{
				//	printf("Hi im %d\n",i);
					close(f_to_c2[1]);
					close(c2_to_c3[0]);
					
					char c2str [HALF_SIZE];
					
					//VARIABLES
					int i, r;
	
					srand ((unsigned)getpid() ^ (unsigned)time(NULL));
	
					for(;;)
					{	
						//READING PHASE
						r = read(f_to_c2[0], c2str , HALF_SIZE); //RECEIVE STRING
		
						if(r<0)
							break;//if error -> abort
						else if(r==0)
						{
							close(c2_to_c3[1]);
							return 0;//Reading Pipe closed -> finish writing as well 
						}
						printf("Received %d bytes through pipe f_to_c2.\n", (int)strlen(c2str)+1);
						printf("Text before conversion: %s\n", c2str);
						//CHANGE CASE
						for(i=0 ; c2str[i] ; i++)
							if (rand() > RAND_MAX/2)
								if(c2str[i] >= 'a' && c2str[i] <= 'z')
									c2str[i] -= ('a' - 'A');
						printf("Text after coonversion: %s\n", c2str);
	
						//WRITING PHASE -> WRITE THE CHANGES
						if(write(c2_to_c3[1], c2str , strlen(c2str) + 1) < 0)
						{
							break;
						}
						printf("Sending %d bytes through pipe c2_to_c3.\n", (int)strlen(c2str)+1);
					}
	
					perror("C2");
					return -1;
			}


			case 3:
			{
				//	printf("Hi im %d\n",i);
					close(c2_to_c3[1]);
					close(c3_to_c4[0]);
					
					char c3str [HALF_SIZE];
					
					//VARIABLES
					int i, r;
	
					srand ((unsigned)getpid() ^ (unsigned)time(NULL));
	
					for(;;)
					{	
						//READING PHASE
						r = read(c2_to_c3[0], c3str , HALF_SIZE); //RECEIVE STRING
		
						if(r<0)
							break;//if error -> abort
						else if(r==0)
						{
							close(c3_to_c4[1]);
							return 0;//Reading Pipe closed -> finish writing as well 
						}
						printf("Received %d bytes through pipe c2_to_c3.\n", (int)strlen(c3str)+1);
						printf("Text before conversion: %s\n", c3str);
						//CHANGE CASE
						for(i=0 ; c3str[i] ; i++)
							if (rand() > RAND_MAX/2)
								if(c3str[i] >= 'a' && c3str[i] <= 'z')
									c3str[i] -= ('a' - 'A');
						printf("Text after coonversion: %s\n", c3str);
	
						//WRITING PHASE -> WRITE THE CHANGES
						if(write(c3_to_c4[1], c3str , strlen(c3str) + 1) < 0)
						{
							break;
						}
						printf("Sending %d bytes through pipe c3_to_c4.\n", (int)strlen(c3str)+1);
					}
	
					perror("C3");
					return -1;
			}

			case 4: 
			{
				//	printf("Hi im %d\n",i);
					close(c3_to_c4[1]);
					close(c1_to_c4[1]);
					close(c4_to_f[0]);
					
					char half1 [HALF_SIZE];
					char half2 [HALF_SIZE];
					char final [SIZE];
					
					//VARIABLES
					int r1 , r2;
	
					srand ((unsigned)getpid() ^ (unsigned)time(NULL));
	
					for(;;)
					{	
						//READING PHASE
						r1 = read(c1_to_c4[0], half1 , HALF_SIZE); //RECEIVE STRING
		
						if(r1<0)
							break;//if error -> abort
						else if(r1==0)
						{
							close(c3_to_c4[0]);
							return 0;//Reading Pipe closed -> close the other reading pipe
						}
						r2 = read(c3_to_c4[0], half2 , HALF_SIZE); //RECEIVE STRING
		
						if(r2<0)
							break;//if error -> abort
						else if(r2==0)
						{
							close(c1_to_c4[0]);
							return 0;//Reading Pipe closed -> close the other reading pipe
						}
						
						printf("Received %d bytes through pipe c1_to_c4.\n", (int)strlen(half1)+1);
						printf("Received %d bytes through pipe c3_to_c4.\n", (int)strlen(half2)+1);
						//CONCATENATE
						concatenate(final , half1 , half2);
						
						//WRITING PHASE -> WRITE THE CHANGES
						if(write(c4_to_f[1], final , strlen(final) + 1) < 0)
						{
							break;
						}
						printf("Sending %d bytes through pipe c4_to_f.\n", (int)strlen(final)+1);
					}
	
					perror("C4");
					return -1;
			}

		}
	}
	else //FATHER
	{
		char buff [SIZE];
		char part1 [HALF_SIZE];
		char part2 [HALF_SIZE];
		int r;
		
		printf("IM the father\n");
		//close unused pipes
		close(f_to_c1[0]);
		close(f_to_c2[0]);
		close (c4_to_f[1]);
	
		printf("Enter lines of text. Ctrl + D to exit.\n");
		for(;;)
		{
		//WRITE PHASE
			if(fgets (buff , SIZE , stdin)) // read from keyboard
			{
				//first slpit message
				split(buff , part1 , part2);
			
				if(write (f_to_c1[1], part1 , 1 + strlen(part1)) < 0)
					break;
				if(write (f_to_c2[1], part2 , 1 + strlen(part2)) < 0)
					break;
			printf("Sending %d bytes through pipe f_to_c1.\n", (int)strlen(part1)+1);
			printf("Sending %d bytes through pipe f_to_c2.\n", (int)strlen(part2)+1);		
		
			}
			else//End of File
			{
				close(f_to_c1[1]);
				close(f_to_c2[1]);
				break;
			}
		//READ PHASE
		
			r = read (c4_to_f[0] , buff , SIZE);
		
			if(r < 0) //ERROR -> Abort
				break;
			else if(r==0)
				return 0; //PIPE CLOSED -> finish
		
			printf("Received %d bytes through pipe c4_to_f.\n", (int)strlen(buff)+1);
			fputs (buff , stdout); // SHOW WHAT WAS RECEIVED FROM CHILD
	}
	
	//FINISHING
	
	perror("IoMux");
	return -1;
	}

	return 0;
}
