#include "ofApp.h"


void ofApp::setup() {
    ofSetVerticalSync(true);
    ofBackgroundHex(0xFFFF00);
    
    bounds.set((ofGetWidth()-500)/2, (ofGetHeight()-500)/2, 500, 500);
    
    int n = 10;
    for(int i=0; i<n; i++) {
        swpr.addSource(randInRect(bounds));
    }

    touched = true;
}

void ofApp::update() {
    if(touched) {

        // regenerate voronoi mesh
		swpr.diagram();

        // set cells to random colors
        for(std::size_t i = 0; i < swpr.clls.size(); i++) {
            swpr.clls[i].setColor(
                ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
        }

        swpr.mesh();
        touched = false;

	}
}

void ofApp::draw() {

    // the bounds of all the points
    ofSetColor(90);
    ofNoFill();
    ofDrawRectangle(bounds);
    
    // draw the voronoi mesh
    swpr.vrn.draw(OF_MESH_FILL);

    // draw the raw points
    for(int i=0; i<swpr.srcs.size(); i++) {
        ofSetColor(0);
        ofDrawCircle(swpr.srcs[i], 2);
    }
    
}

void ofApp::mousePressed(int x, int y, int button){
    swpr.addSource(glm::vec3(x, y, 0));
    touched = true;
}