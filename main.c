#include <math.h>
#include <string.h>
#include "list/list.h"

#define tile_empty 0
#define tile_wall 1
#define tile_start 2
#define tile_end 3
#define tile_open 7
#define tile_closed 9

void draw(int grid[128][128], int width, int height);
void drawFinalPath(int grid[128][128], int width, int height, POINT *lastPoint, POINT *start, POINT *end);
int manhattanDistance(POINT *p1, POINT *p2);
POINT *lowestFScore(LIST *list);

int main(int argc, char *argv[])
{
    int width = 128, height = 128;
    int grid[128][128];

    POINT start;
    POINT end;

    /* READING FILE */

    char fileName[80];
    char ch[128];
    FILE *fp;

    printf("Enter .amap file name:\n");
    gets(fileName);

    fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        printf("Error while opening the file.\n");
        system("pause");
        return 0;
    }

    int index = 0;
    int f_x = 0, f_y = 0;
    while (fgets(ch, 128, fp))
    {
        if (index == 0)
        {
            sscanf(ch, "%d", &width);
            index++;
        }
        else if (index == 1)
        {
            sscanf(ch, "%d", &height);
            index++;
        }
        else
        {
            f_x = 0;
            for (; f_x < width; f_x++)
            {
                grid[f_x][f_y] = ch[f_x] - '0';

                if (grid[f_x][f_y] == 2)
                {
                    start.x = f_x;
                    start.y = f_y;
                }
                else if (grid[f_x][f_y] == 3)
                {
                    end.x = f_x;
                    end.y = f_y;
                }
            }
            f_y++;
        }
    }

    /* FIRST DRAW */

    draw(grid, width, height);

    /* INIT */

    LIST open = {.len = 0}, closed = {.len = 0};

    int found = 0;
    POINT *s;
    POINT walkableTiles[4];
    int walkableTilesCount = 0;

    l_insertFirst(&open, (POINT){.x = 2, .y = 4, .scoreF = manhattanDistance(&start, &end), .scoreG = 0, .scoreH = manhattanDistance(&start, &end), .parent = NULL});

    /* START */

    while (open.len != 0 && !found)
    {

        /* GET LOWEST F SCORE POINT AND ADD IT TO CLOSED LIST */

        s = lowestFScore(&open);
        l_insertLast(&closed, (POINT){.x = s->x, .y = s->y, .scoreF = s->scoreF, .scoreG = s->scoreG, .scoreH = s->scoreH, .parent = s->parent});
        l_deleteNodeAt(&open, l_getNodePos(&open, createNode(*s)));
        s = &l_getNodeAt(&closed, closed.len - 1)->data;

        grid[s->x][s->y] = tile_closed; //CLOSED TILE

        /* GET ADJACENT TILES */

        walkableTilesCount = 0;

        //Top
        if (s->y - 1 >= 0 && s->y - 1 < height)
        {
            switch (grid[s->x][s->y - 1])
            {
            case tile_empty:
            case tile_closed:
            case tile_open:
            case tile_end:
                walkableTiles[walkableTilesCount++] = (POINT){.x = s->x, .y = s->y - 1};
            default:
                break;
            }
        }

        //Bottom
        if (s->y + 1 >= 0 && s->y + 1 < height)
        {
            switch (grid[s->x][s->y + 1])
            {
            case tile_empty:
            case tile_closed:
            case tile_open:
            case tile_end:
                walkableTiles[walkableTilesCount++] = (POINT){.x = s->x, .y = s->y + 1};
            default:
                break;
            }
        }

        //Left
        if (s->x - 1 >= 0 && s->x - 1 < width)
        {
            switch (grid[s->x - 1][s->y])
            {
            case tile_empty:
            case tile_closed:
            case tile_open:
            case tile_end:
                walkableTiles[walkableTilesCount++] = (POINT){.x = s->x - 1, .y = s->y};
            default:
                break;
            }
        }

        //Right
        if (s->x + 1 >= 0 && s->x + 1 < width)
        {
            switch (grid[s->x + 1][s->y])
            {
            case tile_empty:
            case tile_closed:
            case tile_open:
            case tile_end:
                walkableTiles[walkableTilesCount++] = (POINT){.x = s->x + 1, .y = s->y};
            default:
                break;
            }
        }

        /* CHECK ADJACENT TILES */

        for (int i = 0; i < walkableTilesCount; i++)
        {
            int isClosed = l_getNodePos(&closed, createNode(walkableTiles[i])) > -1;
            int openPos = l_getNodePos(&open, createNode(walkableTiles[i]));

            if (isClosed)
            {
                //Do nothing
            }
            else if (openPos == -1)
            {
                walkableTiles[i].scoreH = manhattanDistance(&walkableTiles[i], &end);
                walkableTiles[i].scoreG = s->scoreG + 1;
                walkableTiles[i].scoreF = walkableTiles[i].scoreH + walkableTiles[i].scoreG;
                walkableTiles[i].parent = s;
                l_insertLast(&open, walkableTiles[i]);

                grid[walkableTiles[i].x][walkableTiles[i].y] = tile_open; //OPEN TILE
            }
            else if (openPos > -1)
            {
                // TODO: test if using the current G score makes the walkableTiles[i].scoreF score lower, if yes update the parent because it means its a better path
            }
        }

        /* CHECK IF END IS REACHED */

        if (manhattanDistance(s, &end) == 0)
        {
            drawFinalPath(grid, width, height, s, &start, &end);
            found = 1;
        }
    }

    /* DEBUG DRAW */

    if (argc == 2)
    {
        if (strcmp(argv[1], "-d\n"))
        {
            printf("\nDebug:\n");
            draw(grid, width, height);
        }
    }

    if (!found)
    {
        printf("No path found!");
    }

    printf("\n");
    system("pause");

    return 0;
}

void draw(int grid[128][128], int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (grid[j][i] == tile_empty)
                printf("  ");
            else
                printf("%d ", grid[j][i]);
        }
        printf("\n");
    }
}

void drawFinalPath(int grid[128][128], int width, int height, POINT *lastPoint, POINT *start, POINT *end)
{
    LIST path = (LIST){.len = 0};

    POINT *p = lastPoint;

    while (p != NULL)
    {
        l_insertLast(&path, *p);
        p = p->parent;
    }

    printf("\nSteps: %d\n", path.len - 1);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (grid[j][i] == tile_empty)
                printf("  ");
            else if (grid[j][i] == tile_wall)
                printf("%d ", grid[j][i]);
            else if (l_getNodePos(&path, createNode((POINT){.x = j, .y = i})) > -1)
            {
                if (start->x == j && start->y == i)
                    printf("%d ", tile_start);
                else if (end->x == j && end->y == i)
                    printf("%d ", tile_end);
                else
                    printf("%d ", grid[j][i]);
            }
            else
                printf("  ");
        }
        printf("\n");
    }
}

int manhattanDistance(POINT *p1, POINT *p2)
{
    return (int)(fabs(p1->x - p2->x) + fabs(p1->y - p2->y));
}

POINT *lowestFScore(LIST *list)
{

    POINT *p = NULL;

    for (int i = 0; i < list->len; i++)
    {
        if (i == 0)
        {
            p = &list->start->data;
            continue;
        }
        else
        {
            if (l_getNodeAt(list, i)->data.scoreF <= p->scoreF)
            {
                p = &l_getNodeAt(list, i)->data;
            }
        }
    }

    return p;
}