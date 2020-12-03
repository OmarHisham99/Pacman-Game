#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML/Audio.hpp"
#include <string>
#include <conio.h> //for getch() function
#include <stdio.h> //special for printf() function
#include <stdlib.h>
#include <cstdlib> //for rand () function
#include <ctime>
#include <windows.h>
#include <queue>
#include <sstream> //for read numbers
#include <math.h>


#define ROW 22
#define COL 42
using namespace std;
using namespace sf;

///////////Declare Your Global Variables Here.
bool gameOver, winn;
int pacX, pacY, pacXX, pacYY, prevpacX, prevpacY, ghostX, ghostY, ghost1X, ghost1Y, ghost2X, ghost2Y, ghost3X, ghost3Y, Score = 0;
int random;
bool  level2 = false, level3 = false;
unsigned int lives = 5;
int score = 0;
char key, character;

string s(int n);
///BFS Variables
queue <int> Rqueue, Cqueue;
bool visitedArray[22][42],visitedArray2[22][42], visitedArray3[22][42], visitedArray4[22][42], reached_end = false;
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };
char dir[4] = { 'u', 'd', 'r', 'l' };
int r, c, rr, cc, xr, xc;
bool moved = false;
string pppath;

 //level 1

string tailmap[22]={
"________________________________________",
"|                                      |",     //118 '.'
"| .# .########## .#### .########## .# .|",//6
"| .# .   ####    .#### .   ####    .# .|",//6
"| .#### .### .## .#### .##  ### .#### .|",//7
"| .     .    .## .#### .## .    .     .|",//8
"|### .###### .## .     .## .###### .###|",//6
"|##  .###### .##### .##### .###### . ##|",//5
"|   ..       .             .       ..  |",//6
"|# .##### .## .##&&&&&&## .## .##### .#|",//6
"|##    ## .## .#        # .## .##    ##|",//4
"|#### .## .## .########## .## .## .####|",//6
"|#### .## .   .           .   .## .####|",//6
"|###  .## .## .########## .## .## . ###|",//6
"|     .   .## .   ####    .## .   .    |",//6     //level 1
"|##### .######## .#### .######## .#####|",//4
"|      .         .     .         .     |",//4
"| .##### .## ..########## ..## .##### .|",//8
"| .##    .## ..   ####    ..## .   ## .|",//8
"| .## .##### .## .#### .## .##### .## .|",//8
"| .   .      .## .     .## .      .   .|",//8
"________________________________________"
};

/*

//level 2
string tailmap2[22]= {    //level 2
"________________________________________",
"|        ##                  ##        |",     //156 '.'
"| .#### .## .................## .#### .|",//21
"|#   ## .## .############## .## .##   #|",//4
"|##   # .   .               .   .#   ##|",//4
"|   ..  .## .................## .  ..  |",//23
"|##  .# .## ....######## ....## .#  .##|",//12
"|#  .## .##### . ######  .##### .##   #|",//5
"|   ### .      ..       ..      .###   |",//6
"| .#### .## ..###&&&&&&### ..## .#### .|",//8
"| .     .## ..##        ## ..## .     .|",//8
"|## .###### ..############ ..###### .##|",//6
"|## .       ..             ..       .##|",//6
"|## ..## .###### .#### .###### .## ..##|",//8
"|   ..## .##     .#### .    ## .## ..  |",//8
"| .##### .## .############ .## .##### .|",//6
"| .      .## .             .## .      .|",//6
"|### .## .## .############ .## .## .###|",//6
"|    .## .  ..###      ### .   .## .   |",//7
"| .######### .### .## .### .######### .|",//6
"| .          .    .## .    .          .|",//6
"________________________________________"

};*/


//level 3
/*string tailmap3[22]=
{

"________________________________________",
"|         #                  #         |",    //106 '.'
"| .##### .# .############## .# .##### .|",//6
"| .      .  .     ####      .  .      .|",//6
"| .######### .## .#### .## .######### .|",//6
"| .    ###   .## .#### .## .  ###     .|",//6
"|#### .##  # .## .     .## .#  ## .####|",//6
"|  ## .#  ## .############ .##  # .##  |",//4
"| .## .  ### .             .###   .## .|",//6
"|#### .##### .###&&&&&&### .##### .####|",//4
"|     .  ### .#          # .###   .    |",//4
"| .#####  ## .#          # .##  ##### .|",//4
"| .    # . # .############ .#  .#     .|",//6
"|# ## .# ..  .             .  ..# .## #|",//8
"|# ## .# ..# .############ .# ..# .## #|",//8
"|#    .  .###     ####     ### .  .   #|",//4
"|  ## .######### .#### .######### .##  |",//4
"| .   .   ###    .     .   ###    .   .|",//6
"|## .## .. #   ##########   #  ..## .##|",//6
"|   .   .#   #  #      #  #   # .   .  |",//4
"|###### .  ..  .  ####   .  ..  .######|",//8
"________________________________________"


};*/
void standards()
{
    gameOver = false;
    winn = false;
    pacX = 19;
    pacY = 20;
    pacXX = 18;
    pacYY = 20;
    prevpacX = -1;
    prevpacY = -1;
    Score = 0;
    ghostX = 11;
    ghostY = 17;
    ghost1X = 11;
    ghost1Y = 19;
    ghost2X = 11;
    ghost2Y = 21;
    ghost3X = 11;
    ghost3Y = 23;
    //lives = 3;
}
struct structForThePath
{
    string path;
    string path2;
    string path3;
    string path4;
} nodePath[22][42];


bool  explore_neighbours(int ro, int co, int rTarget, int cTarget, string grid[50], int ghost_num, bool visitedArrayy[22][42])
{
    for (int i = 0; i < 4; i++)
    {
        rr = ro + dr[i];
        cc = co + dc[i];
        /*if (ghost_num == 2)
        {
        if (visitedArrayy[rr][cc] == true)
            continue;
        else if (grid[rr][cc] == '#' && rr!=rTarget && cc!=cTarget)
            continue;
        }*/
      // else
        //{

        if ((rr < 0 || cc < 0) )
            continue;
       // else if (grid[rr][cc] == '#' && rr != 0 && rr != 21 && cc != 0 && cc != 41 && rr != rTarget && cc != cTarget && ghost_num ==2)
         //   continue;
        else if ((rr >= 22 || cc >= 42) )
            continue;
        else if (visitedArrayy[rr][cc] == true)
            continue;
        else if (grid[rr][cc] == '#' || grid[rr][cc] == '|' || grid[rr][cc] == '_')
            continue;
        //}


        Rqueue.push(rr);
        Cqueue.push(cc);
        visitedArrayy[rr][cc] = true;

       if (ghost_num == 1)
            nodePath[rr][cc].path = nodePath[ro][co].path + dir[i];
        else if (ghost_num == 2)
            nodePath[rr][cc].path2 = nodePath[ro][co].path2 + dir[i];
        else if (ghost_num == 2)
            nodePath[rr][cc].path3 = nodePath[ro][co].path3 + dir[i];
        else if (ghost_num == 4)
            nodePath[rr][cc].path4 = nodePath[ro][co].path4 + dir[i];

        if (rr == rTarget && cc == cTarget)
        {
            xr = rr;
            xc = cc;
            return true;
        }
    }
    return false;
}

int solve(int srr, int scc, int rTarget, int cTarget, string grid[50], int ghost_num, bool visitedArrayyy[22][42])
{
    reached_end = false;
     for (int i=0; i<22; i++)
     {
    	 for (int j=0; j<42; j++)
    	 {
                visitedArrayyy[i][j]=false;
                if (ghost_num == 1)
                    nodePath[i][j].path.clear();
                else if (ghost_num == 2)
                    nodePath[i][j].path2.clear();
                else if (ghost_num == 3)
                    nodePath[i][j].path3.clear();
                else if (ghost_num == 4)
                    nodePath[i][j].path4.clear();
    	 }
     }

    Rqueue.push(srr);
    Cqueue.push(scc);
    visitedArrayyy[srr][scc] = true;

    while (Rqueue.size() > 0)
    {
        r = Rqueue.front();
        c = Cqueue.front();
        Rqueue.pop();
        Cqueue.pop();

        if (r == rTarget && c == cTarget)
        {
            reached_end = true;
            xr = r;
            xc = c;

            break;
        }

        bool found = explore_neighbours(r, c, rTarget, cTarget, grid, ghost_num,  visitedArrayyy);

        if (found)
        {
            reached_end = true;
            break;
        }
    }

    if (reached_end)
        return 0;

   return -1;

}


/////////////////////////////////////////////////////////////////////////////
int main()
{

    int c = 0, clickx, clicky;
    bool loser = false;


    sf::RenderWindow window(sf::VideoMode(1250, 800), "PACMAN");
    window.setKeyRepeatEnabled(false);

    sf::Music music;
    if (!music.openFromFile("[Trap] - Aero Chord - Surface [Monstercat Release] (mp3cut.net)-2.ogg"))
    {
        std::cout << "Error loading music file " << std::endl;
    }

    music.play();
    sf::Texture texture;
    sf::Sprite pacmanimage;
    if (!texture.loadFromFile("Menuu.jpg"))
    {
        std::cout << "Error on loading pacman's photo" << std::endl;
    }
    pacmanimage.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                std::cout << "Mouse button has been pressed" << std::endl;
                Vector2i mousepos = Mouse::getPosition(window);
                //std::cout << (float)mousepos.x << ' ' << (float)mousepos.y << std::endl;
                clickx = (float)mousepos.x;
                clicky = (float)mousepos.y;
                if (clickx >= 47 && clickx <= 380 && clicky >= 75 && clicky <= 230)
                {
                    std::cout << "Play button has been pressed" << std::endl;

                    //*****************************************Level(1)**********************************************:
                    mainn:
                    standards();

                    RenderWindow window(VideoMode(50*15, 40*15), "PACMAN");;
                    window.setVerticalSyncEnabled(true); //game will run at the same frequency as the monitor's refresh rate

                    //drawing the maze
                    CircleShape dot; //dots
                    dot.setRadius(2.5);
                    dot.setFillColor(Color::White);

                    Texture b;   ///walls
                    b.loadFromFile("blue.jpg");
                    Sprite ball(b);
                    ball.setTextureRect(IntRect(0, 0, 15, 15));



                    /// drawing pacmann
                    Texture PacManTex;
                    PacManTex.loadFromFile("pacmansheet.png");
                    Sprite PacMan(PacManTex);
                    PacMan.setTextureRect(IntRect(16, 0, 15, 15));

                    /// drawing ghost1
                    Sprite Ghost1;
                    Texture ghost1Tex;
                    ghost1Tex.loadFromFile("pacmansheet.png", sf::IntRect(0, 64, 18, 15));
                    Ghost1.setTexture(ghost1Tex);
                    Ghost1.setScale(sf::Vector2f(0.8, 0.8));
                    /// drawing ghost2
                    Sprite Ghost2;
                    Texture ghost2Tex;
                    ghost2Tex.loadFromFile("pacmansheet.png", sf::IntRect(0, 80, 18, 15));
                    Ghost2.setTexture(ghost2Tex);

                    /// drawing ghost3
                    Sprite Ghost3;
                    Texture ghost3Tex;
                    ghost3Tex.loadFromFile("pacmansheet.png", sf::IntRect(0, 96, 18, 15));
                    Ghost3.setTexture(ghost3Tex);

                    /// drawing ghost4
                    Sprite Ghost4;
                    Texture ghost4Tex;
                    ghost4Tex.loadFromFile("pacmansheet.png", sf::IntRect(0, 112, 18, 15));
                    Ghost4.setTexture(ghost4Tex);

                    ///their positions
                    Ghost1.setPosition(sf::Vector2f(ghostY * 15, ghostX * 15));
                    Ghost2.setPosition(sf::Vector2f(ghost1Y * 15, ghost1X * 15));
                    Ghost3.setPosition(sf::Vector2f(ghost2Y * 15, ghost2X * 15));
                    Ghost4.setPosition(sf::Vector2f(ghost3Y * 15, ghost3X * 15));
                    PacMan.setPosition(Vector2f((pacY * 15), (pacX * 15)));

                    //for font
                    Font font;
                    font.loadFromFile("Bullpen3D.ttf");


                    //display score
                    Text Score;
                    Score.setFont(font);
                    Score.setString("SCORE : ");
                    Score.setCharacterSize(20);
                    Score.setPosition(15 * 7, 15 * 28);


                    //display lives
                    Text Lives;
                    Lives.setFont(font);
                    Lives.setString("LIVES : ");
                    Lives.setCharacterSize(21);
                    Lives.setPosition(15 * 7, 15 * 33);


                    //for winning
                    Text congrats;
                    congrats.setFont(font);
                    congrats.setString(" CONGRATS ! YOU WON ");
                    congrats.setCharacterSize(40);
                    congrats.setPosition(15 * 17, 15 * 30);

                    // END GAME
                    Text Gmover;
                    Gmover.setFont(font);
                    Gmover.setString(" OOPS ! GAME OVER ");
                    Gmover.setCharacterSize(40);
                    Gmover.setPosition(15 * 17, 15 * 30);

                    ///BFS
                    int i = 0, j = 0, k=0, r=0;
                    int targetX,targetY, target2X, target2Y;

                    ///GHOSTS ALGORITHM CALL
                    solve(ghostX, ghostY, pacY, pacX, tailmap, 1, visitedArray );
                    solve(ghost1X, ghost1Y, pacY, pacX, tailmap, 2, visitedArray2);
                    solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);
                    cout << nodePath[pacX][pacY].path2 <<endl;

                    prevpacX = pacX;
                    prevpacY = pacY;


                    while (window.isOpen())
                    {
                        Event event;

                        //calc score
                        Text points;
                        points.setFont(font);
                        points.setString(s(score));
                        points.setCharacterSize(20);
                        points.setPosition(15 * 14, 15 * 28);

                        Sleep(50);

                        //calc lives
                        Text l;
                        l.setFont(font);
                        l.setString(s(lives));
                        l.setCharacterSize(20);
                        l.setPosition(15 * 14, 15 * 33);



                        while (window.pollEvent(event))
                        {
                            if (event.type == Event::Closed)
                                window.close();

                            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                                window.close();
                            if (Keyboard::isKeyPressed(Keyboard::Left) && tailmap[pacX][pacY - 1] != '#'
                                && tailmap[pacX][pacY - 1] != '|' && tailmap[pacX][pacY - 1] != '_'
                                && tailmap[pacX][pacY - 1] != '&')
                            {

                                prevpacX = pacX;
                                prevpacY = pacY;
                                moved = true;
                                pacY--;
                                PacMan.move(-15, 0);
                                PacMan.setTextureRect(IntRect(17, 16, 15, 15));
                                i = 0; j=0; k=0; r=0;

                                solve(ghostX, ghostY, pacY, pacX, tailmap, 1, visitedArray);
                                solve(ghost1X, ghost1Y, pacY, pacX, tailmap, 2, visitedArray2);
                                solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);

                                cout << nodePath[pacX][pacY].path2 <<endl;

                            }
                            else if (Keyboard::isKeyPressed(Keyboard::Right) && tailmap[pacX][pacY + 1] != '#'
                                     && tailmap[pacX][pacY + 1] != '|' && tailmap[pacX][pacY + 1] != '_'
                                     && tailmap[pacX][pacY + 1] != '&')
                            {

                                prevpacX = pacX;
                                prevpacY = pacY;
                                moved = true;
                                pacY++;
                                PacMan.move(15, 0);
                                PacMan.setTextureRect(IntRect(16, 0, 15, 15));
                                i = 0; j=0; k=0; r=0;

                               solve(ghostX, ghostY, pacY, pacX, tailmap, 1, visitedArray);
                               solve(ghost1X, ghost1Y, pacY, pacX, tailmap, 2, visitedArray2);
                               solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);

                               cout << nodePath[pacX][pacY].path2 <<endl;

                            }
                            else if (Keyboard::isKeyPressed(Keyboard::Up) && tailmap[pacX - 1][pacY] != '#'
                                     && tailmap[pacX - 1][pacY] != '|' && tailmap[pacX - 1][pacY] != '_'
                                     && tailmap[pacX - 1][pacY] != '&')
                            {

                                prevpacX = pacX;
                                prevpacY = pacY;
                                moved = true;
                                pacX--;
                                PacMan.move(0, -15);
                                PacMan.setTextureRect(IntRect(17, 32, 15, 15));
                                i = 0; j=0; k=0; r=0;

                               solve(ghostX, ghostY, pacY, pacX, tailmap, 1, visitedArray);
                               solve(ghost1X, ghost1Y, pacY, pacX, tailmap, 2, visitedArray2);
                               solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);

                                cout << nodePath[pacX][pacY].path2 <<endl;

                            }
                            else if (Keyboard::isKeyPressed(Keyboard::Down) && tailmap[pacX + 1][pacY] != '#'
                                     && tailmap[pacX + 1][pacY] != '|' && tailmap[pacX + 1][pacY] != '_'
                                     && tailmap[pacX + 1][pacY] != '&')
                            {

                                prevpacX = pacX;
                                prevpacY = pacY;
                                moved = true;
                                pacX++;
                                PacMan.move(0, 15);
                                PacMan.setTextureRect(IntRect(17, 48, 15, 15));
                                i = 0; j=0; k=0; r=0;

                               solve(ghostX, ghostY, pacY, pacX, tailmap, 1, visitedArray);
                               target2X = pacX+4; target2Y = pacY;
                               solve(ghost1X, ghost1Y, pacY, (pacX+4), tailmap, 2, visitedArray2);
                               solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);

                                cout << nodePath[pacX][pacY].path2 <<endl;


                            }
                        }


                            /// GHOST NUMBER 1 MOVEMENT
                            if (nodePath[pacX][pacY].path[i] == 'u' && tailmap[ghostX-1][ghostY] !='#'
                                && tailmap[ghostX-1][ghostY] !='|' && tailmap[ghostX-1][ghostY] !='_' )
                            {
                                Sleep(50);
                                Ghost1.move(Vector2f(0, -15));
                                ghostX--;
                                i++;

                            }
                            else if (nodePath[pacX][pacY].path[i] == 'd' && tailmap[ghostX+1][ghostY] !='#'
                                     && tailmap[ghostX+1][ghostY] !='|' && tailmap[ghostX+1][ghostY] !='_')
                            {
                                Sleep(50);
                                Ghost1.move(Vector2f(0, 15));
                                ghostX++;
                                i++;
                            }
                            else if (nodePath[pacX][pacY].path[i] == 'r' && tailmap[ghostX][ghostY+1] !='#'
                                     && tailmap[ghostX][ghostY+1] !='|' && tailmap[ghostX][ghostY+1] !='_')
                            {
                                Sleep(50);
                                Ghost1.move(Vector2f(15, 0));
                                ghostY++;
                                i++;
                            }
                            else if (nodePath[pacX][pacY].path[i] == 'l' && tailmap[ghostX][ghostY-1] !='#'
                                     && tailmap[ghostX][ghostY-1] !='|' && tailmap[ghostX][ghostY-1] !='_')
                            {
                                Sleep(50);
                                Ghost1.move(Vector2f(-15, 0));
                                ghostY--;
                                i++;
                            }

                             ///GHOST NUMBER 2 MOVEMENT
                                if (nodePath[pacX][pacY].path2[j] == 'u' && tailmap[ghost1X-1][ghost1Y] !='#'
                                    && tailmap[ghost1X-1][ghost1Y] !='|' && tailmap[ghost1X-1][ghost1Y] !='_')
                            {
                                Ghost2.move(Vector2f(0, -15));
                                ghost1X--;
                                j++;
                            }
                            else if (nodePath[pacX][pacY].path2[j] == 'd' && tailmap[ghost1X+1][ghost1Y] !='#'
                                     && tailmap[ghost1X+1][ghost1Y] !='|' && tailmap[ghost1X+1][ghost1Y] !='_')
                            {
                                Ghost2.move(Vector2f(0, 15));
                                ghost1X++;
                                j++;
                            }
                            else if (nodePath[pacX][pacY].path2[j] == 'r' && tailmap[ghost1X][ghost1Y+1] !='#'
                                     && tailmap[ghost1X][ghost1Y+1] !='|' && tailmap[ghost1X][ghost1Y+1] !='_')
                            {
                                Ghost2.move(Vector2f(15, 0));
                                ghost1Y++;
                                j++;

                            }
                            else if (nodePath[pacX][pacY].path2[j] == 'l' && tailmap[ghost1X][ghost1Y-1] !='#'
                                     && tailmap[ghost1X][ghost1Y-1] !='|' && tailmap[ghost1X][ghost1Y-1] !='_')
                            {
                                Ghost2.move(Vector2f(-15, 0));
                                ghost1Y--;
                                j++;

                            }

                            /// GHOST NUMBER 4 MOVEMENT

                            if(sqrt( ( pow((ghost3X - pacX),2) + pow((ghost3Y - pacY),2) )) < 8)
                            {
                                solve(ghost3X, ghost3Y, 2, 20, tailmap, 4, visitedArray4);
                                targetX = 20;
                                targetY = 2;
                            }
                            else
                            {
                                solve(ghost3X, ghost3Y, pacY, pacX, tailmap, 4, visitedArray4);
                                targetX = pacX;
                                targetY = pacY;
                            }

                            if (nodePath[targetX][targetY].path4[r] == 'u' && tailmap[ghost3X-1][ghost3Y] !='#'
                                && tailmap[ghost3X-1][ghost3Y] !='|' && tailmap[ghost3X-1][ghost3Y] !='_' )
                            {
                                Ghost4.move(Vector2f(0, -15));
                                ghost3X--;
                                r++;
                            }
                            else if (nodePath[targetX][targetY].path4[r] == 'd' && tailmap[ghost3X+1][ghost3Y] !='#'
                                     && tailmap[ghost3X+1][ghost3Y] !='|' && tailmap[ghost3X+1][ghost3Y] !='_')
                            {
                                Ghost4.move(Vector2f(0, 15));
                                ghost3X++;
                                r++;
                            }
                            else if (nodePath[targetX][targetY].path4[r] == 'r' && tailmap[ghost3X][ghost3Y+1] !='#'
                                     && tailmap[ghost3X][ghost3Y+1] !='|' && tailmap[ghost3X][ghost3Y+1] !='_')
                            {
                                Ghost4.move(Vector2f(15, 0));
                                ghost3Y++;
                                r++;

                            }
                            else if (nodePath[targetX][targetY].path4[r] == 'l' && tailmap[ghost3X][ghost3Y-1] !='#'
                                     && tailmap[ghost3X][ghost3Y-1] !='|' && tailmap[ghost3X][ghost3Y-1] !='_')
                            {
                                Ghost4.move(Vector2f(-15, 0));
                                ghost3Y--;
                                r++;

                            }

                        window.clear();


                        window.draw(l);

                        for (int i = 0; i < 22; i++) //for level 1
                        {
                            for (int j = 0; j < 43; j++)
                            {
                                if (tailmap[pacX][pacY] == '.' && pacX == i && pacY == j)
                                {
                                    tailmap[i][j] = ' ';
                                    score++;

                                }
                                if (i == pacX && j == pacY)
                                {
                                    window.draw(PacMan);
                                    tailmap[i][j] = 'x';

                                }
                                else if (tailmap[i][j] == '#' || tailmap[i][j] == '|' || tailmap[i][j] == '_')
                                {
                                    ball.setPosition(Vector2f(j * 15, i * 15));
                                    window.draw(ball);
                                    //win.display();
                                }
                                else if (ghostX == i && ghostY == j)
                                {

                                    window.draw(Ghost1);

                                }
                                else if (ghost1X == i && ghost1Y == j)
                                {

                                    window.draw(Ghost2);


                                }
                                else if (ghost2X == i && ghost2Y == j)
                                {

                                    window.draw(Ghost3);

                                }
                                else if (ghost3X == i && ghost3Y == j)
                                {
                                    window.draw(Ghost4);

                                }
                                else if (tailmap[i][j] == '.')
                                {
                                    dot.setPosition(Vector2f(j * 15, i * 15));
                                    window.draw(dot);
                                }

                                if (pacX == i && pacY == j && ghost2X == i && ghost2Y == j || pacX == i && pacY == j && ghost3X == i && ghost3Y == j
                                        || pacX == i && pacY == j && ghost1X == i && ghost1Y == j || pacX == i && pacY == j && ghostX == i && ghostY == j)
                                {

                                    lives--;
                                    goto mainn;

                                }

                                if (lives > 0)
                                {
                                    continue;
                                }
                                else if (lives == 0)
                                {
                                    break;
                                }
                                //win.display();




                            }
                        }


                        // DRAW GAME OVER
                        if (lives == 0)
                        {

                            window.draw(Gmover);

                        }

                        //DRAW WIN
                        if (score == 118)
                        {
                            window.draw(congrats);
                        }

                        cout << score << endl;
                        cout << lives << endl;


                        window.draw(Score);
                        window.draw(Lives);
                        window.draw(points);
                        window.display();


                    }

                }
                else if (clickx >= 52 && clickx <= 385 && clicky >= 268 && clicky <= 424)
                {
                    std::cout << "Options button has been pressed" << std::endl;


                    sf::RenderWindow window(sf::VideoMode(1250, 800), "PACMAN");
                    window.setKeyRepeatEnabled(false);

                    sf::Texture pTexture;
                    sf::Sprite pacmanImage;
                    if (!pTexture.loadFromFile("options.jpg"))
                        std::cout << "Error couldn't load options image" << std::endl;

                    pacmanImage.setTexture(pTexture);

                    while (window.isOpen())
                    {
                        sf::Event Event;
                        while (window.pollEvent(Event))
                        {
                            switch (Event.type)
                            {
                            case sf::Event::Closed:
                                window.close();
                                break;
                            }
                        }

                        window.draw(pacmanImage);
                        window.display();
                    }

                }

                else if (clickx >= 49 && clickx <= 377 && clicky >= 465 && clicky <= 619)
                {
                    std::cout << "High Scores button has been pressed" << std::endl;
                }
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    std::cout << "Left button has been pressed" << std::endl;
                    c++;
                    //std::cout << c << std::endl;
                    break;
                }
                break;
            }
        }

        window.clear();
        window.draw(pacmanimage);
        window.display();
    }
}
// for read numbers (score , lives)
string s(int n)
{
    stringstream s;
    s << n;
    return s.str();
}

