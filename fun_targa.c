/**
 *
 * Creation date: 2015-10-22
 * Description:
 *    This file contains the functions that make transformations on a Targa image represented
 *    as an image_desc structure.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fun_targa.h"
#include "mem_targa.h"

/**
 * Clone a image represented by an image_desc structure by copying it pixel by pixel.
 * @param imgIn input image
 * @param pimgOut pointer to the target output image
*/
void image_clone(image_desc imgIn, image_desc *pimgOut)
{
  int i = 0, err = 1;
  err = mallocImage(pimgOut, imgIn.width, imgIn.height);
  if(!err){
    return ;
  }

  /* Transformation  : equiv. to : for (i=0; i < i_img.width*i_img.height; i++)*/
  for (i=0; i<(imgIn.width) * (imgIn.height); i++) {
    (pimgOut->pBlue)[i] = (imgIn.pBlue)[i];
    (pimgOut->pGreen)[i] = (imgIn.pGreen)[i];
    (pimgOut->pRed)[i] = (imgIn.pRed)[i];
  }
}
