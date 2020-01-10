#pragma once

#define DRAW_DEBUG_INFO
#define MSTAGE 4



#include "ofMain.h"
#include "ofxLibwebsockets.h"
#include "ofxHapPlayer.h"
#include "ofxDSHapVideoPlayer.h "

#include "PParameter.h"
#include "PSceneBase.h"
#include "PCharacter.h"



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
		
		void drawFrameVideo(int index_);
		void updateFrameVideo(int index_);
		void startFrameVideo(int index_,int frame_=0);
		void startFrameVideoLoop(int index_);
		void stopFrameVideo(int index_);

		list<string> _string_to_update;
		PTextGroup _textgroup;

		string _user_name;
		int _frame_type;

private:
		PStage _stage,_stage_pre,_stage_next;
		PSceneBase* _scene[MSTAGE];
		void loadScene();
		void onSceneInFinish(int &e);
		void onSceneOutFinish(int &e);
		void setStage(PStage set_);

		
		void clearWishText();
		void updateWishText(string set_);
		void drawWishText();

		ofxDSHapVideoPlayer _dshap_player[MVIDEO_FRAME];
		
};
