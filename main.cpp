#include <iostream>
#include <conio.h>
#include <windows.h>
#include "spielfeld.h"
#include "snake.h"

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
                case 'w':
                    if (cSnakeHead.GetRichtung() != 's')
                    cSnakeHead.SetRichtung('w');
                    break;
                case 's':
                    if (cSnakeHead.GetRichtung() != 'w')
                    cSnakeHead.SetRichtung('s');
                    break;
                case 'd':
                    if (cSnakeHead.GetRichtung() != 'a')
                    cSnakeHead.SetRichtung('d');
                    break;
                case 'a':
                    if (cSnakeHead.GetRichtung() != 'd')
                    cSnakeHead.SetRichtung('a');
                    break;
            }
        }
        // Move the snake into that direction.
        switch (cSnakeHead.GetRichtung())
        {
            case 'w':
                cSnakeHead.MoveUp();
                break;
            case 's':
                cSnakeHead.MoveDown();
                break;
            case 'd':
                cSnakeHead.MoveRight();
                break;
            case 'a':
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
       if(cSnakeHead.GetXPos()== cSpielfeld.GetSize() + 1 || cSnakeHead.GetXPos()== 0
               || cSnakeHead.GetYPos()== cSpielfeld.GetSize() + 1 || cSnakeHead.GetYPos()== 0 || cSnakeHead.GetHeadHitPart())
       {
           // Returns true or false depending whether the user wants to play again.
           exit = cSpielfeld.GameEnd(cSnakeHead);
       }


        Sleep(50);
    }


}

