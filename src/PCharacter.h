#pragma once
#ifndef P_CHARACTER_H
#define P_CHARACTER_H

#define PTEXT_UPDATE_INTERVAL 100
#define PTEXT_IN_INTERVAL 1000
#define PTEXT_DELAY_INTERVAL 100

#define PTEXT_MCOLUMN 4
#define PTEXT_MROW 5

#define PTEXT_FONT_SIZE 180
#define PTEXT_SPACING 1.5

#define PTEXT_TILT_ANGLE -5

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "FrameTimer.h"
#include "PParameter.h"
#include "PStampText.h"

class PCharacter{
public:
	static ofxTrueTypeFontUC Font;

	PCharacter(string set_char_,ofVec2f set_pos_,int delay=0){
		_timer_in=FrameTimer(PTEXT_IN_INTERVAL,delay);
		_timer_out=FrameTimer(PTEXT_UPDATE_INTERVAL);

		_timer_in.restart();

		_char=_char_update=set_char_;
		_pos=_pos_update=set_pos_;

		//ofAddListener(_timer_out.finish_event,this,&PCharacter::onTimerOutFinish);
	}
	void draw(){

		ofPushStyle();
		ofSetColor(0,255.0*_timer_in.valEaseIn());
		//ofSetColor(0);

		ofPushMatrix();
			ofTranslate(_pos.x*PTEXT_FONT_SIZE*PTEXT_SPACING,_pos.y*PTEXT_FONT_SIZE*PTEXT_SPACING);
			Font.drawString(_char,0,0);
		ofPopMatrix();

		ofPopStyle();
	}
	void update(float dt_){
		_timer_in.update(dt_);
		_timer_out.update(dt_);
		if(_timer_out.val()==1){
			_pos=_pos_update;
			_char=_char_update;
			_timer_out.reset();
		}
	}
	void updatePos(ofVec2f set_){
		_timer_in=FrameTimer(PTEXT_UPDATE_INTERVAL,PTEXT_UPDATE_INTERVAL);

		_pos_update=set_;
		_timer_in.restart();
		_timer_out.restart();
	}
	void updateChar(string set_){

		if(_char==set_) return;

		_timer_in=FrameTimer(PTEXT_UPDATE_INTERVAL,PTEXT_UPDATE_INTERVAL);
		_char_update=set_;
		
		_timer_in.restart();
		_timer_out.restart();
	}
	ofVec2f getPos(){ return _pos;}

private:
	ofVec2f _pos;
	ofVec2f _pos_update;

	FrameTimer _timer_in,_timer_out;
	string _char;
	string _char_update;

};
class PTextLine{
public:
	vector<PCharacter> _text;
	PTextLine(wstring wstr_,int start_col,int start_row){
		
		//wstring wstr_=GlobalParam::utf82ws(str_);
		int len=wstr_.length();
		
		ofVec2f p_(start_col,start_row);

		for(int i=0;i<len;++i){
			string char_=GlobalParam::ws2utf8(wstr_.substr(i,1));
			ofLog()<<"add char "<<char_;

			_text.push_back(PCharacter(char_,p_));
			p_.x++;
		}
	}
	void udpateText(wstring wstr_){
		
		//wstring wstr_=GlobalParam::utf82ws(set_);
		int len=wstr_.length();
		if(len<_text.size()){
			for(int i=0;i<_text.size()-len;++i) _text.pop_back();
		}

		for(int i=0;i<len;++i){
			
			string char_=GlobalParam::ws2utf8(wstr_.substr(i,1));

			if(i<_text.size()){
				_text[i].updateChar(char_);
			}else{
				ofVec2f pos_=_text.back().getPos();
				pos_.x++;
				_text.push_back(PCharacter(char_,pos_));
			}
		}
		
	}
	void updatePos(ofVec2f set_){


	}

	float getLastPosX(){
		return (float)_text.size()*PTEXT_FONT_SIZE*PTEXT_SPACING+getMarginSpace();
	}
	float getMarginSpace(){
		return ((float)PTEXT_MCOLUMN-(float)_text.size())/2*PTEXT_FONT_SIZE*PTEXT_SPACING;
	}
	void draw(){
		ofPushMatrix();
		ofTranslate(getMarginSpace(),0);
			for(int i=0;i<_text.size();++i) _text[i].draw();
		ofPopMatrix();
	}
	void update(float dt_){
		for(int i=0;i<_text.size();++i) _text[i].update(dt_);
	}

};

class PTextGroup{

		vector<PTextLine> _text;
		PStampText _stamp;
	public:
		
		PTextGroup(){
			PCharacter::Font.loadFont("font/font2.otf",PTEXT_FONT_SIZE);
			PStampText::Font.loadFont("font/font2.otf",PSTAMP_FONT_SIZE);
		}
		void draw(float alpha_=1.0f){
			ofPushMatrix();
			ofTranslate(GlobalParam::Val()->TextFrame.x,GlobalParam::Val()->TextFrame.y);

			ofPushMatrix();
			float scale_=getTextScale();
			auto r=getRect();
			ofTranslate(GlobalParam::Val()->TextFrame.width/2-r.width*scale_/2,GlobalParam::Val()->TextFrame.height/2-r.height*scale_/2);
			
			/* tilt */
			ofPushMatrix();
			if(_text.size()<3){
				ofTranslate(r.width*scale_/2,r.height*scale_/2);
				ofRotate(PTEXT_TILT_ANGLE);
				ofTranslate(-r.width*scale_/2,-r.height*scale_/2);
			}


				ofPushMatrix();
				ofScale(scale_,scale_);
					if(_text.size()>0)
						for(auto& v:_text) v.draw();
				ofPopMatrix();
			
			ofPopMatrix();

				ofPushMatrix();
				float last_wid=0;
				if(_text.size()>0) last_wid=_text.back().getLastPosX()*scale_;


				ofTranslate(last_wid,r.height*scale_);
					_stamp.draw(min(20.0f,GlobalParam::Val()->TextFrame.width-120-last_wid),20,alpha_);
				ofPopMatrix();

			ofPopMatrix();

			ofPopMatrix();
			
		}
		void update(float dt_){
			if(_text.size()>0)
				for(auto& v:_text) v.update(dt_);			

			_stamp.update(dt_);
		}
		/*void updateText(string set_){
			auto text_=ofSplitString(set_,"|");
			for(int i=0;i<text_.size();++i){
				if(i<getRowCount()) updateLine(i,text_[i]);
				else addLine(text_[i]);
			}
		}*/
		float getTextScale(){			
			
			auto rect_=getRect();

			return min(GlobalParam::Val()->TextFrame.width/rect_.width,GlobalParam::Val()->TextFrame.height/rect_.height);
		}

		void updateText(string set_){
			
			wstring wstr_=GlobalParam::utf82ws(set_);
			int len=wstr_.length();			
			
			int mline=ceil((float)len/(float)PTEXT_MCOLUMN);
			if(mline<_text.size()){
				for(int i=0;i<_text.size()-mline;++i) _text.pop_back();
			}

			for(int i=0;i<mline;++i){
				if(i<getRowCount()) updateLine(i,wstr_.substr(i*PTEXT_MCOLUMN,min(PTEXT_MCOLUMN,len-PTEXT_MCOLUMN*i)));
				else addLine(wstr_.substr(i*PTEXT_MCOLUMN,min(len-i*PTEXT_MCOLUMN,PTEXT_MCOLUMN)));
			}

		}
		void reset(){
			_text.clear();
			_stamp.reset();
		}
		int getRowCount(){
			return _text.size();
		}
		ofRectangle getRect(){
			
			if(_text.size()<1)  return ofRectangle(0,0,0,0);

			float tw=_text[0]._text.size()*PTEXT_FONT_SIZE*PTEXT_SPACING+_text[0].getMarginSpace();
			float th=_text.size()*PTEXT_FONT_SIZE*PTEXT_SPACING;
			
			return ofRectangle(0,0,tw,th);
		}

		void setStampText(string name_){
			_stamp.setText(name_);
		}
		void restartStamp(){
			_stamp.restart();
		}

		private:
			void addLine(wstring wstr_){
				
				if(wstr_.length()==0) return;

				int last_row=_text.size();
				_text.push_back(PTextLine(wstr_,0,last_row+1));

			}
			void updateLine(int idx_, wstring wstr_){
				_text[idx_].udpateText(wstr_);
			}


};

#endif
	