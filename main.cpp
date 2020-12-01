#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);
    
    Scene scene;
    scene.setShadow(1);
    Vector3d paint;
    paint[0]=1.0;
    paint[1]=0.0;
    paint[2]=0.0;
    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, paint,2,0.5));
   paint[0]=0.0;
    paint[1]=1.0;
    paint[2]=0.0;
    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, paint,.5,0.5));
 paint[0]=0.0;
    paint[1]=0.0;
    paint[2]=1.0;
    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, paint,.5,0.5));

//   center[0] = 10;
//     center[1] = 10.25;
//     center[2] = 20.75;
//     scene.addShape(new Sphere(center, 2));
    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
