#include "ofMain.h"
#include "ofApp.h"


GlobalParam* GlobalParam::_instance;
string GlobalParam::ParamFilePath="_param.json";


//========================================================================
int main( ){
	ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context

	//// this kicks off the running of my app
	//// can be OF_WINDOW or OF_FULLSCREEN
	//// pass in width and height too:
	ofRunApp(new ofApp());


	/*ofGLWindowSettings settings;
	settings.width = 1920;
	settings.height = 1080;
	settings.setGLVersion(3, 2);
	ofCreateWindow(settings);
	ofRunApp(new ofApp);*/
}
