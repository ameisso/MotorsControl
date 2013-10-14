#pragma once

#include "ofMain.h"
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
        int nbDcMotors;
        int nbStepperMotor;
        int nbMemory;
		//void createMotors();
		//void createSteppers();
        vector< ofPtr<dcMotor> > theDcMotors;
        vector< ofPtr<stepperMotor> > theSteppers;

        //OSC
        int oscSendPort;
        int oscReceivePort;
        string oscSendAddress;
        ofxOscReceiver thisOscReceiver;
        ofxOscMessage thisOscReceivedMessage;
        string wrongMess;//String that contain an osc message if it wasn't destined to this programm.


};
