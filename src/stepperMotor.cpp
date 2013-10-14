#include "stepperMotor.h"

stepperMotor::stepperMotor(int theNumber,string name,int positionX,int positionY, string sendIp,int sendPort,int theNbSteps)
{
    thisRefNumber=theNumber;
    thisName=name;
    thisPositionX=positionX;
    thisPositionY=positionY;
    thisRadius=50;
    nbSteps=theNbSteps;
    currentPosition=0;
    oscSender.setup(sendIp,sendPort);
    cout<<"Stepper : '"<<thisName<<"' @:"<<sendIp<<":"<<ofToString(sendPort)<<" nbSteps="<<nbSteps<<endl;
}
void stepperMotor::stepTo(int position)
{
    currentPosition=position;
    controlChanged=true;
    //TODO : send the new position over OSC
    sendOneFloat("/4/S"+ofToString(thisRefNumber),position);
}
void stepperMotor::draw()
{
    ofNoFill();
    ofSetColor(100,100,255);
    ofCircle(thisPositionX,thisPositionY,thisRadius);
    ofSetColor(48,222,242);
    int theta=ofMap(currentPosition,0,nbSteps,0,360);
    theta+=270;
    int endX=thisPositionX+thisRadius*cos(theta*PI/180);
    int endY=thisPositionY+thisRadius*sin(theta*PI/180);
    ofLine(thisPositionX,thisPositionY,endX, endY);
    ofDrawBitmapString(ofToString(currentPosition),endX+5,endY+5);
    ofDrawBitmapString(thisName,thisPositionX-thisRadius+20,thisPositionY+thisRadius+15);
}
void stepperMotor::checkMousePressed(int mouseX,int mouseY)
{
    if((abs(mouseX-thisPositionX)<thisRadius)&(abs(mouseY-thisPositionY)<thisRadius))
    {
        //cout<<"we're in"<<thisRefNumber<<endl;
        float mousePosX=mouseX-thisPositionX;//absolute position of the Mouse from the center of the circle.
        float mousePosY=mouseY-thisPositionY;
        float angle=0;
        //cout<<"Y="<<mousePosY<<" X="<<mousePosX<<endl;
        if (mousePosX>0)
        {
            angle=atan(mousePosY/mousePosX);
        }
        else if (mousePosX<0)
        {
            angle=atan(mousePosY/mousePosX)+PI;
        }
        if ((mousePosX==0)&(mousePosY>0))
        {
            angle=PI/2;
        }
        if ((mousePosX==0)&(mousePosY<0))
        {
            angle=3*PI/4;
        }
        //cout<<"angle"<<angle*180/PI<<"° and "<<angle<<"rad"<<endl;
        stepTo(ofMap(angle,-PI/2,3*PI/2,0,nbSteps));
    }
}
void stepperMotor::setControlChange(bool boolean)
{
    controlChanged=boolean;
}
bool stepperMotor::getControlChange()
{
    return controlChanged;
}
int stepperMotor::getRefNumber()
{
    return thisRefNumber;
}
int stepperMotor::getCurrentPosition()
{
    return currentPosition;
}
string stepperMotor::getName()
{
    return thisName;
}
stepperMotor::~stepperMotor()
{
    //dtor
}
void stepperMotor::sendOneFloat(string address,float value)
{
    ofxOscMessage msgToSend = ofxOscMessage();
    msgToSend.setAddress(address);
    msgToSend.addFloatArg(value);
    oscSender.sendMessage(msgToSend);
    //cout<<"Sended : "<<value<<" @"<< address<< " on :"<<oscSendIP<<":"<<oscSendPort<<endl;
    messageSended=true;
}
void stepperMotor::setMessageSended(bool boolean)
{
    messageSended=boolean;
}
bool stepperMotor::getMessageSended()
{
    return messageSended;
}
