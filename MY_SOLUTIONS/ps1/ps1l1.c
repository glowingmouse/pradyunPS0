#include <stdio.h>
#include <string.h>

void printgrid(int rows, int columns, char gridk[rows + 2][columns + 2]);
void generation(int rows, int columns, char gridk[rows + 2][columns + 2]);
int population(int rows, int columns, char gridr[rows + 2][columns + 2]);

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
    char inpgrid[R][C + 1]; //grid of input and last column in 2d array is all \0's
//------------------------------------------------------------------------------------------------------------------------
    for (int i = 0; i < R; i++)
    {
        scanf("%s", inpgrid[i]);
    }
//------------------------------------------------------------------------------------------------------------------------
    char grid[R + 2][C + 2]; //{(C+2),(C+2),(C+2),..R+2}
    for (int i = 0; i < C + 2; i++)
    {
        grid[0][i] = 'n';
        grid[R + 1][i] = 'n';
    }
    for (int i = 1; i < R + 1; i++)
    {
        grid[i][0] = 'n';
        grid[i][C + 1] = 'n';
    }

    for(int i = 1; i < R + 1; i++)
    {
        for(int k = 1; k < C + 1; k++)
        {
            grid[i][k] = inpgrid[i - 1][k - 1];
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
    printf("INITIAL POPULATION: %i\n", initialpop);
    printf("PEAK POPULATION: %i\n", maxpop);
    printf("FINAL POPULATION: %i\n", population(R, C, grid));
    printf("FINAL GRID:\n");
    printgrid(R, C, grid);
}

void printgrid(int rows, int columns, char gridk[rows + 2][columns + 2]) //prints the grid
{
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns; k++)
        {
            printf("%c", gridk[i + 1][k + 1]);
        }
        printf("\n");
    }
}

void generation(int rows, int columns, char gridk[rows + 2][columns + 2]) //updates by one generation
{
    int counts[rows][columns];
    int tempcount = 0;
    char workgrid[rows + 2][columns + 2];
    memcpy(workgrid, gridk, sizeof(workgrid)); //duplicate grid of intitial state

    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < columns + 1; j++)
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
                    if (workgrid[i + a1][j + a2] == '#')
                    {
                        tempcount++;
                    }
                }
            }
            counts[i - 1][j - 1] = tempcount;
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

int population(int rows, int columns, char gridr[rows + 2][columns + 2])
{
    int num = 0;
    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < columns + 1; j++)
        {
            if (gridr[i][j] == '#')
            {
                num++;
            }
        }
    }
    return num;
}