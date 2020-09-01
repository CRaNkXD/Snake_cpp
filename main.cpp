#include <iostream>
#include <conio.h>
#include <windows.h>

#include "spielfeld.h"
#include "snake.h"
#include "constants.h"

int main()
{
    Spielfeld cSpielfeld(15);
    Snake cSnakeHead(cSpielfeld.GetSize()/2, cSpielfeld.GetSize()/2, cSpielfeld);

    std::cout << "Dies ist eine Comandfenster Snake Version." << std::endl;
    std::cout << "Die Schlange wird mit w,a,s,d gesteuert.\nBei Start bewegt sich die Schlange nach oben." << std::endl;
    std::cout << "Dein Highscore wird in der Datei Snake_Highscore gespeichert." << std::endl;
    std::cout << "Zum Starten druecke s." << std::endl;

    bool start(false);
    while (!start)
    {
        if(_kbhit())
        {
            // Get the direction for the snake.
            if (_getch() == 's')
                start = true;
        }
    }

    system("cls");

    bool exit = false;
    while(!exit)
    {
        // Wait for user to press a button. If not go on moving.
        if(_kbhit())
        {
            // Get the direction for the snake.
            switch (_getch())
            {
//                case 'e':
//                    exit = true;
//                    break;
                case constants::Direction::UP:
                    if (cSnakeHead.GetDirection() != constants::Direction::DOWN)
                    cSnakeHead.SetDirection(constants::Direction::UP);
                    break;
                case constants::Direction::DOWN:
                    if (cSnakeHead.GetDirection() != constants::Direction::UP)
                    cSnakeHead.SetDirection(constants::Direction::DOWN);
                    break;
                case constants::Direction::RIGHT:
                    if (cSnakeHead.GetDirection() != constants::Direction::LEFT)
                    cSnakeHead.SetDirection(constants::Direction::RIGHT);
                    break;
                case constants::Direction::LEFT:
                    if (cSnakeHead.GetDirection() != constants::Direction::RIGHT)
                    cSnakeHead.SetDirection(constants::Direction::LEFT);
                    break;
            }
        }
        // Move the snake into that direction.
        switch (cSnakeHead.GetDirection())
        {
            case constants::Direction::UP:
                cSnakeHead.MoveUp();
                break;
            case constants::Direction::DOWN:
                cSnakeHead.MoveDown();
                break;
            case constants::Direction::RIGHT:
                cSnakeHead.MoveRight();
                break;
            case constants::Direction::LEFT:
                cSnakeHead.MoveLeft();
                break;
        }

        // If the snake has at least one extra part move this parts.
        if (cSnakeHead.GetSnakePartCounter() >= 1)
        {
            cSnakeHead.MoveSnakePart();
        }

        // Print the game.
        cSpielfeld.Print(cSnakeHead);

        //Add a part to the snake if the head of the snake hit a part.
       if (cSnakeHead.GetXPos() == cSpielfeld.GetSnakePartXPos()
               && cSnakeHead.GetYPos() == cSpielfeld.GetSnakePartYPos())
       {
           cSnakeHead.AddSnakePart();
           cSpielfeld.SetSnakePartPos(cSnakeHead);

       }

       // If the head hits a wall or itself the game is lost.
       if(cSnakeHead.GetXPos() == cSpielfeld.GetSize() + 1 || cSnakeHead.GetXPos() == 0
               || cSnakeHead.GetYPos()== cSpielfeld.GetSize() + 1 || cSnakeHead.GetYPos()== 0 || cSnakeHead.GetHeadHitPart())
       {
           // Returns true or false depending whether the user wants to play again.
           exit = cSpielfeld.GameEnd(cSnakeHead);
       }


        Sleep(50);
    }


}

