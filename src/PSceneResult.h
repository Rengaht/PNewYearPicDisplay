#pragma once
#ifndef PSCENE_RESULT_H
#define PSCENE_RESULT_H

#include "PSceneBase.h"

class PSceneResult:public PSceneBase{
	ofImage _img_hint;
public:
	PSceneResult(ofApp* set_):PSceneBase(set_){
		_order_scene=3;
		_mlayer=2;

		_img_hint.loadImage("img/hint_watch.png");

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:
				// draw frame
				_ptr_app->_dshap_player[0].draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
				// draw text
				_ptr_app->_textgroup.draw();
				
				// draw name

				break;
			case 1:
				_img_hint.draw(GlobalParam::GetInstance()->FrameSize.x/2-_img_hint.getWidth()/2,ofGetHeight()-MARGIN_BOTTOM-_img_hint.getHeight());
				break;
			default:
				break;
		}
	}
	void update(float dt_){
		PSceneBase::update(dt_);
		_ptr_app->_textgroup.update(dt_);
		_ptr_app->_dshap_player[0].update();
	}
	void init(){
		PSceneBase::init();
		_ptr_app->_dshap_player[0].play();
	}



};



#endif