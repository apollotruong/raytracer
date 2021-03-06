#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"
#include <vector>
extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    // Added Lab 2
    double min_t = std::numeric_limits<double>::max(); // highest int possible
	Hit hit = {NULL, 0.0, 0};
	for(auto object : objects){
			Hit compare = object->Intersection(ray, 0);
			if(compare.dist < min_t && (compare.dist > small_t)){
					hit = compare;
					min_t = compare.dist;
			}
	}

	
    // Added Lab 2
    return hit;
	// Added Lab 2
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{

    Ray ray;
    
	// Added Lab 2
	ray.endpoint = camera.position;
	ray.direction = (camera.World_Position(pixel_index) - ray.endpoint).normalized();
	// Added Lab 2

	vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    // determine the color here
	//
	// Added Lab 2
	Hit Closest_Hit = {NULL, 0.0, 0}; 
	Closest_Hit = this->Closest_Intersection(ray);
	vec3 intersect = ray.Point(Closest_Hit.dist);
	if(Closest_Hit.object != NULL){
			color = Closest_Hit.object->
					material_shader->
					Shade_Surface(ray, intersect, Closest_Hit.object->Normal(intersect,0), recursion_depth);
	}else{
			color = this->background_shader->
					Shade_Surface(ray,color,color,recursion_depth);
	}

	// Added Lab 2
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
