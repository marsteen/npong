//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceTooltipp.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceTooltipp : public CG3DResourceBox
{
    public:

        CG3DResourceTooltipp();

        int UnscaledWidth()
        {
            return mContent->UnscaledWidth();
        }


        int UnscaledHeight()
        {
            return mContent->UnscaledHeight();
        }


        void AddResRef(CG3DResource* res);
        void Draw(SG3DDrawParams* dp);


    protected:

        CG3DResourceString* mContent;
};
