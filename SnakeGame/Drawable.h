#pragma once

class Drawable {
public:
	virtual void draw() const = 0; // using const to implement without chaging 
	virtual ~Drawable() {};
};