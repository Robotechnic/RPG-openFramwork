#include "ofAppRunner.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(800,400,OF_WINDOW);			// <-------- setup the GL context
                //1366,694
                //800,400
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
