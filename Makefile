g++ -c Image.cpp main.cpp Scene.cpp Shape.cpp Sphere.cpp -lpng
g++ -o test Image.o Scene.o Shape.o Sphere.o main.o -lpng