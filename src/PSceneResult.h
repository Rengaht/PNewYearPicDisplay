#pragma once
#ifndef PSCENE_RESULT_H
#define PSCENE_RESULT_H

#include "PSceneBase.h"

class PSceneResult:public PSceneBase{
	ofImage _img_back;
public:
	PSceneResult(ofApp* set_):PSceneBase(set_){
		_order_scene=2;
		_mlayer=2;

		_img_back.loadImage("img/test-3.png");

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
	}



};



#endif