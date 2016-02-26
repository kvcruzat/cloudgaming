Procedural Tree
Khen Cruzat - sc13kvc - 200760716

Compile:
	sh make.sh		(runs qmake and make with required -lGLU)

Execution:
	./game

NOTES:
 -	Setting Seasons spinner box to 11 and above will cause considerable performance loss especially with Leaves enabled.
 	This is due to drawing 2^nSeasons branches.
 -	GLU library used to draw conical frustums (cylinders with different radius) for branches
