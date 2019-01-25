//Anthony Smiderle
//100695532
#pragma once

//forward declaring a vec2 class for use in constructor
namespace cocos2d {
	class Vec2;
	class DrawNode;
}


namespace Pm {

	class Capsule {

	public:
		Capsule(cocos2d::Vec2& ORIGIN, cocos2d::Vec2& ENDPOINT, float RADIUS);
		~Capsule();

		//returns the draw note
		cocos2d::DrawNode* getDrawNode() const;
	private:
		//node that allows us to draw things like primitives
		cocos2d::DrawNode* Node;
	};
	class LinePrimitive {
	
	public:
		LinePrimitive(cocos2d::Vec2& ORIGIN, cocos2d::Vec2& ENDPOINT);
		LinePrimitive();
		~LinePrimitive();


		cocos2d::DrawNode* getDrawNode() const;

	private:
		cocos2d::DrawNode * Node;
	};
	class SquarePrimitive {

	public:
		//using reference operator to denote a pointer, otherwise it won't work. Vec2 &name literally means an integer in the computer's memory
		SquarePrimitive(const cocos2d::Vec2 &startingPosition,const cocos2d::Vec2 &endPosition);
		SquarePrimitive();
		~SquarePrimitive();


		cocos2d::DrawNode* getDrawNode() const;
	private:
		cocos2d::DrawNode *Node;

	};
	class CirclePrimitive {
	public:
		CirclePrimitive(const cocos2d::Vec2 &LOCATION,float RADIUS, float ANGLE,unsigned int SEGMENTS);
		CirclePrimitive();
		~CirclePrimitive();


		cocos2d::DrawNode* getDrawNode() const;

	private:
		cocos2d::DrawNode* Node;
	};

}