/* MACROS */
#define DEF_BPP 10
#define DEF_WIDTH 3840
#define DEF_HEIGHT 2160
#define DEF_IGNORE_8BPP 1
#define DEF_IGNORE_10BPP 5
#define DEF_IGNORE_12BPP 3
#define DEF_IGNORE_16BPP 2
#define FILE_SUFFIX "OUT_"

/* structure for Image info */
struct imageInfo {
	int width;
	int height;
	int bpp;
	int ignoreBytes;
};

/* Pixel Structure for available bits per Pixels */
struct pxl8Bpp {
	unsigned char pix;
};
struct pxl16Bpp {
	unsigned char pixFirstHalf;
	unsigned char pixSecondHalf;
};
struct pxl10Bpp {
	unsigned char pix1;
	unsigned char pix2;
	unsigned char pix3;
	unsigned char pix4;

	unsigned char pix1Bit:2;
	unsigned char pix2Bit:2;
	unsigned char pix3Bit:2;
	unsigned char pix4Bit:2;
};
struct pxl12Bpp {
	unsigned char pix1;
	unsigned char pix2;

	unsigned char pix1Bit:4;
	unsigned char pix2Bit:4;
};

/* function prototypes */
int ignoreBytes(char *filename, struct imageInfo *imgData);
int ignorePixels10bpp(unsigned char *buf, struct imageInfo *imgData);
int saveToFile (unsigned char *buf, struct imageInfo *imgData, char *newFilename);
