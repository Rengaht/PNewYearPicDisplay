#pragma once
#ifndef PSCENE_SLEEP_H
#define PSCENE_SLEEP_H

#define INTERVAL_PIC_STAY 10000
#define INTERVAL_PIC_SCROLL 2000
#define SCROLL_MARGIN 200

#include "PSceneBase.h"

class PSceneSleep:public PSceneBase{
	ofImage _img_hint;
	int _index_pic,_index_next;

	FrameTimer _timer_scroll;
	bool _flag_next_video;

	
public:
	PSceneSleep(ofApp* set_):PSceneBase(set_){
		_order_scene=0;
		_mlayer=2;

		_img_hint.loadImage("img/hint_start.png");

		_timer_scroll=FrameTimer(INTERVAL_PIC_SCROLL,INTERVAL_PIC_STAY);

		setup();
	}
	void drawLayer(int i){
		switch(i){
			case 0:

				// TODO: draw pics
				ofPushMatrix();
				ofTranslate(0,-(ofGetHeight())*_timer_out[0].valEaseInOut());

				ofTranslate(0,-(ofGetHeight()+SCROLL_MARGIN)*_timer_scroll.valEaseInOut());
						_ptr_app->drawFrameVideo(_index_pic);
					ofTranslate(0,(ofGetHeight()+SCROLL_MARGIN));
						if(_index_next!=_index_pic) _ptr_app->drawFrameVideo(_index_next);
				ofPopMatrix();

				//ofPushStyle();
				//ofSetColor(255);
				//	ofDrawRectangle(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
				//	//_img_back.draw(0,0,GlobalParam::GetInstance()->FrameSize.x,GlobalParam::GetInstance()->FrameSize.y);
				//ofPopStyle();

				break;
			case 1:
				ofPushMatrix();
				ofTranslate(0,-(ofGetHeight())*_timer_out[0].valEaseInOut());
					_img_hint.draw(GlobalParam::GetInstance()->FrameSize.x/2-_img_hint.getWidth()/2,ofGetHeight()-MARGIN_BOTTOM-_img_hint.getHeight());
				ofPopMatrix();
				break;
			default:
				break;
		}
	}
	void update(float dt_){
		PSceneBase::update(dt_);
		_ptr_app->updateFrameVideo(_index_pic);
		if(_index_next!=_index_pic) _ptr_app->updateFrameVideo(_index_next);

		_timer_scroll.update(dt_);

		if(_timer_scroll.pos()>=0 && !_flag_next_video){
			_flag_next_video=true;
			_ptr_app->startFrameVideoLoop(_index_next);
		}

		if(_timer_scroll.val()==1){
			
			_ptr_app->stopFrameVideo(_index_pic);
			_index_pic=_index_next;

			_index_next=(_index_pic+1)%3;						
			_flag_next_video=false;
			
			_timer_scroll.restart();			
		}
	}
	void init(){
		PSceneBase::init();
		
		// TODO: load latest pics

		_index_pic=0;
		_index_next=1;
		
		// start for loop
		_flag_next_video=false;
		_timer_scroll.restart();
		
		_ptr_app->startFrameVideoLoop(_index_pic);
		
	}

	void end(){
		PSceneBase::end();

	}


};



#endif