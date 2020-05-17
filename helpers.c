#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image [i][j].rgbtRed = round(((float)image [i][j].rgbtRed + image [i][j].rgbtGreen + image [i][j].rgbtBlue)/3);
            image [i][j].rgbtGreen = image [i][j].rgbtRed;
            image [i][j].rgbtBlue = image [i][j].rgbtRed;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage [height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyimage [i][j] = image [i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if(round (copyimage [i][j].rgbtRed * 0.393 + copyimage [i][j].rgbtGreen * 0.769 + copyimage [i][j].rgbtBlue * 0.189) > 254)
            {
                image [i][j].rgbtRed = 255;
            }
            else
            {
                image [i][j].rgbtRed = round (copyimage [i][j].rgbtRed * 0.393 + copyimage [i][j].rgbtGreen * 0.769 + copyimage [i][j].rgbtBlue * 0.189);
            }

            if(round (copyimage [i][j].rgbtRed * 0.349 + copyimage [i][j].rgbtGreen * 0.686 + copyimage [i][j].rgbtBlue * 0.168) > 254)
            {
                image [i][j].rgbtGreen =  255;
            }
            else
            {
                image [i][j].rgbtGreen =  round (copyimage [i][j].rgbtRed * 0.349 + copyimage [i][j].rgbtGreen * 0.686 + copyimage [i][j].rgbtBlue * 0.168);
            }

             if(round (copyimage [i][j].rgbtRed * 0.272 + copyimage [i][j].rgbtGreen * 0.534 + copyimage [i][j].rgbtBlue * 0.131) > 254)
            {
                image [i][j].rgbtGreen =  255;
            }
            else
            {
                 image [i][j].rgbtBlue =  round (copyimage [i][j].rgbtRed * 0.272 + copyimage [i][j].rgbtGreen * 0.534 + copyimage [i][j].rgbtBlue * 0.131);
            }


        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE a = image [i][width -1 -j];
            image [i][width -1 -j] = image [i][j];
            image [i][j] = a;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyimage [height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyimage [i][j] = image [i][j];

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if( i == 0 && j == 0)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i+1][j].rgbtRed +  copyimage [i][j+1].rgbtRed + copyimage [i+1][j+1].rgbtRed)/4;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen +  copyimage [i][j+1].rgbtGreen + copyimage [i+1][j+1].rgbtGreen)/4;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue +  copyimage [i][j+1].rgbtBlue + copyimage [i+1][j+1].rgbtBlue)/4;
            }
            else if (i == 0 && j == width - 1)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i][j-1].rgbtRed + (float) copyimage [i+1][j-1].rgbtRed + (float) copyimage [i+1][j].rgbtRed)/4;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen + (float) copyimage [i+1][j-1].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen)/4;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue + (float) copyimage [i+1][j-1].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue)/4;
            }
            else if(i == height - 1 && j == width - 1)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i][j-1].rgbtRed + (float) copyimage [i-1][j-1].rgbtRed + (float) copyimage [i-1][j].rgbtRed)/4;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen + (float) copyimage [i-1][j-1].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen)/4;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue + (float) copyimage [i-1][j-1].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue)/4;
            }
            else if(i == height - 1 && j == 0)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i][j+1].rgbtRed + (float) copyimage [i-1][j].rgbtRed + (float) copyimage [i-1][j+1].rgbtRed)/4;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i][j+1].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen + (float) copyimage [i-1][j+1].rgbtGreen)/4;
                image [i][j].rgbtBlue = round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i][j+1].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue + (float) copyimage [i-1][j+1].rgbtBlue)/4;
            }
            else if(i == 0)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i][j-1].rgbtRed + (float) copyimage [i][j+1].rgbtRed + (float) copyimage [i+1][j-1].rgbtRed + (float) copyimage [i+1][j].rgbtRed + (float) copyimage [i+1][j+1].rgbtRed)/6;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen + (float) copyimage [i][j+1].rgbtGreen + (float) copyimage [i+1][j-1].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen + (float) copyimage [i+1][j+1].rgbtGreen)/6;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue + (float) copyimage [i][j+1].rgbtBlue + (float) copyimage [i+1][j-1].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue + (float) copyimage [i+1][j+1].rgbtBlue)/6;
            }
            else if(j == 0)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i-1][j].rgbtRed + (float) copyimage [i-1][j+1].rgbtRed + (float) copyimage [i][j+1].rgbtRed + (float) copyimage [i+1][j].rgbtRed + (float) copyimage [i+1][j+1].rgbtRed)/6;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen + (float) copyimage [i-1][j+1].rgbtGreen + (float) copyimage [i][j+1].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen + (float) copyimage [i+1][j+1].rgbtGreen)/6;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue + (float) copyimage [i-1][j+1].rgbtBlue + (float) copyimage [i][j+1].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue + (float) copyimage [i+1][j+1].rgbtBlue)/6;
            }
            else if(i == height - 1)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i-1][j-1].rgbtRed + (float) copyimage [i-1][j].rgbtRed + (float) copyimage [i-1][j+1].rgbtRed + (float) copyimage [i][j-1].rgbtRed + (float) copyimage [i][j+1].rgbtRed)/6;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i-1][j-1].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen + (float) copyimage [i-1][j+1].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen + (float) copyimage [i][j+1].rgbtGreen)/6;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i-1][j-1].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue + (float) copyimage [i-1][j+1].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue + (float) copyimage [i][j+1].rgbtBlue)/6;
            }
            else if(j == width - 1)
            {
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i+1][j].rgbtRed + (float) copyimage [i-1][j].rgbtRed + (float) copyimage [i-1][j-1].rgbtRed + (float) copyimage [i+1][j-1].rgbtRed + (float) copyimage [i][j-1].rgbtRed)/6;
                image [i][j].rgbtGreen =  round ((float)copyimage [i][j].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen + (float) copyimage [i-1][j-1].rgbtGreen + (float) copyimage [i+1][j-1].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen)/6;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue + (float) copyimage [i-1][j-1].rgbtBlue + (float) copyimage [i+1][j-1].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue)/6;
            }
            else if(j != 0 && i !=0)
            {
                if(j != width - 1 && i != height - 1)
                image [i][j].rgbtRed =  round((float)copyimage [i][j].rgbtRed + (float) copyimage [i-1][j-1].rgbtRed + (float) copyimage [i-1][j].rgbtRed + (float) copyimage [i-1][j+1].rgbtRed + (float) copyimage [i][j-1].rgbtRed + (float) copyimage [i][j+1].rgbtRed + (float) copyimage [i+1][j-1].rgbtRed + (float) copyimage [i+1][j].rgbtRed + (float) copyimage [i+1][j+1].rgbtRed)/9;
                image [i][j].rgbtGreen =  round((float)copyimage [i][j].rgbtGreen + (float) copyimage [i-1][j-1].rgbtGreen + (float) copyimage [i-1][j].rgbtGreen + (float) copyimage [i-1][j+1].rgbtGreen + (float) copyimage [i][j-1].rgbtGreen + (float) copyimage [i][j+1].rgbtGreen + (float) copyimage [i+1][j-1].rgbtGreen + (float) copyimage [i+1][j].rgbtGreen + (float) copyimage [i+1][j+1].rgbtGreen)/9;
                image [i][j].rgbtBlue =  round((float)copyimage [i][j].rgbtBlue + (float) copyimage [i-1][j-1].rgbtBlue + (float) copyimage [i-1][j].rgbtBlue + (float) copyimage [i-1][j+1].rgbtBlue + (float) copyimage [i][j-1].rgbtBlue + (float) copyimage [i][j+1].rgbtBlue + (float) copyimage [i+1][j-1].rgbtBlue + (float) copyimage [i+1][j].rgbtBlue + (float) copyimage [i+1][j+1].rgbtBlue)/9;
            }
        }
    }
    return;
}
