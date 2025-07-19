//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	SG3DDrawParams.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

struct SG3DDrawParams
{
    SG3DDrawParams()
    {
        mPos.Set(0, 0);
        mScale.Set(1.0, 1.0);
    }


    CVector2<float> mPos;
    CVector2<float> mScale;
    float			mParentWidth;
    float			mParentHeight;
};
