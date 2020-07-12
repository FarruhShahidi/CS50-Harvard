
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // ony two arg count
    if (argc != 2)
    {
        printf(" Two arguments\n");
        return 1;
    }

    // check if open
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not be opened\n");
        return 2;
    }
    //a file to write
    FILE *img;
    //name file
    char filename[7];
    //counter
    int pic_count = 0;
    //buffer
    unsigned char *buffer = malloc(512);

    while (fread(buffer, 512, 1, card))
    {
        // check if it is a beginning of a jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if we have seen a jpeg, we close
            if (pic_count > 0)
            {
                fclose(img);
            }

            // create
            sprintf(filename, "%03d.jpg", pic_count++);
            img = fopen(filename, "w");
            // check if img is opened
            if (img == NULL)
            {
                fclose(card);
                free(buffer);
                return 3;
            }


        }


        if (pic_count > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    //close the files
    fclose(img);
    fclose(card);
    //free the memory
    free(buffer);
    return 0;
}


