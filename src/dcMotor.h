#ifndef DCMOTOR_H
#define DCMOTOR_H
#include "ofMain.h"
#include "ofxOsc.h"



class dcMotor
{
    public:
        dcMotor(int theNumber,string name,string address,int positionX,int positionY, string sendIP, int sendPort);
        ~dcMotor();
        void draw();
        void update();
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
        void sendOneFloat(float value);
        string getName();
        bool getMessageSended();//true if messageSended
        void setMessageSended(bool boolean);
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
        //OSC Var
        ofxOscSender oscSender;
        ofxOscMessage oscMessage;
        int oscSendPort ;
        string oscSendIP;
        string theOscAddress;
        bool messageSended;//true if sendOneFloat is called
};

#endif // DCMOTOR_H
