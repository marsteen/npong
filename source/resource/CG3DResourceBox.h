//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceBox.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceBox : public CG3DResource
{
    public:

        CG3DResourceBox();

        int UnscaledWidth()  { return mBrect.Width(); }
        int UnscaledHeight() { return mBrect.Height(); }

        void Draw(SG3DDrawParams* dp);
        void DrawBox(int RectNr, SG3DDrawParams* dp);

        bool HasStatus(int i)
        {
            return (mBoxColor != NULL) || (mFrameColor != NULL);
        }


        CRectT<int> mBrect;
        float* mBoxColor[3];
        float* mFrameColor[3];
        int mStdColor;

    protected:
};
