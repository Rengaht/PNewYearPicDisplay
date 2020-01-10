#pragma once
#ifndef PSCENE_HINT_H
#define PSCENE_HINT_H

#define INTERVAL_HINT_STAY 6000
#define INTERVAL_HINT_SCROLL 2000


#include "PSceneBase.h"
#include "ofxDSHapVideoPlayer.h"

class PSceneHint:public PSceneBase{
	ofImage _img_hint;
	ofxDSHapVideoPlayer _video;
	bool _video_finished;

	FrameTimer _timer_scroll;

public:
	PSceneHint(ofApp* set_):PSceneBase(set_){
		_order_scene=1;
		_mlayer=1;

		_img_hint.loadImage("img/hint_text.png");
		_video.load("video/mic_part_0428-0802.avi");
		_video.setLoopState(OF_LOOP_NORMAL);

		_timer_scroll=FrameTimer(INTERVAL_HINT_SCROLL,INTERVAL_HINT_STAY);

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:
				ofPushMatrix();
				ofTranslate(0,-ofGetHeight()*_timer_scroll.valEaseOut());
					_video.draw(GlobalParam::GetInstance()->FrameSize.x/2-_video.getWidth()/2,0,
								_video.getWidth(),GlobalParam::GetInstance()->FrameSize.y);
				ofPopMatrix();
				break;
			default:
				break;
		}
	}
	void update(float dt_){
		PSceneBase::update(dt_);
		_video.update();
		if(_video.getCurrentFrame()>=242){
			_video.setFrame(148);
		}

		_timer_scroll.update(dt_);


		if(!_video_finished && _timer_scroll.val()==1){
			_ptr_app->prepareStage(ofApp::PStage::PINPUT);
			_video_finished=true;
		}
	}
	void init(){
		PSceneBase::init();

		_video.setFrame(0);
		_video.play();
		_video_finished=false;
		
		_timer_scroll.restart();
	}



};



#endif