#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char fileName[20];
    char artist[20];
    char title[20];
    char album[20];
    int year;
    char genre[20];
    int rating;

    struct List* nextSong;
}List;
List *music;
int currSize = 1;
int exactSize = 0;
const char file[] = "audio.bin";

List *newAudio()
{
    List *result = NULL;
    result = (List *)malloc(sizeof(List));
    printf("Enter file path: ");
    scanf("%s",&result->fileName);
    fflush(stdin);
    printf("Enter artist: ");
    gets(result->artist);
    printf("Enter title: ");
    gets(result->title);
    printf("Enter album: ");
    scanf("%s",&result->album);
    fflush(stdin);
    printf("Enter year: ");
    scanf("%d",&result->year);
    fflush(stdin);
    printf("Enter genre: ");
    gets(result->genre);
    printf("Enter rating: ");
    scanf("%d",&result->rating);
    if(result->rating<0 || result->rating>5)
    {
        printf("Rating 0-5\nEnter new rating: ");
        scanf("%d",&result->rating);
    }
    result->nextSong=NULL;
    return result;
}

List *get_new_song(List *root)
{
    List *current = root;
    List *newSong;
    newSong=malloc(sizeof(List));
    newSong=newAudio();
    while(current!=NULL)
    {
        if(current->nextSong=NULL )
                current=current->nextSong;
        else
                current->nextSong=newSong;
    }
    return current;
}

void save_file()
{
    FILE *fp;
    List *item = newSong;
    fp=fopen(file,"ab+");
    if(fp==NULL)
    {
        printf("Error opening file!");
    }
    else
    {
        fwrite(&item,sizeof(List),1,fp);
    }
    fclose(fp);
}

void read_file(List * root)
{
          FILE *fp;
          fp=fopen(file,"rb");
          if (fp == NULL) {
          printf("Error opening!");
          }
          if(fread(&exactSize,sizeof(int),1,fp)!=1)
          {
              fclose(fp);
              printf("No audio loaded!\n");
          }
          fclose(fp);
}

bool compare_strings(char *string1, char *string2)
{
    const char *delim = " ,.-\'\\\"@#$%^&*()_=+";
    char *str1 = strtok(string1,delim);
    int sameElements = 0;
    int cnt1 = 0;
    int cnt2 = 0;

    while(str1 != NULL)
    {
        cnt1++;
        char *str2 = strtok(string2,delim);

        while(str2 != NULL)
        {
            cnt2++;
            if(strcmp(str1,str2)==0)
                sameElements++;
            str2=strtok(NULL,delim);
        }
        str1=strtok(NULL,delim);
    }
    if(sameElements>((cnt1+cnt2)/2))
            return true;

}

void compare(List *root)
{
    List *item1=root;
    List *item2=root;
    while(item1!=NULL)
    {
        while(item2!=NULL)
        {
            if ((item1->year == item2->year) && compare_strings(item1->artist, item2->artist) &&
                compare_strings(item1->title, item2->title) && compare_strings(item1->album, item2->album)
                && compare_strings(item1->genre, item2->genre))
                   printf("%s and %s are duplicated!\n", item1->fileName, item2->fileName);
            else
                    printf("No duplicated songs!\n");
            item2=item2->nextSong;
        }
        item1=item1->nextSong;
    }
}




int main()
{
     List *root = NULL;
     FILE *fp;
     music = calloc(currSize,sizeof(*music));
     //read_file();
     char option[1];

     int read = 1;
     while(read)
     {
     printf("                                   Choose an option\n");
     printf("Add new song - A || Show duplicate songs - S || Delete all songs from an artist - D  || Close program - C\n");
     scanf("%s",option);
     if(strcmp(option,"A")==0){
        get_new_song(root);
        save_file();
        }
     else if(strcmp(option,"S")==0)
     {
        //compare(root);
     }
     else if(strcmp(option,"D")==0)
     {

     }
     else if(strcmp(option,"C")==0){
        exit(1);
     }
     system("cls");
     fflush(stdin);
     }
}

