#include "projet.h"



int main()
{
	

	int processus =1,taille = 62	;
	
	//swap_in(processus,  taille, "image.tga");
	/*
	int page = my_free(processus,taille,"image1.tga");
	printf("Le processus %d vient d'effacer %d à la page : %d\n",processus,taille,page);*/
	int page = my_malloc(processus,taille,"image1.tga");
	printf("Le processus %d à écrire à la page : %d\n",processus,page);
	//int page = swap_out(processus,taille,"image.tga");
	/*char *id_a_cacher = "amadousalladieng", *imageCachante = "ensta_Tatoo_nb.tga", *id_cache = malloc(6*sizeof(char));
	cacherId ( id_a_cacher, imageCachante );
	getId ( id_cache, "imageAvecCode.tga" );
	printf("La taille de l'identifiant est : %d\n",strlen(id_cache));
	printf("j'ai récupéré %s\n",id_cache);*/
	return EXIT_SUCCESS;
	
}
/*
void blank(){
	int blanc[3]={255,255,255};
	int k,j;
	for (j=1;j<=5;j++)
	{
	for(k=0;k<314;k++)colorierLigne("image.tga",k,j,blanc);
}*/
