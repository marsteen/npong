//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResRef.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResource;
class CG3DResRef
{
    public:

        CG3DResRef()
        {
            mRef = NULL;
        }


        string mName;
        CG3DResource* mRef;
};
