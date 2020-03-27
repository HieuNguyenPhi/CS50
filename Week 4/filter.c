#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (float)((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            average = round(average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy[i][j].rgbtBlue = limit(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));
            imagecopy[i][j].rgbtGreen = limit(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            imagecopy[i][j].rgbtRed = limit(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
        }
        
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }
    free(imagecopy);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagecopy[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            imagecopy[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            imagecopy[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }
    free(imagecopy);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*imagecopy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 1; i < height - 1; i++) //1 and height - 1 are due to different treatment of the edges
    {
        for (int j = 1; j < width - 1; j++) //1 and height - 1 are due to different treatment of the edges
        {
            imagecopy[i][j].rgbtBlue = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
            imagecopy[i][j].rgbtGreen = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
            imagecopy[i][j].rgbtRed = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
        }
    }

    //first and last line
    for (int j = 1; j < width - 1; j++) //corners treated separately
    {
        imagecopy[0][j].rgbtBlue = round((image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[0][j + 1].rgbtBlue + image[0 + 1][j - 1].rgbtBlue + image[0 + 1][j].rgbtBlue + image[0 + 1][j + 1].rgbtBlue) / 6.0);
        imagecopy[0][j].rgbtGreen = round((image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[0][j + 1].rgbtGreen + image[0 + 1][j - 1].rgbtGreen + image[0 + 1][j].rgbtGreen + image[0 + 1][j + 1].rgbtGreen) / 6.0);
        imagecopy[0][j].rgbtRed = round((image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[0][j + 1].rgbtRed + image[0 + 1][j - 1].rgbtRed + image[0 + 1][j].rgbtRed + image[0 + 1][j + 1].rgbtRed) / 6.0);
        imagecopy[height - 1][j].rgbtBlue = round((image[height - 1 - 1][j - 1].rgbtBlue + image[height - 1 - 1][j].rgbtBlue + image[height - 1 - 1][j + 1].rgbtBlue + image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue) / 6.0);
        imagecopy[height - 1][j].rgbtGreen = round((image[height - 1 - 1][j - 1].rgbtGreen + image[height - 1 - 1][j].rgbtGreen + image[height - 1 - 1][j + 1].rgbtGreen + image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen) / 6.0);
        imagecopy[height - 1][j].rgbtRed = round((image[height - 1 - 1][j - 1].rgbtRed + image[height - 1 - 1][j].rgbtRed + image[height - 1 - 1][j + 1].rgbtRed + image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed) / 6.0);
    }

    //first and last column
    for (int i = 1; i < height - 1; i++)
    {
        imagecopy[i][0].rgbtBlue = round((image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue + image[i][0].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][0].rgbtBlue + image[i + 1][1].rgbtBlue) / 6.0);
        imagecopy[i][0].rgbtGreen = round((image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen + image[i][0].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][0].rgbtGreen + image[i + 1][1].rgbtGreen) / 6.0);
        imagecopy[i][0].rgbtRed = round((image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed + image[i][0].rgbtRed + image[i][1].rgbtRed + image[i + 1][0].rgbtRed + image[i + 1][1].rgbtRed) / 6.0);
        imagecopy[i][width - 1].rgbtBlue = round((image[i - 1][width - 2].rgbtBlue + image[i - 1][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue + image[i][width - 1].rgbtBlue + image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue) / 6.0);
        imagecopy[i][width - 1].rgbtGreen = round((image[i - 1][width - 2].rgbtGreen + image[i - 1][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen + image[i][width - 1].rgbtGreen + image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen) / 6.0);
        imagecopy[i][width - 1].rgbtRed = round((image[i - 1][width - 2].rgbtRed + image[i - 1][width - 1].rgbtRed + image[i][width - 2].rgbtRed + image[i][width - 1].rgbtRed + image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed) / 6.0);
    }

    //corners
    imagecopy[0][0].rgbtBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0);
    imagecopy[0][0].rgbtGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0);
    imagecopy[0][0].rgbtRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0);

    imagecopy[0][width - 1].rgbtBlue = round((image[0][width - 2].rgbtBlue + image[0][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue) / 4.0);
    imagecopy[0][width - 1].rgbtGreen = round((image[0][width - 2].rgbtGreen + image[0][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen) / 4.0);
    imagecopy[0][width - 1].rgbtRed = round((image[0][width - 2].rgbtRed + image[0][width - 1].rgbtRed + image[1][width - 2].rgbtRed + image[1][width - 1].rgbtRed) / 4.0);

    imagecopy[height - 1][0].rgbtBlue = round((image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue + image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue) / 4.0);
    imagecopy[height - 1][0].rgbtGreen = round((image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen + image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen) / 4.0);
    imagecopy[height - 1][0].rgbtRed = round((image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed + image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed) / 4.0);

    imagecopy[height - 1][width - 1].rgbtBlue = round((image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue) / 4.0);
    imagecopy[height - 1][width - 1].rgbtGreen = round((image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen) / 4.0);
    imagecopy[height - 1][width - 1].rgbtRed = round((image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed) / 4.0);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = imagecopy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = imagecopy[i][j].rgbtGreen;
            image[i][j].rgbtRed = imagecopy[i][j].rgbtRed;
        }
    }
    free(imagecopy);
    return;
}
