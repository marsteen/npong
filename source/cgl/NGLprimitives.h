//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	NGLprimitives.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef NGLPRIMITIVES_H
#define NGLPRIMITIVES_H

#include <tools/CRectT.h>

namespace NGLprimitives
{
    void DrawRect(const CRectT<float>* vrc);

    void DrawRect(const CRectT<float>* vrc, const CRectT<float>* trc);
    void DrawRect(const CRectT<double>* vrc, const CRectT<float>* trc, bool yFlipped = false);

    void DrawFrame(const CRectT<int>* vrc);
    void DrawFrame(const CRectT<float>* vrc);
    void DrawFrame(const CRectT<double>* vrc);
    void DrawTexture(const CRectT<float>* vrc);

    void DrawLine(float VonX, float VonY, float BisX, float BisY);
    void DrawRectTranslated(const CRectT<float>* vrc, const CRectT<float>* nrc);
}

#endif
