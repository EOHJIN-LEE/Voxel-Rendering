#include "gmath.h"


// 정적 데이터 멤버의 초기화
double GLine::Precision = 1.0e-7;
double GPlane::Precision = 1.0e-7;
double GPos3::Precision = 1.0e-7;
double GVec3::Precision = 1.0e-7;


////////////////////////////////////////////////////////////

/*!
*	\brief 디폴트 생성자
*	
*	\param x x-좌표
*	\param y y-좌표
*	\param z z-좌표
*/
GVec3::GVec3(double x, double y, double z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
}

/*!
*	\brief	복사생성자
*
*	\param cpy 복사될 객체
*/
GVec3::GVec3(const GVec3 &cpy)
{
	V[0] = cpy.V[0];
	V[1] = cpy.V[1];
	V[2] = cpy.V[2];
}

/*!
*	\brief 소멸자
*/
GVec3::~GVec3()
{
}

/*!
*	\brief 대입연산자
*
*	\param rhs 오른쪽 피연산자
*
*	\return 대입된 자신
*/
GVec3 &GVec3::operator =(const GVec3 &rhs)
{
	V[0] = rhs.V[0];
	V[1] = rhs.V[1];
	V[2] = rhs.V[2];
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param rhs 오른쪽 피연산자
*
*	\return 연산후 대입된 자신
*/
GVec3 &GVec3::operator +=(const GVec3 &rhs)
{
	V[0] += rhs.V[0];
	V[1] += rhs.V[1];
	V[2] += rhs.V[2];
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param rhs 오른쪽 피연산자
*
*	\return 연산후 대입된 자신
*/
GVec3 &GVec3::operator -=(const GVec3 &rhs)
{
	V[0] -= rhs.V[0];
	V[1] -= rhs.V[1];
	V[2] -= rhs.V[2];
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param s 곱할 상수
*
*	\return 연산후 대입된 자신
*/
GVec3 &GVec3::operator *=(const double &s)
{
	V[0] *= s;
	V[1] *= s;
	V[2] *= s;
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param s 나눌 상수
*
*	\return 연산후 대입된 자신
*/
GVec3 &GVec3::operator /=(const double &s)
{
	V[0] /= s;
	V[1] /= s;
	V[2] /= s;
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param rhs 외적의 오른쪽 피연산자
*
*	\return 연산후 대입된 자신
*/
GVec3 &GVec3::operator ^=(const GVec3 &rhs)
{
	double x = V[0], y = V[1], z = V[2];
	V[0] = y * rhs.V[2] - z * rhs.V[1];
	V[1] = z * rhs.V[0] - x * rhs.V[2];
	V[2] = x * rhs.V[1] - y * rhs.V[0];
	return *this;
}

/*!
*	\brief 단항연산자
*
*	\return 반대부호를 갖는 객체
*/
GVec3 GVec3::operator +() const
{
	return *this;
}

/*!
*	\brief 단항연산자
*
*	\return 반대부호를 갖는 객체
*/
GVec3 GVec3::operator -() const
{
	return *this * -1;
}

/*!
*	\brief 산술연산자(+)
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 연산의 결과를 반환
*/ 
GVec3 operator +(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[0] + rhs.V[0], lhs.V[1] + rhs.V[1], lhs.V[2] + rhs.V[2]);
}

/*!
*	\brief 산술연산자(-)
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 연산의 결과를 반환
*/ 
GVec3 operator -(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[0] - rhs.V[0], lhs.V[1] - rhs.V[1], lhs.V[2] - rhs.V[2]);
}

/*!
*	\brief 내적연산자(*)
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 내적의 결과를 반환
*/
double operator *(const GVec3 &lhs, const GVec3 &rhs)
{
	return lhs.V[0] * rhs.V[0] + lhs.V[1] * rhs.V[1] + lhs.V[2] * rhs.V[2];
}

/*!
*	\brief 산술연산자(/)
*
*	\param s 나룰 상수
*	\return 연산의 결과를 반환
*/
GVec3 operator /(const GVec3 &lhs, const double &s)
{
	return GVec3(lhs.V[0] / s, lhs.V[1] / s, lhs.V[2] / s);
}

/*!
*	\brief 외적연산자(^)
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 외적의 결과를 반환
*/
GVec3 operator ^(const GVec3 &lhs, const GVec3 &rhs)
{
	return GVec3(lhs.V[1] * rhs.V[2] - lhs.V[2] * rhs.V[1], lhs.V[2] * rhs.V[0] - lhs.V[0] * rhs.V[2], lhs.V[0] * rhs.V[1] - lhs.V[1] * rhs.V[0]);
}

/*!
*	\brief 등호연산자
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 비교 결과를 반환
*/
bool operator ==(const GVec3 &lhs, const GVec3 &rhs)
{
	double error = GVec3::Precision;
	return (EQ(lhs.V[0], rhs.V[0], error) && EQ(lhs.V[1], rhs.V[1], error) && EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief 부등호연산자
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 비교 결과를 반환
*/
bool operator !=(const GVec3 &lhs, const GVec3 &rhs)
{
	double error = GVec3::Precision;
	return (!EQ(lhs.V[0], rhs.V[0], error) || !EQ(lhs.V[1], rhs.V[1], error) || !EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief 첨자연산자([])
*
*	\param idx 첨자
*	\param 벡터의 \a idx번째 원소를 반환
*/
double &GVec3::operator [](const int &idx)
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief 상수객체에 대한 첨자연산자([])
*
*	\param idx 첨자
*	\param 벡터의 \a idx번째 원소를 반환
*/
const double &GVec3::operator [](const int &idx) const
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief 벡터의 좌표를 설정
*
*	\param x x-좌표
*	\param y y-좌표
*	\param z z-좌표
*/
GVec3 &GVec3::Set(const double &x, const double &y, const double &z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
	return *this;
}

/*!
*	\brief 벡터를 정규하여 단위벡터로 변환
*
*	\return 변환된 자신을 반환
*/
GVec3 &GVec3::Normalize()
{
	double len = norm(*this);
	if (EQ_ZERO(len, Precision))
		return *this;
	V[0] /= len;
	V[1] /= len;
	V[2] /= len;
	return *this;
}

/*!
*	\brief 등호 및 부등호 연산자의 오차의 한계 설정
*
*	\param error 오차의 한계
*/
void GVec3::SetPrecision(double error)
{
	Precision = error;
}

/*!
*	\brief 설정된 오차의 한계를 반환
*
*	\return 설정된 오차의 한계
*/
double GVec3::GetPrecision()
{
	return Precision;
}

/*!
*	\brief 산술연산자(*)
*
*	\param lhs 왼쪽 피연산자
*	\param s 오른쪽 피연산자
*
*	\return 연산의 결과를 반환
*/
GVec3 operator *(const GVec3 &lhs, const double &s)
{
	GVec3 ret(lhs);
	ret *= s;
	return ret;
}

/*!
*	\brief 산술연산자(*)
*
*	\param s 왼쪽 피연산자
*	\param lhs 오른쪽 피연산자
*
*	\return 연산의 결과를 반환
*/
GVec3 operator *(const double &s, const GVec3 &rhs)
{
	GVec3 ret(rhs);
	ret *= s;
	return ret;
}

/*!
*	\brief 출력연산자(<<)
*
*	\param os 출력스트림
*	\param v 출력할 벡터
*
*	\return \a v가 출력된 스트림을 반환
*/
std::ostream &operator <<(std::ostream &os, const GVec3 &v)
{
	os << "(" << std::setw(10) << v.V[0] << ", " << std::setw(10) << v.V[1] << ", " << std::setw(10) << v.V[2] << ")";
	return os;
}

/*!
*	\brief 입력연산자(>>)
*
*	\param is 입력스트림
*	\param v 입력값이 저장될 벡터
*
*	\return 입력값이 제거된 입력스트림
*/
std::istream &operator >>(std::istream &is, GVec3 &v)
{
	is >> v.V[0] >> v.V[1] >> v.V[2];
	return is;
}

/*!
*	\brief 벡터 v를 벡터 w에 사영시킨 벡터를 구한다.
*
*	\param v 벡터.
*	\param w 벡터.
*
*	\return 벡터 v를 벡터 w에 사영시킨 벡터를 반환한다.
*/
GVec3 proj(const GVec3 &v, const GVec3 &w)
{
	return (v * w / (w.V[0] * w.V[0] + w.V[1] * w.V[1] + w.V[2] * w.V[2])) * w;
}

/*!
*	\brief 벡터 v에 수직한 벡터를 구한다.
*
*	\param v 벡터
*
*	\return 벡터 v를 수직한 벡터를 구하여 반환한다.
*/
GVec3 ortho(const GVec3 &v)
{
	GVec3 ret;

	double min_val = MIN(MIN(v[0], v[1]), v[2]);
	if (min_val == v[0])
		ret.Set(0.0, -v[2], v[1]);
	
	if (min_val == v[1])
		ret.Set(v[2], 0.0, -v[0]);

	if (min_val == v[2])
		ret.Set(-v[1], v[0], 0.0);

	return ret;
}

/*!
*	\brief 벡터 v, w의 차이벡터의 길이를 구한다.
*
*	\param v 벡터.
*	\param w 벡터.
*
*	\return  벡터 \a v, \a w의 차이벡터의 길이
*/
double dist(const GVec3 &v, const GVec3 &w)
{
	return norm(v - w);
}

/*!
*	\brief 벡터 u, v, w의 행렬식을 계산한다.
*
*	\param u 벡터.
*	\param v 벡터.
*	\param w 벡터.
*
*	\return  벡터 u, v, w의 행렬식의 값을 반환한다.
*/
double det(const GVec3 &u, const GVec3 &v, const GVec3 &w)
{
	return (u[0] * v[1] * w[2] + u[1] * v[2] * w[0] + u[2] * v[0] * w[1]) - (w[0] * v[1] * u[2] + v[0] * u[1] * w[2] + u[0] * w[1] * v[2]);
}

/*!
*	\brief 벡터 v의 크기를 구한다.
*
*	\param v 벡터
*
*	\return 벡터 \a v의 크기
*/ 
double norm(const GVec3 &v)
{
	return SQRT(SQR(v.V[0]) + SQR(v.V[1]) + SQR(v.V[2]));
}

/*!
*	\brief 두 벡터 사이의 사이각을 구한다.
*	\warning 0 <= 사이각 <= 180
*
*	\param v 시작 벡터
*	\param w 끝 벡터
*	\param radian 각도의 형태(true: radian, false: degree)
*
*	\return 벡터 \a v에서 벡터 \a w까지의 사이각(예각, 방향 상관없음)
*/
double angle(const GVec3 &v, const GVec3 &w, bool radian)
{
	GVec3 p(v);
	GVec3 q(w);
	double cs, sn, theta;

	p.Normalize();
	q.Normalize();

	cs = p * q;
	sn = norm(p ^ q);

	theta = radian ? atan2(sn, cs) : RAD2DEG(atan2(sn, cs));
	return theta;
}

/*!
*	\brief 두 벡터 사이의 사이각을 구한다.
*	\warning 0 <= 사이각 <= 360
*
*	\param v 시작 벡터
*	\param w 끝 벡터
*	\param up 기준 벡터
*	\param radian 각도의 형태(true: radian, false: degree)
*
*	\return 벡터 \a v에서 벡터 \a w까지의 사이각(기준 벡터를 기준으로한 반 시계방향)
*/
double angle(const GVec3 &v, const GVec3 &w, const GVec3 &up, bool radian)
{
	GVec3 p(v);
	GVec3 q(w);
	double cs, sn, theta;

	p.Normalize();
	q.Normalize();
	GVec3 r = p ^ q;

	cs = p * q;
	sn = norm(r);

	theta = atan2(sn, cs);
	if (r * up < 0.0)	
		theta = 2 * M_PI - theta;
	
	theta = radian ? theta : RAD2DEG(theta);
	return theta;
}


/////////////////////////////////////////////////////////////////////

/*!
*	\brief 디폴트 생성자
*	
*	\param x x-좌표
*	\param y y-좌표
*	\param z z-좌표
*/
GPos3::GPos3(double x, double y, double z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
}

/*!
*	\brief 복사생성자
*
*	\param cpy 복사될 객체
*
*	\return 복사된 자신을 반환
*/
GPos3::GPos3(const GPos3 &cpy)
{
	V[0] = cpy.V[0];
	V[1] = cpy.V[1];
	V[2] = cpy.V[2];
}

/*!
*	\brief  소멸자
*/
GPos3::~GPos3()
{
}

/*!
*	\brief 대입연산자
*
*	\param rhs 오른쪽 피연산자
*
*	\return 대입된 자신을 반환
*/
GPos3 &GPos3::operator =(const GPos3 &rhs)
{
	V[0] = rhs.V[0];
	V[1] = rhs.V[1];
	V[2] = rhs.V[2];
	return *this;
}

/*!
*	\brief 복합대입연산자
*
*	\param rhs 오른쪽 피연산자
*
*	\return 연산후 대입된 자신
*/
GPos3 &GPos3::operator +=(const GVec3 &rhs)
{
	V[0] += rhs.V[0];
	V[1] += rhs.V[1];
	V[2] += rhs.V[2];
	return *this;
}

/*!
*	\brief 산술연산자(-)
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 연산의 결과(벡터)를 반환
*/
GVec3 operator -(const GPos3 &lhs, const GPos3 &rhs)
{
	return GVec3(lhs.V[0] - rhs.V[0], lhs.V[1] - rhs.V[1], lhs.V[2] - rhs.V[2]);
}

/*!
*	\brief 산술연산자(-)
*
*	\param lhs 왼쪽 피연산자(포인트)
*	\param rhs 오른쪽 피연산자(벡터)
*
*	\return 연산의 결과(포인트)를 반환
*/
GPos3 operator -(const GPos3 &lhs, const GVec3 &rhs)
{
	return GPos3(lhs.V[0] - rhs[0], lhs.V[1] - rhs[1], lhs.V[2] - rhs[2]);
}

/*!
*	\brief 산술연산자(+)
*
*	\param lhs 왼쪽 피연산자(포인트)
*	\param rhs 오른쪽 피연산자(벡터)
*
*	\return 연산의 결과(포인트)를 반환
*/
GPos3 operator +(const GPos3 &lhs, const GVec3 &rhs)
{
	return GPos3(lhs.V[0] + rhs[0], lhs.V[1] + rhs[1], lhs.V[2] + rhs[2]);
}

/*!
*	\brief 산술연산자(+)
*
*	\param lhs 왼쪽 피연산자(벡터)
*	\param rhs 오른쪽 피연산자(포인트)

*
*	\return 연산의 결과(포인트)를 반환
*/
GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs)
{
	return GPos3(lhs.V[0] + rhs[0], lhs.V[1] + rhs[1], lhs.V[2] + rhs[2]);
}

/*!
*	\brief 등호연산자
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 비교결과를 반환
*/
bool operator ==(const GPos3 &lhs, const GPos3 &rhs)
{
	double error = GPos3::Precision;
	return (EQ(lhs.V[0], rhs.V[0], error) && EQ(lhs.V[1], rhs.V[1], error) && EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief 부등호연산자
*
*	\param lhs 왼쪽 피연산자
*	\param rhs 오른쪽 피연산자
*
*	\return 비교결과를 반환
*/
bool operator !=(const GPos3 &lhs, const GPos3 &rhs)
{
	double error = GPos3::Precision;
	return (!EQ(lhs.V[0], rhs.V[0], error) || !EQ(lhs.V[1], rhs.V[1], error) || !EQ(lhs.V[2], rhs.V[2], error));
}

/*!
*	\brief 첨자연산자([])
*
*	\param idx 첨자
*
*	\return \a idx 번째 원소를 반환
*/
double &GPos3::operator [](const int &idx)
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief 상수객체의 첨자연산자([])
*
*	\param idx 첨자
*
*	\return \a idx 번째 원소를 반환
*/
const double &GPos3::operator [](const int &idx) const
{
	assert(idx >= 0 && idx < 3);
	return V[idx];
}

/*!
*	\brief 포인트의 좌표를 설정한다.
*
*	\param x x-좌표
*	\param y y-좌표
*	\param z z-좌표
*
*	\return 설정된 자신을 반환
*/
GPos3 &GPos3::Set(const double &x, const double &y, const double &z)
{
	V[0] = x;
	V[1] = y;
	V[2] = z;
	return *this;
}

/*!
*	\brief 등호 및 부등호 연산자의 오차의 한계 설정
*
*	\param error 오차의 한계
*/
void GPos3::SetPrecision(double error)
{
	Precision = error;
}

/*!
*	\brief 설정된 오차의 한계를 반환
*
*	\return 설정된 오차의 한계
*/
double GPos3::GetPrecision()
{
	return Precision;
}

/*!
*	\brief 출력연산자(<<)
*
*	\param os 출력스트림
*	\param p 출력할 객체
*
*	\return 출력된 스트림 객체를 반환
*/
std::ostream &operator <<(std::ostream &os, const GPos3 &p)
{
	os << "(" << std::setw(5) << p.V[0] << ", " << std::setw(5) << p.V[1] << ", " << std::setw(5) << p.V[2] << ")";
	return os;
}

/*!
*	\brief 입력연산자(>>)
*
*	\param is 입력스트림
*	\param v 입력값이 저장될 벡터
*
*	\return 입력값이 제거된 입력스트림
*/
std::istream &operator >>(std::istream &is, GPos3 &p)
{
	is >> p.V[0] >> p.V[1] >> p.V[2];
	return is;
}

/*!
*	\brief 점 \a p의 길이를 구한다.
*
*	\param p 점
*
*	\return 점 \a p의 길이.
*/
double norm(const GPos3 &p)
{
	return SQRT(SQR(p.V[0]) + SQR(p.V[1]) + SQR(p.V[2]));
}

/*!
*	\brief 점 \a p에서 점 \a q까지의 거리를 구한다.
*
*	\param p 점
*	\param q 점
*
*	\return 점 \a p에서 점 \a q까지의 거리
*/
double dist(const GPos3 &p, const GPos3 &q)
{
	return SQRT(SQR(p.V[0] - q.V[0]) + SQR(p.V[1] - q.V[1]) + SQR(p.V[2] - q.V[2]));
}

/*!
*	\brief 점 \a p에서 점 \a q까지의 거리의 제곱을 구한다.
*
*	\param p 점
*	\param q 점
*
*	\return 점 \a p에서 점 \a q까지의 거리
*/
double dist_sq(const GPos3 &p, const GPos3 &q)
{
	return (SQR(p.V[0] - q.V[0]) + SQR(p.V[1] - q.V[1]) + SQR(p.V[2] - q.V[2]));
}

/*!
*	\brief 점 pt의 좌표를 벡터형태로 반환한다.
*
*	\param pt 3차원 공간의 점
*
*	\return pt의 3차원 벡터 표현
*/
GVec3 cast_GVec3(const GPos3 &pt)
{
	return GVec3(pt[0], pt[1], pt[2]);
}

/*!
*	\brief 점 p의 좌표를 주어진 자리수까지(반올림하여) 나타냄
*
*	\param p 3차원 공간의 점
*
*	\return 반올림된 점의 표현
*/
GPos3 round_off(const GPos3 &p, int place)
{
	double a = pow(10.0, -place);
	double x = ((int)(p[0] * a + 0.5)) / a;
	double y = ((int)(p[1] * a + 0.5)) / a;
	double z = ((int)(p[2] * a + 0.5)) / a;

	return GPos3(x, y, z);
}

/*!
*	\brief 벡터 v의 좌표를 포인트 형태로 반환
*
*	\param v 3차원 공간의 벡터
*
*	\return v의 좌표를 포인트 형태로 반환
*/
GPos3 cast_pt3(const GVec3 &v)
{
	return GPos3(v[0], v[1], v[2]);
}

/*!
*	\brief 점들의 affine combination을 구한다
*
*	\param N 점의 개수
*	\param alpha0 상수
*	\param p0 첫 번째 점
*	\param alpha1 상수
*	\param p1 첫 번째 점
*
*	\return 점들의 affine combination의 결과 (alpha0 * p0 + alpha1 * p1 + ... + alpha_n-1 * p_n-1)
*/
GPos3 affine_sum(int N, ...)
{
	GPos3 ret;

	va_list ap;
	va_start(ap, N);
	for (int i = 0; i < N; ++i)
	{
		double alpha = va_arg(ap, double);
		GPos3 p = va_arg(ap, GPos3);

		ret[0] = ret[0] + alpha * p[0];
		ret[1] = ret[1] + alpha * p[1];
		ret[2] = ret[2] + alpha * p[2];
	}
	va_end(ap);

	return ret;
}

/*!
*	\brief 점들의 affine combination을 구한다
*
*	\param Points 점의 배열에 대한 포인터
*	\param Weights combination의 상수값
*	\param Size 점의 개수 (Points, Weights 배열의 크기)
*
*	\return 점들의 affine combination의 결과 (= Point[0] * Weight[0] + Points[1] * Weight[1] + ... + Points[Size-1] * Weight[Size-1])
*/
GPos3 affine_sum(GPos3 *Points, double *Weights, const int Size)
{
	GPos3 ret;
	for (int i = 0; i < Size; i++)
	{	
		ret.V[0] += Points[i][0] * Weights[i];
		ret.V[1] += Points[i][1] * Weights[i];
		ret.V[2] += Points[i][2] * Weights[i];
	}
	return ret;
}

///////////////////////////////////////////////////////////
/*!
*	\brief 직선위의 한 점과 방향으로 직선을 생성하는 생성자.
*	
*	\param _p 직선위의 한 점
*	\param _v 직선의 방향 벡터.
*/
GLine::GLine(const GPos3 &_p, const GVec3 &_v)
{
	p = _p;
	v = _v;
	v.Normalize();
}

/*!
*	\brief 3차원 공간상의 두 점을 지나는 직선을 생성하는 생성자.
*	
*	\param _p 직선위의 점
*	\param _q 직선위의 점
*/
GLine::GLine(const GPos3 &_p, const GPos3 &_q)
{
	p = _p;
	v = _q - _p;
	v.Normalize();
}

/*!
*	\brief 복사생성자.
*	
*	\param copy 복사될 직선의 객체.
*/
GLine::GLine(const GLine &copy)
: p(copy.p), v(copy.v)
{
}

/*!
*	\brief 소멸자.
*/
GLine::~GLine()
{
}

/*!
*	\brief	대입연산자 중복
*	
*	\param rhs 오른쪽 피연산자.
*
*	\return 대입된 자신을 반환한다.
*/
GLine &GLine::operator =(const GLine &rhs)
{
	this->p = rhs.p;
	this->v = rhs.v;
	return *this;
}

/*!
*	\brief	함수호출연산자 중복
*			- 직선위의 매개변수 t에서의 점 l(t)를 구한다.
*	
*	\param t 매개변수.
*
*	\return 직선위의 점 l(t)를 반환한다.
*/
GPos3 GLine::Eval(const double t) const
{
	return p + t * v;
}

/*!
*	\brief	등호입연산자 중복.
*	
*	\param rhs 오른쪽 피연산자.
*
*	\return true: 같으면, false: 다르면.
*/
bool operator ==(const GLine &lhs, const GLine &rhs)
{
	if (lhs.IsOnLine(rhs.p) && EQ_ZERO(norm(lhs.v ^ rhs.v), GLine::Precision))
		return true;
	else
		return false;
}

/*!
*	\brief	부등호입연산자 중복.
*	
*	\param rhs 오른쪽 피연산자.
*
*	\return true: 다르면, false: 같으면.
*/
bool operator !=(const GLine &lhs, const GLine &rhs)
{
	return !(lhs == rhs);
}

/*!
*	\brief 점 q가 직선위의 점인지 조사한다.
*	
*	\param q 조사할 점.
*
*	\return true: q가 직선위의 점 일경우, false: 아닐경우.
*/
bool GLine::IsOnLine(const GPos3 &q) const
{
	GVec3 w = q - p;
	double s = norm(v ^ w);
	if (EQ_ZERO(s, Precision))
		return true;
	else
		return false;
}

/*!
*	\brief 출력연산자 중복.
*
*	\param os 출력스트림
*	\param l 출력할 라인객체
*
*	\return 출력된 스트림
*/
std::ostream &operator <<(std::ostream &os, const GLine &l)
{
	os << "(" 
		<< l.p[0] << " + (" << l.v[0] << ") * t, "
		<< l.p[1] << " + (" << l.v[1] << ") * t, "
		<< l.p[2] << " + (" << l.v[2] << ") * t)";
	return os;
}

/*!
*	\brief 한 점에서 직선까지의 거리를 구한다.
*
*	\param l 직선
*	\param q 한 점
*
*	\return 점 \a q에서 직선 \a l까지의 수직거리
*/
double dist(const GLine &l, const GPos3 &q)
{
	return norm(proj(q - l.p, l.v) - (q - l.p));
}

/*!
*	\brief 두 직선 l1(t)와 l2(t)사이의 최단 거리를 구한다.
*
*	\param l1 첫 번째 직선
*	\param l2 두 번째 직선
*	\param t1 최단 거리가 생기는 l1의 파리미터 값이 저장됨
*	\param t2 최단 거리가 생기는 l2의 파리미터 값이 저장됨
*
*	\return 두 직선 사이의 최단거리를 계산하여 반환한다 (두 직선이 만나는 경우 -1.0을 반환한다).
*/
double dist(const GLine &l1, const GLine &l2, double &t1, double &t2)
{
	GPos3 p1 = l1.p;
	GPos3 p2 = l2.p;
	GVec3 v1 = l1.v;
	GVec3 v2 = l2.v;

	double a11 = v1 * v1;
	double a12 = -v2 * v1;
	double a21 = v1 * v2;
	double a22 = -v2 * v2;
	double b1 = (p1 - p2) * v1;
	double b2 = (p1 - p2) * v2;
	double D = a11 * a22 - a12 * a21;

	double ret = 0.0;
	if (EQ_ZERO(D, 0.00001))
	{
		t1 = 0.0;
		t2 = 0.0;
		ret = -1.0;
	}
	else
	{
		t1 = (a22 * b1 - a12 * b2) / D;
		t2 = (-a21 * b1 + a11 * b2) / D;

		GPos3 q1 = l1.Eval(t1);
		GPos3 q2 = l2.Eval(t2);

		ret = dist(q1, q2);
	}

	return ret;
}

/*!
*	\brief 새로운 점을 지나도록 직선의 방정식을 변경한다 (방향은 변경없음).
*
*	\param _p 새로운 점
*
*	\return 변경된 자신을 반환한다.
*/
GLine &GLine::SetPt(const GPos3 &_p)
{
	p = _p;
	return *this;
}

/*!
*	\brief 직선의 방향을 변경한다.
*
*	\param _v 새로운 방향.
*
*	\return 변경된 자신을 반환한다.
*/
GLine &GLine::SetDir(const GVec3 &_v)
{
	v = _v;
	return *this;
}

/*!
*	\brief 직선의 시작점을 리턴한다.
*
*	\return 직선의 시작점.
*/
GPos3 GLine::GetPt() const
{
	return p;
}

/*!
*	\brief 직선의 방향을 리턴한다.
*
*	\return 직선의 방향.
*/
GVec3 GLine::GetDir() const
{
	return v;
}

/*!
*	\brief 수치오류의 한계치를 설정한다.
*/
void GLine::SetPrecision(double err)
{
	Precision = err;
}

/*!
*	\brief 수치오류의 한계치를 리턴한다.
*
*	\return 한계치.
*/
double GLine::GetPrecision()
{
	return Precision;
}

///////////////////////////////////////////////////////////

/*!
*	\brief 평면의 생성자.
*	
*	\param _n 생성되는 평면의 법선벡터
*	\param _p 생성되는 평면위의 임의의 한점
*/
GPlane::GPlane(const GVec3 &_n, const GPos3 &_p)
{
	n = _n;
	d = -(n[0] * _p[0] + n[1] * _p[1] + n[2] * _p[2]);
}

/*!
*	\brief 세 점 p1, p2, p3 를 지나는 평면의 생성자
*	
*	\param p1 평면상의 점.
*	\param p2 평면상의 점.
*	\param p3 평면상의 점.
*/
GPlane::GPlane(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3)
{
	n = (p2 - p1) ^ (p3 - p1);
	d = -(n[0] * p1[0] + n[1] * p1[1] + n[2] * p1[2]);
}

/*!
*	\brief 평면의 복사생성자
*	
*	\param copy 복사될 평면의 객체에 대한 레퍼런스
*/
GPlane::GPlane(const GPlane &cpy)
: n(cpy.n), d(cpy.d)
{
}

/*!
*	\brief 평면의 생성자.
*	
*	\param _n 법선벡터.
*	\param _d 상수 d = - n * p (p: 평면위의 임의의 점).
*/
GPlane::GPlane(const GVec3 &_n, const double &_d)
: n(_n), d(_d)
{
}

/*!
*	\brief 평면의 생성자.
*	
*	\param a, b, c, d 평면 방정식 ax + by + cz +d = 0 의 계수
*/
GPlane::GPlane(const double &a, const double &b, const double &c, const double &d)
{
	this->n = GVec3(a, b, c);
	this->d = d;
}

/*!
*	\brief 평면의 소멸자.
*/
GPlane::~GPlane()
{
}

/*!
*	\brief 대입연산자 중복
*	
*	\param rhs 오른쪽 피연산자
*
*	\return 대입된 자신을 반환한다.
*/
GPlane &GPlane::operator =(const GPlane &rhs)
{
	this->n = rhs.n;
	this->d = rhs.d;
	return *this;
}

/*!
*	\brief 법선벡터를 반환한다.
*
*	\return 법선벡터.
*/
GVec3 GPlane::GetNormal() const
{
	return n;
}

/*!
*	\brief 점 p가 평면상의 점 인지를 조사.
*	
*	\param p 조사할 점
*
*	\return true: 점 p가 평면상의 점 일경우, false: 그렇지 않을경우.
*/
bool GPlane::IsOnPlane(const GPos3 &p) const
{
	double s;
	s = -(n[0] * p[0] + n[1] * p[1] + n[2] * p[2]);
	if (EQ(s, d, GPlane::Precision))
		return true;
	else
		return false;
}

/*!
*	\brief 점 p가 평면의 위쪽 점인지를 조사.
*	
*	\param p 조사할 점
*
*	\return true: 점 p가 평면의 위쪽 점 일경우, false: 그렇지 않을경우.
*/
bool GPlane::IsAbovePlane(const GPos3 &p) const
{
	double s;
	s = n[0] * p[0] + n[1] * p[1] + n[2] * p[2] + d;
	if (s > 0.0)
		return true;
	else
		return false;
}

/*!
*	\brief 점 p가 평면의 아래쪽 점인지를 조사.
*	
*	\param p 조사할 점
*
*	\return true: 점 p가 평면의 아래쪽 점 일경우, false: 그렇지 않을경우.
*/
bool GPlane::IsBelowPlane(const GPos3 &p) const
{
	double s;
	s = n[0] * p[0] + n[1] * p[1] + n[2] * p[2] + d;
	if (s < 0.0)
		return true;
	else
		return false;
}

/*!
*	\brief 수치오류의 한계치를 설정한다.
*/
void GPlane::SetPrecision(const double err)
{
	Precision = err;
}

/*!
*	\brief 수치오류의 한계치를 리턴한다.
*
*	\return 한계치.
*/
double GPlane::GetPrecision()
{
	return Precision;
}

/*!
*	\brief 출력연산자 중복.
*
*	\param os 출력스트림.
*	\param pi 출력할 평면객체.
*
*	\return 출력스트림
*/
std::ostream &operator <<(std::ostream &os, const GPlane &pi)
{
	os << "(" << pi.n[0] << ") * x + (" 
		<< pi.n[1] << ") * y + ("
        << pi.n[2] << ") * z + ("
		<< pi.d << ") = 0";
	return os;
}

/*!
*	\brief	평면 pi에서 점 p까지의 부호있는 거리를 계산한다.
*
*	\param pi 평면의 객체.
*	\param p 평면 밖의 한점.
*
*	\return 평면 \a pi에서 점 \a p까지의 부호있는 거리
*/
double dist(const GPlane &pi, const GPos3 &p)
{
    double D;
	D = (p[0] * pi.n[0] + p[1] * pi.n[1] + p[2] * pi.n[2] + pi.d) / norm(pi.n);
	return D;
}

/*!
*	\brief	점 p를 평면 pi에 사영시킨 점을 구한다.
*
*	\param p 평면 밖의 점.
*	\param pi 평면객체.
*/
GPos3 proj(const GPos3 &p, const GPlane &pi)
{
	double s = -dist(pi, p) / norm(pi.n);
	return p + s * pi.n;
}

/*!
*	\brief	직선과 직선의 교차점을 계산한다.
*
*	\param p 교차점이 저장될 변수
*	\param l0 첫번째 직선의 방정식 (ruling line)
*	\param l1 두번째 직선의 방정식 (boundary line)
*	\param t0 첫번째 직선위 교차점의 파라미터 값이 저장됨
*	\param t1 두번째 직선위 교차점의 파라미터 값이 저장됨
*
*	\return true: 성공, false: 직선이 꼬인 위치에 있거나, (0 ~ 1)사이를 벗어날 경우
*/
bool intersect_line_line(GPos3 &p, const GLine &l0, const GLine &l1, double &t0, double &t1)
{
	double a = l0.v[0];
	double b = -l1.v[0];
	double c = l0.v[1];
	double d = -l1.v[1];
	double e = l1.p[0] - l0.p[0];
	double f = l1.p[1] - l0.p[1];

	double det = a * d - b * c;
	if (EQ(det, 0.0, 1.0e-6))
		return false;

	t0 = (d * e - b * f) / det;
	t1 = (a * f - c * e) / det;

	if (EQ(t0, 0.0, 1.0e-6))
		t0 = 0.0;

	if (EQ(t0, 1.0, 1.0e-6))
		t0 = 1.0;

	if (EQ(t1, 0.0, 1.0e-6))
		t1 = 0.0;

	if (EQ(t1, 1.0, 1.0e-6))
		t1 = 1.0;

	if (t0 < 0.0 || t0 > 1.0)
		return false;

	if (t1 < 0.0 || t1 > 1.0)
		return false;

	// p = l0.Eval(t0);
	p = l1.Eval(t1);

	return true;
}

/*!
*	\brief	직선과 직선의 교차점을 계산한다.
*
*	\param p 교차점이 저장될 변수
*	\param l0 첫번째 직선의 방정식 (ruling line)
*	\param l1 두번째 직선의 방정식 (boundary line)
*
*	\return true: 성공, false: 직선이 꼬인 위치에 있는 경우
*/
bool intersect_line_line2(GPos3 &p, GLine &l0, GLine &l1)
{
	double a = l0.v[0];
	double b = -l1.v[0];
	double c = l0.v[1];
	double d = -l1.v[1];
	double e = l1.p[0] - l0.p[0];
	double f = l1.p[1] - l0.p[1];

	double det = a * d - b * c;
	if (EQ(det, 0.0, 0.00001))
		return false;

	double t0, t1;
	t0 = (d * e - b * f) / det;
	t1 = (a * f - c * e) / det;

	// p = l0.Eval(t0);
	p = l1.Eval(t1);

	return true;
}

/*!
*	\brief	직선과 평면의 교차점을 계산한다.
*
*	\param p 교차점이 저장될 변수.
*	\param l 직선 객체.
*	\param pi 평면 객체.
*
*	\return true: 성공, false: 직선이 평면과 평행하거나, 평면이 직선을 포함하는 경우.
*/
bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi)
{
	if (EQ_ZERO(l.v * pi.n, GPlane::Precision))
	{
		std::cout << "line is parallel to plane !" << std::endl;
		return false;
	}

	double t = -(l.p[0] * pi.n[0] + l.p[1] * pi.n[1] + l.p[2] * pi.n[2] + pi.d) / (l.v * pi.n);
	p = l.Eval(t);
    return true;
}

/*!
*	\brief	직선과 삼각형 (p1p2p3)의 교차점을 계산한다.
*
*	\param p1 삼각형의 정점
*	\param p2 삼각형의 정점
*	\param p3 삼각형의 정점
*	\param l 직선의 방정식
*	\param t q = l(t)를 만족하는 직선의 파라미터
*	\param q 교차점이 저장됨
*	\param alpha barycentric 좌표가 저장됨
*	\param beta barycentric 좌표가 저장됨
*	\param gamma barycentric 좌표가 저장됨
*	\param bCullBackFace 직선이 삼각형의 뒷면과 만나는 경우를 제외하려면. (디폴트: true).
*	\note q = alpha * p1 + beta * p2 + gamma * p3, (alpha + beta + gamma = 1)
*
*	\return true: 성공, false: 직선이 삼각형이 평행하거나 교차점이 삼각형의 외부에 존재하는 경우.
*/
bool intersect_line_triangle(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3, const GLine &l, double &t, GPos3 &q, double &alpha, double &beta, double &gamma, const bool bCullBackFace)
{
	GVec3 e1, e2, u, v, w;
	double det;
	e1 = p1 - p3;
	e2 = p2 - p3;
	u = l.v ^ e2;
	det = e1 * u;

	if (bCullBackFace)	// 직선이 삼각형의 뒷면과 만나는 경우는 제외.
	{
		if (det < GLine::Precision)
			return false;

		w = l.p - p3;
		alpha = w * u;
		if (alpha < 0.0 || alpha > det)
			return false;

		v = w ^ e1;
		beta = l.v * v;
		if (beta < 0.0 || alpha + beta > det)
			return false;

		t = e2 * v;

		alpha /= det;
		beta /= det;
		t /= det;
	}
	else
	{
		if (det > -GLine::Precision && det < GLine::Precision)
			return false;

		w = l.p - p3;
		alpha = w * u / det;
		if (alpha < 0.0 || alpha > 1.0)
			return false;

		v = w ^ e1;
		beta = l.v * v / det;
		if (beta < 0.0 || alpha + beta > 1.0)
			return false;

		t = e2 * v / det;
	}

	gamma = 1.0 - alpha - beta;
	q = l.Eval(t);
	return true;
}

//////////////////////////////////////////////////////////////
GSphere::GSphere(GPos3 _Pos, double _Rad)
{
	Pos = _Pos;
	Rad = _Rad;
}


GSphere::GSphere(const GSphere &cpy)
{
	Pos = cpy.Pos;
	Rad = cpy.Rad;
	Ka = cpy.Ka;
	Kd = cpy.Kd;
	Ks = cpy.Ks;
	ns = cpy.ns;
}

GSphere::~GSphere()
{
}

GSphere &GSphere::operator =(const GSphere &rhs)
{
	Pos = rhs.Pos;
	Rad = rhs.Rad;
	Ka = rhs.Ka;
	Kd = rhs.Kd;
	Ks = rhs.Ks;
	ns = rhs.ns;
	
	return *this;
}

//////////////////////////////////////////////////////////////
GLight::GLight(GPos3 _Pos, GVec3 _Ia, GVec3 _Id, GVec3 _Is)
{
	Pos = _Pos;
	Ia = _Ia;
	Id = _Id;
	Is = _Is;
}

GLight::GLight(const GLight &cpy)
{
	Pos = cpy.Pos;
	Ia = cpy.Ia;
	Id = cpy.Id;
	Is = cpy.Is;
}

GLight::~GLight()
{
}

GLight &GLight::operator = (const GLight &rhs)
{
	Pos = rhs.Pos;
	Ia = rhs.Ia;
	Id = rhs.Id;
	Is = rhs.Id;

	return *this;
}
