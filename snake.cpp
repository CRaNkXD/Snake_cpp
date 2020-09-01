#include "snake.h"
#include "spielfeld.h"
#include <iostream>

Snake::Snake()
    : m_nXPos(10), m_nYPos(10), m_sRichtung('w'), m_nSnakePartCounter(0)
    , m_bHeadHitPart(false)
{
    m_vSnakePart = std::vector<m_strSnakePart>(22 * 22);
}

Snake::Snake(int nXpos, int nYpos, Spielfeld &cSpielfeld)
    : m_nXPos(nXpos), m_nYPos(nYpos), m_sRichtung('w'), m_nSnakePartCounter(0)
    , m_bHeadHitPart(false)
{
    m_vSnakePart = std::vector<m_strSnakePart>(cSpielfeld.GetSize()*cSpielfeld.GetSize());
}

Snake::~Snake()
{
//    std::cout << "Destructor Snake" << std::endl;
}

int Snake::GetXPos()
{
    return m_nXPos;
}

void Snake::SetXPos(int nXPos)
{
     m_nXPos = nXPos;
}

int Snake::GetYPos()
{
    return m_nYPos;
}

void Snake::SetYPos(int nYPos)
{
     m_nYPos = nYPos;
}

char Snake::GetRichtung()
{
    return m_sRichtung;
}

void Snake::SetRichtung(char sRichtung)
{
    m_sRichtung = sRichtung;
}

void Snake::MoveUp()
{
    m_nYPos -= 1;
}

void Snake::MoveDown()
{
    m_nYPos += 1;
}

void Snake::MoveLeft()
{
    m_nXPos -= 1;
}

void Snake::MoveRight()
{
    m_nXPos += 1;
}

std::vector<m_strSnakePart> Snake::GetSnakePart()
{
    return m_vSnakePart;
}

void Snake::AddSnakePart()
{
    m_nSnakePartCounter += 1;
    if (m_nSnakePartCounter == 1)
    {
    m_vSnakePart[m_nSnakePartCounter - 1].str_nId = m_nSnakePartCounter;
    m_vSnakePart[m_nSnakePartCounter - 1].str_nXPos = m_nXPos;
    m_vSnakePart[m_nSnakePartCounter - 1].str_nYPos = m_nYPos;
    m_vSnakePart[m_nSnakePartCounter - 1].str_sRichtung = 'z';
    }
    else
    {
        m_vSnakePart[m_nSnakePartCounter - 1].str_nId = m_nSnakePartCounter;
        m_vSnakePart[m_nSnakePartCounter - 1].str_nXPos = m_vSnakePart[m_nSnakePartCounter - 2].str_nXPos;
        m_vSnakePart[m_nSnakePartCounter - 1].str_nYPos = m_vSnakePart[m_nSnakePartCounter - 2].str_nYPos;
        m_vSnakePart[m_nSnakePartCounter - 1].str_sRichtung = 'z';
    }
}


int Snake::GetSnakePartCounter()
{
    return m_nSnakePartCounter;
}

void Snake::MoveSnakePart()
{
    for (int nSnakePart(m_nSnakePartCounter - 1); nSnakePart >= 0  ; nSnakePart--)
    {
        // Check if the head hits a part of the snake. When this happens the game will stop.
        if (m_nXPos == m_vSnakePart[nSnakePart].str_nXPos && m_nYPos == m_vSnakePart[nSnakePart].str_nYPos)
        {
            m_bHeadHitPart = true;
            break;
        }
            
        // Move the current part in the direction, which is saved in str_sRichtung.
        // New parts have no direction until now. They will get the direction in the next step.
        switch (m_vSnakePart[nSnakePart].str_sRichtung)
        {
        case 'w':
            m_vSnakePart[nSnakePart].str_nYPos -= 1;
            break;
        case 's':
            m_vSnakePart[nSnakePart].str_nYPos += 1;
            break;
        case 'a':
            m_vSnakePart[nSnakePart].str_nXPos -= 1;
            break;
        case 'd':
            m_vSnakePart[nSnakePart].str_nXPos += 1;
            break;
        }

        // Set the direction for each part depending on the part which runs before.
        if (m_vSnakePart[nSnakePart].str_nId == 1)
        {
            switch (m_sRichtung)
            {
            case 'w':
                m_vSnakePart[nSnakePart].str_sRichtung = 'w';
                break;
            case 's':
                m_vSnakePart[nSnakePart].str_sRichtung = 's';
                break;
            case 'a':
                m_vSnakePart[nSnakePart].str_sRichtung = 'a';
                break;
            case 'd':
                m_vSnakePart[nSnakePart].str_sRichtung = 'd';
                break;
            }
        }
        else
        {
            switch (m_vSnakePart[nSnakePart - 1].str_sRichtung)
            {
            case 'w':
                m_vSnakePart[nSnakePart].str_sRichtung = 'w';
                break;
            case 's':
                m_vSnakePart[nSnakePart].str_sRichtung = 's';
                break;
            case 'a':
                m_vSnakePart[nSnakePart].str_sRichtung = 'a';
                break;
            case 'd':
                m_vSnakePart[nSnakePart].str_sRichtung = 'd';
                break;
            }
        }
    }
}

void Snake::SetSnakePartCounter(int nCounter)
{
    m_nSnakePartCounter = nCounter;
}

bool Snake::GetHeadHitPart()
{
    return m_bHeadHitPart;
}

void Snake::SetHeadHitPart(bool bHeadHitPart)
{
    m_bHeadHitPart = bHeadHitPart;
}
