all: run run_p run_n clean

run: bcast
	mpirun -n 5 ./bcast 11
run_batch: bcast
	sbatch bcast.batch
bcast: bcast.c
	mpiicc -o bcast bcast.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ bcast *.out *.err

