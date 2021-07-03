#include "ofApp.h"
float t = 0;

float startT = 0;
float recCounter = 0;

int frameCount = 0;
//--------------------------------------------------------------
void ofApp::setup() {

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
   // mesh.enableIndices();

    wireMesh.setMode(OF_PRIMITIVE_LINES);
    //wireMesh.enableIndices();

    ofSetFrameRate(60);

    fbo.allocate(2816, 1720, GL_RGB, 4);
    fbo.begin();
    ofClear(26.0f);
    fbo.end();

    ofEnableDepthTest();

    baseVertices = new ofVec3f[50*3];

    for (int i = 0; i < 50; i++) {
        ofVec3f v1 = ofVec3f(ofRandomf() * 350.0f, ofRandomf() * 200.0f, ofRandomf() * 25.0f);
        
        ofVec3f v2 = v1 + ofVec3f(ofRandomf() * 25.0f, ofRandomf() * 25.0f, ofRandomf() * 25.0f);

        ofVec3f v3 = (v1 + v2) / 2.0f + ofVec3f(ofRandomf() *25.0f, ofRandomf() * 25.0f, ofRandomf() * 25.0f);

        ofVec3f normal = (v1 - v2).cross(v1 - v3).normalize();

        ofColor c = ofColor(255.0f, 103.0f, 0.0f,215.0f);

        baseVertices[i*3] = ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000));
        baseVertices[i*3 + 1] = ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000));
        baseVertices[i*3 + 2] = ofVec3f(ofRandom(0, 100000), ofRandom(0, 100000), ofRandom(0, 100000));

        mesh.addVertex(v1);
        mesh.addColor(c);
        mesh.addNormal(normal);

        mesh.addVertex(v2);
        mesh.addColor(c);
        mesh.addNormal(normal);

        mesh.addVertex(v3);
        mesh.addColor(c);
        mesh.addNormal(normal);

    }


    ofEnableLighting();
    light.setup();
    light.enable();

}

//--------------------------------------------------------------
void ofApp::update(){

    

    if (startRec) {

        if(frameCount == 0)
            startT = ofGetFrameNum();

        frameCount++;

        if (frameCount <= 1200) {
            t = ofGetFrameNum()/ 500.0f;
        }
        else if (frameCount <= 2400) {
            t = (startT + 1200 - (frameCount - 1200)) / 500.0f;
        }
        else {
            startRec = false;
        }
    }
    else {
        t = ofGetFrameNum() / 500.0f;
    }

    int numVerts = mesh.getNumVertices();

    for (int i = 0; i < numVerts; ++i) {
        ofVec3f v = mesh.getVertex(i);
        ofVec3f timeOffsets = baseVertices[i];
        
        v.x += (ofSignedNoise(t  + timeOffsets.x)) * 0.85f;
        v.y += (ofSignedNoise(t + timeOffsets.y)) * 0.85f;
        v.z += (ofSignedNoise(t + timeOffsets.z)) * 0.85f;

        mesh.setVertex(i, v);
    }

    for (int i = 0; i < numVerts - 2; i = i + 3) {
        ofVec3f v1 = mesh.getVertex(i);
        ofVec3f v2 = mesh.getVertex(i + 1);
        ofVec3f v3 = mesh.getVertex(i + 2);

        ofVec3f normal = (v1 - v2).cross(v1 - v3).normalize();

        mesh.setNormal(i, normal);
        mesh.setNormal(i + 1, normal);
        mesh.setNormal(i + 2, normal);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    fbo.begin();

    ofBackground(26.0f);

    cam.begin();

    mesh.draw();

    fbo.end();

    ofBackground(0.0f);

    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());

    if (startRec) {
        ofPixels pixels;

        fbo.readToPixels(pixels);
        img.setFromPixels(pixels);

        img.save("render" + to_string(ofGetFrameNum()) + ".jpg");
    }

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key = 'h') {
        startRec = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}