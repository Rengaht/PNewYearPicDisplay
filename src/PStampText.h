#pragma once
#ifndef PSTAMP_TEXT_H
#define PSTAMP_TEXT_H

#define PSTAMP_FONT_SIZE 80

#define STAMP_INTERVAL 800
#define STAMP_BORDER 8.0
#define STAMP_SCALE .75

#define CIRCLE_INTERVAL 1000

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#include "PParameter.h"
#include "FrameTimer.h"

class PStampText{
	
	wstring _text;
	vector<int> _pattern;
	FrameTimer _timer_in;
	FrameTimer _timer_circle;
	
	float _mgrid;
	float _grid_width;

	
public:
	static ofxTrueTypeFontUC Font;
	static ofImage _img;
	static ofImage _img_circle;

	PStampText(){
		_timer_in=FrameTimer(STAMP_INTERVAL,CIRCLE_INTERVAL);
		_timer_circle=FrameTimer(CIRCLE_INTERVAL);
	
	}
	void draw(float dx, float dy,float alpha_=1){
		draw(dx,dy,_timer_circle.valEaseOut(),_timer_in.valEaseOut(),alpha_);
	}
	void draw(float dx,float dy,float valcircle_,float valin_,float alpha_=1){
		
		
		if(_text.size()<1) return;

		ofPushStyle();
		ofSetColor(255,255*alpha_*valcircle_);

			ofPushMatrix();
			ofTranslate(-20,-20);
				_img_circle.draw(0,0);
				ofPushStyle();
				/*ofSetColor(255,0,0);
					ofDrawCircle(0,0,100);
				ofPopStyle();*/
			ofPopMatrix();

		ofPopStyle();
		
		
		ofPushMatrix();
		ofTranslate(dx,dy);
		
		alpha_*=valin_;
		ofPushStyle();
		ofSetColor(255,255*alpha_);

		float ascale_=ofMap(valin_,0,1,3,STAMP_SCALE,true);
		ofTranslate(_img.getWidth()/2,_img.getHeight()/2);
		ofScale(ascale_,ascale_);
		ofTranslate(-_img.getWidth()/2,-_img.getHeight()/2);
		
		_img.draw(0,0);

		/*ofPushStyle();
		ofSetColor(255,255,0);
			ofDrawCircle(0,0,100);
		ofPopStyle();*/

		ofTranslate(STAMP_BORDER,STAMP_BORDER);
		ofPushStyle();
		ofSetColor(246,235,225,255*alpha_);
			

			int index_=0;
			for(int i=0;i<_mgrid;++i){

				float tw=_grid_width;
				float th=_img.getHeight()/_pattern[i];
				for(int j=0;j<_pattern[i];++j){
					
					string char_=GlobalParam::ws2utf8(_text.substr(index_,1));
					auto r=Font.getStringBoundingBox(char_,0,0);
					float sx=(tw-STAMP_BORDER*2)/r.width;
					float sy=(th-STAMP_BORDER*2)/r.height;
					ofPushMatrix();
					ofTranslate(tw*i,th*j);
					ofScale(sx,sy);
						Font.drawString(char_,-r.x,-r.y);
					ofPopMatrix();

					index_++;
				}
			}
		ofPopStyle();

		ofPopMatrix();

		ofPopStyle();
	}
	void update(float dt_){
		_timer_in.update(dt_);
		_timer_circle.update(dt_);
	}
	void setText(string set_){
		_text=GlobalParam::utf82ws(set_);		
		int len=ofClamp(_text.size(),0,MAX_STAMP_TEXT);
		_pattern=GlobalParam::Val()->StampPattern[len];

		_mgrid=_pattern.size();
		_grid_width=(_img.getWidth()-STAMP_BORDER*2)/(float)_mgrid;

		
	}
	void restart(){
		_timer_in.restart();
		_timer_circle.restart();
	}
	void reset(){
		_timer_in.reset();
		_timer_circle.reset();
		_text.clear();
	}
	void setFinish(){
		_timer_in.setVal(1);
		_timer_circle.setVal(1);
	}
};

#endif