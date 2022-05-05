/*
    Project: File Dispatcher
    Author: Evan Green
    Course: CmpSci 472
    Instructor: F. Ganther
*/

#include <stdio.h>
#define MAX_SECTORS 40
#define SECTOR_SIZE 500

char sectors[MAX_SECTORS];
char stored[MAX_SECTORS][MAX_SECTORS + 1];
int stored_size = 0;

void initialize()
{
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        sectors[i] = ' ';
    }
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        stored[i][0] = ' ';
    }
}

int valid(int rs)
{
    int vcount = 0;
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        if (sectors[i] == ' ')
        {
            vcount++;
        }
        else
        {
            vcount = 0;
        }

        if (vcount == rs)
        {
            return i - rs + 1;
        }
    }
    return -1;
}

int invalid(int rs)
{
    int count = 0;
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        if (sectors[i] == ' ')
        {
            count++;
        }
    }
    if (count >= rs)
    {
        return 1;
    }
    return 0;
}

int getns(int begin)
{
    while (begin < MAX_SECTORS && sectors[begin] != ' ')
    {
        begin++;
    }
    if (begin == MAX_SECTORS)
    {
        return -1;
    }
    else
    {
        return begin;
    }
}

void addItem()
{
    char file;
    int size, i, ps, ns;

    printf("##                                                    ##\n"
           "  =>  Enter the file name (single character) : ");
    scanf("%s", &file);
    printf("##                                                    ##\n"
           "  =>  Enter the size of the file (1-3300 bytes):  ");
    scanf("%d", &size);

    int rs = size / SECTOR_SIZE;
    if (size % SECTOR_SIZE != 0)
    {
        rs += 1;
    }

    stored[stored_size][0] = file;
    int start = valid(rs);

    if (start != -1)
    {
        for (i = 0; i < rs; i++)
        {
            sectors[start + i] = file;
            stored[stored_size][i + 1] = start + i;
        }
        stored[stored_size][i + 1] = ' ';
        stored_size++;

        printf("\n##                                                    ##\n"
               "##  File has been added!                              ##\n"
               "##                                                    ##\n"
               "#######################################################\n\n");
    }

    else if (invalid(rs))
    {
        ps = -1;
        for (i = 0; i < rs; i++)
        {
            ns = getns(ps + 1);
            sectors[ns] = file;
            stored[stored_size][i + 1] = ns;
        }
        stored[stored_size][i + 1] = ' ';
        stored_size++;

        printf("\n##                                                   ##\n"
               "##  File has been added!                             ##\n"
               "##                                                   ##\n"
               "#######################################################\n\n");
    }
    else
    {
        printf("\n##                                                    ##\n"
               "##  File cannot be allocated!                         ##\n"
               "##                                                    ##\n"
               "########################################################\n\n");
    }
}

void removeItem()
{
    char file;
    int i, sector_index;

    printf("\n########################################################\n"
           "  =>  Enter the file name (single character) :  ");
    scanf("%s", &file);

    int stored_index = -1;
    for (i = 0; i < stored_size; i++)
    {
        if (stored[i][0] == file)
        {
            stored_index = i;
            break;
        }
    }

    if (stored_index == -1)
    {
        printf("\n##                                                   ##\n"
               "## File not found!                                   ##\n"
               "#######################################################\n\n");
        return;
    }

    i = 1;
    sector_index = stored[stored_index][i];
    while (sector_index != ' ')
    {
        sectors[sector_index] = ' ';
        i++;
        sector_index = stored[stored_index][i];
    }

    printf("##                                                   ##\n"
           "## File has been removed!                            ##\n"
           "#######################################################\n\n");
}

void showSectors()
{
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        printf("%-3c", sectors[i]);
    }
    printf("\n");
    for (int i = 0; i < MAX_SECTORS; i++)
    {
        printf("%-3d", i);
    }
    printf("\n");
}

int main()
{
    int choice;
    initialize();

    do
    {
        printf("\n########################################################\n"
               "## 1. Add data to device                              ##\n"
               "## 2. Remove data from device                         ##\n"
               "## 3. Show stored sectors                             ##\n"
               "## 4. Exit                                            ##\n"
               "##                                                    ##\n"
               "  => Please Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            removeItem();
            break;
        case 3:
            showSectors();
            break;
        case 4:
            printf("Exiting\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 4);
    return 0;
}