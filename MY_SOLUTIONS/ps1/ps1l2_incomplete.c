#include <stdio.h>
#include <string.h>
#include <math.h>

void printgrid(int rows, int columns, char gridk[rows][columns]);
void generation(int rows, int columns, char gridk[rows][columns]);
int population(int rows, int columns, char gridr[rows][columns]);
void COM(int rows, int columns, char gridr[rows][columns], float *xcord, float *ycord, int pop, int *minx, int *miny, int *maxx, int *maxy);

int main(void)
{
    int R; 
    printf("ROWS: ");
    scanf("%i", &R);
    int C;
    printf("COLUMNS: ");
    scanf("%i", &C);
    int G;
    printf("GENERATIONS: ");
    scanf("%i", &G);
//------------------------------------------------------------------------------------------------------------------------    
    char inpgrid[R][C + 1]; //grid of input and last column in 2d array is all \0's
    for (int i = 0; i < R; i++)
    {
        scanf("%s", inpgrid[i]);
    }
//------------------------------------------------------------------------------------------------------------------------
    char grid[R][C]; //making the intial grid

    for(int i = 0; i < R; i++)
    {
        for(int k = 0; k < C; k++)
        {
            grid[i][k] = inpgrid[i][k];
        }
    }
//------------------------------------------------------------------------------------------------------------------------
    int initialpop = population(R, C, grid);
    int maxpop = population(R, C, grid);
    for (int l = 0; l < G; l++)
    {
        generation(R, C, grid);
        int p = population(R, C, grid);
        if (p > maxpop)
        {
            maxpop = p;
        }
    }
//------------------------------------------------------------------------------------------------------------------------
    float xcor; //xcor is actually the row and ycor is actually the column
    float ycor;
    int minX; int minY; int maxX; int maxY;
    COM(R, C, grid, &xcor, &ycor, maxpop, &minX, &minY, &maxX, &maxY); //set the coordinates of centre of mass
//------------------------------------------------------------------------------------------------------------------------
    printf("BOUNDING BOX: %i x %i (Rows %i - %i, Cols %i - %i)\n", maxX - minX + 1, maxY - minY + 1, minX, maxX, minY, maxY);
    printf("CO-ORDINATES: (%.2f, %.2f)\n", xcor, ycor);
    printf("INITIAL POPULATION: %i\n", initialpop);
    printf("PEAK POPULATION: %i\n", maxpop);
    printf("FINAL POPULATION: %i\n", population(R, C, grid));
    printf("FINAL GRID:\n");
    printgrid(R, C, grid);
}

void printgrid(int rows, int columns, char gridk[rows][columns]) //prints the grid
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns; k++)
        {
            printf("%c", gridk[i][k]);
        }
        printf("\n");
    }
}

void generation(int rows, int columns, char gridk[rows][columns]) //updates by one generation
{
    int counts[rows][columns];
    int tempcount = 0;
    char workgrid[rows][columns];
    memcpy(workgrid, gridk, sizeof(workgrid)); //duplicate grid of intitial state

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            tempcount = 0;
            for (int a1 = -1; a1 < 2; a1++)
            {
                for (int a2 = -1; a2 < 2; a2++)
                {
                    if (a1 == 0 && a2 == 0)
                    {
                        continue;
                    }
                    if (workgrid[(i + a1 + rows) % rows][(j + a2 + columns) % columns] == '#')
                    {
                        tempcount++;
                    }
                }
            }
            counts[i][j] = tempcount;
            if (gridk[i][j] == '#') //if alive cell
            {
                switch(tempcount)
                {
                    case 0 ... 1:
                        gridk[i][j] = '.';
                        break;
                    case 2 ... 3:
                        break;
                    case 4 ... 8:
                        gridk[i][j] = '.';
                        break;
                    default:
                        break;
                }
            }
            else //if dead cell
            {
                if (tempcount == 3)
                {
                    gridk[i][j] = '#';
                }
            }
            
        }
    }
}

int population(int rows, int columns, char gridr[rows][columns])
{
    int num = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (gridr[i][j] == '#')
            {
                num++;
            }
        }
    }
    return num;
}

void COM(int rows, int columns, char gridr[rows][columns], float *xcord, float *ycord, int pop, int *minx, int *miny, int *maxx, int *maxy)
{
    *xcord = 0;
    *ycord = 0;
    *minx = 0;
    *miny = 0;
    *maxx = 0;
    *maxy = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (gridr[i][j] == '#')
            {
                *xcord += i;
                *ycord += j;
                if (i > *maxx)
                {
                    *maxx = i;
                }
                else if (i < *minx)
                {
                    *minx = i;
                }
                if (j > *maxy)
                {
                    *maxy = j;
                }
                else if (j < *miny)
                {
                    *miny = j;
                }
            }
        }
    }
    *xcord = round((*xcord / pop) * 100) / 100.0;
    *ycord = round((*ycord / pop) * 100) / 100.0;
}
