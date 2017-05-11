#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED

//Represents an image
class Image{
public:
	Image(char* ps, int w, int h);
	~Image();
	//  array of the form(R#,G#,B#) to indicate color of each pixel
	//  array starts at the bottom left and goes accross the row
	//  thens moves up acolumn, and repeats until it is done.
	char* pixels;
	int width;
	int height;
};
// Reads in bitmap image from file
Image* loadBMP(const char* filename);

#endif
