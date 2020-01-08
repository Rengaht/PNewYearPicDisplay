#include "ofApp.h"
#include "PSceneSleep.h"
#include "PSceneHint.h"
#include "PSceneInput.h"
#include "PSceneResult.h"

ofxTrueTypeFontUC PCharacter::Font;


//--------------------------------------------------------------
void ofApp::setup(){
	
	//ofSetVerticalSync(true);
    //ofHideCursor();
	ofLog()<<"FramePosition= "<<GlobalParam::GetInstance()->FramePosition;

	loadScene();
	_stage_pre=PEMPTY;
	_stage=PSLEEP;
	_scene[_stage]->init();
	setStage(_stage);

	ofAddListener(PSceneBase::sceneInFinish,this,&ofApp::onSceneInFinish);
	ofAddListener(PSceneBase::sceneOutFinish,this,&ofApp::onSceneOutFinish);
	
	_millis_now=ofGetElapsedTimeMillis();

	client.connect("127.0.0.1",3000);
	client.addListener(this);


	
	soundStream.printDeviceList();
	int bufferSize = 256;
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetBackgroundColor(0);
	int dt_=ofGetElapsedTimeMillis()-_millis_now;
	_millis_now+=dt_;

	_scene[_stage]->update(dt_);

	
	while(_string_to_update.size()>0){
		
		_textgroup.updateText(_string_to_update.front());
		_string_to_update.pop_front();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//ofEnableAlphaBlending();

	ofPushMatrix();
	ofTranslate(GlobalParam::GetInstance()->FramePosition);

	ofPushStyle();
	ofSetColor(255);
	
		ofPushStyle();
		ofSetColor(255);
		ofDrawRectangle(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
		ofPopStyle();

		ofEnableAlphaBlending();
		_scene[_stage]->draw();
		//_dshap_player.draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
		//_hap_player.draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
	ofPopStyle();

	//ofPushStyle();
	//	ofSetColor(255,255,0);
	//	ofDrawCircle(200,200,2000*smoothedVol);
	//ofPopStyle();
	

	ofPopMatrix();

	
	

#ifdef DRAW_DEBUG_INFO
	ofPushStyle();
	ofSetColor(255,0,0);
		ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);
		//ofDrawBitmapString(_text_wish,10,20);
	ofPopStyle();
#endif

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key){
		case ' ':
			prepareStage(PStage(((int)_stage+1)%3));
			break;
		case 'f':
		case 'F':
			ofToggleFullscreen();
			break;
		case 'a':
			//_ws_client.send("hello of");
			break;
	}
}

//--------------------------------------------------------------
void ofApp::loadScene(){
	_scene[0]=new PSceneSleep(this);
	_scene[1]=new PSceneHint(this);
	_scene[2]=new PSceneInput(this);
	_scene[3]=new PSceneResult(this);

	
	
	_dshap_player[0].load("video/A.avi");
	_dshap_player[1].load("video/A.avi");
	_dshap_player[2].load("video/A.avi");

}
void ofApp::onSceneInFinish(int &e){
	ofLog()<<"Scene "<<e<<" In finish!";
}
void ofApp::onSceneOutFinish(int &e){
	ofLog()<<"Scene "<<e<<" Out finish!";
	setStage(_stage_next);	
}
void ofApp::prepareStage(PStage set_){
	
	if(set_==_stage_next) return;

	ofLog()<<"Preparing for stage "<<set_;
	_stage_next=set_;
	if(_stage!=PEMPTY) _scene[_stage]->end();

}
void ofApp::setStage(PStage set_){
	
	_scene[set_]->init();
	switch(set_){
		case PSLEEP:
			break;
		case PINPUT:
			_textgroup.reset();
			break;
		case PRESULT:
			break;
	}

	_stage=set_;
	ofLog()<<"Set Scene "<<set_;
}

//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"[ws] on connected"<<endl;	
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"[ws] on open"<<endl;

	client.send("hello from of!");
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"[ws] on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"[ws] on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
    cout<<"[ws] got message: "<<args.message<<endl;

	string message_=args.message;
	if(message_=="/home"){
		prepareStage(PSLEEP);		
	}else if(message_=="/start"){		
		prepareStage(PHINT);
	}else if(message_=="/again"){
		_textgroup.reset();	
	}else if(message_.find("/name")!=std::string::npos){		
		
		// TODO: parse name & frame

		prepareStage(PRESULT);
	}else{
		if(_stage==PINPUT) updateWishText(message_);
	}
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"[ws] got broadcast "<<args.message<<endl;
}
void ofApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		curVol += (input[i*2]*0.5)*(input[i*2]*0.5);
		curVol += (input[i*2+1]*0.5)*(input[i*2+1]*0.5);
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	//bufferCounter++;
	
}

void ofApp::clearWishText(){
	_textgroup.reset();
}

void ofApp::updateWishText(string set_){
	_string_to_update.push_back(set_);
}

void ofApp::drawWishText(){

}