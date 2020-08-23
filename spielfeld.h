#ifndef SPIELFELD_H
#define SPIELFELD_H

class Snake;

class Spielfeld
{
private:
    int m_nSize;
    int m_nSnakePartXPos;
    int m_nSnakePartYPos;
    int m_nNewPart;
    int m_nPoints;

public:
    Spielfeld();
    Spielfeld(int nSize);
    ~Spielfeld();

    void Print(Snake &pcSnakeHead);
    int GetSize();
    void SetSnakePartPos(Snake &pcSnakeHead);
    void SetNewPartCounter(int nValue);
    int GetSnakePartXPos();
    int GetSnakePartYPos();
    void AddPoints(int nPoints);
    int GetPoints();
    void SetPoints(int nValue);
    bool GameEnd(Snake &pcSnakeHead);
};

#endif // SPIELFELD_H
