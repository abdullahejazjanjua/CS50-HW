#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtRed = (int) round(avg);
            image[i][j].rgbtBlue = (int) round(avg);
            image[i][j].rgbtGreen = (int) round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float SepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            if (SepiaRed > 255)
            {
                SepiaRed = 255;
            }

            float SepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            if (SepiaGreen > 255)
            {
                SepiaGreen = 255;
            }

            float SepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            if (SepiaGreen > 255)
            {
                SepiaGreen = 255;
            }

            image[i][j].rgbtRed = (int) round(SepiaRed);
            image[i][j].rgbtGreen = (int) round(SepiaGreen);
            image[i][j].rgbtBlue = (int) round(SepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) // for each pixel
        {
            float count = 0;
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;
            for (int k = -1; k >= -1 && k <= 1; k++)
            {
                for (int f = -1; f >= -1 && f <= 1; f++) // for each neighbour of THAT pixel
                {
                    if (i + k >= 0 && i + k < height && j + f >= 0 &&
                        j + f < width) // THAT pixel's neighbour's are within the bounds of the image
                    {
                        count++;
                        sumRed = (image[i + k][j + f].rgbtRed) + sumRed;
                        sumGreen = (image[i + k][j + f].rgbtGreen) + sumGreen;
                        sumBlue = (image[i + k][j + f].rgbtBlue) + sumBlue;
                    }
                }
            }

            float avgRed = sumRed / count;
            float avgGreen = sumGreen / count;
            float avgBlue = sumBlue / count;
            temp[i][j].rgbtRed = (int) round(avgRed);
            temp[i][j].rgbtGreen = (int) round(avgGreen);
            temp[i][j].rgbtBlue = (int) round(avgBlue);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
