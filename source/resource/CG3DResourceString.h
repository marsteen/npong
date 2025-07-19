//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceString.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceString : public CG3DResource
{
    public:

        CG3DResourceString()
        {
            static float sWhite[] = { 1.0, 1.0, 1.0, 1.0 };

            mFontRef = NULL;
            mColorRef = NULL;
            mOrigColor = sWhite;
        }


        int UnscaledWidth();
        int UnscaledHeight();

        void AddResRef(CG3DResource* res);
        void Draw(SG3DDrawParams* dp);
        void Draw(const char* str, CVector2<float>* Pos);
        void Draw(CVector2<float>* Pos);
        void Reset(int mode);


        string mText[8];
        CG3DResourceFont* mFontRef;     // Zeichensatz
        float* mColorRef;               // Farbe
        float* mOrigColor;              // Original-Farbe

    protected:

        char* GetText();
};
