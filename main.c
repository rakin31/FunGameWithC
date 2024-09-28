#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <MMSystem.h>
#include <string.h>

#define MAP_WIDTH 9
#define MAP_HEIGHT 8
#define PLAYER_POSITION pos_y * MAP_WIDTH + pos_x

char map[] = {

    "########\n"
    "#      #\n"
    "# @    #\n"
    "#x     #\n"
    "#      #\n"
    "#      #\n"
    "#B     #\n"
    "#      #\n"
    "########\n"

};

int dest_square;
int pos_x;
int pos_y;
int win = 0;

void GetDestSquares()
{
    int count, cell;

    for(int row = 0; row < MAP_HEIGHT; row++)
    {
        for(int col = 0; col < MAP_WIDTH; col++)
        {
            cell = row * MAP_WIDTH + col;

            if(map[cell] == 'x')
            {
                //printf("row: %d col: %d\n",row,col);
                dest_square = cell;
            }
        }
    }
}

void GetPosition()
{
    int cell;

    for(int row = 0; row < MAP_HEIGHT; row++)
    {
        for(int col = 0; col < MAP_WIDTH; col++)
        {
            cell = row * MAP_WIDTH + col;

            if(map[cell] == '@')
            {
                //printf("Cell: %d\n",cell);
                pos_x = col;
                pos_y = row;
            }
        }
    }
}

void MoveCharacter(int offset)
{
    if((map[PLAYER_POSITION + offset] != '#') &&
       !((map[PLAYER_POSITION + offset] == 'B') &&
        (map[PLAYER_POSITION + offset * 2] == '#')))
    {
        if(((map[PLAYER_POSITION + offset] == 'B') ||                   // if player hits the box
            (map[PLAYER_POSITION + offset] == 'O')) &&                  // or the box on 'x' cell
            (map[PLAYER_POSITION + offset * 2] != '#' ||                // and box doesn't hit a wall
             map[PLAYER_POSITION + offset * 2] != 'B' ||                // or another box
             map[PLAYER_POSITION + offset * 2] != 'O'))                 // or box on 'x' cell
        {
            map[PLAYER_POSITION] = ' ';                                 // clear previous player's position
            pos_x += offset;                                            // update player's coordinate

            if(map[PLAYER_POSITION + offset] == ' ')                    // if the square next to the box is empty
                map[PLAYER_POSITION + offset] = 'B';                    // push the box

            else if(map[PLAYER_POSITION + offset] == 'x')
            {                                                           // if the square next to the box is 'x'
                map[PLAYER_POSITION + offset] = 'O';
                win = 1;
            }                                                           // mark the box is on it's place

            else
            {
                map[PLAYER_POSITION - offset] = '@';                    // if box hits the wall or another box
                return;                                                 // don't push it any further
            }

            map[PLAYER_POSITION] = '@';                                 // draw the player in the new position
        }

        else                                                            // if the square next to the player is empty
        {
            map[PLAYER_POSITION] = ' ';                                 // clear previous player position
            pos_x += offset;                                            // update player's coordinate
            map[PLAYER_POSITION] = '@';                                 // draw the player in the new position
        }
    }
}

DWORD WINAPI PlayMusic(LPVOID lpParam) {
    PlaySound("Luke-Bergs-Paradise-chosic.com_.wav", NULL, SND_FILENAME | SND_ASYNC);
    return 0;
}

int main()
{
    //PlaySound("Luke-Bergs-Paradise-chosic.com_.wav",NULL,SND_SYNC);
    HANDLE hThread = CreateThread(NULL, 0, PlayMusic, NULL, 0, NULL);
    if (hThread == NULL) {
        // Failed to create thread, handle error
        return 1;
    }
    printf("\033[1;32m");
    printf("%s\n",map);
    GetDestSquares();
    GetPosition();
    //printf("Dest square: %d\n",dest_square);
    //printf("pos_x: %d pos_y: %d\n",pos_x,pos_y);
    char key;

    while(key != 'q')                                                    // game loop
    {
                                                                    // get player's coordinates
        if(win == 1)
        {
            printf("You win!\n");
            break;
        }

        printf("\033[1;34m");
        printf("Move up key: w\nMove down key: s\nMove left key: a\nMove right key: d\n\n");
        printf("\033[1;33m");
        printf("Enter your move: ");
        scanf(" %c",&key);                                         // get user input
        printf("\n");
        printf("\033[0m");
        printf("\033[1;26m");

        switch(key)
        {


            // move character up
            case 'w':
                MoveCharacter(- MAP_WIDTH);
                printf("After moving the player up: \n\n");
                break;

            // move character down
            case 's':
                MoveCharacter(MAP_WIDTH);
                printf("After moving the player down: \n\n");
                break;

            // move character left
            case 'a':
                MoveCharacter(-1);
                printf("After moving the player left: \n\n");
                break;

            // move character right
            case 'd':
                MoveCharacter(1);
                printf("After moving the player right: \n\n");
                break;

        }

        if(map[dest_square] == ' ')                             // if 'x' cell has been erased
                map[dest_square] = 'x';

        printf("\033[1;32m");
        printf("%s\n", map);
    }
    //printf("Hello world!\n");
    return 0;
}
