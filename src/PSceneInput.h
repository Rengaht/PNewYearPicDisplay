#pragma once
#ifndef PSCENE_INPUT_H
#define PSCENE_INPUT_H

#include "PSceneBase.h"

class PSceneInput:public PSceneBase{
	ofImage _img_hint;
public:
	PSceneInput(ofApp* set_):PSceneBase(set_){
		_order_scene=2;
		_mlayer=2;

		_img_hint.loadImage("img/hint_text.png");

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:
				// draw wave
				_ptr_app->_wave_circle.draw();

				// draw text
				_ptr_app->_cur_pic->draw();
				break;
			case 1:
				_img_hint.draw(GlobalParam::Val()->Hint.x,GlobalParam::Val()->Hint.y,GlobalParam::Val()->Hint.width,GlobalParam::Val()->Hint.height);
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