#pragma once
#ifndef PSCENE_INPUT_H
#define PSCENE_INPUT_H

#include "PSceneBase.h"

class PSceneInput:public PSceneBase{
	ofImage _img_back;
public:
	PSceneInput(ofApp* set_):PSceneBase(set_){
		_order_scene=1;
		_mlayer=2;

		_img_back.loadImage("img/test-2.png");

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