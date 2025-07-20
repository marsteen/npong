//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSprite.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CSPRITE_H
#define CSPRITE_H

#include <graflib/CDataRect.h>
#include <cgl/CGL_Texture.h>
#include <vector/CVector3T.h>
#include <tools/CRectT.h>

class CSprite : public CDataRect
{
public:

	CSprite()
	{
		mBorders.Set(40.0f, 40.0f, 40.0f, 40.0f);
	}

	bool load(const char* filename);
	void draw(float posx, float posy, const float& scale) const;
	
	CRectT<float> mBorders;

	int width() const { return mTexture.mTexWidth; }
	int height() const { return mTexture.mTexHeight; }

	int logicalWidth() const { return mTexture.mTexWidth - (mBorders.left + mBorders.right); }
	int logicalHeight() const { return mTexture.mTexHeight - (mBorders.top + mBorders.bottom); }
	int posX(int posx) const { return posx - mBorders.left; }
	int posY(int posy) const { return posy - mBorders.top; }
	
protected:

	CGL_Texture mTexture;
};


#endif
