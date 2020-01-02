#pragma once
#ifndef PSCENE_SLEEP_H
#define PSCENE_SLEEP_H

#include "PSceneBase.h"

class PSceneSleep:public PSceneBase{
	ofImage _img_back;

public:
	PSceneSleep(ofApp* set_):PSceneBase(set_){
		_order_scene=0;
		_mlayer=2;

		_img_back.loadImage("img/test-1.png");

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:
				ofPushStyle();
				ofSetColor(255);
					ofDrawRectangle(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
					_img_back.draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
				ofPopStyle();
				break;
			case 1:
				ofDrawBitmapString("Scene "+ofToString(_order_scene),0,10);
				break;
			default:
				break;
		}
	}
	void update(float dt_){
		PSceneBase::update(dt_);
	}
	void init(){
		PSceneBase::init();
		// TODO: load latest pics
	}



};



#endif