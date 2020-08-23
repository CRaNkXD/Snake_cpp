#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "spielfeld.h"
#include "snake.h"
#include <windows.h>

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

int iRand(int iMin, int iMax)
{
    return iMin + (rand() % (iMax - iMin + 1));
}

using namespace std;

Spielfeld::Spielfeld()
{
    srand(time(0));

    m_nSize = 22;
    m_nNewPart = 0;
    m_nSnakePartXPos = iRand(1,m_nSize);
    m_nSnakePartYPos = iRand(1,m_nSize);
    m_nPoints = 0;
}

Spielfeld::Spielfeld(int nSize)
{
    srand(time(0));

    m_nSize = nSize;
    m_nNewPart = 0;
    m_nSnakePartXPos = iRand(1,m_nSize);
    m_nSnakePartYPos = iRand(1,m_nSize);
    m_nPoints = 0;
}

Spielfeld::~Spielfeld()
{
//    std::cout << "Destructor Spielfeld" << std::endl;
}

int Spielfeld::GetSize()
{
    return m_nSize;
}

void Spielfeld::Print(Snake &pcSnakeHead)
{
    bool bPrint = false;
    for (int nRow(0); nRow <= m_nSize + 1; nRow++)
    {
        for (int nCol(0); nCol <= m_nSize + 1; nCol++)
        {
            // Print the walls.
            if (nRow * nCol == 0 || (nCol == m_nSize + 1 || nRow == m_nSize + 1))
            {
                cout << "+";
                bPrint = true;
            }
            else if (pcSnakeHead.GetXPos() == nCol && pcSnakeHead.GetYPos() == nRow)
            {
                cout << "@";
                bPrint = true;
            }
            else if(m_nSnakePartXPos == nCol && m_nSnakePartYPos == nRow)
            {
                cout << "@";
                bPrint = true;
            }
            else if (pcSnakeHead.GetSnakePartCounter() >= 1)
            {
                for (int nSnakeParts(0); nSnakeParts < pcSnakeHead.GetSnakePartCounter(); nSnakeParts++)
                {

                    if(pcSnakeHead.GetSnakePart()[nSnakeParts].str_nXPos == nCol
                            && pcSnakeHead.GetSnakePart()[nSnakeParts].str_nYPos == nRow)
                    {
                        cout << "@";
                        bPrint = true;
                    }
                }

            }
            // If no other sign was printed, print now a " ".
            if (!bPrint)
            {
                cout << " ";
            }
            else
            {
                bPrint = false;
            }

        }
        cout << endl;
    }
    std::cout << " Punkte:  " << m_nPoints;
    COORD p = { 0, 0 };
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), p );
}

void Spielfeld::SetSnakePartPos(Snake &pcSnakeHead)
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
            cerr << "Fehler bei der Positionierung des SnakePart!";
        }

    }
    while(!bPosSet);
}

int Spielfeld::GetSnakePartXPos()
{
    return m_nSnakePartXPos;
}

int Spielfeld::GetSnakePartYPos()
{
    return m_nSnakePartYPos;
}

void Spielfeld::SetNewPartCounter(int nValue)
{
    m_nNewPart = nValue;
}

void Spielfeld::AddPoints(int nPoints)
{
    m_nPoints += nPoints;
}

int Spielfeld::GetPoints()
{
    return m_nPoints;
}

void Spielfeld::SetPoints(int nValue)
{
    m_nPoints = nValue;
}

bool Spielfeld::GameEnd(Snake &pcSnakeHead)
{

        system("cls");
        cout << endl<< endl;

        // Width for the Highscore file.
        int width(14);
        bool bNewHighscore(false);
        string sName[8];
        string sPoints[8];
        string sDummy;
        string sNameTemp, sNameTemp2, sPointsTemp, sPointsTemp2;

        fstream InputFile("Snake_Highscore.txt");
        if (!InputFile)
        {
            ofstream OutputFile("Snake_Highscore.txt");
            OutputFile << left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
            OutputFile << left << setw(width) << "LoupingLoui" << right << setw(width) << "5000" << endl;
            OutputFile << left << setw(width) << "Fritz" << right << setw(width) << "4000" << endl;
            OutputFile << left << setw(width) << "SumseBiene" << right << setw(width) << "3000" << endl;
            OutputFile << left << setw(width) << "KingKarl" << right << setw(width) << "2000" << endl;
            OutputFile << left << setw(width) << "LarsLarson" << right << setw(width) << "1000" << endl;
            OutputFile << left << setw(width) << "HasiHinterbein" << right << setw(width) << "500" << endl;
            OutputFile << left << setw(width) << "BlinderMoench" << right << setw(width) << "200" << endl;
            OutputFile << left << setw(width) << "LahmeEnte" << right << setw(width) << "100" << endl;
            OutputFile.close();

            fstream InputFile("Snake_Highscore.txt");
            getline(InputFile, sDummy);
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

                if (stoi(sPoints[i]) <= this->GetPoints() && bNewHighscore == false)
                {
                    cout << "Du hast " << this->GetPoints() << " Punkte erreicht!" << endl;
                    cout << "Du hast einen neuen Highscore errungen! Gib deinen Namen ein:" << endl;
                    cout << "Es sind keine Leerzeichen erlaubt!" << endl;
                    sNameTemp = sName[i];
                    cin >> sName[i];
                    getline(cin ,sDummy);
                    sPointsTemp = sPoints[i];
                    sPoints[i] = to_string(this->GetPoints());
                    bNewHighscore = true;
                }

            }

            if (bNewHighscore)
            {
                cout << endl << endl;
                InputFile.seekg(0, ios::beg);

                InputFile << left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
                cout <<  left << setw(width) << "Platz" <<  left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
                for (int i(0); i < 8; i++)
                {
                    InputFile  << left << setw(width) << sName[i] << right << setw(width) << sPoints[i] << endl;
                    cout << i+1 << left << setw(width) << ". Platz" << left << setw(width) << sName[i] << right << setw(width) << sPoints[i] << endl;
                }
            }

            InputFile.close();

        }
        else
        {
            fstream InputFile("Snake_Highscore.txt");
            getline(InputFile, sDummy);
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

                if (stoi(sPoints[i]) <= this->GetPoints() && bNewHighscore == false)
                {
                    cout << "Du hast " << this->GetPoints() << " Punkte erreicht!" << endl;
                    cout << "Du hast einen neuen Highscore errungen! Gib deinen Namen ein:" << endl;
                    cout << "Es sind keine Leerzeichen erlaubt!" << endl;
                    sNameTemp = sName[i];
                    cin >> sName[i];
                    getline(cin ,sDummy);
                    sPointsTemp = sPoints[i];
                    sPoints[i] = to_string(this->GetPoints());
                    bNewHighscore = true;
                }
            }

            if (bNewHighscore)
            {
                cout << endl << endl;
                InputFile.seekg(0, ios::beg);

                InputFile << left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
                cout <<  left << setw(width) << "Platz" << left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
                for (int i(0); i < 8; i++)
                {
                    InputFile  << left << setw(width) << sName[i] << right << setw(width) << sPoints[i] << endl;
                    cout << i+1 << left << setw(width) << ". Platz" << left << setw(width) << sName[i] << right << setw(width) << sPoints[i] << endl;
                }
            }

            InputFile.close();
        }

        if (!bNewHighscore)
        {
             cout << "Du bist gegen die Wand gefahren oder hast versucht dich selbst zu fressen." << endl;
             cout << "Du hast verloren!" << endl;
             cout << "Du hast " << this->GetPoints() << " Punkte erreicht!" << endl;
             cout << endl << endl;
             cout <<  left << setw(width) << "Platz"  <<  left << setw(width) << "Name" << right << setw(width) << "Punkte" << endl;
             for (int i(0); i < 8; i++)
             {
                 cout << i+1 << left << setw(width) << ". Platz" << left << setw(width) << sName[i] << right << setw(width) << sPoints[i] << endl;
             }
        }

        cout << endl;
        cout << "Druecke e fuer Exit und n fuer nochmal!" << endl;
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
                pcSnakeHead.SetRichtung('w');
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
