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

		

		setup();
	}
	void drawLayer(int i){

				
		switch(i){
			case 0:
				//_ptr_app->_textgroup.draw(getLayerAlpha(0));
				//_ptr_app->drawFrameVideo(_ptr_app->_frame_type);
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
		/*_ptr_app->_textgroup.update(dt_);
		_ptr_app->updateFrameVideo(_ptr_app->_frame_type);*/
	}
	void init(){
		PSceneBase::init();
		/*_ptr_app->startFrameVideo(_ptr_app->_frame_type);
		_ptr_app->_textgroup.restartStamp();*/

		_ptr_app->_cur_pic->start();
	}
	void end(){
		PSceneBase::end();
	}



};



#endif