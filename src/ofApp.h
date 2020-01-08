#pragma once

#define DRAW_DEBUG_INFO

#include "ofMain.h"
#include "ofxLibwebsockets.h"
#include "ofxHapPlayer.h"
#include "ofxDSHapVideoPlayer.h "

#include "PParameter.h"
#include "PSceneBase.h"
#include "PCharacter.h"

#define MSTAGE 4
#define MVIDEO_FRAME 3

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
		ofxDSHapVideoPlayer _dshap_player[MVIDEO_FRAME];
		
		list<string> _string_to_update;
		PTextGroup _textgroup;


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

};
