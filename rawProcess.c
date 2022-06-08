/***************************************************************************
 * Author : Sunny
 * Code : To remove excessive padding in each line of RAW bayerformat image
 * Note : This code assumes image as BAYER packed in MIPI format
 * *************************************************************************/

#include "appCommon.h"

/* Function Prototypes */
int validateInfo(struct imageInfo *imgData, char *filename);
void printInfo(struct imageInfo *imgData, char *filename);

int main (int argc, char *argv[])
{
	struct imageInfo imgData = {DEF_WIDTH, DEF_HEIGHT, DEF_BPP};
	char *filename = NULL;
	int ret = 0;

	if (processArgs (&imgData, argc, argv, &filename) == FAIL) {
		printUsage ();
		ret = -1;
		goto deinit;
	}

	if (validateInfo(&imgData, filename)) {
		ret = -1;
		goto deinit;
	}
	
	if (ignoreBytes (filename, &imgData)) {
		printf("\nError in ignoreBytes()\n");
		ret = -1;
		goto deinit;
	}

deinit:
	freeIfValid((void**)&filename);
	return ret;
}

int validateInfo(struct imageInfo *imgData, char *filename) 
{
	FILE *fp = NULL;
	long int fileSize = 0, actualSize = 0;
	int ret = 0;

	if (imgData->width == 0) {
		printf ("Width is given 0. Seting Default! '3840'\n");
		imgData->width = DEF_WIDTH;
	}
	if (imgData->height == 0) {
		printf ("Height is given 0. Setting Default! '2160'\n");
		imgData->height = DEF_HEIGHT;
	}
	if (imgData->bpp != 8 && imgData->bpp != 10 && imgData->bpp != 12 && imgData->bpp != 16) {
		printf ("invalid Bits per pixel. Setting Default '10'!\n");
		imgData->bpp = DEF_BPP;
	}

	while (1) {
		if (imgData->bpp == 8 && imgData->ignoreBytes % DEF_IGNORE_8BPP != 0) {
			printf ("invalid Ignore Bytes. Setting Default '1'!\n");
			imgData->ignoreBytes = DEF_IGNORE_8BPP;
		} else if (imgData->bpp == 10 && imgData->ignoreBytes % DEF_IGNORE_10BPP != 0) {
			printf ("invalid Ignore Bytes. Setting Default '5'!\n");
			imgData->ignoreBytes = DEF_IGNORE_10BPP;
		} else if (imgData->bpp == 12 && imgData->ignoreBytes % DEF_IGNORE_12BPP != 0) {
			printf ("invalid Ignore Bytes. Setting Default '3'!\n");
			imgData->ignoreBytes = DEF_IGNORE_12BPP;
		} else if (imgData->bpp == 16 && imgData->ignoreBytes % DEF_IGNORE_16BPP != 0) {
			printf ("invalid Ignore Bytes. Setting Default '2'!\n");
			imgData->ignoreBytes = DEF_IGNORE_16BPP;
		}
		if (imgData->ignoreBytes >= ((imgData->width * imgData->bpp) / BYTE)) {
		} else {
			break;
		}
	}

	fp = fopen (filename, "r");
	if (!fp) {
		printf("%s File open Error!\n", filename);
		ret = -1;
		goto end;
	}
	fseek(fp, 0L, SEEK_END);
	fileSize = ftell(fp);

	/* Assuming MIPI BAYER Packed Image */
	actualSize = (long int) (imgData->width * imgData->height * imgData->bpp) / BYTE;
	if (actualSize > fileSize) {
		printf ("file size doesnt match the input! enter valid image info!\n");
		ret = -1;
	}
	printf ("\nFile size = %ld", fileSize);
	printf ("\nActual size = %ld", actualSize);

end:
	fcloseIfValid(&fp);
	printInfo(imgData, filename);
	return ret;
}

void printInfo (struct imageInfo *imgData, char *filename)
{
	printf ("\n====================\n");
	printf ("filename : %s\n", filename);
	printf ("width  : %d\n", imgData->width);
	printf ("height : %d\n", imgData->height);
	printf ("bits per pixel : %d\n", imgData->bpp);
	printf ("ignore Bytes : %d\n", imgData->ignoreBytes);
	printf ("====================\n");
}
