#pragma once
#ifndef PSCENE_RESULT_H
#define PSCENE_RESULT_H

#include "PSceneBase.h"

class PSceneResult:public PSceneBase{
	ofImage _img_hint;
	ofImage _img_stamp;
	ofImage _img_circle;
public:
	PSceneResult(ofApp* set_):PSceneBase(set_){
		_order_scene=3;
		_mlayer=2;

		_img_hint.loadImage("img/hint_watch.png");

		_img_stamp.loadImage("img/img-08.png");
		_img_circle.loadImage("img/img-09.png");

		setup();
	}
	void drawLayer(int i){

		auto text_rec_=_ptr_app->_textgroup.getRect();
				
		switch(i){
			case 0:
				// draw frame
				_ptr_app->drawFrameVideo(0);
				// draw text
				_ptr_app->_textgroup.draw();
				
				ofPushMatrix();
				ofTranslate(text_rec_.getBottomRight());
					// draw circle
					_img_circle.draw(0,0);

					ofTranslate(50,50);
					// draw name
					_img_stamp.draw(0,0);

					// TODO
					PCharacter::Font.drawString(_ptr_app->_user_name,0,0);
				ofPopMatrix();

				

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
		_ptr_app->updateFrameVideo(0);
	}
	void init(){
		PSceneBase::init();
		_ptr_app->startFrameVideo(0);
	}



};



#endif