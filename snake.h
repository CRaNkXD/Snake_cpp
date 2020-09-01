#pragma once
#include <vector>

#include "spielfeld.h"

class Snake
{
private:
    unsigned int m_nXPos;
    unsigned int m_nYPos;
    char m_sRichtung;
    unsigned int m_nSnakePartCounter;
    bool m_bHeadHitPart;
    struct m_strSnakePart
    {
        unsigned int str_nXPos;
        unsigned int str_nYPos;
        char str_sDirection;
        unsigned int str_nId;
    };
    std::vector<m_strSnakePart> m_vSnakePart;
    Snake();

public:

    Snake(unsigned const int& nXPos, const unsigned int& nYpos, const Spielfeld &cSpielfeld);
     ~Snake();
    int GetXPos() const;
    void SetXPos(const unsigned int& nXPos);
    int GetYPos() const;
    void SetYPos(const unsigned int& nYPos);
    char GetDirection() const;
    void SetDirection(const char& sRichtung);
    int GetSnakePartCounter() const;
    void SetSnakePartCounter(const unsigned int& nCounter);
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

