#include <iostream>

#include "snake.h"
#include "spielfeld.h"
#include "constants.h"

Snake::Snake()
    : m_nXPos(10), m_nYPos(10), m_sRichtung(constants::Direction::UP), m_nSnakePartCounter(0)
    , m_bHeadHitPart(false)
{
    m_vSnakePart = std::vector<m_strSnakePart>(22 * 22);
}

Snake::Snake(const int& nXpos, const int& nYpos, const Spielfeld &cSpielfeld)
    : m_nXPos(nXpos), m_nYPos(nYpos), m_sRichtung(constants::Direction::UP), m_nSnakePartCounter(0)
    , m_bHeadHitPart(false)
{
    m_vSnakePart = std::vector<m_strSnakePart>(cSpielfeld.GetSize()*cSpielfeld.GetSize());
}

Snake::~Snake()
{
//    std::cout << "Destructor Snake" << std::endl;
}

int Snake::GetXPos() const
{
    return m_nXPos;
}

void Snake::SetXPos(const int& nXPos)
{
     m_nXPos = nXPos;
}

int Snake::GetYPos() const
{
    return m_nYPos;
}

void Snake::SetYPos(const int& nYPos)
{
     m_nYPos = nYPos;
}

char Snake::GetDirection() const
{
    return m_sRichtung;
}

void Snake::SetDirection(const char& sRichtung)
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

std::vector<Snake::m_strSnakePart> Snake::GetSnakePart() const
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
    m_vSnakePart[m_nSnakePartCounter - 1].str_sDirection = 'z';
    }
    else
    {
        m_vSnakePart[m_nSnakePartCounter - 1].str_nId = m_nSnakePartCounter;
        m_vSnakePart[m_nSnakePartCounter - 1].str_nXPos = m_vSnakePart[m_nSnakePartCounter - 2].str_nXPos;
        m_vSnakePart[m_nSnakePartCounter - 1].str_nYPos = m_vSnakePart[m_nSnakePartCounter - 2].str_nYPos;
        m_vSnakePart[m_nSnakePartCounter - 1].str_sDirection = 'z';
    }
}


int Snake::GetSnakePartCounter() const
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
        switch (m_vSnakePart[nSnakePart].str_sDirection)
        {
        case constants::Direction::UP:
            m_vSnakePart[nSnakePart].str_nYPos -= 1;
            break;
        case constants::Direction::DOWN:
            m_vSnakePart[nSnakePart].str_nYPos += 1;
            break;
        case constants::Direction::LEFT:
            m_vSnakePart[nSnakePart].str_nXPos -= 1;
            break;
        case constants::Direction::RIGHT:
            m_vSnakePart[nSnakePart].str_nXPos += 1;
            break;
        }

        // Set the direction for each part depending on the part which runs before.
        if (m_vSnakePart[nSnakePart].str_nId == 1)
        {
            switch (m_sRichtung)
            {
            case constants::Direction::UP:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::UP;
                break;
            case constants::Direction::DOWN:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::DOWN;
                break;
            case constants::Direction::LEFT:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::LEFT;
                break;
            case constants::Direction::RIGHT:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::RIGHT;
                break;
            }
        }
        else
        {
            switch (m_vSnakePart[nSnakePart - 1].str_sDirection)
            {
            case constants::Direction::UP:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::UP;
                break;
            case constants::Direction::DOWN:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::DOWN;
                break;
            case constants::Direction::LEFT:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::LEFT;
                break;
            case constants::Direction::RIGHT:
                m_vSnakePart[nSnakePart].str_sDirection = constants::Direction::RIGHT;
                break;
            }
        }
    }
}

void Snake::SetSnakePartCounter(const int& nCounter)
{
    m_nSnakePartCounter = nCounter;
}

bool Snake::GetHeadHitPart() const
{
    return m_bHeadHitPart;
}

void Snake::SetHeadHitPart(const bool& bHeadHitPart)
{
    m_bHeadHitPart = bHeadHitPart;
}
