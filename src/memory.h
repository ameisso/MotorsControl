#ifndef MEMORY_H
#define MEMORY_H
#include "ofMain.h"
#include "ofxOsc.h"
class memory
{
    public:
        memory(int theNumber,string name,int positionX,int positionY);
        virtual ~memory();
        void draw();
        void update();
        void reccord();
        void play();
        void checkMousePressed(int mouseX, int mouseY);
        void setOnPlay(bool boolean);
        bool getOnPlay();
        void setOnRec(bool boolean);
        bool getOnRec();
        void setControlChange(bool boolean);
        bool getControlChange();
        int getRefNumber();
    protected:
    private:
        int thisRefNumber;
        string thisName;
        int thisPositionX;
        int thisPositionY;
        bool isPlay;
        bool isRec;
        int rectRoundRadius;
        int rectWidth;
        bool controlChanged;
};

#endif // MEMORY_H
