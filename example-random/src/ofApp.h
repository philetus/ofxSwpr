#pragma once

#include "ofMain.h"
#include "ofxSwpr.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);

    static glm::vec3 randInRect(float x, float y, float w, float h) {
        float rx = ofRandom(x, x + w);
        float ry = ofRandom(y, y + h);
        return glm::vec3(rx, ry, 0);
    }
    static glm::vec3 randInRect(const ofRectangle &r) {
        return randInRect(r.x, r.y, r.width, r.height);
    }
    
    ofRectangle bounds;
    ofxSwpr::Swpr swpr;
    bool touched;
};
