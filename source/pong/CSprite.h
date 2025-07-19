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

class CSprite : public CDataRect
{
public:

	CSprite()
	{
		mOffset.Set(-40.0f, -40.0f);
	}

	bool load(const char* filename);
	void draw(float posx, float posy, const float& scale) const;
	

	CVector2<float> mOffset;

	int witdh() const { return mTexture.mTexWidth; }
	int height() const { return mTexture.mTexHeight; }
	
	
protected:

	CGL_Texture mTexture;
};


#endif
