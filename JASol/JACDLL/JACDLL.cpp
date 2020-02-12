// JACDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "JACDLL.h"

long int BmpPixel(int x, int y, unsigned long color, int change, int noOfBytes, BYTE *bytesDIB)
{
	BYTE *chosenPixel;

	chosenPixel = bytesDIB + y * noOfBytes + x * 3; // correct pixel position

	// changing the RGB values of the chosen pixel
	if (change)
	{
		chosenPixel[0] = GetRValue(color);
		chosenPixel[1] = GetGValue(color);
		chosenPixel[2] = GetBValue(color);
	}

	color = RGB(chosenPixel[0], chosenPixel[1], chosenPixel[2]);

	return color;
}

void findBorders(int height, int width, int noOfBytes, BYTE *bytesDIB, BYTE *newBmpPlace, int *table)
{
	// check the whole bmp pixel by pixel and if there is a different color horizontally or vertically put 1 in array,
	// otherwise put 0 
	int i, j;

	for (j = 0; j < height; j++)
	{
		*(table + j * width) = 1;
	}

	for (j = 0; j < height; j++)
	{
		for (i = 1; i < width; i++)
		{
			if ((j == 0) || (j == height - 1))
			{
				if ((BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i - 1, j, 0, 0, noOfBytes, bytesDIB)))
					|| (BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i + 1, j, 0, 0, noOfBytes, bytesDIB))))
					*(table + j * width + i) = 1; // different color
				else
					*(table + j * width + i) = 0; // same color
				continue;
			}

			if ((BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i, j - 1, 0, 0, noOfBytes, bytesDIB)))
				|| (BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i, j + 1, 0, 0, noOfBytes, bytesDIB)))
				|| (BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i - 1, j, 0, 0, noOfBytes, bytesDIB)))
				|| (BmpPixel(i, j, 0, 0, noOfBytes, bytesDIB) != (BmpPixel(i + 1, j, 0, 0, noOfBytes, bytesDIB))))
				*(table + j * width + i) = 1; // different color
			else
				*(table + j * width + i) = 0; // same color
		}
	}

	// coloring the bmp according to numbers in the 2d array
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			// checking the number
			if (*(table + j * width + i))
				BmpPixel(i, j, RGB(0, 0, 0), 1, noOfBytes, newBmpPlace); // 1 = true, black color
			else
				BmpPixel(i, j, RGB(255, 255, 255), 1, noOfBytes, newBmpPlace); // 0 = false, white color
		}
	}
}
