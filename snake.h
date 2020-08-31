#pragma once

#include "spielfeld.h"

struct m_strSnakePart
{
    int str_nXPos;
    int str_nYPos;
    char str_sRichtung;
    int str_nId;
};

class Snake
{
private:
    int m_nXPos;
    int m_nYPos;
    char m_sRichtung;
    int m_nSnakePartCounter;
    bool m_bHeadHitPart;
    m_strSnakePart* m_pstrSnakePart;
    Snake();

public:

    Snake(int nXPos, int nYpos, Spielfeld &cSpielfeld);
     ~Snake();
    int GetXPos();
    void SetXPos(int nXPos);
    int GetYPos();
    void SetYPos(int nYPos);
    char GetRichtung();
    void SetRichtung(char sRichtung);
    int GetSnakePartCounter();
    void SetSnakePartCounter(int nCounter);
    bool GetHeadHitPart();
    void SetHeadHitPart(bool bHeadHitPart);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void MoveSnakePart();
    m_strSnakePart* GetSnakePart();
    void AddSnakePart();

};

