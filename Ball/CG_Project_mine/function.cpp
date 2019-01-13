#include "function.h"

GLuint textures[56];

void _loadBitmap(string picture, int material)
{
	int i, j = 0;
	unsigned char *l_texture;
	FILE *l_file;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;

	if ((l_file = fopen(picture.c_str(), "rb")) == NULL) {
		printf("error\n");
		return;
	}
	fread(&fileheader, sizeof(fileheader), 1, l_file);
	fseek(l_file, sizeof(fileheader), SEEK_SET);
	fread(&infoheader, sizeof(infoheader), 1, l_file);
	while (infoheader.biWidth % 4 != 0)
	{
		infoheader.biWidth++;
	}
	l_texture = (byte*)malloc(infoheader.biWidth * infoheader.biHeight * 4);
	memset(l_texture, 0, infoheader.biWidth *infoheader.biHeight * 4);

	for (i = 0; i < infoheader.biWidth*infoheader.biHeight; i++)
	{
		// Weload an RGB value from the file
		fread(&rgb, sizeof(rgb), 1, l_file);
		// Andstore it
		l_texture[j + 0] = rgb.rgbtRed;// Redcomponent
		l_texture[j + 1] = rgb.rgbtGreen;// Greencomponent
		l_texture[j + 2] = rgb.rgbtBlue;// Bluecomponent
		l_texture[j + 3] = 255;// Alphavalue
		j += 4; // Go to the next position
	}
	glBindTexture(GL_TEXTURE_2D, material);// Bind the ID texture specified by the 2nd parameter
									// The nextcommands sets the texture parameters


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	// Finally wedefine the 2d texture

	glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
	//glEnable(GL_TEXTURE_2D);
	//printf("%d\t%d", infoheader.biWidth, infoheader.biHeight);
}

void Init()
{
	glGenTextures(56, textures);
	_loadBitmap("Pictures/0.bmp", textures[0]);//wood
	_loadBitmap("Pictures/1.bmp", textures[1]);//paper
	_loadBitmap("Pictures/2.bmp", textures[2]);
	_loadBitmap("Pictures/track.bmp", textures[3]);
	_loadBitmap("Pictures/wall.bmp", textures[4]);
	_loadBitmap("Pictures/3.bmp", textures[5]);
	_loadBitmap("Pictures/4.bmp", textures[6]);
	_loadBitmap("Pictures/5.bmp", textures[7]);
	_loadBitmap("Pictures/6.bmp", textures[8]);
	_loadBitmap("Pictures/7.bmp", textures[9]);
	_loadBitmap("Pictures/8.bmp", textures[10]);
	_loadBitmap("Pictures/9.bmp", textures[11]);
	_loadBitmap("Pictures/10.bmp", textures[12]);
	_loadBitmap("Pictures/11.bmp", textures[13]);
}
