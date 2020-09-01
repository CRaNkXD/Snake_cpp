#pragma once
#include <vector>

#include "spielfeld.h"

class Snake
{
private:
    int m_nXPos;
    int m_nYPos;
    char m_sRichtung;
    int m_nSnakePartCounter;
    bool m_bHeadHitPart;
    struct m_strSnakePart
    {
        int str_nXPos;
        int str_nYPos;
        char str_sDirection;
        int str_nId;
    };
    std::vector<m_strSnakePart> m_vSnakePart;
    Snake();

public:

    Snake(const int& nXPos, const int& nYpos, const Spielfeld &cSpielfeld);
     ~Snake();
    int GetXPos() const;
    void SetXPos(const int& nXPos);
    int GetYPos() const;
    void SetYPos(const int& nYPos);
    char GetDirection() const;
    void SetDirection(const char& sRichtung);
    int GetSnakePartCounter() const;
    void SetSnakePartCounter(const int& nCounter);
    bool GetHeadHitPart() const;
    void SetHeadHitPart(const bool& bHeadHitPart);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void MoveSnakePart();
    std::vector<m_strSnakePart> GetSnakePart() const;
    void AddSnakePart();

};

