#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
	ofEnableAlphaBlending();
    
    // load fragment shader files
    if (mDir.listDir(ofToDataPath("shader"))) {
        for (int i = 0; i < mDir.size(); i++) {
            mShaders.push_back(ofShader());
            assert(mShaders.back().load("shader_vert/test.vert", mDir.getPath(i)));
        }
    }
    
    mCurrent = 0;
    bInfo = true;
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0, 0);
    ofSetColor(255, 255, 255, 255);
    ofFill();
    
    mShaders[mCurrent].begin();
    
    float resolution[2];
    resolution[0] = ofGetWidth();
    resolution[1] = ofGetHeight();
    float time = ofGetElapsedTimef();
    float mousePos[2];
    mousePos[0] = (float)ofGetMouseX() / (float)ofGetWidth();
    mousePos[1] = -((float)ofGetMouseY() / (float)ofGetHeight()) + 1.;
    
    mShaders[mCurrent].setUniform1f("time", time);
    mShaders[mCurrent].setUniform2fv("resolution", resolution);
    mShaders[mCurrent].setUniform2fv("mouse", mousePos);

//    glEnable(GL_DEPTH_TEST);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(ofGetWidth(), 0);
    glVertex2f(0, ofGetWidth());
    glVertex2f(ofGetWidth(), ofGetHeight());
    glEnd();
    mShaders[mCurrent].end();
    
    if (bInfo) {
        stringstream s;
        s << "fps       : " << ofGetFrameRate() << endl;
        s << "shader id : " << mCurrent << endl;
        s << "filename  : " << mDir.getName(mCurrent) << endl;
        s << "time      : " << time << endl;
        s << "resolution: " << resolution[0] << "/" << resolution[1] << endl;
        s << "mouse pos : " << mousePos[0] << "/" << mousePos[1] << endl;
        s << "-----------------" << endl;
        s << "left/right key is change shader file" << endl;
        s << "f key is change fullscreen mode" << endl;
        s << "space key is visible/hide this infomation text";
        ofDrawBitmapStringHighlight(s.str(), 20, 20);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'f': ofToggleFullscreen(); break;
            
        case OF_KEY_LEFT:
            mCurrent = (mCurrent + 1) % mDir.size();
            break;
        case OF_KEY_RIGHT:
            --mCurrent;
            if (mCurrent < 0) mCurrent = mDir.size() - 1;
            break;
            
        case 'o':
            //TODO: open shader file
            break;
            
        case ' ':
            bInfo = !bInfo;
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
