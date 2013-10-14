#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H
#include "ofMain.h"
#include "ofxOsc.h"
class stepperMotor
{
    public:
        stepperMotor(int theNumber,string name,int positionX,int positionY, string sendIp,int sendPort,int theNbSteps);
        virtual ~stepperMotor();
        void stepTo(int position);
        void draw();
        void checkMousePressed(int mouseX, int mouseY);
        bool getControlChange();
        void setControlChange(bool boolean);
        int getRefNumber();
        int getCurrentPosition();
        string getName();
    protected:
    private:
        int thisRefNumber;
        string thisName;
        int thisPositionX;
        int thisPositionY;
        int currentPosition; //Position reached by the stepper
        int thisRadius;//Radius value of the draw method
        int nbSteps;//nb steps for one complete rotation
        bool controlChanged;
        ofxOscSender oscSender;
};
#endif // STEPPERMOTOR_H
