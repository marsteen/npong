//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CFixpointT.hpp
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CFixpointT_HPP
#define CFixpointT_HPP

//typedef __int64 Tfixtype;
typedef long long Tfixtype;

template<int Tbits>
inline CFixpointT<Tbits> CFixpointT<Tbits>::operator*(const CFixpointT<Tbits> z)
{
    CFixpointT<Tbits> v;

    v.value = (Tfixtype(value) * z.value) >> Tbits;
    return v;
}


template<int Tbits>
inline CFixpointT<Tbits> CFixpointT<Tbits>::operator/(const CFixpointT<Tbits> z)
{
    CFixpointT<Tbits> v;

    v.value = (Tfixtype(value) << Tbits) / z.value;
    return v;
}


template<int Tbits>
inline CFixpointT<Tbits>& CFixpointT<Tbits>::operator*=(const CFixpointT<Tbits> z)
{
    value = (Tfixtype(value) * z.value) >> Tbits;
    return *this;
}


template<int Tbits>
inline CFixpointT<Tbits>& CFixpointT<Tbits>::operator/=(const CFixpointT<Tbits> z)
{
    value = (Tfixtype(value) << Tbits) / z.value;
    return *this;
}


#endif
