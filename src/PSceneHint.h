#pragma once
#ifndef PSCENE_HINT_H
#define PSCENE_HINT_H

#include "PSceneBase.h"
#include "ofxDSHapVideoPlayer.h"

class PSceneHint:public PSceneBase{
	ofImage _img_hint;
	ofxDSHapVideoPlayer _video;
	bool _video_finished;
public:
	PSceneHint(ofApp* set_):PSceneBase(set_){
		_order_scene=1;
		_mlayer=2;

		_img_hint.loadImage("img/hint_text.png");
		_video.load("video/mic_part.avi");
		_video.setLoopState(OF_LOOP_NONE);

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:
				//ofPushStyle();
				//ofSetColor(255);
					//ofDrawRectangle(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
					_video.draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
				//ofPopStyle();
				break;
			case 1:
				//ofDrawBitmapString("Scene "+ofToString(_order_scene),0,10);
				_img_hint.draw(GlobalParam::GetInstance()->FrameSize.x/2-_img_hint.getWidth()/2,ofGetHeight()-MARGIN_BOTTOM-_img_hint.getHeight());
				break;
			default:
				break;
		}
	}
	void update(float dt_){
		PSceneBase::update(dt_);
		_video.update();

		if(!_video_finished && _video.getIsMovieDone()){
			_ptr_app->prepareStage(ofApp::PStage::PINPUT);
			_video_finished=true;
		}
	}
	void init(){
		PSceneBase::init();
		_video.play();
		_video_finished=false;
		// TODO: load latest pics
	}



};



#endif