//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGL_NGO_BlurShader.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGL_NGO_BLURSHADER_H
#define CGL_NGO_BLURSHADER_H

#include <shader/CGL_NGO_Shader.h>


class CGL_NGO_BlurShader : public CGL_NGO_Shader
{
    public:


        CGL_NGO_BlurShader()
        {
        }


    protected:

        void SetUniformShaders();
};


#endif
