#pragma once
class Snake;

class Spielfeld
{
private:
    const unsigned int m_nSize;
    unsigned int m_nSnakePartXPos;
    unsigned int m_nSnakePartYPos;
    unsigned int m_nNewPart;
    unsigned int m_nPoints;

public:
    Spielfeld();
    Spielfeld(const unsigned int& nSize);
    ~Spielfeld();

    void Print(const Snake &pcSnakeHead) const;
    int GetSize() const;
    void SetSnakePartPos(const Snake &pcSnakeHead);
    void SetNewPartCounter(const unsigned int& nValue);
    int GetSnakePartXPos() const;
    int GetSnakePartYPos() const;
    void AddPoints(const unsigned int& nPoints);
    int GetPoints() const;
    void SetPoints(const unsigned int& nValue);
    bool GameEnd(Snake &pcSnakeHead);
};
