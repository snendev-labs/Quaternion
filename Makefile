quaternion: badguy.cpp bullet.cpp shield.cpp leveldesigner.cpp quaternion.cpp quaternionlib.cpp goodguy.cpp
	g++ badguy.cpp bullet.cpp shield.cpp leveldesigner.cpp quaternion.cpp quaternionlib.cpp goodguy.cpp -o quaternion -lGL -lGLU -lglut -L/usr/local -std=c++11
