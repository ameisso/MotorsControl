#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H
#include "ofMain.h"
#include "ofxOsc.h"
class stepperMotor
{
    public:
        stepperMotor(int theNumber,string name,string address,int positionX,int positionY, string sendIp,int sendPort,int theNbSteps);
        virtual ~stepperMotor();
        void stepTo(int position);
        void draw();
        void checkMousePressed(int mouseX, int mouseY);
        bool getControlChange();
        void setControlChange(bool boolean);
        int getRefNumber();
        int getCurrentPosition();
        string getName();
        void sendOneFloat(float value);
        bool getMessageSended();//true if messageSended
        void setMessageSended(bool boolean);
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
        //OSC Var
        ofxOscSender oscSender;
        ofxOscMessage oscMessage;
        int oscSendPort ;
        string oscSendIP;
        string theOscAddress;
        bool messageSended;//true if sendOneFloat is called
};
#endif // STEPPERMOTOR_H
