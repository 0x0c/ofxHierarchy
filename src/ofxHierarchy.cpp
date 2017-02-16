//
//  ofxHierarchy.cpp
//  ofxHierarchy
//
//  Created by Akira Matsuda on 11/18/15.
//
//

#include <functional>
#include "ofxHierarchy.h"
#include "ofGraphics.h"
#include "ofBaseTypes.h"

namespace ofxHierarchy {
	View::View() : hidden(false), alpha(1), frame({0, 0, 0, 0}), rotation(0, 0, 0), scale(1, 1, 1), color(ofColor::white), superview(nullptr), will_draw(nullptr), drawable_content(nullptr), did_draw(nullptr) {}
	
	View::View(ofxHierarchy::Rect frame, std::function<void(ofxHierarchy::Rect *frame)> drawable_content) : hidden(false), alpha(1), color(ofColor::white), superview(nullptr), frame(frame), rotation(0, 0, 0), scale(1, 1, 1), will_draw(nullptr), drawable_content(nullptr), did_draw(nullptr) {
	}
	
	void View::add_subview(ofxHierarchy::View *v) {
		v->superview = this;
		this->subviews.push_back(v);
	}
	
	void View::draw() {
		if (!this->hidden) {
			if (this->will_draw) {
				this->will_draw(&this->frame);
			}
			
			ofPushMatrix();
			ofScale(scale.x, scale.y, scale.z);
			ofTranslate(this->frame.origin.x, this->frame.origin.y);
			ofRotateX(this->rotation.x);
			ofRotateY(this->rotation.y);
			ofRotateZ(this->rotation.z);
			ofSetColor(this->color.r, this->color.g, this->color.b, 255.0 * this->alpha);
			if (this->drawable_content) {
				this->drawable_content(&this->frame);
			}
			for (auto view : this->subviews) {
				view->draw();
			}
			ofPopMatrix();
			
			if (this->did_draw) {
				this->did_draw(&this->frame);
			}
		}
	}
	
	void View::setCenterX(float x) {
		this->frame.origin.x = x - this->frame.size.width / 2.0;
	}
	
	void View::setCenterY(float y) {
		this->frame.origin.y = y - this->frame.size.height / 2.0;
	}
	
	void View::setCenter(float x, float y) {
		this->setCenterX(x);
		this->setCenterY(y);
	}
	
	ofxHierarchy::Point View::center() {
		ofxHierarchy::Point p = {static_cast<float>(this->frame.origin.x + this->frame.size.width / 2.0), static_cast<float>(this->frame.origin.y + this->frame.size.height / 2.0)};
		
		return p;
	}
	
	bool View::hitTest(float x, float y) {
		bool result = false;
		if ((this->frame.origin.x < x && x < this->frame.origin.x + this->frame.size.width) && (this->frame.origin.y < y && y < this->frame.origin.y + this->frame.size.height)) {
			result = true;
		}
		
		return result;
	}
}
