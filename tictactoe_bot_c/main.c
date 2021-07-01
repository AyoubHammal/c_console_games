/**
 * Author: Ayoub Hammal
 * email: ayoubhammal@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/***************************************************************************************/

typedef enum Bool Bool;
enum Bool
{
    false, true
};
typedef enum joueur joueur;
enum joueur
{
    jx, jo
};

/***************************************************************************************/

void printTab (char table[3][3]);
Bool fillTable (joueur jActuel, int coup, char table[3][3]);
Bool GG (char table [3][3]);
Bool IAxo (char table [3][3], int coup);

/***************************************************************************************/
int main (int argc, char *argv[])
{   
    char table[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}} ;
    int i, coup = 0;
    Bool valCoup = false, fin, testeIA = true;
    printf ("Tic Tac Toe\n>Use numbers to select a square:\n\n");
    printf ("_____________\n| 1 | 2 | 3 |\n_____________\n| 4 | 5 | 6 |\n_____________\n| 7 | 8 | 9 |\n_____________");
    
    i = 0;
    fin = false;
    do
    {
        if (i % 2 == 0)
        {
            printf ("\nYour turn : ");
            scanf ("%d", &coup);
            valCoup = fillTable (jx, coup, table);
        }
        else 
        {   
            //scanf ("%d", &coup); 
            //valCoup = fillTable (jo, coup, table);
            testeIA  = IAxo (table, coup);
        }
        if (valCoup == false)
        {    
            printf ("This square is already used !!\n");
        }
        else
        {
            printTab (table);
            i++;
        }

        fin = GG (table);

    } while (i < 9 && fin == false && testeIA == true);

    if (i == 9 && fin  ==  false)
        printf ("Stalemate ehh !!\n");
    else if ((i - 1) % 2 == 0)
        printf ("First player wins, GG !!\n");
    else if ((i - 1) % 2 == 1)
        printf ("Second player wins, GG !!\n");
    

    system("PAUSE");
    return 0;
}

/***************************************************************************************/

void printTab (char table[3][3])
{
    int i, j;
    system ("cls");
    for (i = 0; i < 3; i++)
    {
        printf("____________\n");
        printf ("|");
        for (j = 0; j < 3; j++)
        {
            printf (" %c |", table[i][j]);
        }
        printf ("\n");
    }
    printf("_____________\n");
}

Bool fillTable (joueur jActuel, int coup, char table[3][3])
{
    int i = (coup - 1) / 3;
    int j = (coup - 1) % 3;
    if (table [i][j] == ' ')
    {
        if (jActuel == jx)
            table [i][j] = 'x';
        else
            table [i][j] = 'o';

        return true;
    }
    else
    {
        return false;
    }
}

Bool GG (char table [3][3])
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if (table [i][0] == table [i][1] && table [i][1] == table [i][2] && table [i][0] != ' ')
            return true;
        else if (table [0][i] == table [1][i] && table [1][i] == table [2][i] && table [0][i] != ' ')
            return true;
    }
    if (table [0][0] == table [1][1] && table [1][1] == table [2][2] && table [1][1] != ' ')
        return true;
    else if (table [0][2] == table [1][1] && table [1][1] == table [2][0] && table [1][1] != ' ')
        return true;

    return false;
}

/***************************************************************************************/
//partie IA "version beta"

Bool IAxo (char table [3][3], int coup)
{
    int i, j, nbx = 0, nbo = 0;
    static int cas = 0;
    static int ix, jx;
    
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (table [i][j] == table [i][(j + 1) % 3] && table [i][j] != ' ')
            {   
                if (table [i][(j + 2) % 3] == ' ')
                {
                    table [i][(j + 2) % 3] = 'o';
                    return true;
                }
            }
            if (table [j][i] == table [(j + 1) % 3][i] && table [j][i] != ' ')
            {   
                if (table [(j + 2) % 3][i] == ' ')
                {    
                    table [(j + 2) % 3][i] = 'o';
                    return true;
                }
            }
        }
    }
    
    for (i = 0; i < 3; i++)
    {
        if (table [i][i] == table [(i + 1) % 3][(i + 1) % 3] && table [i][i] != ' ')
        {   
            if (table [(i + 2) % 3][(i + 2) % 3] == ' ')
            {
                table [(i + 2) % 3][(i + 2) % 3] = 'o';
                return true;
            }
        }
        if (table [2 - i][i] == table [(4 - i) % 3][(i + 1) % 3] && table [2 - i][i] != ' ')
        {   
            if (table [3 - (2 - i) - ((4 - i) % 3)][3 - i - ((i + 1) % 3)] == ' ')
            {
                table [3 - (2 - i) - ((4 - i) % 3)][3 - i - ((i + 1) % 3)] = 'o';
                return true;
            }
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (table [i][j] == 'x')
            {
                nbx++;
            }
            if (table [i][j] == 'o')
            {
                nbo++;
            }
        }
    }
    if (nbx == 1 && nbo == 0)
    {
        if (coup == 1 || coup == 3 || coup == 7 || coup == 9)
        {
            table [1][1] = 'o';
            cas = 1;
            ix = (coup - 1) % 3;
            jx = (coup - 1) / 3;
            return true;
        }
        if (coup == 2 || coup == 4 || coup == 6 || coup == 8)
        {
            table [1][1] = 'o';
            cas = 2;
            ix = (coup - 1) % 3;
            jx = (coup - 1) / 3;
            return true;
        }
        if (coup == 5)
        {
            table [0][0] = 'o';
            cas = 3;
            return true;
        }
    }
    else if (nbx == 2 && nbo == 1)
    {
        if (cas == 1)
        {
            if (table [1][(jx + 2) % 3] != 'x')
            {
                table [1][(jx + 2) % 3] = 'o';
                return true;
            }
            else
            {
                table [(ix + 2) % 3][1] = 'o';
                return true;
            }
        }
        /*if (cas == 2)
        {
            je gagne sans ta mère !!
        }*/
        if (cas == 3)
        {
            if (coup == 9) 
            {
                table [2][0] = '0';
                return true;
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (table[i][j] == ' ')
            {
                table [i][j] = 'o';
                return true;
            }    
        }
    }
}

    
