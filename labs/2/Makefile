run: send_receive
	mpirun -n 2 ./send_receive
run_batch: send_receive
	sbatch send_receive.batch
send_receive: send_receive.c
	mpiicc -o send_receive send_receive.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ send_receive *.out *.err

