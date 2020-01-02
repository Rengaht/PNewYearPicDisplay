#include "ofApp.h"
#include "PSceneSleep.h"
#include "PSceneInput.h"
#include "PSceneResult.h"


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
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetBackgroundColor(0);
	int dt_=ofGetElapsedTimeMillis()-_millis_now;
	_millis_now+=dt_;

	_scene[_stage]->update(dt_);

}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofPushMatrix();
	ofTranslate(GlobalParam::GetInstance()->FramePosition);

	ofPushStyle();
	ofSetColor(255);
		ofDrawRectangle(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
	ofPopStyle();

	_scene[_stage]->draw();

	ofPopMatrix();

#ifdef DRAW_DEBUG_INFO
	ofPushStyle();
	ofSetColor(255,0,0);
		ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);
		ofDrawBitmapString(_text_wish,10,20);
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
	_scene[1]=new PSceneInput(this);
	_scene[2]=new PSceneResult(this);

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

	_text_wish=args.message;

}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"[ws] got broadcast "<<args.message<<endl;
}
