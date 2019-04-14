run_vector: vector
	mpirun -n 2 ./vector
run_vector_batch: vector
	sbatch vector.batch
vector: vector.c
	mpiicc -std=gnu11 -o vector vector.c
run_struct: struct
	mpirun -n 2 ./struct
run_struct_batch: struct
	sbatch struct.batch
struct: struct.c
	mpiicc -o struct struct.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ vector struct *.err *.out

