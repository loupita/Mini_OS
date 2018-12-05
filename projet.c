#include "projet.h"

/*
Definition des fonctions qui vont permettre de representer l'attribution de memoire.
Image de l'occupation memoire d'un processus.
Image sera enregistree sous le nom : occupation_memoire_PID.tga
*/

// Fonction permettant de colorier une ligne
void colorierLigne(char* fName,int ligne, int page,int couleur[3])
{
	image_desc desc;
	targa_header head;
	int r = readImage(&desc, &head, fName),i=0;
	if (r==0)printf("Impossible de lire l'image\n");
	int largeur = head.width;
	int largeurPage = largeur/4;
	//int hauteur = head.height;
	// ligne n , (n-1)*largeur + 1
	int debut = (ligne)*largeur+(page-1)*largeurPage;
  for(i=debut; i<debut+largeurPage; i++)
  {
		desc.pBlue[i] = couleur[0];
    desc.pGreen[i] = couleur[1];
    desc.pRed[i] = couleur[2];
  }
	int e = writeImage (desc, head, fName);
	if (e==0)printf("Impossible de creer l'image l'image\n");
}

/* Cette fonction renvoie la couleur du premier pixel non occupé en espace mémoire, on a consideré que les pixels d'une ligne ont la même couleur */
int gestionDePage(int page,int processus, image_desc image,targa_header head )
{
	printf("Gestion De Page\n");
	int blanc = 255;
	int largeur = head.width, hauteur = head.height;
	int hauteurProcessus = (hauteur/5) * (largeur) ,largeurProcessus = largeur/4;
	int debutProcessus = (processus-1)*hauteurProcessus + (page-1)*largeurProcessus;	
	int i=debutProcessus;
	while ((i<=debutProcessus + hauteurProcessus) )
	{
  	printf("i = %d \t debut processus %d\t fin processus = %d\n",i,debutProcessus,debutProcessus+hauteurProcessus);
		
		if ( (image.pBlue[i] == blanc) && (image.pBlue[i] == blanc)&& (image.pBlue[i] == blanc))
		{
			printf(" Je trouve 1ere ligne blanche  = %d\n",i/largeur);
			return i;
		}
		i+=largeur;		 
	}
	return i;
}


/* Fonction qui permet à un processus d'occuper un espace mémoire */
int my_malloc(int processus,int taille, char* nomImgeMemoire)
{	
	printf("[---my_malloc---]\n");
	image_desc desc;
	targa_header head;
	int noir[3] = {0,0,0},gris[3] = {96,96,96},rouge[3] ={0,0,255},bleu[3] = {255,0,0},vert[3] = {0,255,0};
	int* couleurs[5] = {rouge,vert,bleu,noir,gris};
	int r = readImage(&desc, &head, nomImgeMemoire);
	if (r==0)
	{
		printf("Impossible de lire l'image\n");
		return -2;
	}
	int largeur = head.width, hauteur = head.height;
	int hauteurProcessus = (hauteur/5) * (largeur) ,largeurProcessus = largeur/4;
	int	page =1,i,ligne,debutProcessus,finProcessus;
	
  do
  {
  	i =gestionDePage(page,processus, desc,head );
  	debutProcessus = (processus-1)*hauteurProcessus + (page-1)*largeurProcessus;	
		finProcessus = debutProcessus + hauteurProcessus - largeur;
  	page++;
  	printf("i = %d \t fin processus = %d\n My malloc : Taille disponible à la page %d = %d octets\n",i,debutProcessus,page+1, (finProcessus-i)/largeur);
  }
  while ( (finProcessus-i+largeur) < taille * largeur && page<5);
  //page--;
  
  if (page >=5 && taille ==hauteur/5)
 	{ 		
 		int a=swap_out(processus, taille, nomImgeMemoire);
  	printf("Pas assez d'espace memoire je swap\n");
  	return a;
 	}
 	else printf(" Erreur de Segmentation\n");
 	for (ligne =i/largeur;ligne<i/largeur + taille;ligne++)	colorierLigne(nomImgeMemoire, ligne, page-1,couleurs[processus-1]);
	printf("[my_malloc_fin] \n");
	return page-1;
  
}
  
int liberationEspacePage(int page,int processus, image_desc image,targa_header head )
{

	int blanc = 255;
	int largeur = head.width, hauteur = head.height;
	int hauteurProcessus = (hauteur/5) * (largeur) ,largeurProcessus = largeur/4;
	int debutProcessus = (processus-1)*hauteurProcessus + (page-1)*largeurProcessus;	
	int finProcessus = debutProcessus+hauteurProcessus-largeur;
	int i=finProcessus;
	while (i>=debutProcessus )
	{
  	printf("ligne = %d \t debut processus %d\t fin processus = %d\n",i/largeur,debutProcessus/largeur,(finProcessus)/largeur);
		
		if ( (image.pBlue[i] != blanc) && (image.pBlue[i] != blanc)&& (image.pBlue[i] != blanc))
		{                                                           
			printf(" Je trouve dernière ligne occupée = %d\n",(i-debutProcessus)/largeur);
			return i;
		}
		i-=largeur;		 
	}
	return i;
}

int my_free(int processus,int taille, char* nomImgeMemoire)
{	
	image_desc desc;
	targa_header head;
	int blanc[3] = {255,255,255};
	
	int r = readImage(&desc, &head, nomImgeMemoire);
	if (r==0)
	{
		printf("Impossible de lire l'image\n");
		return -2;
	}
	int largeur = head.width, hauteur = head.height;
	int hauteurProcessus = (hauteur/5) * (largeur) ,largeurProcessus = largeur/4;
	int	page =4,i,ligne,debutProcessus,finProcessus;
	
  do
  {
  	printf("Je passe à la page %d\n",page);
  	i =liberationEspacePage(page,processus, desc,head );
  	debutProcessus = (processus-1)*hauteurProcessus + (page-1)*largeurProcessus;	
		finProcessus = debutProcessus+hauteurProcessus-largeur;
  	page--;
  	printf("i = %d \t fin processus = %d\nTaille occupée à la page %d = %d octets\n",i/largeur,finProcessus/largeur,page+1, (i-debutProcessus+largeur)/largeur);
  
  }
  while ( (i-debutProcessus+largeur) < taille * largeur && page>0);                                                                                                          
  //page--;
  if (page <=0 && (i-debutProcessus+largeur) < taille * largeur)
 	{
  	printf("Segmentation Fault\n");
  	return -1;
 	}
 	for (ligne =i/largeur;ligne>i/largeur - taille;ligne--)	colorierLigne(nomImgeMemoire, ligne, page+1,blanc);
	return page+1;
}    

int swap_in(int processus,  int taille, char* nomImgeMemoire)
  {
int b= my_malloc(processus,taille, nomImgeMemoire);
	printf("Le processus %d vient d'écrire à la page : %d\n",processus,b);
	int c= my_free(processus,taille, "memoireSecondaire.tga");   
	printf("Le processus %d vient d'écrire à la page : %d\n",processus,b);	    
	return c;
  }
  
int swap_out(int processus,  int taillePage, char* nomImgeMemoire)
  {
  	
	int c= my_free(processus,taillePage, nomImgeMemoire); 
	printf("Le processus %d vient d'effacer %d à la page : %d\n",processus,taillePage,c);           
	int b= my_malloc(processus,taillePage,"memoireSecondaire.tga");   
	printf("Le processus %d vient d'écrire à la page : %d\n",processus,b);
  return c;
	  
  }



