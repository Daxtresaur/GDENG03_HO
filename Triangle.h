#pragma once

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};


class Triangle
{
public:
	Triangle();

	vertex* getVertexList();
	void setVertexList(vertex* list_vertices);
	


	~Triangle();

		
private:
	
	vertex list[];

};

