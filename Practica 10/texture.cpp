#include "texture.h"

bool CTexture::LoadTGA(char *filename)			// Loads A TGA File Into Memory
{
	unsigned char	TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	unsigned char	TGAcompare[12];					// Used To Compare TGA Header
	unsigned char	header[6];					// First 6 Useful Bytes From The Header
	unsigned int	bytesPerPixel;					// Holds Number Of Bytes Per Pixel Used In The TGA File
	unsigned int	imageSize;					// Used To Store The Image Size When Setting Aside Ram
	unsigned int	temp;						// Temporary Variable

	FILE *file = fopen(filename, "rb");				// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{

		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
		{
			imageData=NULL;
			return false;									// Return False
		}
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

 	if(	width	<=0	||								// Is The Width Less Than Or Equal To Zero
		height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= width*height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

    name=new char[strlen(filename)+1];
    strcpy(name,filename);

	imageData=new unsigned char [imageSize];

	if(	imageData==NULL ||							// Does The Storage Memory Exist?
		fread(imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(imageData!=NULL)						// Was Image Data Loaded
        {
			delete[] imageData;						// If So, Release The Image Data
            imageData=NULL;
        }
		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(int i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=imageData[i];							// Temporarily Store The Value At Image Data 'i'
		imageData[i] = imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File
	return true;											// Texture Building Went Ok, Return True
}

bool CTexture::LoadBMP(char* filename)
{
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1)     
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&width, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if ((i = fread(&height, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = width * height * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    imageData = new unsigned char[size];
    if (imageData == NULL) {
	printf("Error allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(imageData, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = imageData[i];
	imageData[i] = imageData[i+2];
	imageData[i+2] = temp;
    }
    
    //we're done.
    return true;
}


void CTexture::BuildGLTexture()
{
    unsigned int color_type;    //default color type for images

    glGenTextures(1,&GLindex);      //Hacemos una lista de texturas para OpenGL

    if(bpp==24)
        color_type=GL_RGB;          //Verificamos el tipo de color a usar
	
    else
        color_type=GL_RGBA;


    glBindTexture(GL_TEXTURE_2D, GLindex);
    //los siguientes ajustes de los parametros de la textura se hacen al
    //elemento de la lista texturelist especificado arriba
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, color_type, width,
                height,0, color_type, GL_UNSIGNED_BYTE,
                imageData);	
}

void CTexture::ReleaseImage()
{
	if(imageData!=NULL)
		delete[] imageData;
    	imageData=NULL;
}
