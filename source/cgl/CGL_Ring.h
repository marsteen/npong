//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_Ring.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_RING_H
#define CGL_RING_H

class CGL_Ring : public CGL_Object
{
    public:

        void MakeObject();

        CVector3<float> mOrigin;
        int mSegments;
        float mRadius;
};

void CGL_Ring::MakeObject()
{
    CVector3<float> CirclePoint;
    float Alpha = 0;
    float AlphaPlus = 360.0 / mSegments;

    glBegin(GL_TRIANGLE_FAN);
    glVertex3fv(mOrigin.v());

    for (int i = 0; i <= mSegments; i++)
    {
        CirclePoint.x = (cos(Alpha) * mRadius) + mOrigin.x;
        CirclePoint.y = (sin(Alpha) * mRadius) + mOrigin.y;
        CirclePoint.z = mOrigin.z;
        glVertex3fv(CirclePoint.v());

        Alpha += AlphaPlus;
    }


    glEnd();
}

#endif
