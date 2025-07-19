#ifndef CPong_H
#define CPong_H

#include <iostream>
#include <deque>
#include <vector>
#include <pong/CSprite.h>

enum ESnakeDir: int
{
	DOWN,
	RIGHT,
    UP,
	LEFT,
	NONE,
};

class CPong
{
public:


	CPong();
	void addPos(int x, int y);
	void reset();
	void testMove(const CVector2<int>& head, const CPong& otherSnake, int newx, int newy);
	bool move(const CVector2<int>& bait, const CPong& otherSnake);
	void draw(const CSprite* const* sprites, float scale) const;
	bool hasKoor(const CVector2<int>& tkoor) const;
	bool checkCollision(const CPong& snake2, int newx, int newy) const;
	bool checkCollision(const CPong& snake2, const CVector2<int>& head) const;
	bool checkDead(int newx, int newy) const;
	bool compareDir(ESnakeDir newdir) const;
	void changeDir(ESnakeDir newdir);

    int move(const std::vector<CVector2<int>>& baitsw, const CPong& otherSnake);


	int mNumber;
	bool mGetLonger;
	ESnakeDir mDirection;
	int mStatus;
	const float* mColor;

protected:

	std::deque<CVector2<int> > mBody;
	std::deque<ESnakeDir> mDirectionNext;

};

#endif

