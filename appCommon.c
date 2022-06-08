#include "appCommon.h"

/* General helper print function to display App usage */
void printUsage()
{
	printf ("\nUsage : ./rawProcess <filename> -w<width> -h<height> -b<bpp> -i<ignoreBytes>\n");
}

/* Function to process the command line arguments and fill the imageInfo Structure */
int processArgs (struct imageInfo  *imgData, int argc, char *argv[], char **filename)
{
	int i = 0, flag = 0;
	if (argc < 2 || argc > 6) {
		return -1;
	} else {
		for (i = 1; i < argc; i++) {
			switch (argv[i][0]) {
				case '-' :
					switch (argv[i][1]) {
						case 'w':
							imgData->width = getNum(argv[i]);
							break;
						case 'h':
							imgData->height = getNum(argv[i]);
							break;
						case 'b':
							imgData->bpp = getNum(argv[i]);
							break;
						case 'i':
							imgData->ignoreBytes = getNum(argv[i]);
							break;
		 				default:
							printf ("\nInvalid Option \'%s\'", argv[i]);
							return -1;
							break;
					}
					break;
				default:
					*filename = (char*)malloc((strlen(argv[i]) + 1) * sizeof(char));
					if (!*filename) {
						printf ("malloc Failure\n");
						return -1;
					}
					strcpy (*filename, argv[i]);
					if (flag == 1) return -1;
					flag++;
					break;
			}
		}
	}
	if (flag == 0) {
		printf ("\nNo Filename given");
		return -1;
	}
	return 0;	
}

/* Function to extract number from commandline argument */
int getNum(char *str)
{
	int num = 0;
	str += 2; /* Skipping option parameter (-w, -h or -b) */

	num = atoi(str);

	return num;
}

/* Function to free Dynamic memory if Non null pointer is given */
void freeIfValid(void **ptr)
{
	if (*ptr) {
		free(*ptr);
		*ptr = NULL;
	}
}

/* function to close file if pointer is not null */
void fcloseIfValid(FILE **fp)
{
	if (*fp) {
		fclose (*fp);
		*fp = NULL;
	}
}
