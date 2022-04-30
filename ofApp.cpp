#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	
	string word = "Today 1952th Days";
	int sample_count = 180;
	auto noise_param = ofRandom(1000);
	auto word_size = this->font.getStringBoundingBox(word, 0, 0);
	vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);

	for (int i = 0; i < 4; i++) {

		ofRotateX(90);
		for (int word_index = 0; word_index < word_path.size(); word_index++) {

			vector<ofPolyline> outline = word_path[word_index].getOutline();

			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(word_size.getWidth() * 0.5, -word_size.getHeight() * 0.5, 80);
					auto rotation = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_param, location.x * 0.00085 + ofGetFrameNum() * 0.0035), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(word_size.getWidth() * 0.5, -word_size.getHeight() * 0.5, 80);
					auto rotation = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_param, location.x * 0.00085 + ofGetFrameNum() * 0.0035), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}