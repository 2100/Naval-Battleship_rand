#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SHIPS 6

typedef struct une_case{
    int x;
    int y;
}Case;

typedef struct ship{
    int size;
    int dir;
    int life;
    Case start;
}Ship;

char** grid1;
char** grid2;
Ship randships[SHIPS];

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while( clock() < endwait );
}

void intialiseboard(char** grid, int size) {
    int i,j;
    for(i=0;i<size;i++){
        for(j=0;j<size;j++)
            grid[i][j]='.';
    }
}

char** createBoard(char** grid, int size)
{
    int i;
    grid=(char**)malloc(size*sizeof(char *));
    for(i=0;i<size;i++)
    {
        grid[i]=malloc(size*sizeof(char));
    }
    intialiseboard(grid,size);
    return grid;//new grid that create board has created
}

void showBoard(char** grid, int size) //grid here is that created by createboard
{
    int i, j;
    printf("\n");
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
            printf("%c\t",grid[i][j]);
        printf("\n");
    }
}

int randNumberGen(int min, int max)
{
    return (min + rand()%(max-min+1));
}

void randomizeShips(int size)
{
    int i = 0, j, s, d, x, y, k = 0, flag = 0;
    srand(time(NULL));
    while(k<6){// k<6 this a condition to random size ships as long as  it is <6
        s = randNumberGen(2,6);
        x = randNumberGen(0,size-1);
        y = randNumberGen(0,size-1);
       if((x+s<8) || (y+s<8))//8 is a board size .as long as the coords are in 8x8 do if
       {
            if ((x+s<size-1) && (y+s>size-1))//here we command the progr to take dir 2
            {
                d = 2;
                for(j=x;j<x+s;j++)
                {
                    if(grid1[y][j]=='.')
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }
            else if ((y+s<size-1) && (x+s>size-1))
            {
                d = 3; //here the same we command it to take dir 3
                for(i=y;i<y+s;i++)
                {
                    if(grid1[i][x]=='.')
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }
            else
            {
                d=randNumberGen(2,3);//  here we command it to choose between dir 2 or 3 randomly
                switch(d)
                {
                    case 2:
                        for(j=x;j<x+s;j++)
                        {
                            if(grid1[y][j]=='.')// when j increase y main const
                            {
                                flag = 1;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                        break;

                    case 3:
                        for(i=y;i<y+s;i++)
                        {
                            if(grid1[i][x]=='.')//when i increase as we move vertically ,x remain const.
                            {
                                flag = 1;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                        break;
                    default:
                        flag=0;// we ask the program to quit the condion if the dir isn t 2 or 3 an begin after new dir 0 or 1
                }

            }
       }


       else if ((x-s+1>=0) || (y-s+1>=0))
       {
            if ((x-s+1>=0) && (y-s+1<0))
            {
                d=0;
                for(j=x;j>x-s;j--)//counter decrease as we go backward horizontally
                {
                    if(grid1[y][j]=='.')
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }
            else if ((y-s+1>=0) && (x-s+1<0))
            {
                d=1;
                for(i=y;i>y-s;i--)// counter i decrease as we go upward vertically
                {
                    if(grid1[i][x]=='.')
                    {
                        flag = 1;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
            }
            else
            {
                d=randNumberGen(0,1);
                switch(d)
                {
                    case 0:
                        for(j=x;j>x-s;j--)
                        {
                            if(grid1[y][j]=='.')
                            {
                                flag = 1;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                        break;
                    case 1:
                        for(i=y;i>y-s;i--)
                        {
                            if(grid1[i][x]=='.')
                            {
                                flag = 1;
                            }
                            else
                            {
                                flag = 0;
                                break;
                            }
                        }
                        break;
                    default:
                        flag=0;
                }
            }
        }
        else
            continue;

        if(flag == 0)
        {
            continue;
        }
        else if(flag == 1)
        {
            switch(d)
            {
                case 0:
                    for(j=x;j>x-s;j--)
                    {
                        grid1[y][j] = k + 48;
                    }
                    break;
                case 1:
                    for(i=y;i>y-s;i--)
                    {
                        grid1[i][x] = k + 48;
                    }
                    break;
                case 2:
                    for(j=x;j<x+s;j++)
                    {
                        grid1[y][j] = k + 48;
                    }
                    break;
                case 3:
                    for(i=y;i<y+s;i++)
                    {
                        grid1[i][x] = k + 48;
                    }
                    break;
            }
            randships[k].dir = d;
            randships[k].size = s;
            randships[k].start.x = x;
            randships[k].start.y = y;
            k++;
        }
    }
}

int check(int x, int y, int size)
{
    int i,j, shipCount = 0, ship;
    if(grid2[y][x] == '.')
    {
        if(grid1[y][x]=='.')
        {
            grid1[y][x] = 'o';
            grid2[y][x] = 'o';
            return 0;
        }
        else if (grid1[y][x]>=48 || grid1[y][x]<=54)
        {
            ship = grid1[y][x];
            grid1[y][x] = 'x';
            grid2[y][x] = 'x';
            for(i=0;i<size;i++)
                for(j=0;j<size;j++)
                    if(grid1[i][j] == ship)
                        shipCount++;
            if(shipCount == 0)
            {
                return 2;
            }
            else{
                return 1;
            }
        }
    }
    else{
        return -1;
    }
}

int loadFromFile (char** board, char*filename)
{
    int i, j, size;
    char *str = (char*) malloc(100*sizeof(char));
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL)
    {
        return -1;
    }
    else{
        if(fgets(str,10,fp)==NULL)
        {
            return -1;
        }
        else{
            size=atoi(str); /* bet7awel str lei integer*/
        }
        board = createBoard(board,size);
        for(i=0;i<size;i++){
            for(j=0;j<size;j++)//board[i][j]='.';
                if(fscanf(fp,"%c\t",&board[i][j])==EOF)
                {
                    return -1;
                    break;
                }
                for(i=0;i<size;i++){
            for(j=0;j<size;j++)//board[i][j]='.';
                if(fscanf(fp,"%c\t",&board2[i][j])==EOF)
                {
                    return -1;
                    break;
                }
        }
        fclose(fp);
    }
    return size;
}

void saveToFile(char* filename, char** board1, char** board2, int size)
{
    int i,j;
    FILE *fp;
    fp=fopen(filename,"w");
    if(fp==NULL)
    {
        printf("\nError: Can't open file");
    }
    else
    {
        fprintf(fp,"%d\n",size);
        for(i=0;i<size;i++)
        {
            for(j=0;i<size;j++)
            {
                fprintf(fp,"%c\t",board1[i][j]); /* el \t beta3ml tab */
            }
            fprintf(fp,"\n");
        }
        for(i=0;i<size;i++)
        {
            for(j=0;i<size;j++)
            {
                fprintf(fp,"%c\t",board2[i][j]); /* el \t beta3ml tab */
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
    }
}

int main()
{
    int x, y, status, res,roundCount = 0, score = 0,size;
    time_t start, end;
    double elapsed = 0;

    system("color 0B");

    printf("\n\n\t    ~naval battle~\n\n\t\t#\n\t\t#|\n\t\t#|#\n\t\t#|##\n\t\t#|###\n\t\t#|####");
    printf("\n\t\t#|#####\n\t\t#|######\n\t#########################\n\t _______________________");
    printf("\n\t  ####/)###############\n\t   ###(/##############\n\t    #################\n\t     ###############");
    printf("\n\n\n\t1- play\n\n\t2- load\n\n\n\n\t3- exit\n\n\n\t choose:");
    scanf("%d", &res);
    system("cls");
    switch(res)
    {

       case 1:
       {
           printf("\n\n\t    ~naval battle~\n\n\t\t#\n\t\t#|\n\t\t#|#\n\t\t#|##\n\t\t#|###\n\t\t#|####");
    printf("\n\t\t#|#####\n\t\t#|######\n\t#########################\n\t _______________________");
    printf("\n\t  ####/)###############\n\t   ###(/##############\n\t    #################\n\t     ###############");
    printf("\n\n\n\t1- easy\n\n\t2- normal\n\n\n\n\t3- hard\n\n\n\t choose:");
    scanf("%d", &res);
    system("cls");
switch(res)
{
    case 1:

      size=7;
      break;
    case 2:

      size=9;
      break;
    case 3:



      size = 11;
      break;

}
        grid1=createBoard(grid1,size);
        grid2=createBoard(grid2,size);
        randomizeShips(size);
        showBoard(grid2,size);
           printf("\n\n\n\t\t ready?\n\n");
           wait(1);
           printf("\n\t\t now!!!");
           wait(1);

           do
           {
               time(&start);
               system("cls");
        showBoard(grid2,size);
        xyerror:printf("Enter a coordinates to attack:(or -1 to save and exit)\nX:");
        scanf("%d",&x);
        if(x==-1)
        {
            saveToFile("lastgame",grid2,size);
            goto endl;
        }
        printf("\nY:");
        scanf("%d",&y);
        if(x>=size || y>=size)
        {
            printf("\nError: Out of boundary!\n");
            goto xyerror;
        }
        status = check(x,y,size);
        switch (status)
        {
            case -1:
                printf("Already played!\n");
                break;

            case 0:
                printf("Missed!\n");
                break;

            case 1:
                printf("Hit!\n");
                score+=1;
                break ;

            case 2:
                printf("One ship is destroyed!\n");
                score+=2;
                break;
        }
        roundCount++;
        time(&end);
        elapsed += difftime(end, start);
        printf("\nTime Elapsed: %lf sec", elapsed);
        wait(1);
    }while(elapsed < 120);
    printf("\nGame Over! Your score: %d", score);
    break;
    }
        case 2:
        //load
        //if load function output == -1 then there's an error "NO FILE LOADED!"
        break;
        case 3:
        return 0;

    }
    endl:
    return 0;
}
