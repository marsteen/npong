//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorT.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CVECTORT_H
#define CVECTORT_H

template<class T, int D>
class CVector
{
    public:

        T v[D];

        CVector() { }
        CVector2<T, D> operator=(CVector2<T, D> v2);
        CVector2<T, D> operator+(CVector2<T, D> v2);
        CVector2<T, D> operator-(CVector2<T, D> v2);
        CVector2<T, D> operator*(CVector2<T, D> v2);
        CVector2<T, D> operator*(T f);
        void operator*=(T f);

        CVector2<T, D> operator+=(CVector2<T, D> v2);
        CVector2<T, D> operator-=(CVector2<T, D> v2);
        CVector2<T, D> operator/(T c);
        CVector2<T, D> operator/=(T c);

        T Betrag();
        void Normalize();
        void Reverse();
        void SubtractVector(CVector2<T, D>* v1, CVector2<T, D>* v2);


        bool operator==(CVector2<T, D>& v2)
        {
            for (int i = 0; i < D; i++)
            {
                if (v[i] != v2.v[i])
                {
                    return false;
                }
            }
            return true;
        }


        bool operator!=(CVector2<T>& v2)
        {
            return (x != v2.x) || (y != v2.y);
        }


        T Abstand(CVector2<T>* v1)
        {
            return (*this - *v1).Betrag();
        }


        T SkalarProdukt(CVector2<T>* v1);
};

#endif
