#pragma once
#include <cmath>
#include <tuple>

#include "Surface.h"

template<class T>
class TurtleGraphics {
public:

	typedef T Color;
	//typedef std::tuple<std::intmax_t, std::intmax_t> Point2;
	typedef std::tuple<double, double> Point2;

	TurtleGraphics() {}
	TurtleGraphics(std::size_t Width, std::size_t Height):S(Width,Height) {}

	bool Angel(const double& In) {
		A = std::abs(In);
		return true;
	}
	bool Turn(const double& In) {
		A -= In;
		A = std::abs(A+360);
		A = std::fmod(A+360, 360.0);
		return true;
	}
	bool SetPoint(const double& X, const double& Y) {
		P = Point2{ X,Y };
		return true;
	}
	Point2 GetPoint() {
		return P;
	}
	bool Move(const double& L) {
		double X = std::sin(A * Rad) * L;
		double Y = std::cos(A * Rad) * L;

		Line(std::get<0>(P), std::get<1>(P), X, Y);
		
		std::get<0>(P) += X;
		std::get<1>(P) += Y;

		return true;
	}
	bool Resize(std::size_t W, std::size_t H) {
		return S.Resize(W, H);
	}
	bool MovePoint(const double& X, const double& Y) {
		std::get<0>(P) += X;
		std::get<1>(P) += Y;
		return true;
	}
	bool Clear() {
		S.Clear();
		C = Color();
		P = Point2();
		O = Point2();
		A = 0;
	}

	bool SetOrigin(const double& X, const double& Y) {
		O = Point2(X, Y);
		return true;
	}
	bool MoveOrigin(const double& X, const double& Y) {
		std::get<0>(O) += X;
		std::get<1>(O) += Y;
	}
	const Color& GetColor() {
		return C;
	}
	bool SetColor(const Color& In) {
		C = In;
		return true;
	}
	const Point2 GetOrigin() {
		return O;
	}
	double GetAngle() {
		return A;
	}
	const Surface<T>& GetSurface() {
		return S;
	}

	bool SetPixelAbsolute(double X, double Y) {
		if (X < 0) { return false; }
		if (Y < 0) { return false; }
		if (X >= S.Width()) { return false; }
		if (Y >= S.Height()) { return false; }

		auto&& A = S.Index(X, Y);
		if (std::get<0>(A)) { std::get<1>(A) = C; }
		return std::get<0>(A);
	}

	bool SetPixel(double X, double Y) {
		X = X + std::get<0>(O);
		Y = Y + std::get<1>(O);
		if (X < 0) { return false; }
		if (Y < 0) { return false; }
		if (X >= S.Width()) { return false; }
		if (Y >= S.Height()) { return false; }
		double XA = !RightIsForward ? Width()- X: X;
		double YA = TopIsUp ? Height()-Y : Y;

		auto&& A = S.Index(XA,YA);
		if (std::get<0>(A)) { std::get<1>(A) = C; }
		return std::get<0>(A);
	}  
	std::size_t Width() {
		return S.Width();
	}
	std::size_t Height() {
		return S.Height();
	}
	bool SetTopIsUp(bool In) {
		TopIsUp = In;
		return true;
	}
	bool SetRightIsForward(bool In) {
		RightIsForward = In;
		return true;
	}
	bool GetTopIsUp() {
		return TopIsUp;
	}
	bool GetRightIsForward() {
		return RightIsForward;
	}
	bool Line(double x0, double y0, double x1, double y1) {
		double dx = std::abs((double)(x1)-(double)(x0));
		double dy = std::abs((double)(y1)-(double)(y0));
		double sx = (x0 < x1) ? sx = 1 : sx = -1;
		double sy = (y0 < y1) ? sy = 1 : sy = -1;
		double err = dx - dy;

		while (true) {
			SetPixel(x0, y0);

			double X = std::abs(x1 - x0);
			double Y = std::abs(y1 - y0);

			if (std::hypot(X, Y) <= 1) {
				break;
			}

			double e2 = 2 * err;

			if (e2 > -dy) {
				err = err - dy;
				x0 = x0 + sx;
			}
			if (e2 < dx) {
				err = err + dx;
				y0 = y0 + sy;
			}
		}
		return true;
	}

protected:
	Surface<T> S;
	Color C = Color();
	Point2 P;
	Point2 O = Point2(0, 0);
	double A = 0;
	double Rad = 3.1415926535 / 180.0;
	bool TopIsUp = true;
	bool RightIsForward = true;
};