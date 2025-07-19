//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CPlayfieldSegment.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#define CPLAYFIELDSEGMEMT_H
#define CPLAYFIELDSEGMEMT_H


class CPlayfieldSegmemt
{

    void Insert(const CVectorUnit* vu);
    bool Test(const CVectorUnit* vu);


  public:

    set<CVectorUnit*> mUnitSet;
};


void CPlayfieldSegmemt::Insert(const CVectorUnit* vu)
{
  mUnitSet.insert(vu);
}

bool Test(const CVectorUnit* vu)
{
  if (
}


#endif
