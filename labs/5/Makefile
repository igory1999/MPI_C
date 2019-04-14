run: avg
	mpirun -n 5 ./avg 100
run_batch: avg
	sbatch avg.batch
avg: avg.c
	mpiicc -o avg avg.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ avg *.out *err

