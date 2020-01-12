#pragma once
#ifndef PNEWYEAR_PIC_H
#define PNEWYEAR_PIC_H


#include "ofMain.h"
#include "ofxDSHapVideoPlayer.h "

class PNewYearPic{

	
public:
	static ofxDSHapVideoPlayer _dshap_player[MVIDEO_FRAME];
	enum PicStatus {PINIT,PREADY};

	PicStatus _status;

	PNewYearPic(){
		_index=-1;
		_status=PINIT;
	}
	PNewYearPic(string wish_,string name_,int index_){
		_index=index_;
		_textgroup.updateText(wish_);
		_textgroup.setStampText(name_);

		_status=PREADY;
		_textgroup.setStampReady();
	}
	
	void updateText(string set_){
		_textgroup.updateText(set_);
	}
	void updateNameAndIndex(string set_,int index_){
		_textgroup.setStampText(set_);
		_index=index_;
		_status=PREADY;
	}

	void update(float dt_){
		_textgroup.update(dt_);
		if(_index>-1) updateFrameVideo(_index);
	}

	void resetText(){
		_textgroup.reset();	
	}

	void draw(){

		_textgroup.draw();
		drawFrameVideo(_index);

	}
	void stop(){
		stopFrameVideo(_index);
	}
	void start(){
		startFrameVideo(_index);
		_textgroup.restartStamp();
	}
	void startLoop(){
		startFrameVideoLoop(_index);
	}
	int getIndex(){
		return _index;
	}
private:
	int _index;
	PTextGroup _textgroup;

	void drawFrameVideo(int index_){

		if(index_<0 || index_>MVIDEO_FRAME) return;

		if(!_dshap_player[index_].isPlaying()) return;
		_dshap_player[index_].draw(GlobalParam::Val()->Frame.x,GlobalParam::Val()->Frame.y,
		GlobalParam::Val()->Frame.width,GlobalParam::Val()->Frame.height);
	}
	void updateFrameVideo(int index_){
		if(index_<0 || index_>MVIDEO_FRAME) return;

		_dshap_player[index_].update();
		if(_dshap_player[index_].getCurrentFrame()>=GlobalParam::Val()->FrameLoopEnd[index_]){
			_dshap_player[index_].setFrame(GlobalParam::Val()->FrameLoopStart[index_]);
		}
	}
	void startFrameVideo(int index_, int frame_=0){
		if(index_<0 || index_>MVIDEO_FRAME) return;

		_dshap_player[index_].setFrame(frame_);
		_dshap_player[index_].play();
	}
	void startFrameVideoLoop(int index_){
		if(index_<0 || index_>MVIDEO_FRAME) return;

		if(_dshap_player[index_].isPlaying()) return;
		startFrameVideo(index_,GlobalParam::Val()->FrameLoopEnd[index_]);		
	}
	void stopFrameVideo(int index_){
		if(index_<0) return;

		_dshap_player[index_].stop();
	}


};



#endif