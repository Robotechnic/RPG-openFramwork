#include "zone.h"

Zone::Zone(vector <ofVec2f> basePoints ) :
    points(basePoints)
{

}

void Zone::calcRect(){

    for (ofVec2f p : this->points) {
        if (p.x < this->rect.x){
            this->rect.x = p.x;
        }
        if (p.y<this->rect.y){
            this->rect.y = p.y;
        }
    }
}

void Zone::draw(ofColor c){
    ofPath line;
    for (ofVec2f point : points) {
        line.lineTo(ofVec3f(point.x,point.y,0));
    }
    line.setColor(c);
    line.draw();
}

void Zone::addPoint(ofVec2f point){
    this->points.push_back(point);
}

bool Zone::inZone(ofVec2f point){
    bool colision = false;

    for (int i = 0; i < (int)this->points.size(); ++i) {
        ofVec2f curr = this->points.at(i);
        ofVec2f next = this->points.at(i+1 < (int)this->points.size() ? i+1 : 0 );

        if (((curr.y >= point.y && next.y < point.y) || (curr.y < point.y && next.y >= point.y)) &&
                (point.x < (next.x-curr.x)*(point.y-curr.y) / (next.y-curr.y)+curr.x)){
            colision = ! colision;
        }
    }
    return colision;
}
