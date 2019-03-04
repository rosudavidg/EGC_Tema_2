#pragma once

class MyBallObject
{
public:
	MyBallObject(float posx, float posz, float R, float G, float B);
	~MyBallObject();

	float posx;
	float posz;
	float radius;
	
	bool moving;
	bool visible;

	float speedx;
	float speedz;

	float R;
	float G;
	float B;

	void foo() {}
};

