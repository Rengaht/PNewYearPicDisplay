#pragma once
#ifndef PSCENE_H
#define PSCENE_H

#include "ofMain.h"
#include "FrameTimer.h"

#define EASE_DUE 500
#define EASE_OFFSET 300

#include "PParameter.h"

class ofApp;

class PSceneBase{
	public:
		static ofEvent<int> sceneInFinish;
		static ofEvent<int> sceneOutFinish;

		static FrameTimer _timer_sleep;
		int _order_scene;

		enum SceneStatus {Init, Due, End};
		SceneStatus _status;

		ofApp* _ptr_app;

		PSceneBase(ofApp *set_ptr);
		~PSceneBase(){};

		void setup();

		virtual void draw();
		virtual void drawLayer(int i);

		virtual void init();
		virtual void end();
		virtual void update(float dt_);
		virtual void reset();
		bool _trigger_in,_trigger_out;

		vector<FrameTimer> _timer_in;
		vector<FrameTimer> _timer_out;
		int _mlayer;
    
		float getLayerAlpha(int layer_);
	



};


#endif
