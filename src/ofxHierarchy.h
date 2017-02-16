//
//  ofxHierarchy.h
//  ofxHierarchy
//
//  Created by Akira Matsuda on 11/18/15.
//
//

#ifndef ofxHierarchy_hpp
#define ofxHierarchy_hpp

#include <vector>
#include <functional>
#include "ofBaseTypes.h"
#include "ofPoint.h"

namespace ofxHierarchy {
	struct Size {
		float width;
		float height;
	};
	
	struct Point {
		float x;
		float y;
	};
	
	struct Rect {
		ofxHierarchy::Point origin;
		ofxHierarchy::Size size;
	};

	class View {
	public:
		View();
		View(ofxHierarchy::Rect frame, std::function<void(ofxHierarchy::Rect *frame)> drawable_content);
		~View() {};
		bool hidden;
		float alpha;
		ofColor color;
		ofVec3f scale;
		ofVec3f rotation;
		ofxHierarchy::Rect frame;
		View *superview;
		std::vector<ofxHierarchy::View *> subviews;
		std::function<void(ofxHierarchy::Rect *frame)> will_draw;
		std::function<void(ofxHierarchy::Rect *frame)> drawable_content;
		std::function<void(ofxHierarchy::Rect *frame)> did_draw;
		
		virtual void add_subview(ofxHierarchy::View *v);
		virtual void draw();
		void setCenterX(float x);
		void setCenterY(float y);
		void setCenter(float x, float y);
		float getMaxX() {
			return this->frame.origin.x + this->frame.size.width;
		}
		float getMaxY() {
			return this->frame.origin.y + this->frame.size.height;
		}
		ofxHierarchy::Point center();
		bool hitTest(float x, float y);
	};
}

#endif /* ofxHierarchy_hpp */
