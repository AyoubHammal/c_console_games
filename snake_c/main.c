/**
 * Author: Ayoub Hammal
 * email: ayoubhammal@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAPX 40
#define MAPY 20

int compter = 1;
/*-----------------------------------------------------------------------*/
typedef enum Bool Bool;
enum Bool
{
    false, true
};
/*-----------------------------------------------------------------------*/
typedef enum Direction Direction;
enum Direction
{
    up, right, down, left
};
/*-----------------------------------------------------------------------*/
typedef struct BodyPart BodyPart;
struct BodyPart
{
    int posX;
    int posY;
    BodyPart* nextPart;
};
/*-----------------------------------------------------------------------*/
typedef struct Head Head;
struct Head
{
    int posX;
    int posY;
    BodyPart* firstPart;
    Direction direction;
    int lenght;
};
/*-----------------------------------------------------------------------*/
typedef struct Food Food;
struct Food
{
    int posX;
    int posY;
};
/*-----------------------------------------------------------------------*/
void snakeOrientation (char controller, Head* head);
Bool snakeMove (Head* head, char** map);
char** creatMap ();
void printMap (char** map, Head head, Food food);
void generatFood (Head head, Food* food);
void snakeExtension (Head* head);
Head* creatSnake ();
Bool gameOver (Head head);
void cleanBuffer ();
/*-----------------------------------------------------------------------*/
int main (int argc, char* argv [])
{
    int i = 0;
    char** map = NULL;
    char controller = 'd';
    map = creatMap ();
    
    Head* head = creatSnake ();
    BodyPart* bp = head->firstPart;
    BodyPart* bpt = NULL;

    Food food;

    Bool flag = false;
    generatFood (*head, &food);
    while (1)
    {
        system ("cls");
        if (flag == true)
            generatFood (*head, &food);

        printMap(map, *head, food);
        
        if (head->direction == right || head->direction == left)
            Sleep (0.00001);
        if (head->direction == up || head->direction == down)
            Sleep (0.00001);

        if (kbhit ()) 
            controller = getch ();
        
        if (controller == 'a')
            break;

        snakeOrientation (controller, head);

        if (flag == false)
            flag = snakeMove (head, map);
        else
        {
            snakeExtension (head);
            flag = false;
        }
        if (gameOver (*head) == false)
            break;
    }

    if (gameOver (*head) == false)
    {
        system ("cls");
        printMap (map, *head, food);
        printf ("game over\n");
    }
    
    while (bp != NULL)
    {
        bpt = bp;
        bp = bp->nextPart;
        free (bpt);
    }
    free (head);

    for (i = 0; i < MAPY + 2; i++) // to y + 2
    {
        free (map [i]);
    }
    free (map);

    system ("PAUSE");
    return 0;
}
/*-----------------------------------------------------------------------*/
void snakeOrientation (char controller, Head* head)
{
    if (controller == 'z' || controller == 'Z')
    {
        if (head->direction != down)
            head->direction = up;
    }
    else if (controller == 'd' || controller == 'D')
    {
        if (head->direction != left)
            head->direction = right;
    }
    else if (controller == 's' || controller == 'S')
    {
        if (head->direction != up)
            head->direction = down;
    }
    else if (controller == 'q' || controller == 'Q')
    {
        if (head->direction != right)
            head->direction = left;
    }
}
/*-----------------------------------------------------------------------*/
Bool snakeMove (Head* head, char** map)
{
    int i = 0;
    BodyPart* actuelBodyPart = head->firstPart;
    int x = 0, y = 0;
    int xt = 0, yt = 0;

    if (head->direction == up)
    {
        x = head->posX;
        y = head->posY;
        head->posY -= 1;
    }
    else if (head->direction == right)
    {
        x = head->posX;
        y = head->posY;
        head->posX += 1;
    }
    else if (head->direction == down)
    {
        x = head->posX;
        y = head->posY;
        head->posY += 1;
    }
    else if (head->direction == left)
    {
        x = head->posX;
        y = head->posY;
        head->posX -= 1;
    }

    while (actuelBodyPart!= NULL)
    {
        xt = actuelBodyPart->posX;
        yt = actuelBodyPart->posY;

        actuelBodyPart->posX = x;
        actuelBodyPart->posY = y;

        x = xt;
        y =yt;

        actuelBodyPart = actuelBodyPart->nextPart;
    }

    if (map [head->posY][head->posX] == 'o')
        return true;
    else
        return false;
}
/*-----------------------------------------------------------------------*/
char** creatMap ()
{
    int i = 0, j = 0;

    char** map = NULL;
    map = (char**)malloc (sizeof (char*) * (MAPY + 2));
    if (map == NULL)
    {
        printf("Dynamic allocation error\n");
        exit (EXIT_FAILURE);
    }

    for (i = 0; i < (MAPY + 2); i++)
    {
        map [i] = (char*)malloc (sizeof (char) * (MAPX + 2));
        if (map [i] == NULL)
        {
            printf("Dynamic allocation error\n");
            exit (EXIT_FAILURE);
        }
    }

    for (i = 0; i < MAPY + 2; i++)
    {
        for (j = 0; j < MAPX + 2; j++)
        {
            if (i == 0 || i == MAPY + 1 || j == 0 || j == MAPX + 1)
                map [i][j] = '!';
            else
                map [i][j] = ' ';
        }
    }

    return map;
}
/*-----------------------------------------------------------------------*/
void printMap (char** map, Head head, Food food)
{
    int i = 0, j = 0;
    BodyPart* bp = head.firstPart;

    for (i = 1; i < MAPY + 1; i++)
    {
        for (j = 1; j < MAPX + 1; j++)
        {
            map [i][j] = ' ';
        }
    }

    map [food.posY][food.posX] = 'o';

    while (bp != NULL)
    {
        map [bp->posY][bp->posX] = 'O';
        bp = bp->nextPart;
    }
    if (head.direction == up)
        map [head.posY][head.posX] = '^';
    if (head.direction == right)
        map [head.posY][head.posX] = '>';
    if (head.direction == down)
        map [head.posY][head.posX] = 'V';
    if (head.direction == left)
        map [head.posY][head.posX] = '<';

    for (i = 0; i < MAPY + 2; i++)
    {
        for (j = 0; j < MAPX + 2; j++)
        {
            printf ("%c", map [i][j]);
        }
        printf ("\n");
    }

    printf ("===============  Score : %d  ================\n", compter);

}
/*-----------------------------------------------------------------------*/
void generatFood (Head head, Food* food)
{
    BodyPart* bp = NULL;
    Bool bigflag = false, flag = true;
    
    while (bigflag == false)
    {
        bp = head.firstPart;
        flag = true;
        srand (time (NULL));
        food->posX = (rand () % MAPX) + 1;
        food->posY = (rand () % MAPY) + 1;
        
        while (flag == true && bp != NULL)
        {
            if (food->posX == bp->posX && food->posY == bp->posY)
                flag = false;
            else if (food->posX == head.posX && food->posY == head.posY)
                flag = false;
            bp = bp->nextPart;
        }

        if (bp == NULL)
            bigflag = true;
    }
}
/*-----------------------------------------------------------------------*/
void snakeExtension (Head* head)
{
    BodyPart* newBodyPart = NULL;
    newBodyPart = (BodyPart*)malloc (sizeof (BodyPart));
    if (newBodyPart == NULL)
    {
        printf ("Dynamic allocation error\n");
        exit (EXIT_FAILURE);
    }

    newBodyPart->nextPart = head->firstPart;
    head->firstPart = newBodyPart;
    newBodyPart->posX = head->posX;
    newBodyPart->posY = head->posY;
    if (head->direction == up)
        head->posY -= 1;
    else if (head->direction == right)
        head->posX += 1;
    else if (head->direction == down)
        head->posY += 1;
    else if (head->direction == left)
        head->posX -= 1;
    head->lenght++;

    compter++;
}
/*-----------------------------------------------------------------------*/
Head* creatSnake ()
{
    Head* head = NULL;
    head = (Head*)malloc (sizeof (Head));
    if (head == NULL)
    {
        printf ("Dynamic allocation error\n");
        exit (EXIT_FAILURE);
    }
    
    head->posX = 5;
    head->posY = 5;

    BodyPart* part1 = NULL;
    part1 = (BodyPart*)malloc (sizeof (BodyPart));
    if (part1 == NULL)
    {
        printf ("Dynamic allocation error\n");
        exit (EXIT_FAILURE);
    }

    part1->posX = 4;
    part1->posY = 5;
    part1->nextPart = NULL;

    head->firstPart = part1;
    head->lenght = 1;
    head->direction = right;

    return head;
}
/*-----------------------------------------------------------------------*/
Bool gameOver (Head head)
{
    BodyPart* bp = head.firstPart;

    if (head.posX == 0 || head.posX == MAPX + 1)
        return false;
    if (head.posY == 0 || head.posY == MAPY + 1)
        return false;

    while (bp != NULL)
    {
        if (head.posX == bp->posX && head.posY == bp->posY)
            return false;
        bp = bp->nextPart;
    }
    return true;
}
/*-----------------------------------------------------------------------*/
void cleanBuffer ()
{
    int c = 0;
    while (c != EOF && c != '\n')
    {
        c = getchar ();
    }
}
/*-----------------------------------------------------------------------*/