#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Enter a number:\n");
    }
    while (height < 1 || height > 8);
    // loop through the heights
    for (int i = 1; i <= height; i++)
    {
        //loop through each row
        for (int j = 1; j <= height; j++)
        {
            if (i + j <= height) //spaces initially depending on i
            {
                printf(" ");
            }
            else
            {
                printf("#"); // #'s start appearing then.
            }

        }

        printf("\n"); //new line after each row.


    }
}