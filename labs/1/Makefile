hello:	hello.c
	mpiicc -o hello hello.c
run_hello: hello
	mpirun -n 2 ./hello
hello++: hello.C
	mpiicpc -o hello++ hello.C
run_hello++: hello++
	mpirun -n 2 ./hello++
run_batch: hello hello.batch
	sbatch hello.batch
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ hello hello++ *.out *.err

