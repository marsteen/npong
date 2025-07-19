//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceDialog.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceDialog : public CG3DResourceImgRef
{
    public:

        CG3DResourceDialog()
        {
            mBoxRef = NULL;
        }


        void Draw(SG3DDrawParams* dp);
        void AddResRef(CG3DResource* res);

        int UnscaledWidth();
        int UnscaledHeight();

    protected:

        CG3DResourceBox* mBoxRef;
};
