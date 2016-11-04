#pragma once

#include "ofMain.h"
#include "ofxSwpr.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);

    static glm::vec3 randomPointInRect(float x, float y, float w, float h, float padding=0) {
        float rx = ofRandom(x+padding, x+(w-padding*2));
        float ry = ofRandom(y+padding, y+(h-padding*2));
        return glm::vec3(rx, ry, 0);
    }
    static glm::vec3 randomPointInRect(const ofRectangle &r, float padding=0) {
        return randomPointInRect(r.x, r.y, r.width, r.height, padding);
    }
    
    ofRectangle bounds;
    ofxSwpr::ofxSwpr swpr;
};
