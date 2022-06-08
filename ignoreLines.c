#include "appCommon.h"

/* Function to remove last few lines of the BAYER IMG */
int ignoreBytes(char *filename, struct imageInfo *imgData)
{
	char *newFilename = NULL;
	int ret = 0, bufSize = 0;
	int pad = 0;
	FILE *fp = NULL;

	unsigned char *imgBuff = NULL;
	
	newFilename = (char*) malloc ((strlen(filename)+strlen(FILE_SUFFIX)) * sizeof(char));
	if (!newFilename) {
		printf ("malloc Failure\n");
		return -1;
	}
	strcpy (newFilename, FILE_SUFFIX);
	strcat (newFilename, filename);	

	pad = (8 - ((imgData->width * imgData->bpp) / BYTE) % 8);
	bufSize = ((imgData->width + pad) * imgData->height * imgData->bpp) / BYTE ;
	imgBuff = (unsigned char*) malloc (bufSize * sizeof (unsigned char));
	if (!imgBuff) {
		printf ("malloc Failure\n");
		ret = -1;
		goto deinit2;
	}

	fp = fopen (filename, "rb");
	if (!fp) {
		printf("%s File open Error!\n", filename);
		ret = -1;
		goto deinit2;
	}

	if (bufSize != fread(imgBuff, sizeof(unsigned char), bufSize, fp)) {
		printf("%s File read Error!\n", filename);
		ret = -1;
		goto deinit2;
	}

	switch (imgData->bpp) {
		case 8:
		case 12:
 		case 16:
			ret = -1;
			goto deinit2;
			break;
			/* to be implemented */
		case 10:
			/* Ignore Lines code for 10bpp */
			if (ignorePixels10bpp(imgBuff, imgData)) {
				printf ("Image Processing error!\n");
				ret = -1;
				goto deinit2;
			}
			break;
		default:
			/* control never reaches here */
			ret = -1;
			goto deinit2;
			break;		
	}

	if(saveToFile(imgBuff, imgData, newFilename)) {
		printf ("Image Save error!\n");
		ret = -1;
		goto deinit2;
	}

deinit2:
	printf ("Cleaning up...\n");
	freeIfValid((void**)&newFilename);
	freeIfValid((void**)&imgBuff);
	fcloseIfValid(&fp);
	return ret;
	
}

/* 10 bpp process Function */
int ignorePixels10bpp(unsigned char *buf, struct imageInfo *imgData)
{
	int ret = 0;
	/* Implement Ignore PIXEL code here */
	return ret;
}

/* Save image to File */
int saveToFile (unsigned char *buf, struct imageInfo *imgData, char *newFilename)
{
	int ret = 0, i = 0, pad = 0, newWidth = 0, widthInBytes = 0;
	FILE *fp = NULL;
	
	widthInBytes = (imgData->width * imgData->bpp )/ BYTE ;
	newWidth = widthInBytes - imgData->ignoreBytes;
	pad = 8 - (widthInBytes % 8);
	printf ("WidthBytes = %d, newWidth = %d, pad = %d\n", widthInBytes, newWidth, pad);

	fp = fopen (newFilename, "wb");
	if (!fp) {
		printf("%s File open Error!\n", newFilename);
		ret = -1;
		goto deinit3;
	}
	for ( i = 0 ; i < imgData->height ; i++) {
//		printf ("bufPos = %x, *buf = %x, newPos = %x, check = %x, i = %d\n", buf-ptr, *buf, (unsigned int)ftell(fp), newWidth * i, i);
		if (newWidth != fwrite(buf , 1, newWidth, fp)) {
			printf("%s File write Error!\n", newFilename);
			ret = -1;
			goto deinit3;
		}
		buf = buf + widthInBytes + pad;
	}

deinit3:
	fcloseIfValid(&fp);	
	return ret;
}
