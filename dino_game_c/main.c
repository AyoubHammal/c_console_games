/**
 * Author: Ayoub Hammal
 * email: ayoubhammal@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAPX 50
#define MAPY 4

typedef enum Bool
{
    false, true
} Bool;

typedef struct Dino
{
    int posx;
    int posy;
} Dino;

char** creatMap ();
Dino* dinoInit ();
void move (char** map, Dino* dino, char controller);
void printMap (char** map, Dino dino);
Bool gameOver (char** map, Dino dino);

int main (int argc, char* argv [])
{
    int i = 0;
    char controller = 0;
    char** map = creatMap ();
    Dino* dino = dinoInit ();
    
    system ("cls");
    while (1)
    {
        controller = 'd';
        if (kbhit ()) 
            controller = getch ();
        if (controller == 'a')
            break;
        move (map, dino, controller);
        system ("cls");
        printMap (map, *dino);
        if (gameOver (map, *dino) == true)
            break;
        Sleep (10);
        
    }
    
    if (gameOver (map, *dino) == true)
        printf ("GAME OVER !!\n");
    system ("PAUSE");
    for (i = 0; i < MAPY; i++)
    {
        free (map [i]);
    }
    free (map);
    free (dino);
    return 0;
}

char** creatMap ()
{
    int i = 0, j = 0;
    char** map = NULL;
    map = (char**)malloc (MAPY * sizeof (char*));
    if (map == NULL)
    {
        printf ("Erreur allocation dynamique\n");
        exit (EXIT_FAILURE);
    }
    for (i = 0; i < MAPY; i++)
    {
        map [i] = (char*)malloc (MAPX * sizeof (char));
        if (map [i] == NULL)
        {
            printf ("Erreur allocation dynamique\n");
            exit (EXIT_FAILURE);
        }
    }
    for (i = 0; i < MAPX; i++)
    {
        for (j = 0; j < MAPY - 1; j++)
        {
            map [j][i] = ' ';
        }
        map [MAPY - 1][i] = '_';
    }
    return map;
}

Dino* dinoInit ()
{
    Dino* dino = NULL;
    dino = (Dino*)malloc (sizeof (Dino));
    if (dino == NULL)
    {
        printf ("Erreur allocation dynamique\n");
        exit (EXIT_FAILURE);        
    }

    dino->posx = 2;
    dino->posy = MAPY - 1;

    return dino;
}

void move (char** map, Dino* dino, char controller)
{
    static int timeInAir = 7;
    int randNb1 = 0, randNb2 = 0, delay = 0;
    Bool flag = true;
    int i = 0;
    for (i = 1; i < MAPX; i++)
    {
        map [MAPY - 1][i - 1] = map [MAPY - 1][i];
    }
    
    srand (time (NULL));
    delay = (rand () % 7) + 15;
    randNb1 = rand ();
    randNb2 = rand ();
    i = 1;
    while (flag && i < delay)
    {
        if (map [MAPY - 1][MAPX - i] == 'X')
            flag = false;
        i++;
    }

    if ((randNb1 + randNb2) % 2 && flag)
        map [MAPY - 1][MAPX - 1] = 'X';
    else
        map [MAPY - 1][MAPX - 1] = '_';

    if (controller == ' ')
    {
        dino->posy = MAPY - 3;
        timeInAir--;
    }
    else if (timeInAir < 7)
    {
        timeInAir--;
    }

    if (timeInAir < 0)
    {
        timeInAir = 7;
        dino->posy = MAPY - 1;

    }
}

void printMap (char** map, Dino dino)
{
    int i = 0, j = 0;

    for (i = 0; i < MAPY; i++)
    {
        for (j = 0; j < MAPX; j++)
        {
            if (dino.posx == j && dino.posy == i)
                printf ("O");
            else
                printf ("%c", map [i][j]);
        }
        printf ("\n");
    }

}

Bool gameOver (char** map, Dino dino)
{
    if (map [dino.posy][dino.posx] == 'X')
        return true;
    else
        return false;
}