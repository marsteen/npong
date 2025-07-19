//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CPong.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <deque>
#include <pong/CSprite.h>
#include <pong/CPong.h>
#include <pong/gamedefines.h>


CPong::CPong()
{
    mNumber = 0;
    mStatus = 0;
}

void CPong::addPos(int x, int y)
{
    CVector2<int> npos(x, y);
    mBody.push_back(npos);

}


void CPong::reset()
{
    mBody.clear();
    mGetLonger = false;
    mStatus = 1;

    if (mNumber == 0)
    {
        mDirection = ESnakeDir::RIGHT;
        addPos(24, 10);
        addPos(25, 10);
        addPos(26, 10);
        addPos(27, 10);
    }
    else if (mNumber == 1)
    {
        mDirection = ESnakeDir::LEFT;
        addPos(16, 10);
        addPos(15, 10);
        addPos(14, 10);
        addPos(13, 10);
    }
}


void CPong::testMove(const CVector2<int>& head, const CPong& otherSnake, int newx, int newy)
{
    CVector2<int> newPos(head.x + newx, head.y + newy);
    if (!checkCollision(*this, newPos) &&
        !checkCollision(otherSnake, newPos))
    {
        addPos(newPos.x, newPos.y);
        mStatus = 1;
    }
    else
    {
        if (checkDead(head.x, head.y))
        {
            static const float grey[]   = { 0.4f, 0.4f, 0.4, 1.0 };
            mColor = grey;
        }
        mStatus = 2;
    }
}




bool CPong::move(const CVector2<int>& bait, const CPong& otherSnake)
{
    bool hasEaten = false;
    if (mStatus > 0)
    {
        const CVector2<int>& head = mBody.back();

        if (mDirectionNext.size() > 0)
        {
            mDirection = mDirectionNext.front();
            mDirectionNext.pop_front();
        }


        switch (mDirection)
        {
            case ESnakeDir::LEFT:
                testMove(head, otherSnake, -1, 0);
                break;

            case ESnakeDir::RIGHT:
                testMove(head, otherSnake, 1, 0);
                break;

            case ESnakeDir::UP:
                testMove(head, otherSnake,0, -1);
                break;

            case ESnakeDir::DOWN:
                testMove(head, otherSnake, 0, 1);
            break;
        }
        if (mStatus == 1)
        {
            if (head == bait)
            {
                hasEaten = true;
            }
            else
            {
                mBody.pop_front();
            }
        }
    }
    return hasEaten;
}


int CPong::move(const std::vector<CVector2<int>>& baits, const CPong& otherSnake)
{
    int eatenBait = -1;
    if (mStatus > 0)
    {
        const CVector2<int>& head = mBody.back();

        if (mDirectionNext.size() > 0)
        {
            mDirection = mDirectionNext.front();
            mDirectionNext.pop_front();
        }


        switch (mDirection)
        {
            case ESnakeDir::LEFT:
                testMove(head, otherSnake, -1, 0);
                break;

            case ESnakeDir::RIGHT:
                testMove(head, otherSnake, 1, 0);
                break;

            case ESnakeDir::UP:
                testMove(head, otherSnake,0, -1);
                break;

            case ESnakeDir::DOWN:
                testMove(head, otherSnake, 0, 1);
            break;
        }
        if (mStatus == 1)
        {
            for (int i = 0; i < baits.size(); i++)
            {
                if (head == baits[i])
                {
                    eatenBait = i;
                    break;
                }
            }

            if (eatenBait < 0)
            {
                mBody.pop_front();
            }
        }
    }
    return eatenBait;
}


void CPong::draw(const CSprite* const* sprites, float scale) const
{
    int i = 0;
    glColor4fv(mColor);
    for (auto it = mBody.begin(); it != mBody.end(); ++it, ++i)
    {
        const int posx = it->x * 48;
        const int posy = (21-it->y) * 48;
        if (i == mBody.size()-1)
        {
            sprites[mDirection]->draw(posx, posy, scale);
        }
        else
        {
            sprites[4]->draw(posx, posy, scale);
        }
    }
}

bool CPong::hasKoor(const CVector2<int>& tkoor) const
{
    for (auto it = mBody.begin(); it != mBody.end(); ++it)
    {
        if (*it == tkoor) return true;
    }
    return false;
}


bool CPong::checkCollision(const CPong& snake2, int newx, int newy) const
{
    CVector2<int> head(newx, newy);
    return checkCollision(snake2, head);
}

bool CPong::checkCollision(const CPong& snake2, const CVector2<int>& head) const
{
    if ((head.x == 0) || (head.y == 0) ||
        (head.x == FIELD_SIZE_X-1) || (head.y == FIELD_SIZE_Y-1))
    {
        return true;
    }

    for (auto it = snake2.mBody.begin(); it != snake2.mBody.end(); ++it)
    {
        if (*it == head) return true;
    }
    return false;
}


bool CPong::checkDead(int newx, int newy) const
{

    return ((checkCollision(*this, newx-1, newy)) &&
            (checkCollision(*this, newx+1, newy)) &&
            (checkCollision(*this, newx,   newy-1)) &&
            (checkCollision(*this, newx,   newy+1)));

}



bool CPong::compareDir(ESnakeDir newdir) const
{
    if (mDirectionNext.size() > 0)
    {
        return newdir != mDirectionNext.back();
    }
    return true;
}

void CPong::changeDir(ESnakeDir newdir)
{
    switch (mDirection)
    {
        case ESnakeDir::LEFT:
        case ESnakeDir::RIGHT:
            if ((newdir == ESnakeDir::UP) || (newdir == ESnakeDir::DOWN))
            {
                if (compareDir(newdir))
                {
                    mDirectionNext.push_back(newdir);
                    std::cout << "mDirectionNext.size()=" << mDirectionNext.size() << std::endl;
                }
            }
            break;

        case ESnakeDir::UP:
        case ESnakeDir::DOWN:
            if ((newdir == ESnakeDir::LEFT) || (newdir == ESnakeDir::RIGHT))
            {
                if (compareDir(newdir))
                {
                    mDirectionNext.push_back(newdir);
                    std::cout << "mDirectionNext.size()=" << mDirectionNext.size() << std::endl;
                }
            }
            break;

    }
}


