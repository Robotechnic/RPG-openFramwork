#pragma once

#include "ofBaseApp.h"
#include "of3dGraphics.h"
#include "ofColor.h"
#include "ofTrueTypeFont.h"
#include "ofCamera.h"

#include "entity.h"
#include "player.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

//    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);

private:
    ofTrueTypeFont playerNameFont;

    Player *test;

};
