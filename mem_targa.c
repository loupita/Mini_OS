#include <stdlib.h>
#include <stdio.h>
#include "mem_targa.h"

 
/* Free the memory allocated for the given image structure. */
void freeImage(image_desc *pDesc)
{
  free(pDesc->pBlue); pDesc->pBlue = NULL;
  free(pDesc->pGreen); pDesc->pGreen = NULL;
  free(pDesc->pRed); pDesc->pRed = NULL;
}

/* Read an image from fName and create a header structure and an image
 * structure pointed to by pHeader and pDesc.  */
int readImage(image_desc *pDesc, targa_header *pHeader, char * fName)
{
  FILE * fDesc;
  int i = 0, err = 1;
  /* Open fDesc file */
  fDesc = fopen(fName,"r");
  if (fDesc == NULL) {
    fprintf(stderr, "Cannot read the file \"%s\".\n", fName);
    return 0;
  }
  /* Read the header */
  fread(pHeader, sizeof(targa_header), 1, fDesc);

 // printf("[mem_targa] Header : %u %u %u %u %u\n",
   //       pHeader->idlength, pHeader->colourmaptype, pHeader->datatypecode, pHeader->width, pHeader->height);

  /* Initialize image struct */
  err = mallocImage(pDesc, pHeader->width, pHeader->height);
  if(!err){
    fprintf(stderr, "Cannot initialize the image \n");
    return 0;
  }

  /* Fill pixel by pixel the 3 color layers */
  for(i=0; i<pHeader->width*pHeader->height; i++)
  {
    // read 1 int : blue
    fread(pDesc->pBlue+i, sizeof(uint8_t), 1, fDesc);
    // read 1 int : green
    fread(pDesc->pGreen+i, sizeof(uint8_t), 1, fDesc);
    // read 1 int : red
    fread(pDesc->pRed+i, sizeof(uint8_t), 1, fDesc);
  }
  //printf("[readImage] Number of pixels : %d\n", i);

  fclose(fDesc);

  return 1;
}


/* Write an image given a header structure and an image
 * structure into a file named fName.  */
int writeImage (image_desc desc, targa_header head, char * fName)
{
  FILE *fDesc;
  int i;

  /* Open output image file */
  if ((fDesc = fopen(fName, "w")) == NULL)
  {
    fprintf (stderr, "Cannot create the file \"%s\".\n", fName);
    return 0;
  }

  /* Write the header in fDesc*/
  head.width = desc.width;
  head.height = desc.height;
  //printf("[write mem_targa] Header : %u %u %u %u %u \n",
    //     head.idlength, head.colourmaptype, head.datatypecode, head.width, head.height);

  fwrite(&head, sizeof(targa_header), 1, fDesc);

  /* Write in fDesc head.width*head.height pixels for each color */
  for(i=0; i<head.width*head.height; i++)
  {
    fwrite((desc.pBlue)+i, sizeof(uint8_t), 1, fDesc);
    fwrite((desc.pGreen)+i, sizeof(uint8_t), 1, fDesc);
    fwrite((desc.pRed)+i, sizeof(uint8_t), 1, fDesc);
  }
  //printf("[writeImage] Number of pixels : %d\n", i);

  fclose(fDesc);

  return 1;
}


/* Allocate memory for the content of the image structure given in parameter.
 * return 1 if allocation succeeds,
 * 0 otherwise.
 */
int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height)
{
  /* Do not reallocate if the pDesc pointer is already initialized */
  if (pDesc == NULL)
  {
    printf("Pointer on image structure must be allocated first\n");
    pDesc = (image_desc*)malloc(sizeof(image_desc));
  }

  pDesc->width = width;
  pDesc->height = height;

  /* Allocate memory for each image plane */
  pDesc->pBlue = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
  pDesc->pGreen = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
  pDesc->pRed = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
  if (pDesc->pBlue == NULL || pDesc->pGreen == NULL || pDesc->pRed == NULL) {
    return 0;
  }

  return 1;
}
