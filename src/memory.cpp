#include "memory.h"

memory::memory(int theNumber,string name,int positionX,int positionY)
{
    thisRefNumber=theNumber;
    thisName=name;
    thisPositionX=positionX;
    thisPositionY=positionY;
    setOnPlay(false);
    setOnRec(false);
    controlChanged=false;
    //todo send osc message to set the touch osc on no play
    cout<< "Memory "<<thisName<<endl;
}

memory::~memory()
{
    //dtor
}

void memory::draw()
{
    rectRoundRadius=0;
    rectWidth=15;

    //play/pause button
    if(isPlay==true)
    {
    ofFill();
    ofSetColor(100,100,255);
    ofRectRounded(thisPositionX,thisPositionY,rectWidth,rectWidth,rectRoundRadius);
    }
    else
    {
    ofNoFill();
    ofSetColor(100,100,255);
    ofRectRounded(thisPositionX,thisPositionY,rectWidth,rectWidth,rectRoundRadius);
    }

    //rec button
    if(isRec==true)
    {
    ofFill();
    ofSetColor(240,0,0);
    ofRectRounded(thisPositionX,thisPositionY+rectWidth+5,rectWidth,rectWidth/3,rectRoundRadius);
    }
    else
    {
    ofNoFill();
    ofSetColor(100,100,255);
    ofRectRounded(thisPositionX,thisPositionY+rectWidth+5,rectWidth,rectWidth/3,rectRoundRadius);
    }
}
void memory::reccord()
{
cout<<"rec"<<endl;
/*TODO :
create a file named mem+therefNumber
every 300ms log all the values of all the controllers

*/
}
void memory::play()
{
cout<<"play"<<endl;
/*TODO :

check if the file exist
open the file named mem+therefNumber
every 300ms set the controllers values.
*/
}
void memory::checkMousePressed(int mouseX, int mouseY)
{
    if((mouseX>thisPositionX) & (mouseX<(thisPositionX+rectWidth))& (mouseY>thisPositionY) & (mouseY<thisPositionY+rectWidth))
    {
        setOnPlay(!isPlay);
    }
    if((mouseX>thisPositionX) & (mouseX<(thisPositionX+rectWidth))& (mouseY>thisPositionY+rectWidth+5) & (mouseY<thisPositionY+rectWidth+5+rectWidth/3))
    {
        setOnRec(!isRec);
    }
}
void memory::setOnPlay(bool boolean)
{
    isPlay=boolean;
    controlChanged=true;
    if (boolean==true)
    {
    setOnRec(false);
    play();
    }
}
void memory::setOnRec(bool boolean)
{
    isRec=boolean;
    controlChanged=true;
    if (boolean==true)
    {
    setOnPlay(false);
    reccord();
    }
}
bool memory::getControlChange(){
return controlChanged;
}
void memory::setControlChange(bool boolean)
{
    cout<<"controlChanged "<<ofToString(controlChanged)<<endl;
    controlChanged=boolean;
}
int memory::getRefNumber()
{
    return thisRefNumber;
}
bool memory::getOnPlay()
{
    return isPlay;
}
bool memory::getOnRec()
{
    return isRec;
}
