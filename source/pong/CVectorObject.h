//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CVectorObject.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CVECTOROBJECT_H
#define CVECTOROBJECT_H

#include <vector/CVector3T.h>
#include <pong/SShapeParams.h>


#ifndef DEG_TO_RAD_H
#define DEG_TO_RAD_H

#define DEG_TO_RAD(x)		((x) / 57.29577951)
#define RAD_TO_DEG(x)		((x) * 57.29577951)

#endif


class CVectorObject
{
    public:

        CVectorObject();

        virtual void Draw() const = 0;

        void SetColor(float r, float g, float b, float a);

    protected:

        void TransformVertex(const CVector2<float>& v1, CVector2<float>& v2, const SShapeParams& sp);

        float mColor[4];
};

#endif
