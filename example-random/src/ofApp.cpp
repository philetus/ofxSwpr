#include "ofApp.h"


void ofApp::setup() {
    ofSetVerticalSync(true);
    ofBackgroundHex(0xFFFF00);
    
    bounds.set((ofGetWidth()-500)/2, (ofGetHeight()-500)/2, 500, 500);
    
    int n = 10;
    for(int i=0; i<n; i++) {
        swpr.addSource(randInRect(bounds));
    }

    touched = false;
}

void ofApp::update() {
    if(touched) {
		swpr.update(); // regenerate voronoi & delaunay meshes
        touched = false;
	}
}

void ofApp::draw() {

    // the bounds of all the points
    ofSetColor(90);
    ofNoFill();
    ofDrawRectangle(bounds);
    
    // draw the raw points
    for(int i=0; i<swpr.srcs.size(); i++) {
        ofSetColor(0);
        ofDrawCircle(swpr.srcs[i], 2);
    }
    
    swpr.vrn.draw(OF_MESH_WIREFRAME);
}

void ofApp::mousePressed(int x, int y, int button){
    swpr.addSource(glm::vec3(x, y, 0));
    touched = true;
}