/**
 * Creation date: 2015-10-22
 * Description:
 *    This file contains the functions for serializing/deserializing an image given a filename
 */

#include "fun_targa.h"

/* Free the memory allocated for the given image structure. */
void freeImage(image_desc *pdesc);

/* Write an image given a header structure and an image
 * structure into a file named fName.  */
int writeImage(image_desc desc, targa_header head, char* fName);

/* Read an image from fName and create a header structure and an image
 * structure pointed to by pHeader and pDesc.  */
int readImage(image_desc *pDesc, targa_header *pHeader, char * fName);

/* Allocate memory for the image structure given in parameter. */
int mallocImage(image_desc *pDesc, uint16_t width, uint16_t height);
