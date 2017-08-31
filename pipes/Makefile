test: unnamed_pipes.o string_ops.o 
	gcc -Wall -g unnamed_pipes2.o string_ops.o -o processes_mux_tx_demux
unnamed_pipes.o: unnamed_pipes2.c
	gcc -Wall -g -c unnamed_pipes2.c
string_ops.o: string_ops.c
	gcc -Wall -g -c string_ops.c
caps.o: caps.c
	gcc -Wall -g -c caps.c
iopipes.o: iopipes.c
	gcc -Wall -g -c iopipes.c
clean:
	rm *.o
	rm processes_mux_tx_demux
