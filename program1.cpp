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

    Vector3d center;
  

  center[0] = 10;
    center[1] = 10.25;
    center[2] = 20.75;
    scene.addShape(new Sphere(center, 2));
    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
