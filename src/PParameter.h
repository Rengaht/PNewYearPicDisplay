#pragma once
#ifndef PPARAMETER_H
#define PPARAMETER_H


#include <codecvt>

#include "ofMain.h"
#include "ofxJSON.h"

#define MVIDEO_FRAME 3
#define VIDEO_FRAME_RESIZE 0.9
#define MAX_STAMP_TEXT 10

class GlobalParam{

	static GlobalParam* _instance;	
	
public:
	static string ParamFilePath;	
    
	ofRectangle Screen,Frame,Hint;
	ofRectangle TextFrame,TextOutput;

	vector<int> FrameLoopStart,FrameLoopEnd;
	vector<vector<int>> StampPattern;

	string StoreID;
	int LoadLimitCount;

	int GifSize;
	int GifFps;


	string FFmpegCmd,FFmpegFilter;
	string GifFolder[MVIDEO_FRAME];

	GlobalParam(){
		readParam();
	}
	static GlobalParam* Val(){
		if(!_instance)
			_instance=new GlobalParam();
		return _instance;
	}
	void readParam(){


		ofxJSONElement _param;
		bool file_exist=true;
		if(_param.open(ParamFilePath) ){
			ofLog()<<ParamFilePath+" loaded!";
		}else{
			ofLog()<<"Unable to load "+ParamFilePath+" check data/ folder!";
			file_exist=false;
			return;
		}

		Screen.x=_param["Screen"]["Pos"][0].asFloat();
		Screen.y=_param["Screen"]["Pos"][1].asFloat();
		Screen.width=_param["Screen"]["Size"][0].asFloat();
		Screen.height=_param["Screen"]["Size"][1].asFloat();

		Frame.width=_param["Frame"]["Size"][0].asFloat();
		Frame.height=_param["Frame"]["Size"][1].asFloat();
		Frame.x=Screen.width/2-Frame.width/2;
		Frame.y=_param["Frame"]["TopY"].asFloat();

		Hint.width=_param["Hint"]["Size"][0].asFloat();
		Hint.height=_param["Hint"]["Size"][1].asFloat();
		Hint.x=Screen.width/2-Hint.width/2;
		Hint.y=Screen.height-Hint.height-_param["Hint"]["BottomY"].asFloat();

		TextFrame.width=_param["TextFrame"]["Size"][0].asFloat();
		TextFrame.height=_param["TextFrame"]["Size"][1].asFloat();
		TextFrame.x=Screen.width/2-TextFrame.width/2;
		TextFrame.y=Frame.y+_param["TextFrame"]["Pos"][1].asFloat();

		TextOutput.width=_param["Gif"]["TextSize"][0].asFloat();
		TextOutput.height=_param["Gif"]["TextSize"][1].asFloat();
		TextOutput.x=_param["Gif"]["TextPos"][0].asFloat();
		TextOutput.y=_param["Gif"]["TextPos"][1].asFloat();

		for(int i=0;i<MVIDEO_FRAME;++i){
			FrameLoopStart.push_back(_param["Loop"][i]["start"].asInt());
			FrameLoopEnd.push_back(_param["Loop"][i]["end"].asInt());
		}

		for(int i=0;i<=MAX_STAMP_TEXT;++i){
			vector<int> vec_;
			int len=_param["StampPattern"][ofToString(i)].size();
			for(int j=0;j<len;++j){
				vec_.push_back(_param["StampPattern"][ofToString(i)][j].asInt());
			}
			StampPattern.push_back(vec_);
		}

		StoreID=_param["StoreID"].asString();
		LoadLimitCount=_param["LoadLimitCount"].asInt();

		GifFps=_param["Gif"]["Fps"].asInt();
		GifSize=_param["Gif"]["Size"].asInt();

		FFmpegCmd=_param["FFmpeg"]["Cmd"].asString();
		FFmpegFilter=_param["FFmpeg"]["Filter"].asString();
		for(int i=0;i<MVIDEO_FRAME;++i){
			GifFolder[i]=_param["Gif"]["Folder"][i].asString();
		}
	}

	static string ws2utf8(std::wstring &input){
		
		try{
			static std::locale loc("");
			auto &facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
			return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(input);
		}catch(exception& e){
			cout<<e.what();
		}
		return "";
	}

	static wstring utf82ws(std::string &input){
		try{
			std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8conv;
			return utf8conv.from_bytes(input);
		}catch(exception& e){
			cout<<e.what();
		}
		return wstring();
	}
};

#endif
