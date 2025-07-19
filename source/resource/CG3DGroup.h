//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DGroup.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DGroup
{
    public:

        CG3DGroup()
        {
            mGroup = -1;
            mProperties = EBTPROP_AUTOGROUP;
        }


        void SetProperty(int f, bool v)
        {
            mProperties.Set(f, v);
        }


        void SetGroup(int g) { mGroup = g; }
        int Group() { return mGroup; }
        void SetGroupParent(CG3DResource* gp) { mGroupParent = gp; }

    protected:

        int mGroup;                         // Gruppe
        CG3DResource* mGroupParent;
        CG3DStatus mProperties;             // Button properties
};
