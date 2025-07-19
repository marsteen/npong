//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceFrame.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceFrame : public CG3DResource
{
    public:

        int UnscaledWidth()  { return mRect.Width(); }
        int UnscaledHeight() { return mRect.Height(); }

        CRectT<int> mRect;
};
