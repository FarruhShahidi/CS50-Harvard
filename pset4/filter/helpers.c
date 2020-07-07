#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int avg = round(image[i][j].rgbtBlue / 3.0 + image[i][j].rgbtGreen / 3.0 + image[i][j].rgbtRed / 3.0) ;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
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
            int temp_blue = image[i][j].rgbtBlue;
            int temp_green = image[i][j].rgbtGreen;
            int temp_red = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = temp_blue;
            image[i][width - 1 - j].rgbtGreen = temp_green;
            image[i][width - 1 - j].rgbtRed = temp_red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 1; // counting the number of valid neighbors of [i][j]
            int blue = copy[i][j].rgbtBlue;
            int green = copy[i][j].rgbtGreen;
            int red = copy[i][j].rgbtRed;

            if (i > 0 && j > 0)
            {
                blue += copy[i - 1][j - 1].rgbtBlue;
                green += copy[i - 1][j - 1].rgbtGreen;
                red += copy[i - 1][j - 1].rgbtRed;
                count++;
            }
            if (i > 0)
            {
                blue += copy[i - 1][j].rgbtBlue;
                green += copy[i - 1][j].rgbtGreen;
                red += copy[i - 1][j].rgbtRed;
                count++;
            }

            if (i > 0 && j < width - 1)
            {
                blue += copy[i - 1][j + 1].rgbtBlue;
                green += copy[i - 1][j + 1].rgbtGreen;
                red += copy[i - 1][j + 1].rgbtRed;
                count++;
            }
            if (j > 0)
            {
                blue += copy[i][j - 1].rgbtBlue;
                green += copy[i][j - 1].rgbtGreen;
                red += copy[i][j - 1].rgbtRed;
                count++;
            }
            if (j < width - 1)
            {
                blue += copy[i][j + 1].rgbtBlue;
                green += copy[i][j + 1].rgbtGreen;
                red += copy[i][j + 1].rgbtRed;
                count++;
            }
            if (i < height - 1 && j > 0)
            {
                blue += copy[i + 1][j - 1].rgbtBlue;
                green += copy[i + 1][j - 1].rgbtGreen;
                red += copy[i + 1][j - 1].rgbtRed;
                count++;
            }
            if (i < height - 1)
            {
                blue += copy[i + 1][j].rgbtBlue;
                green += copy[i + 1][j].rgbtGreen;
                red += copy[i + 1][j].rgbtRed;
                count++;
            }
            if (i < height - 1 && j < width - 1)
            {
                blue += copy[i + 1][j + 1].rgbtBlue;
                green += copy[i + 1][j + 1].rgbtGreen;
                red += copy[i +  1][j + 1].rgbtRed;
                count++;
            }
            image[i][j].rgbtBlue  = round(blue / (count * 1.0));
            image[i][j].rgbtGreen  = round(green / (count * 1.0));
            image[i][j].rgbtRed  = round(red / (count * 1.0));




        }
    }

    return;
}

// Detect edges

//helper function
int pyth(float a, float b)
{

    return (int)fmin(round(sqrt(a * a + b * b)), 255.0);

}
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int hkernel[3][3] = {{-1, 0, 1}, {-2, 0, -2}, {-1, 0, 1}};
    int vkernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];


        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each color of a pixel, calculate two variable
            // for the blue color of the pixel image[i][j], calculate blue_gx, blue_gy
            float blue_gx = 0.0, blue_gy = 0.0, green_gx = 0.0, green_gy = 0.0, red_gx = 0.0, red_gy = 0.0;
            // edges are just black so the color values are 0.
            //top left
            if ( i > 0 && j > 0)
            {
                blue_gx += temp[i - 1][j - 1].rgbtBlue * hkernel[0][0];
                blue_gy += temp[i - 1][j - 1].rgbtBlue * vkernel[0][0];
                green_gx += temp[i - 1][j - 1].rgbtGreen * hkernel[0][0];
                green_gy += temp[i - 1][j - 1].rgbtGreen * vkernel[0][0];
                red_gx += temp[i - 1][j - 1].rgbtRed * hkernel[0][0];
                red_gy += temp[i - 1][j - 1].rgbtRed * vkernel[0][0];
            }
            //top
            if ( i > 0)
            {
                //blue_gx += temp[i - 1][j].rgbtBlue * hkernel[0][1];
                blue_gy += temp[i - 1][j].rgbtBlue * vkernel[0][1];
                //green_gx += temp[i - 1][j].rgbtGreen * hkernel[0][1];
                green_gy += temp[i - 1][j].rgbtGreen * vkernel[0][1];
                //red_gx += temp[i - 1][j].rgbtRed * hkernel[0][1];
                red_gy += temp[i - 1][j].rgbtRed * vkernel[0][1];
            }
            //top right
            if ( i > 0 && j < width - 1)
            {
                blue_gx += temp[i - 1][j + 1].rgbtBlue * hkernel[0][2];
                blue_gy += temp[i - 1][j + 1].rgbtBlue * vkernel[0][2];
                green_gx += temp[i - 1][j + 1].rgbtGreen * hkernel[0][2];
                green_gy += temp[i - 1][j + 1].rgbtGreen * vkernel[0][2];
                red_gx += temp[i - 1][j + 1].rgbtRed * hkernel[0][2];
                red_gy += temp[i - 1][j + 1].rgbtRed * vkernel[0][2];
            }
            //left
            if (j > 0)
            {
                blue_gx += temp[i][j - 1].rgbtBlue * hkernel[1][0];
                //blue_gy += temp[i][j - 1].rgbtBlue * vkernel[1][0];
                green_gx += temp[i][j - 1].rgbtGreen * hkernel[1][0];
                //green_gy += temp[i][j - 1].rgbtGreen * vkernel[1][0];
                red_gx += temp[i][j - 1].rgbtRed * hkernel[1][0];
                //red_gy += temp[i][j - 1].rgbtRed * vkernel[1][0];
            }
            //right
            if (j < width - 1)
            {
                blue_gx += temp[i][j + 1].rgbtBlue * hkernel[1][2];
                //blue_gy += temp[i][j + 1].rgbtBlue * vkernel[1][2];
                green_gx += temp[i][j + 1].rgbtGreen * hkernel[1][2];
                //green_gy += temp[i][j + 1].rgbtGreen * vkernel[1][2];
                red_gx += temp[i][j + 1].rgbtRed * hkernel[1][2];
                //red_gy += temp[i][j + 1].rgbtRed * vkernel[1][2];
            }
            //bottom left
            if (i < height - 1 && j > 0)
            {
                blue_gx += temp[i + 1][j - 1].rgbtBlue * hkernel[2][0];
                blue_gy += temp[i + 1][j - 1].rgbtBlue * vkernel[2][0];
                green_gx += temp[i + 1][j - 1].rgbtGreen * hkernel[2][0];
                green_gy += temp[i + 1][j - 1].rgbtGreen * vkernel[2][0];
                red_gx += temp[i + 1][j - 1].rgbtRed * hkernel[2][0];
                red_gy += temp[i + 1][j - 1].rgbtRed * vkernel[2][0];
            }
            //bottom
            if (i < height - 1)
            {
                //blue_gx += temp[i + 1][j].rgbtBlue * hkernel[2][1];
                blue_gy += temp[i + 1][j].rgbtBlue * vkernel[2][1];
                //green_gx += temp[i + 1][j].rgbtGreen * hkernel[2][1];
                green_gy += temp[i + 1][j].rgbtGreen * vkernel[2][1];
                //red_gx += temp[i + 1][j].rgbtRed * hkernel[2][1];
                red_gy += temp[i + 1][j].rgbtRed * vkernel[2][1];
            }
            // bottom right
            if (i < height - 1 && j < width - 1)
            {
                blue_gx += temp[i + 1][j + 1].rgbtBlue * hkernel[2][2];
                blue_gy += temp[i + 1][j + 1].rgbtBlue * vkernel[2][2];
                green_gx += temp[i + 1][j + 1].rgbtGreen * hkernel[2][2];
                green_gy += temp[i + 1][j + 1].rgbtGreen * vkernel[2][2];
                red_gx += temp[i + 1][j + 1].rgbtRed * hkernel[2][2];
                red_gy += temp[i + 1][j + 1].rgbtRed * vkernel[2][2];
            }
            image[i][j].rgbtBlue = pyth(blue_gx, blue_gy);
            image[i][j].rgbtGreen = pyth(green_gx, green_gy);
            image[i][j].rgbtRed = pyth(red_gx, red_gy);
        }
    }
    return;
}
