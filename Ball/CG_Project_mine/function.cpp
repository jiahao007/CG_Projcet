#include "function.h"

GLuint textures[3];

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
	glGenTextures(3, textures);
	_loadBitmap("C:/Users/Zihao Wang/Desktop/CG_Project_mine/Pictures/0.bmp", textures[0]);//wood
	_loadBitmap("C:/Users/Zihao Wang/Desktop/CG_Project_mine/Pictures/1.bmp", textures[1]);//paper
	_loadBitmap("C:/Users/Zihao Wang/Desktop/CG_Project_mine/Pictures/2.bmp", textures[2]);
}
