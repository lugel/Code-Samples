#include "pch.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <thread>
#include <cstdlib>
#include <chrono>
#include "JACDLL.h"

extern "C" int __stdcall BordersAsm(int heigth, int width, int noOfBytes, BYTE *bytesDIB, BYTE *newBmpPlace, int *table); // function from assembler dll
void findBorders(int heigth, int width, int noOfBytes, BYTE *bytesDIB, BYTE *newBmpPlace, int *table); // function from C dll

// bitmap structure
typedef struct Bitmap
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER *bih;
	long int bmpsize;
	void* bmp;
	byte* bytesDIB; // pointer to the pixels' data start
	void* colorPalette;
	int bytesInRow;
}Bitmap;

// check how many bytes are in a row (and make it divisible by 4)
int howManyBytes(BITMAPINFOHEADER *bhead) 
{
	int bytesQuant;
	bytesQuant = ((int)bhead->biWidth * bhead->biBitCount) / 8;
	while (bytesQuant % 4)
		bytesQuant++;
	return bytesQuant;
}

// loading the bitmap
int loadBitmap(const char *fname, Bitmap *myBmp)
{
	FILE *myFile;
	int everythingIsOk;
	long int size;

	myFile = fopen(fname, "rb");

	if (myFile == NULL)
		return FALSE;

	size = _filelength(_fileno(myFile)) - sizeof(BITMAPFILEHEADER);

	if (!(fread(&(myBmp->bfh), sizeof(BITMAPFILEHEADER), 1, myFile)))
	{
		fclose(myFile);
		return FALSE;
	}

	myBmp->bmp = malloc(size * 2);

	if (myBmp->bmp == NULL)
	{
		fclose(myFile);
		return FALSE;
	}

	everythingIsOk = fread(myBmp->bmp, size, 1, myFile);

	fclose(myFile);

	if (!everythingIsOk)
	{
		free(myBmp->bmp);
		myBmp->bmp = NULL;
		return FALSE;
	}


	myBmp->bih = (BITMAPINFOHEADER *)(myBmp->bmp);

	myBmp->bmpsize = size;
	myBmp->bytesDIB = (byte *)(myBmp->bmp) + (myBmp->bih)->biSize;
	myBmp->colorPalette = (void *)((byte *)(myBmp->bmp) + (myBmp->bih)->biSize);

	myBmp->bytesInRow = howManyBytes(myBmp->bih);

	return TRUE;
}

// saving the bitmap
int saveBitmap(const char *fname, Bitmap *myBmp)
{
	FILE *f;
	int saveOk;

	f = fopen(fname, "wb");

	if (f == NULL)
		return FALSE;

	fwrite((void *)&(myBmp->bfh), sizeof(BITMAPFILEHEADER), 1, f);

	if (myBmp->bmpsize > 0)
		saveOk = (fwrite(myBmp->bmp, myBmp->bmpsize, 1, f) == 1);
	else
		saveOk = TRUE;

	fclose(f);

	return saveOk;
}

int main(int argc, char *argv[])
{
	int nOfThreads = std::thread::hardware_concurrency(); // optimal number of threads
	Bitmap bmp, newBmp;
	std::string sourcePath;
	bool useC = true;
	bool threadsNoSpec = true;
	bool noFile = true;

	for (size_t i = 0; i < argc; i++)
	{
		if (argv[i] == std::string("-fp"))
		{
			sourcePath = argv[i + 1];
			noFile = false;
		}

		if (argv[i] == std::string("-c"))
			useC = atoi(argv[i + 1]);
		
		if (argv[i] == std::string("-t"))
		{
			nOfThreads = atoi(argv[i + 1]);
			threadsNoSpec = false;
		}
	}

	if (noFile)
	{
		std::cout << "You didn't specified source file, the program will now close.";
		return 1;
	}

	if (threadsNoSpec)
		std::cout << "You didn't specified how many threads you want the program to use\nthe optimal number will be used instead\n";

	printf("Reading from source file: %s \n", sourcePath.c_str());

	if (useC)
		printf("Program will use C to find borders in given bitmap\n");
	else
		printf("Program will use asm to find borders in given bitmap\n");

	printf("Program will use: %i threads\n", nOfThreads);

	std::thread **thTable;
	thTable = new std::thread*[nOfThreads];

	loadBitmap(sourcePath.c_str(), &bmp);
	loadBitmap(sourcePath.c_str(), &newBmp);

	int height = (bmp.bih->biHeight / nOfThreads);
	int correction = bmp.bih->biHeight;
	int width = bmp.bih->biWidth;

	int* table = (int*)malloc(2 * bmp.bih->biWidth * (bmp.bih->biHeight * sizeof(int)));

	auto t1 = std::chrono::high_resolution_clock::now();
	if (useC)
	{
		for (int i = 0; i < nOfThreads; i++)
		{
			byte* bmpPlace = bmp.bytesDIB + i * ((height - 1) * bmp.bytesInRow);
			byte* newBmpPlace = newBmp.bytesDIB + i * ((height - 1) * bmp.bytesInRow);
			int* tablePlace = table + i * height * width;

			if (i == nOfThreads - 1)
				height = correction - height * i;

			height += nOfThreads;
			thTable[i] = new std::thread([=] {findBorders(height, width, bmp.bytesInRow, bmpPlace, newBmpPlace, tablePlace); });
			height -= nOfThreads;
		}
	}
	else
	{
		for (int i = 0; i < nOfThreads; i++)
		{
			byte* bmpPlace = bmp.bytesDIB + i * ((height - 1) * bmp.bytesInRow);
			byte* newBmpPlace = newBmp.bytesDIB + i * ((height - 1) * bmp.bytesInRow);
			int* tablePlace = table + i * height * width;

			if (i == nOfThreads - 1)
				height = correction - height * i;

			height += nOfThreads;
			thTable[i] = new std::thread([=] {BordersAsm(height, width, bmp.bytesInRow, bmpPlace, newBmpPlace, tablePlace); });
			height -= nOfThreads;
		}
	}

	for (size_t i = 0; i < nOfThreads; i++)
	{
		thTable[i]->join();
	}

	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	printf("Bitmap size: %i\n", bmp.bmpsize);
	std::cout << "Proccessing bitmap took: " << duration << " ms\n";
	saveBitmap("result.bmp", &newBmp);
	
	for (size_t i = 0; i < nOfThreads; i++)
	{
		delete thTable[i];
	}

	return 0;
}
