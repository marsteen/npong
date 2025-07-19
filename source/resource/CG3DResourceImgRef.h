//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceImgRef.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceImgRef : public CG3DResource
{
    public:

        CG3DResourceImgRef()
        {
            mImgRef = NULL;
            mStdImage = 0;     // Standard-Image
        }


        bool Check() { return mImgRef != NULL; }

        CG3DResourceImage* mImgRef;   // Image reference

        int UnscaledWidth();
        int UnscaledHeight();

        int mStdImage;
};
