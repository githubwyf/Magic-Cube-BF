run:run.o
	g++ -o run run.o
run.o:run.c includes.h MCBF.h BF.h File_Reader.h Helper_Func.h Element.h
	g++ -c run.c
clean:
	rm run run.o bf mc_bf
