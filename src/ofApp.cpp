#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    playerNameFont.load("00 Starmap Truetype.ttf",9);
    test = new Player(50,50,"sprites/Male/Male 01-1.png","Robotechnic");

    cout<<"Load map: "<<m.loadMap("maps/startMap.tmx")<<endl;

    zoom = 0;

    //m.draw(test->getX(),test->getY(),test->getX()+ofGetWidth(),test->getY()+ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetKeyPressed('z') || ofGetKeyPressed('Z')){
        test->move(Player::UP);
    }
    if (ofGetKeyPressed('s') || ofGetKeyPressed( 'S')){
        test->move(Player::DOWN);
    }
    if (ofGetKeyPressed('q') || ofGetKeyPressed('Q')){
        test->move(Player::LEFT);
    }
    if (ofGetKeyPressed('d') || ofGetKeyPressed( 'D')){
        test->move(Player::RIGHT);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    //draw map and mobs
    ofTranslate(-test->getX(),-test->getY(),zoom);
    m.draw(test->getX(),test->getY(),test->getX()+ofGetWidth(),test->getY()+ofGetHeight());

    //draw player
    ofTranslate(ofGetWidth()/2-SPRITE_SIZE/2,ofGetHeight()/2-SPRITE_SIZE/2,zoom);
    test->draw(playerNameFont);

    //draw fixed things (fps, ui...)
    ofTranslate(test->getX()-ofGetWidth()/2+SPRITE_SIZE/2,test->getY()-ofGetHeight()/2+SPRITE_SIZE/2,zoom);
    playerNameFont.drawString(ofToString(ofGetFrameRate()),10,10);
}

//--------------------------------------------------------------
//void ofApp::keyPressed(int key){

//}

////--------------------------------------------------------------
//void ofApp::keyReleased(int key){

//}

////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){

//}

////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){

//}

////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){

//}

////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){

//}

////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){

//}

////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){

//}

////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){

//}
