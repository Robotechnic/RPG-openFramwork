#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    playerNameFont.load("00 Starmap Truetype.ttf",9);
    test = new Player(50,50,"sprites/Male/Male 01-1.png","Robotechnic");

    cout<<"Load map: "<<m.loadMap("maps/startMap.tmx")<<endl;
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
    m.draw(0,0,ofGetWidth(),ofGetHeight());
    test->draw(playerNameFont);
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
