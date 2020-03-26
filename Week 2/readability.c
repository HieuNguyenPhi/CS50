#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float grade(int l, int w, int s);

int main(void)
{
    string userinput = get_string("Text :\n");
    //int i;
    int letter = 0, word = 0, sentence = 0;
    for (int i=0; i < strlen(userinput); i++)
    {
        if ((userinput[i]>='A' && userinput[i] <= 'Z') || (userinput[i] >='a' && userinput[i]<='z'))
        {
            letter++;
        }
        else if(userinput[i]==' ')
        {
            word++;
        }
        else if(userinput[i] =='.' || userinput[i] =='?' || userinput[i] == '!')
        {
            sentence++;
        }
    }
    printf("%i letters, %i words, %i sentences.\n",letter, word+1, sentence);
    float index = grade(letter,word+1,sentence);
    if (index >=16)
    {
        printf("Grade 16+");
    }
    else if(index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", (int) round(index));
    }
    printf("\n");
}

float grade(int l, int w, int s)
{
    float L = 100*l/w;
    float S = 100*s/w;
    return 0.0588 * L - 0.296 * S - 15.8;
}
