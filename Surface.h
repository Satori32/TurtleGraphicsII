#pragma once
#include <vector>
#include <tuple>
template<class T>
class Surface {
public:

	typedef T Value;

	Surface() {}
	Surface(std::size_t Width, std::size_t Height) { Resize(Width, Height); }

	bool Resize(std::size_t Width, std::size_t Height) {
		D.clear();
		D.resize(Height);
		for (auto& o : D) {
			o.resize(Width);
		}
		W = Width;
		H = Height;

		return true;
	}
	bool SetPixel(std::size_t X, std::size_t Y, const Value& V) {
		if (X >= W) { return false; }
		if (Y >= H) { return false; }
		D[Y][X] = V;
		return 0;
	}

	std::size_t Width() const{
		return W;
	}
	std::size_t Height() const{
		return H;
	}
	std::tuple<bool, T&> Index(std::size_t X, std::size_t Y) {
		if (X >= W) { return { false,DeadBeef }; }
		if (Y >= H) { return { false,DeadBeef }; }
		return { true,D[Y][X] };
	}	
	std::tuple<bool, const T&> Index(std::size_t X, std::size_t Y) const{
		if (X >= W) { return { false,DeadBeef }; }
		if (Y >= H) { return { false,DeadBeef }; }
		return { true,D[Y][X] };
	}
	bool Clear() {
		D.clear();
	}
	typename std::vector<std::vector<T>>::iterator begin() {
		return D.begin();
	}
	typename std::vector<std::vector<T>>::iterator end() {
		return D.end();
	}	
	typename std::vector<std::vector<T>>::const_iterator begin() const{
		return D.cbegin();
	}
	typename std::vector<std::vector<T>>::const_iterator end() const{
		return D.cend();
	}
protected:
	std::vector<std::vector<T>> D;
	std::size_t W = 0;
	std::size_t H = 0;
	T DeadBeef = {};
};