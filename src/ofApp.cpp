#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofToggleFullscreen();
	ofHideCursor();

	ofSetCircleResolution(100);
	ofEnableSmoothing();
	soundPlayer.load("Bolero.mp3");
	soundPlayer.play();	
	soundPlayer.setPosition(0.25);

}

//--------------------------------------------------------------
void ofApp::update(){


	// update the sound playing system:
	ofSoundUpdate();

	color = soundPlayer.getPositionMS() /200;
	newColor = ofMap(color, 0, 500, 0, 255); 


	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++) {

		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}
}

//--------------------------------------------------------------

void ofApp::stripePattern() {
	ofSetColor(255, 255, 255, 100);
	ofSetLineWidth(2.0);
	ofFill();
	for (int i = 0; i < nBandsToGet; i++) {
		ofPushMatrix();
			ofRotate(i * (soundPlayer.getSpeed()*1000));
			ofTranslate(i *(fftSmoothed[i] * 200),0);
			ofLine(0, -150, 0, 150);
			ofRotate(soundPlayer.getPositionMS() / 200);
			ofDrawCircle(150, 150, 5);
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor colorOne(0 + newColor, 103, 158);
	ofColor colorTwo(177, 255, newColor);

	ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_LINEAR);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);	
		ofRotate(angle);
		stripePattern();

		ofPushMatrix();


		for (int i = 0; i < nBandsToGet; i++) {
			angle = ofMap((fftSmoothed[i] * 200), 0, 500, 0, 360);

			//reaction to the drums bam bam bam 
			if (fftSmoothed[i] * 200 >= 1) {
				ofFill();
				ofRotate(angle);
				ofSetColor(255, 255, 255, 3);
				ofSetLineWidth(5.0);
				ofDrawCircle(0, 0, 300+angle);
				
			}

			ofPushMatrix();
			ofNoFill(); 
			ofDrawCircle(0, 0, 400 + angle*20);
			ofPopMatrix();

			if (fftSmoothed[i] * 200 >= 200) {
				ofFill();
				ofSetColor(255, 255, 255);
				ofDrawRectangle(0, 0, fftSmoothed[i] * 200, fftSmoothed[i] * 200);
			} 

		}

		ofPopMatrix();
	ofPopMatrix();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
