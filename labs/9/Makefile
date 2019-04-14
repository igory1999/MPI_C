run: mkrandpfile xrandpfile mkdrandfiles darray
	sbatch io.batch
mkrandpfile: mkrandpfile.c
	mpiicc -DDEBUG -o mkrandpfile mkrandpfile.c
mkdrandfiles: mkdrandfiles.c
	mpiicc -DDEBUG -o mkdrandfiles mkdrandfiles.c
xrandpfile: xrandpfile.c
	mpiicc -DDEBUG -o xrandpfile xrandpfile.c

darray: darray.c
	mpiicc -o darray darray.c
mon:
	watch squeue -u $(USER)
clean:
	rm -f *~ mkrandpfile xrandpfile mkdrandfiles darray *.err *.out /project2/rcc/ivy2/test{.out,_s*,.fv}



