#ifndef _GMATH_H
#define _GMATH_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <iomanip>
#include <vector>

// 매크로 상수
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616

// 매크로 정의
#define SQRT(X)		sqrt((X))
#define SQR(X)		((X) * (X))
#define DEG2RAD(X)	((X) * (M_PI) / (180.0))
#define RAD2DEG(X)	((X) * (180.0) / (M_PI))
#define SWAP(type, x, y) { type temp = (x); (x) = (y); (y) = temp; }
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define ABS(X)		(((X) > 0.0) ? (X) : (-(X)))
#define SIGN(a)		((a) > 0.0 ? (1.0) : (-1.0))
#define SIGN1(a, b) ((b) > 0.0 ? ABS(a) : -ABS(a))
#define SIGN2(a, b)	((b) >= 0.0 ? fabs(a) : -fabs(a))
#define PYTHAG(a, b) SQRT((SQR(a) + SQR(b)))
#define EQ(X, Y, EPS)	(ABS((X) - (Y)) < EPS)
#define EQ_ZERO(X, EPS) (ABS(X) < EPS)
#define ARR_ZERO(A, N) memset((A), 0, sizeof(A[0]) * (N))
#define ARR_COPY(D, S, N) memmove((D), (S), sizeof(S[0]) * (N))
#define ARR_COPY_2D(D, S, M, N) \
	for (int i = 0; i < (M); ARR_COPY(D[i], S[i], N), ++i);
#define ARR_ALLOC(D, TYPE, N) D = new TYPE [(N)]
#define ARR_ALLOC_2D(D, TYPE, M, N) \
	D = new TYPE *[(M)]; \
	for (int i = 0; i < (M); D[i] = new TYPE [(N)], ++i);
#define ARR_FREE(D) \
	delete [] D; \
	D = NULL
#define ARR_FREE_2D(D, M) \
	for (int i = 0; i < (M); delete [] D[i], ++i); \
	delete [] D; \
	D = NULL
#define MTYPE_EPS	1.0e-15

// 클래스 선언.
class GVec3;
class GPos3;
class GLine;
class GPlane;

/*!
*	\class GVec3
*	\brief 3차원 벡터를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GVec3
{
	// 프렌드 함수 및 클래스
	friend GVec3 operator +(const GVec3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs);
	friend GVec3 operator -(const GVec3 &lhs, const GVec3 &rhs);
	friend GVec3 operator *(const GVec3 &lhs, const double &s);
	friend GVec3 operator *(const double &s, const GVec3 &rhs);
	friend double operator *(const GVec3 &lhs, const GVec3 &rhs);
	friend GVec3 operator /(const GVec3 &lhs, const double &s);
	friend GVec3 operator ^(const GVec3 &lhs, const GVec3 &rhs);
	friend bool operator ==(const GVec3 &lhs, const GVec3 &rhs);
	friend bool operator !=(const GVec3 &lhs, const GVec3 &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GVec3 &v);
	friend std::istream &operator >>(std::istream &is, GVec3 &v);
	friend GVec3 proj(const GVec3 &v, const GVec3 &w);
	friend GVec3 ortho(const GVec3 &v);
	friend double dist(const GVec3 &v, const GVec3 &w);
	friend double det(const GVec3 &u, const GVec3 &v, const GVec3 &w);
	friend double norm(const GVec3 &v);
	friend double angle(const GVec3 &v, const GVec3 &w, bool radian = false);
	friend double angle(const GVec3 &v, const GVec3 &w, const GVec3 &up, bool radian = false);
	friend GPos3 cast_pt3(const GVec3 &v);
	
public:
	// 생성자 및 소멸자
	GVec3(double x = 0.0, double y = 0.0, double z = 0.0);
	GVec3(const GVec3 &cpy);
	~GVec3();

	// 대입 및 복합대입연산자
	GVec3 &operator =(const GVec3 &rhs);
	GVec3 &operator +=(const GVec3 &rhs);
	GVec3 &operator -=(const GVec3 &rhs);
	GVec3 &operator *=(const double &s);
	GVec3 &operator /=(const double &s);
	GVec3 &operator ^=(const GVec3 &rhs);

	// 단항연산자
	GVec3 operator +() const;
	GVec3 operator -() const;

	// 첨자연산자
	double &operator [](const int &idx);
	const double &operator [](const int &idx) const;

	// 멤버함수
	GVec3 &Set(const double &x, const double &y, const double &z);
	GVec3 &Normalize();
		
	// 정적맴버함수
	static void SetPrecision(double error);
	static double GetPrecision();

public:
	// 데이터 멤버
	/*! \brief 3차원 벡터의 원소를 저장하는 실수 배열 */
	double V[3];

	/*! \brief 등호 및 부등호연산자의 오차한계 */
	static double Precision;
};

/*!
*	\class GPos3
*	\brief 3차원 공간의 위치를 나타내는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GPos3
{
	// 프렌드 함수 및 클래스
	friend GVec3 operator -(const GPos3 &lhs, const GPos3 &rhs);
	friend GPos3 operator -(const GPos3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GPos3 &lhs, const GVec3 &rhs);
	friend GPos3 operator +(const GVec3 &lhs, const GPos3 &rhs);
	friend bool operator ==(const GPos3 &lhs, const GPos3 &rhs);
	friend bool operator !=(const GPos3 &lhs, const GPos3 &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GPos3 &p);
	friend std::istream &operator >>(std::istream &is, GPos3 &p);
	friend double norm(const GPos3 &p);
	friend double dist(const GPos3 &p, const GPos3 &q);
	friend double dist_sq(const GPos3 &p, const GPos3 &q);
	friend GPos3 affine_sum(int N, ...);
	friend GPos3 affine_sum(GPos3 *Points, double *Weights, const int Size);
	friend GVec3 cast_GVec3(const GPos3 &p);
	friend GPos3 round_off(const GPos3 &p, int place);
	
public:
	// 생성자 및 소멸자
	GPos3(double x = 0.0, double y = 0.0, double z = 0.0);
	GPos3(const GPos3 &cpy);
	~GPos3();

	// 대입연산자
	GPos3 &operator =(const GPos3 &rhs);
	GPos3 &operator +=(const GVec3 &rhs);

	// 첨자연산자
	double &operator [](const int &idx);
	const double &operator [](const int &idx) const;

	// 멤버함수
	GPos3 &Set(const double &x, const double &y, const double &z);
	
	// 정적함수
	static void SetPrecision(double error);
	static double GetPrecision();
   
public:
	/*! \brief 3차원 벡터의 원소를 저장하는 실수배열 */	
	double V[3];	
	/*! \brief 등호 및 부등호연산자의 오차한계 */
	static double Precision;	
};

/*!
*	\class GLine
*	\brief 3차원 공간의 직선을 나타내는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GLine
{
	// 프렌드 함수 및 클래스
	friend bool operator ==(const GLine &lhs, const GLine &rhs);
	friend bool operator !=(const GLine &lhs, const GLine &rhs);
	friend std::ostream &operator <<(std::ostream &os, const GLine &l);
	friend double dist(const GLine &l, const GPos3 &q);
	friend double dist(const GLine &l0, const GLine &l1, double &t1, double &t2);
	friend bool intersect_line_line(GPos3 &p, const GLine &l0, const GLine &l1, double &t0, double &t1);
	friend bool intersect_line_line2(GPos3 &p, GLine &l0, GLine &l1);
	friend bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi);
	friend bool intersect_line_triangle(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3, const GLine &l, double &t, GPos3 &q, double &alpha, double &beta, double &gamma, const bool bCull = true);
	friend bool intersect_planes(GLine &l, const GPlane &pi1, const GPlane &pi2);
	
public:
	// 생성자 및 소멸자
	GLine(const GPos3 &_p = GPos3(0, 0, 0), const GVec3 &_v = GVec3(0, 0, 0));
	GLine(const GPos3 &_p, const GPos3 &_q);
	GLine(const GLine &cpy);
	~GLine();

	// 대입연산자
	GLine &operator =(const GLine &rhs);
	
	// 멤버함수
	GLine &SetPt(const GPos3 &_p);
	GLine &SetDir(const GVec3 &_v);
	GPos3 GetPt() const;
	GVec3 GetDir() const;
	bool IsOnLine(const GPos3 &q) const;
	GPos3 Eval(const double t) const;

	// 정적멤버함수
	static void SetPrecision(double err);
	static double GetPrecision();

public:
	// 데이터 멤버.
	/*! \brief 직선위의 한 점 */
	GPos3 p;
	/*! \brief 직선의 방향 벡터 l(t) = p + v * t */
	GVec3 v;
	/*! \brief 등호 및 부등호연산자의 오차한계 */
	static double Precision;
};

/*!
*	\class GPlane
*	\brief 평면을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 01 Jan 2001	
*/
class GPlane
{
	// 프렌드 함수 및 클래스
	friend std::ostream &operator <<(std::ostream &os, const GPlane &pi);
	friend double dist(const GPlane &pi, const GPos3 &p);
	friend GPos3 proj(const GPos3 &p, const GPlane &pi);
	friend bool intersect_line_plane(GPos3 &p, const GLine &l, const GPlane &pi);
	
public:
	// 생성자 및 소멸자
	GPlane(const GVec3 &_n, const GPos3 &_p);
	GPlane(const GPos3 &p1, const GPos3 &p2, const GPos3 &p3);
	GPlane(const GVec3 &_n, const double &_d);
	GPlane(const double &a, const double &b, const double &c, const double &d);
	GPlane(const GPlane &cpy);
	~GPlane();

	// 대입연산자
	GPlane &operator =(const GPlane &rhs);
	
	// 멤버함수
	GVec3 GetNormal() const;
    bool IsOnPlane(const GPos3 &p) const;
	bool IsAbovePlane(const GPos3 &p) const;
	bool IsBelowPlane(const GPos3 &p) const;

	// 정적함수
	static void SetPrecision(const double err);
	static double GetPrecision();
    
public:
	// 데이터 멤버
	/*! \brief 평면의 방정식(ax + by + cz + d = 0)에서 법선 벡터 n=(a, b, c) */
	GVec3 n;
	/*! \brief 평면의 방정식(ax + by + cz + d = 0)에서 상수 d(= -n * p) */
	double d;
	/*! \brief 등호 및 부등호연산자의 오차한계 */
	static double Precision;
};

/*!
*	\class GSphere
*	\brief 3차원 구를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 18 Sept. 2016	
*/
class GSphere
{
public:
	// 생성자 및 소멸자
	GSphere(GPos3 _Pos = GPos3(0.0, 0.0, 0.0), double _Rad = 0.0);
	GSphere(const GSphere &cpy);
	~GSphere();

	// 대입 연산자 
	GSphere &operator =(const GSphere &rhs);

public:
	// 데이터 멤버
	GPos3 Pos;		// 구의 중심의 위치
	double Rad;		// 구의 반지름
	GVec3 Ka;		// 주변광 반사계수
	GVec3 Kd;		// 난반사 계수
	GVec3 Ks;		// 전반사 계수	
	double ns;		// 전반사 지수
};

/*!
*	\class GLight
*	\brief 3차원 공간의 조명을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date 18 Sept. 2016	
*/
class GLight
{
public:
	// 생성자 및 소멸자
	GLight(GPos3 _Pos = GPos3(), GVec3 _Ia = GVec3() , GVec3 _Id = GVec3() , GVec3 _Is = GVec3());
	GLight(const GLight &cpy);
	~GLight();

	// 대입 연산자
	GLight &operator = (const GLight &rhs);

public:
	// 데이터 멤버
	GPos3 Pos;		// 광원의 위치
	GVec3 Ia;		// 주변광 성분
	GVec3 Id;		// 난반사광 성분
	GVec3 Is;		// 전반사광 성분
};




#endif // _GMATH_H