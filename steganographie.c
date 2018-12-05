#include "projet.h"

void cacherId ( char* id_a_cacher, char* imageCachante )
{   
	targa_header head0;
	image_desc desc0;//,*pimgOut;
	char val_offset = 'a',arret = '|';
	int taille_id = strlen(id_a_cacher);
	int k,iR, mask_MSB = 224u;
	printf("[Fonction CacherId]\n");
	printf("L'identifiant à cacher mesure %d\n",taille_id);
	int r0 =readImage(&desc0, &head0, imageCachante); 
	if (r0==0 ) exit(1);
	printf("[CacherId--1] : ");
	//image_clone(desc0, pimgOut);
	//mallocImage(pimgOut, desc0.width, desc0.height);
	for (k=0;k<taille_id;k++)
	{
		printf("Je rentre dans la boucle k = %d\n",k);
		printf("a=%d\n",desc0.pRed[k]);
		iR=((desc0.pRed)[k])&(mask_MSB);
		printf("iR= %d\n",iR);
		desc0.pRed[k]   = iR + id_a_cacher[k]-val_offset;
		printf(" Red = %d\n",desc0.pRed[k]);
	}
	iR = ((desc0.pRed)[taille_id])&(mask_MSB);
	desc0.pRed[taille_id] = iR +arret - val_offset;
	int e = writeImage (desc0, head0, "imageAvecCode.tga");
	if (e==0)printf("Impossible de creer l'image l'image\n");
}
void getId ( char* id_cache, char* imageCachante )
{   
	targa_header head0;
	image_desc desc0;//,*pimgOut;
	char val_offset = 'a',arret = '|';
	int k=0,iR, mask_LSB = 31u;
	printf("[Fonction CacherId]\n");
	int r0 =readImage(&desc0, &head0, imageCachante); 
	if (r0==0 ) exit(1); 
	printf("[getID--1] \n ");
	iR = ((desc0.pRed)[k])&(mask_LSB);
	while(( ( iR + val_offset) !=arret) )
	//for (k=0;k<taille_id;k++)
	{
		printf("Je rentre dans la boucle k = %d ",k);
		
		printf("iR= %d  caractère = %c\n",iR,iR+val_offset);
		id_cache[k] = iR+val_offset;
		k++;
		iR=((desc0.pRed)[k])&(mask_LSB);
	}
	int e = writeImage (desc0, head0, "imageAvecCode.tga");
	if (e==0)printf("Impossible de creer l'image l'image\n");
}
