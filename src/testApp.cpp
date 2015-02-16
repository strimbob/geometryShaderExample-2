#include "testApp.h"
ofImage img;
//--------------------------------------------------------------
void testApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	
	shader.setGeometryInputType(GL_LINES);
	shader.setGeometryOutputType(GL_POINT);
	shader.setGeometryOutputCount(4);
	shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl"); 
	
	printf("Maximum number of output vertices support is: %i\n", shader.getGeometryMaxOutputCount());
	fbo.allocate( ofGetWidth(), ofGetHeight() );
	// create a bunch of random points
	float r = ofGetHeight()/2;
	for(int i=0; i<100; i++) {
		points.push_back(ofPoint(ofRandomf() * r, ofRandomf() * r, ofRandomf() * r));
	}
	
	doShader = true;	
	ofEnableDepthTest();
    img.loadImage("dot.png");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofEnableDepthTest();
    ofEnableAlphaBlending;
	if(doShader) {
		shader.begin();
        cam.begin();
		shader.setUniformTexture("spark",img.getTextureReference(),0);
		// set thickness of ribbons
		shader.setUniform1f("thickness", 20);
		// make light direction slowly rotate
		shader.setUniform3f("lightDir", sin(ofGetElapsedTimef()/1), cos(ofGetElapsedTimef()/1), 0);
        shader.setUniform1f("imgWidth", (float)img.getWidth());
        shader.setUniform2f("iMouse", (float) ofGetMouseX(),  (float) ofGetMouseY() );
        shader.setUniform1f("imgHeight", (float)img.getHeight());
           shader.setUniform1f("time", (float)ofGetElapsedTimef());
        shader.setUniform3f("gCameraPos",cam.getPosition().x,cam.getPosition().y,cam.getPosition().z);
        
        
	}
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofColor(255);
	

	for(unsigned int i=1; i<points.size(); i++) {
		ofLine(points[i-1], points[i]);
	}
	cam.end();
	if(doShader) shader.end();
	
	ofPopMatrix();
	
	ofDrawBitmapString("fps: " + ofToString((int)ofGetFrameRate()) + "\nPress 's' to toggle shader: " + (doShader ? "ON" : "OFF"), 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if( key == 's' ){
		doShader = !doShader;
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

