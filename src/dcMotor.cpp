#include "dcMotor.h"


dcMotor::dcMotor(int theNumber,string name,int positionX,int positionY,string sendIP, int sendPort)
{
    thisRefNumber=theNumber;
    thisName=name;
    thisPositionX=positionX;
    thisPositionY=positionY;
    cursorPosition=0;
    onMaster=false;
    controlChanged=false;
    oscSendIP=sendIP;
    oscSendPort=sendPort;
    oscSender.setup(sendIP,sendPort);
    cout<<"MOTOR : '"<<thisName<<"' @:"<<sendIP<<":"<<ofToString(sendPort)<<endl;
}
void dcMotor::draw()
{
//cursor
    ofSetColor(100,100,255);
    rectHeight=100;
    rectWidth=15;
    rectRoundRadius=0;
    ofNoFill();
    ofRectRounded(thisPositionX,thisPositionY,rectWidth,rectHeight,rectRoundRadius);
    //ofRect(thisPositionX,thisPositionY,rectWidth,rectHeight);
    ofSetColor(48,222,242);
    ofFill();
    ofRectRounded(thisPositionX+1,thisPositionY+rectHeight/2,rectWidth-3,-1*(cursorPosition/2),rectRoundRadius);
//MasterButtons
    if(onMaster==true)
    {
        ofFill();
        ofSetColor(48,222,242);
        ofRectRounded(thisPositionX,thisPositionY+rectHeight+10,rectWidth,rectWidth,rectRoundRadius);
    }
    else
    {
        ofNoFill();
        ofSetColor(100,100,255);
        ofRectRounded(thisPositionX,thisPositionY+rectHeight+10,rectWidth,rectWidth,rectRoundRadius);
    }
    //draw name
    ofSetColor(48,222,242);
    ofDrawBitmapString(thisName,thisPositionX,thisPositionY+rectWidth+rectHeight+25);
}
void dcMotor::setSpeed(float theValue)
{
    cursorPosition=theValue;
    setControlChange(true);
    //TODO send over OSC
    sendOneFloat("/1/M"+ofToString(thisRefNumber),theValue);
}
void dcMotor::setOnMaster(bool boolean)
{
    onMaster=boolean;
    setControlChange(true);
}
bool dcMotor::getOnMaster()
{
    return onMaster;
}
float dcMotor::getSavedSpeed()
{
    //cout<<"return"<<savedSpeed<<endl;
    return savedSpeed;
}
void dcMotor::saveCurrentSpeed()
{
    savedSpeed=cursorPosition;
    //cout<<"saved:"<<savedSpeed<<endl;
}
void dcMotor::checkMousePressed(int mouseX,int mouseY)
{
    if((mouseX>thisPositionX) & (mouseX<(thisPositionX+rectWidth)) & (mouseY>thisPositionY) & (mouseY<(thisPositionY+rectHeight)))
    {
        speedValue=ofMap(mouseY,thisPositionY+rectHeight,thisPositionY,-100,100);
        setSpeed(speedValue);
    }
    if((mouseX>thisPositionX) & (mouseX<(thisPositionX+rectWidth))& (mouseY>thisPositionY+rectHeight+10) & (mouseY<thisPositionY+rectHeight+10+rectWidth))
    {
        setOnMaster(!onMaster);
    }

}
float dcMotor::getSpeedValue()
{
    return speedValue;
}
int dcMotor::getRefNumber()
{
    return thisRefNumber;
}
bool dcMotor::getControlChange()
{
    return controlChanged;
}
void dcMotor::setControlChange(bool boolean)
{
    //cout<<"controlChanged "<<ofToString(controlChanged)<<endl;
    controlChanged=boolean;
}
string dcMotor::getName()
{
    return thisName;
}
dcMotor::~dcMotor()
{
    //dtor
}
void dcMotor::sendOneFloat(string address,float value)
{
    ofxOscMessage msgToSend = ofxOscMessage();
    msgToSend.setAddress(address);
    msgToSend.addFloatArg(value);
    oscSender.sendMessage(msgToSend);
    //cout<<"Sended : "<<value<<" @"<< address<< " on :"<<oscSendIP<<":"<<oscSendPort<<endl;
    messageSended=true;
}
void dcMotor::setMessageSended(bool boolean)
{
    messageSended=boolean;
}
bool dcMotor::getMessageSended()
{
    return messageSended;
}
