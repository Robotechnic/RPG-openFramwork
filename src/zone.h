#ifndef ZONE_H
#define ZONE_H

#include <ofVec2f.h>
#include <ofRectangle.h>
#include <vector>
#include <ofPath.h>

using namespace std;

class Zone
{
public:
    Zone(vector<ofVec2f> basePoints);
    void addPoint(ofVec2f point);
    bool inZone(ofVec2f point);
    void calcRect();
    void draw(ofColor c);


private:
    ofRectangle rect;
    vector <ofVec2f> points;
};

#endif // ZONE_H
