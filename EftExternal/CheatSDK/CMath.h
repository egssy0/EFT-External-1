#pragma once

enum type_zero { ZERO };

class Vector3
{
public:
	float x, y, z;

	inline Vector3() {
		x = y = z = 0.0f;
	}

	inline Vector3(float var) {
		x = y = z = var;
	}

	inline Vector3(float X, float Y, float Z) {
		x = X; y = Y; z = Z;
	}

	inline float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline Vector3& operator-=(float v) {
		x -= v; y -= v; z -= v; return *this;
	}

	inline Vector3 operator*(float v) const {
		return Vector3(x * v, y * v, z * v);
	}

	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	inline Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	inline Vector3 operator-(const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	inline float Length() {
		return sqrtf(x * x + y * y + z * z);
	}

	inline float dot(Vector3 input) const
	{
		return (x * input.x) + (y * input.y) + (z * input.z);
	}

	inline void Normalize()
	{
		float len = std::sqrt(x * x + y * y + z * z);
		if (len != 0.f)
		{
			x /= len;
			y /= len;
			z /= len;
		}

	}
	static  Vector3 Normalize(Vector3 angle)
	{
		float len = std::sqrt(angle.x * angle.x + angle.y * angle.y + angle.z * angle.z);
		if (len != 0.)
		{
			angle.x /= len;
			angle.y /= len;
			angle.z /= len;
		}
		return angle;
	}

	static Vector3 Cross(Vector3 v1, Vector3 v2)
	{
		Vector3 result = {};
		result.x = v1.y * v2.z - v1.z * v2.y;
		result.y = v1.z * v2.x - v1.x * v2.z;
		result.z = v1.x * v2.y - v1.y * v2.x;
		return result;
	}

	float unity_magnitude()
	{
		return (float)sqrt((double)(x * x + y * y + z * z));
	}

	Vector3 unity_normalize()
	{
		float num = unity_magnitude();
		if (num > 1E-05f)
		{
			x /= num;
			y /= num;
			z /= num;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}
		return { x,y,z };
	}

	template<typename T>
	T get_remainder(T val, T min, T max)
	{
		while (val > max)
			val -= max * 2;
		while (val < min)
			val += max * 2;
		return val;
	}

	void angle_vectors(Vector3* forward, Vector3* right, Vector3* up)
	{
		float sp, sy, cp, cy, sr, cr;

		constexpr auto PI = 3.14159265358979323846;
		sy = sin(y / 180.f * (float)PI);
		cy = cos(y / 180.f * (float)PI);

		sp = sin(x / 180.f * (float)PI);
		cp = cos(x / 180.f * (float)PI);

		sr = 0.f;
		cr = 1.f;

		if (forward) {
			*forward = { cp * cy, -sp, cp * sy };
		}

		if (right) {
			right->x = cp * sy;
			right->y = (cr * sp * sy + -sr * cy);
			right->z = (sr * sp * sy + cr * cy);
		}

		if (up) {
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = cr * cp;
			up->z = (cr * sp * sy + -sr * cy);
		}
	}
	Vector3 clamp()
	{
		constexpr auto yaw_limit = static_cast<float>(180);
		constexpr auto pitch_limit = static_cast<float>(90);

		y = get_remainder(y, -yaw_limit, yaw_limit);
		x = get_remainder(x, -pitch_limit, pitch_limit);



		return *this;
	}

	auto empty() -> bool { return x == 0.000000 && y == 0.000000 && z == 0.000000; }
	
};

class Vector2 {
public:
	float x, y;

	inline Vector2() {
		x = y = 0.0f;
	}

	inline Vector2 operator/(float v) const {
		return Vector2(x / v, y / v);
	}
	inline Vector2(float X, float Y) {
		x = X; y = Y;
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y; return *this;
	}

	inline bool Zero() const {
		return (x > -0.1f && x < 0.1f && y > -0.1f && y < 0.1f);
	}

	inline void Normalize(Vector2& angle)
	{
		if (angle.x > 89)angle.x = 89;
		if (angle.x < -89)angle.x = -89;
		while (angle.y > 180)angle.y -= 360;
		while (angle.y < -180)angle.y += 360;
	}

	inline Vector2 Normalize(Vector2 angle)
	{
		if (angle.x > 89)angle.x = 89;
		if (angle.x < -89)angle.x = -89;
		while (angle.y > 180)angle.y -= 360;
		while (angle.y < -180)angle.y += 360;
		return angle;
	}
};

class Vector4 {
public:
	float x, y, z, w;
};

struct Matrix4x4 
{
	union 
	{
		struct
		{
			float  _11, _12, _13, _14;
			float  _21, _22, _23, _24;
			float  _31, _32, _33, _34;
			float  _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

struct matrix34_t
{
	Vector4 vec0{};
	Vector4 vec1{};
	Vector4 vec2{};
};

enum Bones : int
{
	HumanBase,
	HumanPelvis,
	HumanLThigh1,
	HumanLThigh2,
	HumanLCalf,
	HumanLFoot,
	HumanLToe,
	HumanRThigh1,
	HumanRThigh2,
	HumanRCalf,
	HumanRFoot,
	HumanRToe,
	HumanSpine1,
	HumanSpine2,
	HumanSpine3,
	HumanLCollarbone,
	HumanLUpperarm,
	HumanLForearm1,
	HumanLForearm2,
	HumanLForearm3,
	HumanLPalm,
	HumanRCollarbone,
	HumanRUpperarm,
	HumanRForearm1,
	HumanRForearm2,
	HumanRForearm3,
	HumanRPalm,
	HumanNeck,
	HumanHead
};

static int BoneIndex[29] =
{
	0,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	29,
	36,
	37,
	89,
	90,
	91,
	92,
	93,
	94,
	110,
	111,
	112,
	113,
	114,
	115,
	132,
	133
};

//static std::array<bone_t, 23> bones =
//{
//					bone_t{ Vector3{}, 133, false },
//					bone_t{ Vector3{}, 132, false },
//					bone_t{ Vector3{}, 37, false },
//					bone_t{ Vector3{}, 36, false },
//					bone_t{ Vector3{}, 29, false },
//					bone_t{ Vector3{}, 14, false },
//					bone_t{ Vector3{}, 19, false },
//					bone_t{ Vector3{}, 18, false },
//					bone_t{ Vector3{}, 17, false },
//					bone_t{ Vector3{}, 16, false },
//					bone_t{ Vector3{}, 15, false },
//					bone_t{ Vector3{}, 14, false },
//					bone_t{ Vector3{}, 20, false },
//					bone_t{ Vector3{}, 21, false },
//					bone_t{ Vector3{}, 22, false },
//					bone_t{ Vector3{}, 23, false },
//					bone_t{ Vector3{}, 24, false },
//					bone_t{ Vector3{}, 94, false },
//					bone_t{ Vector3{}, 91, false },
//					bone_t{ Vector3{}, 90, false },
//					bone_t{ Vector3{}, 111, false },
//					bone_t{ Vector3{}, 112, false },
//					bone_t{ Vector3{}, 115, false }

//draw_bone_to_bone(0, 1);
//draw_bone_to_bone(1, 2);
//draw_bone_to_bone(2, 3);
//draw_bone_to_bone(3, 4);
//draw_bone_to_bone(4, 5);
//
//draw_bone_to_bone(6, 7);
//draw_bone_to_bone(7, 8);
//draw_bone_to_bone(8, 9);
//draw_bone_to_bone(9, 10);
//draw_bone_to_bone(10, 11);
//draw_bone_to_bone(11, 12);
//draw_bone_to_bone(12, 13);
//draw_bone_to_bone(13, 14);
//draw_bone_to_bone(14, 15);
//draw_bone_to_bone(15, 16);
//
//draw_bone_to_bone(17, 18);
//draw_bone_to_bone(18, 19);
//draw_bone_to_bone(19, 20);
//draw_bone_to_bone(20, 21);
//draw_bone_to_bone(21, 22);

//};