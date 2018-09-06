#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	this->image.load("images/chu-hi.png");

	for (int i = 0; i < ofGetHeight(); i++) 
	{
		this->y_noise.push_back(glm::vec3(0.f, 0.f, 0.f)); 
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	glm::vec3 noise_value;
	for (int y = 0; y < this->y_noise.size(); y++) {

		if (y % 25 == 0) { 
			
			for (int i = 0; i < 3; i++) {
				
				noise_value[i] = ofMap(ofNoise(i * 10, y * 0.05, ofGetFrameNum() * 0.03), 0, 1, -1, 1);

				if (noise_value[i] > 0.5) {

					noise_value[i] -= 0.5;
				}
				else if (noise_value[i] < -0.5) {

					noise_value[i] += 0.5;
				}
				else {

					noise_value[i] = 0.0;
				}
			}
		}

		this->y_noise[y] = noise_value;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->image, 1);
	this->shader.setUniform3fv("y_noise", &this->y_noise[0].x, ofGetHeight());

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}