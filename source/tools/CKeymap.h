//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CKeymap.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CKeymap_H
#define CKeymap_H

class CKeymap
{
    public:

        CKeymap();

        static bool ReadMapFile(const char* filename);
        static int GetMappedKey(int key);

    protected:
};

#endif
