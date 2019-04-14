run: split
	mpirun -n 20 ./split
split: split.c
	mpicc -o split split.c
run_sbt: split_by_type  split_by_type.batch
	sbatch split_by_type.batch
split_by_type: split_by_type.c
	mpicc -o split_by_type split_by_type.c
run_cart: cart
	mpirun -n 20 ./cart
cart: cart.c
	mpicc -o cart cart.c -lm
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ split split_by_type cart *.err *.out


