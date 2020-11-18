#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    playerNameFont.load("00 Starmap Truetype.ttf",9);
    test = new Player(50,50,"sprites/Male/Male 01-1.png","Robotechnic");

    cout<<"Load map: "<<m.loadMap("maps/startMap.tmx")<<endl;
    ofVec2f pos = m.getSpawn();
    ofLog()<<pos;
    test->setX(pos.x);
    test->setY(pos.y);

    zoom = 00;

   // m.draw(test->getX(),test->getY(),test->getX()+ofGetWidth(),test->getY()+ofGetHeight());
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
    m.updateAnimation();
    if (m.calcDeath(test->getX()+ofGetWidth()/2-SPRITE_SIZE/2,test->getY()+ofGetHeight()/2)){
        ofVec2f spawn = m.getSpawn();
        test->setX(spawn.x);
        test->setY(spawn.y);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

//    int time = ofGetElapsedTimeMillis();
    //draw map and mobs
    ofTranslate(-test->getX(),-test->getY(),zoom);
    m.draw(test->getX(),test->getY(),test->getX()+ofGetWidth(),test->getY()+ofGetHeight());


    //draw player
    ofTranslate(ofGetWidth()/2-SPRITE_SIZE/2,ofGetHeight()/2-SPRITE_SIZE/2,zoom);
    test->draw(playerNameFont);

    //draw fixed things (fps, ui...)
    ofTranslate(test->getX()-ofGetWidth()/2+SPRITE_SIZE/2,test->getY()-ofGetHeight()/2+SPRITE_SIZE/2);
    playerNameFont.drawString(ofToString(ofGetFrameRate()),10,10);
//    ofLog()<<ofGetElapsedTimeMillis()-time<<" "<<int(ofGetFrameRate());

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

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    //calculate ratio
    cout<<w<<" "<<h;
    cout<<ofGetWidth()<<" "<<ofGetHeight()<<endl;
}

////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){

//}

////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){

//}
