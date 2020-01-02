#pragma once

#define DRAW_DEBUG_INFO

#include "ofMain.h"
#include "PParameter.h"
#include "PSceneBase.h"
#include "ofxLibwebsockets.h"

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
		enum PStage{PSLEEP,PINPUT,PRESULT,PEMPTY};
		PStage _stage,_stage_pre,_stage_next;
		PSceneBase* _scene[3];

		void loadScene();
		void onSceneInFinish(int &e);
		void onSceneOutFinish(int &e);
		void prepareStage(PStage set_);
		void setStage(PStage set_);

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
		
		string _text_wish;
		
};
