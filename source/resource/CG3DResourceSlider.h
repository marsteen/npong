//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CG3DResourceSlider.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

class CG3DResourceSlider : public CG3DResourceButton
{
    public:

        void SetSliderLimits(float Slmin, float Slmax)
        {
            mSliderMin = Slmin;
            mSliderMax = Slmax;
        }


        EG3DSliderType mSliderType;
        float mSliderPos;
        float mSliderMin;
        float mSliderMax;
};
