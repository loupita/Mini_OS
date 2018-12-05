default : projet

projet : petitmain.o mem_targa.o fun_targa.o projet.o steganographie.o
	gcc -g -Wall petitmain.o mem_targa.o fun_targa.o projet.o steganographie.o -o projet

petitmain.o : petitmain.c projet.h
	gcc -g -Wall -c petitmain.c -o petitmain.o	

mem_targa.o : mem_targa.c mem_targa.h
	gcc -g -Wall -c mem_targa.c -o mem_targa.o

fun_targa.o : fun_targa.c fun_targa.h
	gcc -g -Wall -c fun_targa.c -o fun_targa.o
	
projet.o : projet.c projet.h
	gcc -g -Wall -c projet.c -o projet.o	
	
steganographie.o : steganographie.c projet.h
	gcc -g -Wall -c steganographie.c -o steganographie.o

zip:
	tar -zcvf DIA_GOHEP_Projet_SE.tar.gz *.c *.h Makefile *.tga

clean :
	rm -f *.o core

mrproper: clean
	rm -f projet

