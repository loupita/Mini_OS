#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_targa.h"
#include "mem_targa.h"


/*
--- Module projet.c
*/
int my_malloc(int processus,int taille, char* nomImgeMemoire);
void colorierLigne(char* fName,int ligne, int page,int couleur[3]);
void colorierUneLigne(char* fName,int ligne,int couleur[3]);
int my_free(int processus,int taille, char* nomImgeMemoire);
int swap_in(int Processus,  int taille, char* nomImgeMemoire);
int swap_out(int processus,  int taillePage, char* nomImgeMemoire);

/* 
---Module steganographie.c---
*/
void cacherId ( char* id_a_cacher, char* imageCachante );
void getId ( char* id_cache, char* imageCachante );
