#include "testApp.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup(){
readXmlSetup();
thisOscReceiver.setup(oscReceivePort);
//nbDcMotors=14;
//nbStepperMotor=4;
//nbMemory=2;
//createMotors();
//createSteppers();
}
/*void testApp::createMotors(){
for (int i=0;i<nbDcMotors;i++){
    theDcMotors.push_back(ofPtr<dcMotor> (new dcMotor(i,"Motor"+ofToString(i),30+30*i,30)));
}
}*/
/*void testApp::createSteppers(){
for (int i=0;i<nbStepperMotor;i++){
    theSteppers.push_back(ofPtr<stepperMotor> (new stepperMotor(i,"Stepper"+ofToString(i),nbDcMotors*30+80+120*i,100,48)));
}
}*/
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);

    //frameRate
    ofDrawBitmapString(ofToString(ofGetFrameRate())+" fps", 20, ofGetWindowHeight() - 10);
    //dc motors
    for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
            (*it)->draw();
    //steppers
    for(vector< ofPtr<stepperMotor> >::iterator it = theSteppers.begin(); it != theSteppers.end(); ++it)
            (*it)->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
            (*it)->checkMousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    for(vector< ofPtr<stepperMotor> >::iterator it = theSteppers.begin(); it != theSteppers.end(); ++it)
            (*it)->checkMousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
void testApp::readXmlSetup()
{
    //TODO block the process if the file is not there or is corrupted....

    //Read "senders.xml" file and create the senders list
    ofFile file;
    file.open("config.xml");
    ofBuffer buffer=file.readToBuffer();
    ofXml configFile;
    configFile.loadFromBuffer(buffer.getText());
    configFile.setTo("osc");
    oscReceivePort=configFile.getIntValue("receivePort");
    //cout<<"receivePort :"<<oscReceivePort<<endl;
    configFile.setTo("../dcMotor"); // go up and then down
    int nbDcMotors=configFile.getNumChildren();
    //cout<<"NB dcMotors : "<<nbDcMotors<<endl;
    for(int i=0; i<nbDcMotors; i++)
    {
        string name=configFile.getValue("motor["+ofToString(i)+"]/name");
        int sendPort=configFile.getIntValue("motor["+ofToString(i)+"]/sendPort");
        string sendIp=configFile.getValue("motor["+ofToString(i)+"]/sendIp");
        theDcMotors.push_back(ofPtr<dcMotor> (new dcMotor(i,name,30+30*i,30,sendIp,sendPort)));
    }
    configFile.setTo("../stepperMotor");
    int nbStepperMotor=configFile.getNumChildren();
    //cout<<"NB dcMotors : "<<nbDcMotors<<endl;
    for(int i=0; i<nbStepperMotor; i++)
    {
        string name=configFile.getValue("stepper["+ofToString(i)+"]/name");
        int sendPort=configFile.getIntValue("stepper["+ofToString(i)+"]/sendPort");
        string sendIp=configFile.getValue("stepper["+ofToString(i)+"]/sendIp");
        int nbSteps=configFile.getIntValue("stepper["+ofToString(i)+"]/nbSteps");
        theSteppers.push_back(ofPtr<stepperMotor> (new stepperMotor(i,name,nbDcMotors*30+80+120*i,100,sendIp,sendPort,nbSteps)));
    }
    //TODO : Read Memory informations.
    file.close();
    buffer.clear();
    configFile.clear();
    cout<<"XML files read, objects created"<<endl << endl;
}
void testApp::receiveOscMessage(){
 while(thisOscReceiver.hasWaitingMessages())
    {
        thisOscReceiver.getNextMessage(&thisOscReceivedMessage);
        for(int i = 0; i < thisOscReceivedMessage.getNumArgs(); i++)
        {
            if(thisOscReceivedMessage.getAddress()=="/ECHO")
            {
                float echoTime=ofGetElapsedTimef()-thisOscReceivedMessage.getArgAsFloat(0);
                int echoRefNumber=thisOscReceivedMessage.getArgAsInt32(1);
                echoPointedAddress=thisOscReceivedMessage.getArgAsString(2);
                echoBuffer=" Echo from["+ofToString(echoRefNumber)+"]"+"in "+ofToString(echoTime)+"s";
                cout<<"echo received in "<<echoTime<<"s from "<<echoRefNumber<<endl;
                //cout<<"SendedFrom :"<<echoPointedAddress<<endl;

            }
        }
    }
}