#ifndef DCMOTOR_H
#define DCMOTOR_H
#include "ofMain.h"
#include "ofxOsc.h"
class dcMotor
{
    public:
        dcMotor(int theNumber,string name,int positionX,int positionY, string sendIP, int sendPort);
        virtual ~dcMotor();
        void draw();
        void setSpeed(float theValue);
        void setOnMaster(bool boolean);
        bool getOnMaster();
        void saveCurrentSpeed();
        float getSavedSpeed();
        float getSpeedValue();
        int getRefNumber();
        void checkMousePressed(int mouseX,int mouseY);
        bool getControlChange();
        void setControlChange(bool boolean);
        string getName();
    protected:
    private:
        int thisRefNumber;
        string thisName;
        int thisPositionX;
        int thisPositionY;
        int cursorPosition;
        bool onMaster;
        float savedSpeed;
        int rectWidth;
        int rectHeight;
        int rectRoundRadius;
        float speedValue;
        bool controlChanged;
        ofxOscSender oscSender;
};

#endif // DCMOTOR_H
