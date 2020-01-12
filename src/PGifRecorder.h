#pragma once
#ifndef PGIF_RECORDER_H
#define PGIF_RECORDER_H

#include "ofMain.h"    
#include "PParameter.h"

class PGifRecorder : public ofThread {    
	public:  
		ofEvent<string> gifFinish;
		string _user_id;
		int _frame_type;

		PGifRecorder(){
			_user_id="";
		}
		void setUserId(string set_,int frame_){
			_user_id=set_;
			_frame_type=frame_;
		}

		void threadedFunction(){
			 while(isThreadRunning()) {
				 if(_user_id.size()>0) createGif(_user_id,_frame_type);
			 }
		}
		void createGif(string set_,int frame_){
			
			string cmd=GlobalParam::Val()->FFmpegCmd
			+" -framerate "+ofToString(GlobalParam::Val()->GifFps)
			+" -i "+ofToDataPath("output/")+_user_id+".png"
			+" -i "+ofToDataPath("gif/"+GlobalParam::Val()->GifFolder[_frame_type]+"/")+ofToString(GlobalParam::Val()->GifFolder[_frame_type])+"%3d.png "
			+" -i "+ofToDataPath("gif/"+GlobalParam::Val()->GifFolder[_frame_type]+"/")+"palette.png "
			+GlobalParam::Val()->FFmpegFilter+" "
			+ofToDataPath("output/")+_user_id+".gif";
			ofLog()<<cmd;
			ofSystem(cmd);

			ofNotifyEvent(gifFinish,_user_id,this);

			_user_id="";
		}
};

#endif
