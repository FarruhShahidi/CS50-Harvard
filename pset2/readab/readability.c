#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text:\n");
    int num_sentences = 0;
    int num_words = 0;
    long num_letters = 0;

    for (size_t i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            num_letters++;
        }
        else if (text[i] == ' ')
        {
            num_words++;
        }
        else if (text[i]  == '!' || text[i]  == '?' || text[i]  == '.')
        {
            num_sentences++;
        }
    }
    // at the end of the text we increased num_sentences but not num_words.
    num_words++;
    //Calculating the average number of sentences and letters per 100 words in the text.
    //Need to cast to float to avoid integer division
    float avg_sentences = ((float)(num_sentences) / num_words) * 100;
    float avg_letters = ((float)(num_letters) / num_words) * 100;
    //Coleman-Liau index
    float Coleman_Liao_index =  0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;

    // ready to print
    if (Coleman_Liao_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (Coleman_Liao_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(Coleman_Liao_index));
    }




}