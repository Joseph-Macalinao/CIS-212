#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Place your struct definitions for Circle, Triangle, and Rectangle here */

typedef struct Shape Shape;


typedef struct Circle {
	double orig_x;
	double orig_y;
	double radius;	
} Circle;

typedef struct Triangle {
	double min_y;
	double max_y;
	double left_x;
	double right_x;
	double top_x;	
} Triangle;

typedef struct Rectangle {
	double min_x;
	double min_y;
	double max_x;
	double max_y;
} Rectangle;


typedef struct Shape{
	void *self;
	double (*GetArea)(Shape *);
	void (*GetBoundingBox)(Shape *, double);
} Shape;


void GetBoundingBox(Shape *s, double bbox);
double GetArea(Shape *s);


/* Define these 9 functions 
void CreateCircle(void *c, double radius, double originX, double originY)
{
	Circle circ = *((Circle *) c);
	circ = malloc(sizeof(Circle));
	c->orig_x = originX;
	c->orig_y = originY;
	c->radius = radius;
};

void CreateRectangle(void *r, double minX, double maxX, double minY, double maxY)
{
	//struct Rectangle *Rectangle;
	//Rectangle *Rectangle = (Rectangle *)malloc(sizeof(Rectangle));
	//Rectangle r = (Rectangle *)malloc(sizeof(Rectangle));
	Rectangle rect = *((Rectangle *) r);
	r = malloc(sizeof(Rectangle));
	r->min_x = minX;
	r->min_y = minY;
	r->max_x = maxX;
	r->max_y = maxY;
};

void CreateTriangle(void *t, double pt1X, double pt2X, double minY, double maxY)
{
	//struct Triangle *Triangle;
	//Triangle *Triangle = (Triangle *)malloc(sizeof(Triangle));
	//Triangle t = (Triangle *)malloc(sizeof(Triangle));
	Triangle tri = *((Triangle *) t);
        t = malloc(sizeof(Triangle));
	t->min_y = minY;
	t->max_y = maxY;
	t->left_x = pt1X;
	t->right_x = pt2X;
	t->top_x = ((pt1X + pt2X) / 2);
};
*/

double GetCircleArea(void *c)
{
	//Circle *c = malloc(sizeof(Circle));
	Circle circ = *((Circle *) c);
	//Circle *c;
	double area;
	area = 3.14159 * (circ.radius * circ.radius);
	return area;
};

double GetRectangleArea(void *r)
{
	//Rectangle *r = malloc(sizeof(Rectangle));
	Rectangle rect = *((Rectangle *) r);
	//Rectangle *r;
	double area;
	area = (rect.max_x - rect.min_x) * (rect.max_y - rect.min_y);
	return area;
};

double GetTriangleArea(void *t)
{
	//Triangle *t = malloc(sizeof(Triangle));
	Triangle tri = *((Triangle *) t);
	//Triangle *t;
	double area = 0.0;
	area = (tri.right_x - tri.left_x) * ((tri.max_y - tri.min_y)/2);
	return area;
};


void GetCircleBoundingBox(void *c, double *bbox)
{
	Circle circ = *((Circle *) c);
	bbox[0] = (circ.orig_x - circ.radius);
	bbox[1] = (circ.orig_x + circ.radius);
	bbox[2] = (circ.orig_y - circ.radius);
	bbox[3] = (circ.orig_y + circ.radius);
	
};

void GetRectangleBoundingBox(void *r, double *bbox)
{
	Rectangle rect = *((Rectangle *) r);
	bbox[0] = (rect.min_x);
	bbox[1] = (rect.max_x);
	bbox[2] = (rect.min_y);
	bbox[3] = (rect.max_y);
};

void GetTriangleBoundingBox(void *t, double *bbox)
{
	Triangle tri = *((Triangle *) t);
	bbox[0] = (tri.left_x);
	bbox[1] = (tri.right_x);
	bbox[2] = (tri.min_y);
	bbox[3] = (tri.max_y);	
};




void CreateCircle(void *c, double radius, double originX, double originY)
{
	//Circle *circ = *((Circle *) c)malloc(sizeof(Circle));
	//circ = malloc(sizeof(Circle));
	Circle *circ = (Circle *) c;
	circ->orig_x = originX;
	circ->orig_y = originY;
	circ->radius = radius;
};

void CreateRectangle(void *r, double minX, double maxX, double minY, double maxY)
{
	//struct Rectangle *Rectangle;
	//Rectangle *Rectangle = (Rectangle *)malloc(sizeof(Rectangle));
	//Rectangle r = (Rectangle *)malloc(sizeof(Rectangle));
	//Rectangle *rect = *((Rectangle *) r)malloc(sizeof(Rectangle));
	//rect = malloc(sizeof(Rectangle));
	Rectangle *rect = (Rectangle *) r;
	rect->min_x = minX;
	rect->min_y = minY;
	rect->max_x = maxX;
	rect->max_y = maxY;
};

void CreateTriangle(void *t, double pt1X, double pt2X, double minY, double maxY)
{
	//struct Triangle *Triangle;
	//Triangle *Triangle = (Triangle *)malloc(sizeof(Triangle));
	//Triangle t = (Triangle *)malloc(sizeof(Triangle));
	//Triangle *tri = *((Triangle *) t)malloc(sizeof(Triangle));
        //tri = malloc(sizeof(Triangle));
	struct Triangle *tri =  (Triangle *) t;
	tri->min_y = minY;
	tri->max_y = maxY;
	tri->left_x = pt1X;
	tri->right_x = pt2X;
	tri->top_x = ((pt1X + pt2X) / 2);
};
/* DO NOT MODIFY AFTER THIS POINT */

void
PrintTriangle(Triangle *t)
{
    double bbox[4];
    double area;
    area = GetTriangleArea(t);
    GetTriangleBoundingBox(t, bbox);
    printf("Triangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void
PrintRectangle(Rectangle *r)
{
    double bbox[4];
    double area;
    area = GetRectangleArea(r);
    GetRectangleBoundingBox(r, bbox);
    printf("Rectangle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

void
PrintCircle(Circle *c)
{
    double bbox[4];
    double area;
    area = GetCircleArea(c);
    GetCircleBoundingBox(c, bbox);
    printf("Circle has area %f and bounding box [%f->%f], [%f->%f]\n",
           area, bbox[0], bbox[1], bbox[2], bbox[3]);
}

int main()
{
	Shape *shapes[9];
	int i;
	shapes[0] = CreateCircle(1,0,0);
	shapes[1] = CreateCircle(1.5,6,8);
	shapes[2] = CreateCricle(0.5, -3, 4);

	
	shapes[3] = CreateRectangle(0,1,0,1);
	shapes[4] = CreateRectangle(1,1.1,10,20);
	shapes[5] = CreateRectangle(1.5,3.5,10,12);


	shapes[6] = CreateTriangle(0,1,0,1);
	shapes[7] = CreateTriangle(0,1,0,.1);
	shapes[8] = CreateTriangle(0,10,0,50);


	for(i = 0; i < 9; i++){
		double bbox[4];
		printf("Shape %d\n", i);
		printf("\tArea: %f\n", GetArea(shapes[i]));
		GetBoundingBox(shapes[i], bbox);
		printf("\tBbox: %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
	}
}
