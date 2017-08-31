all: IoMux Tx Demux Pipes
	echo all done
	
Pipes:
	mknod T0 p
	mknod T1 p
	mknod T2 p
	mknod T3 p
	mknod T4 p
	mknod T5 p
	mknod T6 p
	mknod T7 p
	mknod T8 p
	mknod T9 p
IoMux: fifo_IoMux.o string_ops.o
	gcc -Wall -g fifo_IoMux.o string_ops.o  -o io_mux
Tx: fifo_tx.o string_ops.o 
	gcc -Wall -g fifo_tx.o string_ops.o -o tx
Demux: fifo_demux.o string_ops.o 
	gcc -Wall -g fifo_demux.o string_ops.o -o demux
fifo_IoMux.o: fifo_IoMux.c
	gcc -Wall -g -c fifo_IoMux.c
fifo_tx.o: fifo_tx.c
	gcc -Wall -g -c fifo_tx.c
fifo_demux.o: fifo_demux.c
	gcc -Wall -g -c fifo_demux.c
string_ops.o: string_ops.c
	gcc -Wall -g -c string_ops.c

clean:
	rm *.o
	rm io_mux ; rm demux ; rm tx
	rm T?
