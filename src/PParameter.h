#pragma once
#ifndef PPARAMETER_H
#define PPARAMETER_H


#include <codecvt>

#include "ofMain.h"
#include "ofxJSON.h"

class GlobalParam{

	static GlobalParam* _instance;	
	
public:
	static string ParamFilePath;	
    
	ofVec2f FramePosition;
	ofVec2f FrameSize;


	GlobalParam(){
		readParam();
	}
	static GlobalParam* GetInstance(){
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

		FramePosition=ofVec2f(_param["Frame"]["Pos"][0].asFloat(),_param["Frame"]["Pos"][1].asFloat());
		FrameSize=ofVec2f(_param["Frame"]["Size"][0].asFloat(),_param["Frame"]["Size"][1].asFloat());
		
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
