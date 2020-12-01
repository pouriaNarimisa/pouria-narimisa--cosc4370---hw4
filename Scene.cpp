#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray)
{
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++)
    {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t))
        {
            result = r;
            foundSomething = true;
            result.color = shapes[i]->getColor(result.position);
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int pass, const int trace_limit)
{
    
    Vector3d result(0,0,0);
	Vector3d loc(0,0,0);
	Vector3d sourcecolor(1.0, 1.0, 1.0);

Vector3d objcolor;

    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);
        if (r.t < numeric_limits<double>::epsilon())
        return result;
  
    Ray sRay;
    double stregth_shadow = 1.0;
    sRay.origin = r.position;
    sRay.direction = (lightPos - r.position);
    stregth_shadow = shadowRatio;

Ray rRay;
	rRay.origin= r.position;
//	rRay.direction = ray.direction - 2.0*r.normal.dot(ray.direction)*r.normal;
	rRay.direction = r.normal;
	Vector3d reflect_color(0,0,0);

	if(pass < trace_limit){
		reflect_color = trace(rRay, ++pass, trace_limit);
	}

	Vector3d lightDir = (lightPos - r.position).normalized();
	objcolor = r.color;

	// Ambient
	double ambientStrength = 0.2;
	Vector3d ambient = ambientStrength * sourcecolor;

	// Diffuse
	double diffuseStrength = 1.0;
	Vector3d norm = r.normal.normalized();
	double diff = norm.dot(lightDir);
	Vector3d diffuse = diffuseStrength * max(diff, 0.0) * sourcecolor;

	// Specular
	double specularStrength = 0.5;
	Vector3d viewDir = (loc - r.position).normalized();
	Vector3d reflectDir;
	//I - 2.0 * dot(N, I) * N
	reflectDir = -lightDir - 2.0*norm.dot(-lightDir)*norm;
	double spec = pow(max(viewDir.dot(reflectDir), 0.0), 32);
	Vector3d specular = specularStrength * spec * sourcecolor;


	// double reflectStrength = reflectRatio;
	double reflectStrength = shapes[r.shapeId]->getReflectStrength();
	result = stregth_shadow*(ambient+diffuse+specular).cwiseProduct(objcolor)+reflectStrength*reflect_color;
        return result;
}

void Scene::render(Image &image)
{
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).
const int TRACE_LIMIT = 200;
    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++)
        {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay,0,TRACE_LIMIT);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
void Scene::setShadow(double ratio)
{
    shadowRatio = ratio;
}