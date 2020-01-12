#pragma once

#define DRAW_DEBUG_INFO
#define MSTAGE 4



#include "ofMain.h"
#include "ofxLibwebsockets.h"
#include "ofxHttpUtils.h"


#include "PParameter.h"
#include "PSceneBase.h"
#include "PCharacter.h"
#include "PWaveCircle.h"
#include "PNewyearPic.h"

//#include "Websockets.h"
//#include <websocketpp/config/asio_no_tls_client.hpp>
//#include <websocketpp/client.hpp>

//typedef websocketpp::client client;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		
		/* Scene */
		enum PStage{PSLEEP,PHINT,PINPUT,PRESULT,PEMPTY};
		
		void prepareStage(PStage set_);
		
		
		int _millis_now;

		 ofxLibwebsockets::Client client;

		 // websocket methods
        void onConnect( ofxLibwebsockets::Event& args );
        void onOpen( ofxLibwebsockets::Event& args );
        void onClose( ofxLibwebsockets::Event& args );
        void onIdle( ofxLibwebsockets::Event& args );
        void onMessage( ofxLibwebsockets::Event& args );
        void onBroadcast( ofxLibwebsockets::Event& args );

		//websocketpp::client<websocketpp::config::asio_client> mClient;
		/*websocket*/
		//midnight::websocket::Client _ws_client;
		
		

		ofSoundStream soundStream;
		void audioIn(float * input, int bufferSize, int nChannels); 
		float smoothedVol;

		//ofxHapPlayer _hap_player;
		//ofVideoPlayer _video_player;
		
		

		list<string> _string_to_update;
		//void updateWishText(string set_);

		string _user_name;
		int _frame_type;
		
		PWaveCircle _wave_circle;

		vector<PNewYearPic> _list_pic;
		PNewYearPic *_cur_pic;

		ofxHttpUtils _http_utils;
		void urlResponse(ofxHttpResponse & response);

		void loadLatestPic();
		void pushCurrentPic();

		void sendJandiMessage(string message_);


private:
		PStage _stage,_stage_pre,_stage_next;
		PSceneBase* _scene[MSTAGE];
		void loadScene();
		void onSceneInFinish(int &e);
		void onSceneOutFinish(int &e);
		void setStage(PStage set_);

		
		
		

	
		
};
