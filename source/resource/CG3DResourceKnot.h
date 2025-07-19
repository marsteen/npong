//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceKnot.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceKnot : public CG3DResource, public CG3DGroup
{
    public:

        void DisableRadioGroup()
        {
            if (mGroup >= 0)
            {
                mParent->DeactivateKnotGroup(this);
            }
        }


        int UnscaledWidth()  { return mParent->UnscaledWidth(); }
        int UnscaledHeight() { return mParent->UnscaledHeight(); }
};
