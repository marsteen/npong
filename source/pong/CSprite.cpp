//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CSprite.cpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <cgl/NGLprimitives.h>
#include <pong/CSprite.h>

bool CSprite::load(const char* filename)
{
    return mTexture.LoadTexture(filename, nullptr);
}


void CSprite::draw(float posx, float posy, const float& scale) const
{

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mTexture.mTexHandle);
    
    CVector2<float> offpos(posx - mBorders.left * scale, posy - mBorders.top * scale);
    
    CRectT<float> vrc(offpos.x, offpos.y, offpos.x + mTexture.mTexWidth * scale, offpos.y + mTexture.mTexHeight * scale);
    NGLprimitives::DrawTexture(&vrc);
}
