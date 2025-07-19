//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceRoot.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CG3DRESOURCEROOT_H
#define CG3DRESOURCEROOT_H

class CG3DResourceRoot : public CG3DResource
{
    public:

        void Rollover(CVector2<int>* Mouse)
        {
            CG3DResource::Rollover(&mDrawParams, Mouse, false);
        }


        void DrawRoot()
        {
            CG3DResource::Draw(&mDrawParams);
        }


        void BackDraw()
        {
            CG3DResource::BackDraw(&mDrawParams);
        }


        void FrontDraw()
        {
            CG3DResource::FrontDraw(&mDrawParams);
        }


        void AdjustRoot()
        {
            CG3DResource::Adjust(&mDrawParams);
        }


        void CalcAlignPosition();

        int UnscaledWidth()  { return mBrect.Width(); }
        int UnscaledHeight() { return mBrect.Height(); }
        void InitRoot(int w, int h)
        {
            mBrect.Set(0, 0, w, h);
            mDrawParams.mParentWidth = UnscaledWidth();
            mDrawParams.mParentHeight = UnscaledHeight();
        }


    protected:

        SG3DDrawParams mDrawParams;
        CRectT<int> mBrect;
};

#endif
