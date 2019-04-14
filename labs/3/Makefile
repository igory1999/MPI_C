run: isend_irecv
	mpirun -n 2 ./isend_irecv
run_batch: isend_irecv
	sbatch isend_irecv.batch
isend_irecv: isend_irecv.c
	mpicc -o isend_irecv isend_irecv.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ isend_irecv *.out *.err

