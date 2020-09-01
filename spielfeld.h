#pragma once
class Snake;

class Spielfeld
{
private:
    const int m_nSize;
    int m_nSnakePartXPos;
    int m_nSnakePartYPos;
    int m_nNewPart;
    int m_nPoints;

public:
    Spielfeld();
    Spielfeld(const int& nSize);
    ~Spielfeld();

    void Print(const Snake &pcSnakeHead) const;
    int GetSize() const;
    void SetSnakePartPos(const Snake &pcSnakeHead);
    void SetNewPartCounter(const int& nValue);
    int GetSnakePartXPos() const;
    int GetSnakePartYPos() const;
    void AddPoints(const int& nPoints);
    int GetPoints() const;
    void SetPoints(const int& nValue);
    bool GameEnd(Snake &pcSnakeHead);
};
