#include <stdio.h>
#include <cs50.h>
#include <string.h>

float grade(int l, int w, int s);

int main(void)
{
    string userinput = get_string("Text :\n");
    int letter = 0, word = 1, sentence = 0;
    //counting
    for (int i = 0; i < strlen(userinput); i++)
    {
        if ((userinput[i] >= 'A' && userinput[i] <= 'Z') || (userinput[i] >= 'a' && userinput[i] <= 'z'))
        {
            letter++;
        }
        else if (userinput[i] == ' ')
        {
            word++;
        }
        else if (userinput[i] == '.' || userinput[i] == '?' || userinput[i] == '!')
        {
            sentence++;
        }
    }
    //grading
    float index = grade(letter, word, sentence);
    if (index >= 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", (int)(index + 0.5));
    }
    printf("\n");
}

float grade(int l, int w, int s)
{
    float L = 100 * (float)l / (float)w;
    float S = 100 * (float)s / (float)w;
    return 0.0588 * L - 0.296 * S - 15.8;
}
