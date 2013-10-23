#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "dcMotor.h"
#include "stepperMotor.h"
#include "memory.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void readXmlSetup();
        void receiveOscMessage();
        void oscSendedMessageStatus(); //set true if a message was sended,
        void emergencyStop();//function that stops all the dcmotors  (panicButton)
        void reloadXml();//function that stops all the movements and memories, destroy all the object and read the xmls again
    private :
        bool configFileFound;//bool tested in draw to write "file no found"
        int nbDcMotors;
        int nbStepperMotor;
        int nbMemory;
        //boolean that indicate if a message was received in this loop
        //in order to show an "activity square in the top right corner
        bool messageReceived;
        bool messageSended;
        bool frameActivitySquares;
		//void createMotors();
		//void createSteppers();
        vector< ofPtr<dcMotor> > theDcMotors;
        vector< ofPtr<stepperMotor> > theSteppers;
        vector< ofPtr<memory> > theMemories;
        //OSC
        int oscSendPort;
        int oscReceivePort;
        string oscSendAddress;
        ofxOscReceiver thisOscReceiver;
        ofxOscMessage thisOscReceivedMessage;
        string wrongMess;//String that contain an osc message if it wasn't destined to this programm.
        
        //Timeline
        ofxTimeline timeline;
};
