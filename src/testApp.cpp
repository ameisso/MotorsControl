/*
OscCommands:
- Osc Current Value : /1/M{motor Number}
- On Master : /1/Master{motor Number}
- stepper /4/S{stepper Number}
- MemoryPlay : /2/playMemory{Memory Number}
- Memory Rec : /2/recMemory{Memory Number}
- EmergencyStop : /emerencyStop (if = 1 then stop all the dc motors)
- master fader : /1/Master

key pressed :
-Enter = emergencyStop
-r=reload
*/

//TODO : show msg received if no config file found

#include "testApp.h"
#include "ofxOsc.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(15);
    cout<<"***********************ControlMotorProgram*********************************"<<endl;
    readXmlSetup();
    thisOscReceiver.setup(oscReceivePort);
    ofSetWindowTitle("Remote");

    //Timeline
    timeline.setup();
    timeline.setOffset(ofVec2f(0,20));
    timeline.setDurationInSeconds(60); //TODO
    timeline.setLoopType(OF_LOOP_NORMAL);

    for(int i = 0; i < 2; i++)
    {
        timeline.addPage("Page "+ofToString(i));
        timeline.addCurves("test");
    }

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
void testApp::update()
{
    wrongMess="";
    messageReceived=false;//if no message received, set to false
    receiveOscMessage();
}

//--------------------------------------------------------------
void testApp::draw()
{
    ofBackground(0);
    //Top infos
    ofFill();
    ofRect(0,0,ofGetWindowWidth(),20);
    ofSetColor(0);
    string buffer="Listenning on port:"+ofToString(oscReceivePort)+wrongMess;
    if(configFileFound==false)
    {
        ofSetColor(255);
        buffer= "no config file found, it should be in /data/config.xml -->"+wrongMess;
    }
    ofDrawBitmapString(buffer, 10,14 );
    //Frame Activity square
    ofSetColor(232,210,42);
    if (frameActivitySquares==true)
    {
        frameActivitySquares=false;
        ofRect(ofGetWidth()-30,0,10,10);
        ofRect(ofGetWidth()-20,10,10,10);
        ofRect(ofGetWidth()-10,0,10,10);
    }
    else
    {
        frameActivitySquares=true;
        ofRect(ofGetWidth()-30,10,10,10);
        ofRect(ofGetWidth()-20,0,10,10);
        ofRect(ofGetWidth()-10,10,10,10);
    }
    //OSCactivity Squares
    oscSendedMessageStatus();//check if a message was sended
    if (messageReceived==true)
    {
        ofSetColor(255,0,0);
        ofRect(ofGetWidth()-40,10,10,10);
    }
    else
    {
        ofSetColor(0,0,0);
        ofRect(ofGetWidth()-40,10,10,10);
    }
    if (messageSended==true)
    {
        messageSended=false;
        ofSetColor(0,255,0);
        ofRect(ofGetWidth()-40,0,10,10);
    }
    else
    {
        ofSetColor(0,0,0);
        ofRect(ofGetWidth()-40,0,10,10);
    }
    //dc motors
    for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
        (*it)->draw();
    //steppers
    for(vector< ofPtr<stepperMotor> >::iterator it = theSteppers.begin(); it != theSteppers.end(); ++it)
        (*it)->draw();

    timeline.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    cout<<"keypressed : "<<hex<<key<<endl;
    if (key==0x0d)//Return
    {
        emergencyStop();
    }
    if (key==0x72|| key==0x52)//R or r
    {
        reloadXml();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
        (*it)->checkMousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    for(vector< ofPtr<stepperMotor> >::iterator it = theSteppers.begin(); it != theSteppers.end(); ++it)
        (*it)->checkMousePressed(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
void testApp::readXmlSetup()
{
    ofFile file;
    //TODO block the process if the file is not there or is corrupted....
    //Test the file existance throw an error if not
    if(file.doesFileExist("config.xml",true)==true)
    {
        cout<<"config.xml found"<<endl;
        cout<<"*****************************************************************"<<endl<<endl;
        configFileFound=true;
    }
    else
    {
        cout<<"no config.xml file, default receive port : 8000"<<endl;
        nbDcMotors=0;
        nbStepperMotor=0;
        nbMemory=0;
        //oscReceivePort=8000;
        //thisOscReceiver.setup(oscReceivePort);
        configFileFound=false;
        return;
    }

    file.open("config.xml");
    ofBuffer buffer=file.readToBuffer();
    ofXml configFile;
    configFile.loadFromBuffer(buffer.getText());
    configFile.setTo("osc");
    oscReceivePort=configFile.getIntValue("receivePort");
    cout<<"receivePort :"<<oscReceivePort<<endl;
    configFile.setTo("../dcMotor"); // go up and then down
    nbDcMotors=configFile.getNumChildren();
    cout<<"NB dcMotors : "<<nbDcMotors<<endl;
    for(int i=0; i<nbDcMotors; i++)
    {
        string name=configFile.getValue("motor["+ofToString(i)+"]/name");
        int sendPort=configFile.getIntValue("motor["+ofToString(i)+"]/sendPort");
        string sendIp=configFile.getValue("motor["+ofToString(i)+"]/sendIp");
        string address=configFile.getValue("motor["+ofToString(i)+"]/address");
        theDcMotors.push_back(ofPtr<dcMotor> (new dcMotor(i,name,address,30+30*i,30,sendIp,sendPort)));

    }
    cout<<endl<<"*****************************************************************"<<endl<<endl;
    configFile.setTo("../stepperMotor");
    nbStepperMotor=configFile.getNumChildren();
    cout<<"NB StepperMotors : "<<nbStepperMotor<<endl;
    for(int i=0; i<nbStepperMotor; i++)
    {
        string name=configFile.getValue("stepper["+ofToString(i)+"]/name");
        int sendPort=configFile.getIntValue("stepper["+ofToString(i)+"]/sendPort");
        string sendIp=configFile.getValue("stepper["+ofToString(i)+"]/sendIp");
        int nbSteps=configFile.getIntValue("stepper["+ofToString(i)+"]/nbSteps");
        string address=configFile.getValue("stepper["+ofToString(i)+"]/address");
        theSteppers.push_back(ofPtr<stepperMotor> (new stepperMotor(i,name,address,nbDcMotors*30+80+120*i,100,sendIp,sendPort,nbSteps)));
    }
    //TODO : Read Memory informations.
    file.close();
    buffer.clear();
    configFile.clear();
    cout<<endl<<"*****************************************************************"<<endl;
    cout<<"XML files read, objects created"<<endl << endl;
}
void testApp::receiveOscMessage()
{
    while(thisOscReceiver.hasWaitingMessages())
    {
        thisOscReceiver.getNextMessage(&thisOscReceivedMessage);
        messageReceived=true;
        if(thisOscReceivedMessage.getAddress()=="/emergencyStop")
        {
            cout<<"received an emergency stop from OSC"<<endl;
            emergencyStop();
        }
        for(int i = 0; i < thisOscReceivedMessage.getNumArgs(); i++)
        {
            cout<<"Received "<<thisOscReceivedMessage.getArgAsFloat(0)<<" on"<<thisOscReceivedMessage.getAddress()<<endl;
            if(thisOscReceivedMessage.getAddress()=="/1/Master")
            {
                float value=thisOscReceivedMessage.getArgAsFloat(0);
                for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
                {
                    if((*it)->getOnMaster()==true)
                    {
                        (*it)->setSpeed(value);
                    }
                }
            }
            for (int i=0; i<nbDcMotors; i++)

            {
                if(thisOscReceivedMessage.getAddress()=="/1/M"+ofToString(i))
                {
                    float value=thisOscReceivedMessage.getArgAsFloat(0);
                    theDcMotors[i]->setSpeed(value);
                }
                else if(thisOscReceivedMessage.getAddress()=="/1/stop"+ofToString(i))
                {
                    float value=thisOscReceivedMessage.getArgAsFloat(0);
                    if (value==0.0)
                    {
                        theDcMotors[i]->setSpeed(0);
                    }
                }
                else if(thisOscReceivedMessage.getAddress()=="/1/Master"+ofToString(i))
                {
                    float value=thisOscReceivedMessage.getArgAsFloat(0);
                    if (value==0.0)
                    {
                        theDcMotors[i]->setOnMaster(false);
                    }
                    else
                    {
                        theDcMotors[i]->setOnMaster(true);
                    }
                }
                else
                {
                    wrongMess="!!!received "+ofToString(thisOscReceivedMessage.getArgAsFloat(0))+"on"+thisOscReceivedMessage.getAddress();
                }


            }
            for (int i=0; i<nbStepperMotor; i++)
            {
                if(thisOscReceivedMessage.getAddress()=="/4/S"+ofToString(i))
                {
                    float value=thisOscReceivedMessage.getArgAsFloat(0);
                    theSteppers[i]->stepTo(value);
                }
            }
        }
    }

}
void testApp::oscSendedMessageStatus()
{
    for(vector< ofPtr<dcMotor> >::iterator it = theDcMotors.begin(); it != theDcMotors.end(); ++it)
    {
        if((*it)->getMessageSended()==true)
        {
            (*it)->setMessageSended(false);
            messageSended=true;
        }
    }
    for(vector< ofPtr<stepperMotor> >::iterator it = theSteppers.begin(); it != theSteppers.end(); ++it)
    {
        if((*it)->getMessageSended()==true)
        {
            (*it)->setMessageSended(false);
            messageSended=true;
        }
    }
}
void testApp::emergencyStop()
{
    for(int i=0; i<nbDcMotors; i++)
    {
        theDcMotors[i]->setSpeed(0);
    }
}
void testApp::reloadXml()
{
    cout<<"reload app from XML"<<endl;
//emergencyStop();//stop all the dcMotors...already done in the dtor
    while(theDcMotors.size()!=0)
    {
        theDcMotors.pop_back();
    }
    while(theSteppers.size()!=0)
    {
        theSteppers.pop_back();
    }
    while(theMemories.size()!=0)
    {
        theMemories.pop_back();
    }
    readXmlSetup();
}

