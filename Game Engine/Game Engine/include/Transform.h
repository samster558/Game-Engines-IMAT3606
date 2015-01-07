#pragma

#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform
{
protected:

	int x;
	int y;
	int z; // Keep the same for the player, enemies and bullets, change for some environmental hazards to block the view

public:
	Transform();
	~Transform();

};

#endif // TRANSFORM_H