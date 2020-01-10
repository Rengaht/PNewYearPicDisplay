#pragma once
#ifndef PWAVE_CIRCLE_H
#define PWAVE_CIRCLE_H

#define PWAVE_CIRCLE_RESOLUTION 256
#define PWAVE_CIRCLE_WIDTH 2

#define PWAVE_ROTATE_INTERVAL 2000
#define PWAVE_LIFE_INTERVAL 250

#define PWAVE_MAX_RAD 280
#define PWAVE_MIN_RAD 60
#define PWAVE_RAD_STEP 25

#define PWAVE_MAX_AMP 0.004
#define PWAVE_MIN_AMP 0.0001

#include "ofMain.h"
#include "FrameTimer.h"

class PCircle{
	ofMesh _mesh;
	FrameTimer _timer_in,_timer_out,_timer_rotate;
	float _rad;
	float _alpha;
	bool _show;

	void createMesh(float rad_){

		_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		
		float ang_=TWO_PI/(float)PWAVE_CIRCLE_RESOLUTION;

		for(int i=0;i<=PWAVE_CIRCLE_RESOLUTION;++i){

			_mesh.addVertex(ofVec2f(rad_*sin(ang_*i),rad_*cos(ang_*i)));
			_mesh.addVertex(ofVec2f((rad_-PWAVE_CIRCLE_WIDTH)*sin(ang_*i),(rad_-PWAVE_CIRCLE_WIDTH)*cos(ang_*i)));			

			float step_=(float)i/PWAVE_CIRCLE_RESOLUTION;
			/*if(step_<.5) step_*=2;
			else step_=1.0-(step_-.5)*2;*/
			step_=sin(step_*PI);

			_mesh.addColor(lerpColor(ofColor(209,46,83),ofColor(250,206,157),step_));
			_mesh.addColor(lerpColor(ofColor(209,46,83),ofColor(250,206,157),step_));
		}

	}
	ofColor lerpColor(ofColor from_, ofColor to_, float t){
		return ofColor(ofLerp(from_.r,to_.r,t),ofLerp(from_.g,to_.g,t),ofLerp(from_.b,to_.b,t));
	}
	void updateColor(float set_){
		_alpha=set_;
		for(int i=0;i<=PWAVE_CIRCLE_RESOLUTION;++i){
			float step_=(float)i/PWAVE_CIRCLE_RESOLUTION;
			step_=sin(step_*PI);
			
			_mesh.setColor(i*2,ofColor(lerpColor(ofColor(209,46,83),ofColor(250,206,157),step_),set_));
			_mesh.setColor(i*2+1,ofColor(lerpColor(ofColor(209,46,83),ofColor(250,206,157),step_),set_));
		}
	}
public:
	PCircle(float rad_){
		createMesh(rad_);
		_rad=rad_;

		_timer_rotate=FrameTimer(PWAVE_ROTATE_INTERVAL,ofRandom(PWAVE_ROTATE_INTERVAL));
		_timer_rotate.setContinuous(true);
		_timer_rotate.restart();

		_timer_in=FrameTimer(PWAVE_LIFE_INTERVAL);
		_timer_out=FrameTimer(PWAVE_LIFE_INTERVAL,PWAVE_LIFE_INTERVAL/2);
		
		_show=false;
	}
	
	void draw(){
		ofPushMatrix();
		ofRotate(360*_timer_rotate.valEaseInOut());
			_mesh.draw();
		ofPopMatrix();
	}
	void update(float dt_){
		_timer_rotate.update(dt_);

		_timer_in.update(dt_);
		_timer_out.update(dt_);
		
		updateColor(255.0*_timer_in.valEaseIn()*(1.0-_timer_out.valEaseOut()));
		
	}
	float getRad(){
		return _rad;
	}
	void startCircle(){
		if(!_show){			
			_timer_in.restart();
			_timer_out.reset();
			_show=true;
		}
	}
	void stopCircle(){
		if(_show){
			_show=false;
			_timer_out.restart();
			//_timer_in.stop();
		}		
	}
};

class PWaveCircle{

	vector<PCircle> _circle;

public:
	PWaveCircle(){
		int mcircle=floor((PWAVE_MAX_RAD-PWAVE_MIN_RAD)/PWAVE_RAD_STEP);
		float rad_=PWAVE_MIN_RAD;
		for(int i=0;i<mcircle;++i){
			_circle.push_back(PCircle(rad_));
			rad_+=PWAVE_RAD_STEP;
		}
	}
	void setAmp(float dt_){
		float dest_rad=ofMap(dt_,PWAVE_MIN_AMP,PWAVE_MAX_AMP,PWAVE_MIN_RAD,PWAVE_MAX_RAD,true);
		for(auto& c:_circle){
			if(c.getRad()<=dest_rad){
				c.startCircle();
			}else{
				c.stopCircle();
			}
		}
	}
	void reset(){

	}
	void draw(){
		ofPushMatrix();
		ofTranslate(GlobalParam::Val()->Screen.width/2,GlobalParam::Val()->Screen.height/2);
			for(auto& p:_circle) p.draw();
		ofPopMatrix();
	}
	void update(float dt_){
		for(auto& t:_circle) t.update(dt_);
	}
};

#endif