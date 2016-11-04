#include "ofApp.h"


void ofApp::setup() {
    ofSetVerticalSync(true);
    ofBackgroundHex(0xFFFF00);
    
    bounds.set((ofGetWidth()-500)/2, (ofGetHeight()-500)/2, 500, 500);
    
    int n = 10;
    for(int i=0; i<n; i++) {
        swpr.addVertex(randomPointInRect(bounds));
    }
}

void ofApp::update() {
    if(swpr.touched()) {
		swpr.update(); // regenerate voronoi & delaunay meshes
	}
}

void ofApp::draw() {

    // the bounds of all the points
    ofSetColor(90);
    ofNoFill();
    ofDrawRectangle(bounds);
    
    
    // draw the raw points
    for(int i=0; i<swpr.vrts.size(); i++) {
        ofSetColor(0);
        ofDrawCircle(swpr.vrts[i], 2);
    }
    
    swpr.drawVoronoi();
    swpr.drawDelaunay();
}

void ofApp::mousePressed(int x, int y, int button){
    swpr.addVertex(glm::vec3(x, y, 0));
}