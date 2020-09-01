#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

#include "spielfeld.h"
#include "snake.h"
#include "constants.h"


int iRand(int iMin, int iMax)
{
    return iMin + (rand() % (iMax - iMin + 1));
}


Spielfeld::Spielfeld() :
    m_nSize(22), m_nNewPart(0), m_nPoints(0)
{
    srand(time(0));

    m_nSnakePartXPos = iRand(1,m_nSize);
    m_nSnakePartYPos = iRand(1,m_nSize);
}

Spielfeld::Spielfeld(const int& nSize) :
    m_nSize(nSize), m_nNewPart(0), m_nPoints(0)
{
    srand(time(0));

    m_nSnakePartXPos = iRand(1,m_nSize);
    m_nSnakePartYPos = iRand(1,m_nSize);
}

Spielfeld::~Spielfeld()
{
//    std::cout << "Destructor Spielfeld" << std::endl;
}

int Spielfeld::GetSize() const
{
    return m_nSize;
}

void Spielfeld::Print(const Snake &pcSnakeHead) const
{
    bool bPrint = false;
    for (int nRow(0); nRow <= m_nSize + 1; nRow++)
    {
        for (int nCol(0); nCol <= m_nSize + 1; nCol++)
        {
            // Print the walls.
            if (nRow * nCol == 0 || (nCol == m_nSize + 1 || nRow == m_nSize + 1))
            {
                std::cout << "+";
                bPrint = true;
            }
            else if (pcSnakeHead.GetXPos() == nCol && pcSnakeHead.GetYPos() == nRow)
            {
                std::cout << "@";
                bPrint = true;
            }
            else if(m_nSnakePartXPos == nCol && m_nSnakePartYPos == nRow)
            {
                std::cout << "@";
                bPrint = true;
            }
            else if (pcSnakeHead.GetSnakePartCounter() >= 1)
            {
                for (int nSnakeParts(0); nSnakeParts < pcSnakeHead.GetSnakePartCounter(); nSnakeParts++)
                {

                    if(pcSnakeHead.GetSnakePart()[nSnakeParts].str_nXPos == nCol
                            && pcSnakeHead.GetSnakePart()[nSnakeParts].str_nYPos == nRow)
                    {
                        std::cout << "@";
                        bPrint = true;
                    }
                }

            }
            // If no other sign was printed, print now a " ".
            if (!bPrint)
            {
                std::cout << " ";
            }
            else
            {
                bPrint = false;
            }

        }
        std::cout << std::endl;
    }
    std::cout << " Punkte:  " << m_nPoints;
    COORD p = { 0, 0 };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void Spielfeld::SetSnakePartPos(const Snake &pcSnakeHead)
{
    // Create a new part for the snake to eat and check if it is on a free space.
    bool bPosSet = false;

    m_nPoints += 100;

    do
    {
        m_nSnakePartXPos = iRand(1,m_nSize);
        m_nSnakePartYPos = iRand(1,m_nSize);
        //If the snake has no parts we only check the head.
        if (pcSnakeHead.GetSnakePartCounter() == 0
                && (pcSnakeHead.GetXPos() != m_nSnakePartXPos
                || pcSnakeHead.GetYPos() != m_nSnakePartYPos))
        {
            bPosSet = true;
        }
        else if (pcSnakeHead.GetSnakePartCounter() >= 1)
        {
            // Loop throug all parts of the Snake.
            for (int nSnakePart(0); nSnakePart < pcSnakeHead.GetSnakePartCounter(); nSnakePart++)
            {
                if ((pcSnakeHead.GetSnakePart()[nSnakePart].str_nXPos != m_nSnakePartXPos ||
                     pcSnakeHead.GetSnakePart()[nSnakePart].str_nYPos != m_nSnakePartYPos)
                        && (pcSnakeHead.GetXPos() != m_nSnakePartXPos || pcSnakeHead.GetYPos() != m_nSnakePartYPos))
                {
                    bPosSet = true;
                }
                else
                {
                    bPosSet = false;
                    break;
                }

            }
        }
        else
        {
            bPosSet = true;
            std::cerr << "Fehler bei der Positionierung des SnakePart!";
        }

    }
    while(!bPosSet);
}

int Spielfeld::GetSnakePartXPos() const
{
    return m_nSnakePartXPos;
}

int Spielfeld::GetSnakePartYPos() const
{
    return m_nSnakePartYPos;
}

void Spielfeld::SetNewPartCounter(const int& nValue)
{
    m_nNewPart = nValue;
}

void Spielfeld::AddPoints(const int& nPoints)
{
    m_nPoints += nPoints;
}

int Spielfeld::GetPoints() const
{
    return m_nPoints;
}

void Spielfeld::SetPoints(const int& nValue)
{
    m_nPoints = nValue;
}

bool Spielfeld::GameEnd(Snake& pcSnakeHead)
{

    system("cls");
    std::cout << std::endl << std::endl;

    // Width for the Highscore file.
    int width{ 14 };
    bool bNewHighscore{ false };
    std::vector<std::string> sName(8);
    std::vector<std::string> sPoints(8);
    std::string sDummy;
    std::string sNameTemp, sNameTemp2, sPointsTemp, sPointsTemp2;

    std::fstream InputFile("Snake_Highscore.txt");
    if (!InputFile)
    {
        std::ofstream OutputFile("Snake_Highscore.txt");
        OutputFile << std::left << std::setw(width) << "Name" << std::right << std::setw(width) << "Punkte" << std::endl;
        OutputFile << std::left << std::setw(width) << "LoupingLoui" << std::right << std::setw(width) << "5000" << std::endl;
        OutputFile << std::left << std::setw(width) << "Fritz" << std::right << std::setw(width) << "4000" << std::endl;
        OutputFile << std::left << std::setw(width) << "SumseBiene" << std::right << std::setw(width) << "3000" << std::endl;
        OutputFile << std::left << std::setw(width) << "KingKarl" << std::right << std::setw(width) << "2000" << std::endl;
        OutputFile << std::left << std::setw(width) << "LarsLarson" << std::right << std::setw(width) << "1000" << std::endl;
        OutputFile << std::left << std::setw(width) << "HasiHinterbein" << std::right << std::setw(width) << "500" << std::endl;
        OutputFile << std::left << std::setw(width) << "BlinderMoench" << std::right << std::setw(width) << "200" << std::endl;
        OutputFile << std::left << std::setw(width) << "LahmeEnte" << std::right << std::setw(width) << "100" << std::endl;
        OutputFile.close();
    }
    
    if (!InputFile.is_open())
        InputFile.open("Snake_Highscore.txt");

    std::getline(InputFile, sDummy);
    for (int i(0); i < 8; i++)
    {
        InputFile >> sName[i];
        InputFile >> sPoints[i];

        if (bNewHighscore)
        {
            sNameTemp2 = sName[i];
            sName[i] = sNameTemp;
            sNameTemp = sNameTemp2;

            sPointsTemp2 = sPoints[i];
            sPoints[i] = sPointsTemp;
            sPointsTemp = sPointsTemp2;
        }

        if (std::stoi(sPoints[i]) <= this->GetPoints() && bNewHighscore == false)
        {
            std::cout << "Du hast " << this->GetPoints() << " Punkte erreicht!" << std::endl;
            std::cout << "Du hast einen neuen Highscore errungen! Gib deinen Namen ein:" << std::endl;
            std::cout << "Es sind keine Leerzeichen erlaubt!" << std::endl;
            sNameTemp = sName[i];
            std::cin >> sName[i];
            std::getline(std::cin ,sDummy);
            sPointsTemp = sPoints[i];
            sPoints[i] = std::to_string(this->GetPoints());
            bNewHighscore = true;
        }
    }

    if (bNewHighscore)
    {
        std::cout << std::endl << std::endl;
        InputFile.seekg(0, std::ios::beg);

        InputFile << std::left << std::setw(width) << "Name" << std::right << std::setw(width) << "Punkte" << std::endl;
        std::cout << std::left << std::setw(width) << "Platz" << std::left << std::setw(width) << "Name" << std::right << std::setw(width) << "Punkte" << std::endl;
        for (int i(0); i < 8; i++)
        {
            InputFile  << std::left << std::setw(width) << sName[i] << std::right << std::setw(width) << sPoints[i] << std::endl;
            std::cout << i+1 << std::left << std::setw(width) << ". Platz" << std::left << std::setw(width) << sName[i] << std::right << std::setw(width) << sPoints[i] << std::endl;
        }
    }

    InputFile.close();

    if (!bNewHighscore)
    {
        std::cout << "Du bist gegen die Wand gefahren oder hast versucht dich selbst zu fressen." << std::endl;
        std::cout << "Du hast verloren!" << std::endl;
        std::cout << "Du hast " << this->GetPoints() << " Punkte erreicht!" << std::endl;
        std::cout << std::endl << std::endl;
        std::cout << std::left << std::setw(width) << "Platz"  << std::left << std::setw(width) << "Name" << std::right << std::setw(width) << "Punkte" << std::endl;
        for (int i(0); i < 8; i++)
        {
            std::cout << i+1 << std::left << std::setw(width) << ". Platz" << std::left << std::setw(width) << sName[i] << std::right << std::setw(width) << sPoints[i] << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Druecke e fuer Exit und n fuer nochmal!" << std::endl;
    char c('a');
    while (true)
    {
        c = _getch();
        if(c == 'e')
        {
            return true;
        }
        else if (c == 'n')
        {
            system("cls");
            pcSnakeHead.SetXPos(this->GetSize()/2);
            pcSnakeHead.SetYPos(this->GetSize()/2);
            pcSnakeHead.SetDirection(constants::Direction::UP);
            this->SetSnakePartPos(pcSnakeHead);
            pcSnakeHead.SetSnakePartCounter(0);
            this->SetNewPartCounter(0);
            this->SetPoints(0);
            pcSnakeHead.SetHeadHitPart(false);
            return false;
        }
    }
    return true;
}
