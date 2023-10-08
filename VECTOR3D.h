#pragma once

class VECTOR3D
{
public:
	VECTOR3D() :m_x(0), m_y(0), m_z(0)
	{
	}
	VECTOR3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z)
	{
	}
	VECTOR3D(const VECTOR3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}
	VECTOR3D operator *(float num)
	{
		return VECTOR3D(m_x * num, m_y * num, m_z * num);
	}
	VECTOR3D operator +(VECTOR3D vec)
	{
		return VECTOR3D(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
	}

	static VECTOR3D lerp(const VECTOR3D& start, const VECTOR3D& end, float delta)
	{
		VECTOR3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}


	~VECTOR3D()
	{
	}

	float m_x, m_y, m_z;
};

