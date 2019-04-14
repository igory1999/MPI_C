run: reduce
	mpirun -n 5 ./reduce
run_batch: reduce
	sbatch reduce.batch
mon:
	watch squeue -u $(USER)
reduce: reduce.c
	mpiicc -o reduce reduce.c
clean:
	rm -f *~ reduce *.out *.err
