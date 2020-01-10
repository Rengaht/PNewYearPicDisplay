#pragma once
#ifndef P_CHARACTER_H
#define P_CHARACTER_H

#define PTEXT_UPDATE_INTERVAL 100
#define PTEXT_IN_INTERVAL 1000
#define PTEXT_DELAY_INTERVAL 100

#define PTEXT_MCOLUMN 4
#define PTEXT_MROW 5

#define PTEXT_FONT_SIZE 100
#define PTEXT_WIDTH 1.2

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "FrameTimer.h"
#include "PParameter.h"
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
			ofTranslate(_pos.x*PTEXT_FONT_SIZE*PTEXT_WIDTH,_pos.y*PTEXT_FONT_SIZE*PTEXT_WIDTH);
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
			p_=getNextPos(p_);
		}
	}
	void udpateText(wstring wstr_){
		
		//wstring wstr_=GlobalParam::utf82ws(set_);
		int len=wstr_.length();
		for(int i=0;i<len;++i){
			
			string char_=GlobalParam::ws2utf8(wstr_.substr(i,1));

			if(i<_text.size()){
				_text[i].updateChar(char_);
			}else{
				_text.push_back(PCharacter(char_,getNextPos()));
			}
		}
		
	}
	void updatePos(ofVec2f set_){


	}
	ofVec2f getFirstPos(){
		return (*_text.begin()).getPos();
	}	
	ofVec2f getLastPos(){
		return _text.back().getPos();
	}
	ofVec2f getNextPos(){		
		return getNextPos(_text.back().getPos());
	}
	ofVec2f getNextPos(ofVec2f t){
		if(t.x<PTEXT_MCOLUMN-1){
			t.x++;
		}else{
			t.x=0;
			t.y++;
		}
		return t;
	}

	void draw(){
		for(int i=0;i<_text.size();++i) _text[i].draw();
	}
	void update(float dt_){
		for(int i=0;i<_text.size();++i) _text[i].update(dt_);
	}

};

class PTextGroup{
	public:
		vector<PTextLine> _text;
		PTextGroup(){
			PCharacter::Font.loadFont("font/font1.otf",PTEXT_FONT_SIZE);
		}
		void draw(){
			ofPushMatrix();
			ofTranslate(GlobalParam::GetInstance()->FrameSize.x/2-PTEXT_FONT_SIZE*PTEXT_WIDTH*PTEXT_MCOLUMN/2,200);

			if(_text.size()>0)
				for(auto& v:_text) v.draw();

			ofPopMatrix();
			
		}
		void update(float dt_){
			if(_text.size()>0)
				for(auto& v:_text) v.update(dt_);			
		}
		/*void updateText(string set_){
			auto text_=ofSplitString(set_,"|");
			for(int i=0;i<text_.size();++i){
				if(i<getRowCount()) updateLine(i,text_[i]);
				else addLine(text_[i]);
			}
		}*/
		void updateText(string set_){
			
			wstring wstr_=GlobalParam::utf82ws(set_);
			int len=wstr_.length();

			int mline=ceil((float)len/(float)PTEXT_MCOLUMN);

			for(int i=0;i<mline;++i){
				if(i<getRowCount()) updateLine(i,wstr_.substr(i*PTEXT_MCOLUMN,min(PTEXT_MCOLUMN,len-PTEXT_MCOLUMN*i)));
				else addLine(wstr_.substr(i*PTEXT_MCOLUMN,min(len-i*PTEXT_MCOLUMN,PTEXT_MCOLUMN)));
			}

		}
		void reset(){
			_text.clear();
		}
		int getRowCount(){
			return _text.size();
		}
		ofRectangle getRect(){

			// TODO
			return ofRectangle(0,0,500,800);
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
	