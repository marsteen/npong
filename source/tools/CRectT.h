//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CRectT.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CRECTT_H
#define CRECTT_H

#include <vector/CVector2.h>

template<class T>
class CRectT
{
    public:
    
	    CRectT() { Set(0.0, 0.0, 1.0, 1.0); }
   	    CRectT(T _left, T _top, T _right, T _bottom) 
   	    { Set(_left, _top, _right, _bottom); }

        void Set(T _left, T _top, T _right, T _bottom)
        {
            left = _left;
            top = _top;
            right = _right;
            bottom = _bottom;
        }


        bool InterSectRect(const CRectT* r2, CRectT* ri) const;
        bool InRect(T x, T y) const;
        bool InRect(const CVector2<T>& v) const;
        void TrimRect();
        void Show(const char* str) const;

        T Width() const { return right - left; }
        T Height() const { return bottom - top; }

        T left;
        T top;
        T right;
        T bottom;

    protected:

        bool IntersectLine(T A1, T B1, T A2, T B2, T* A3, T* B3) const;
};



#include <tools/CRectT.hpp>

#endif
