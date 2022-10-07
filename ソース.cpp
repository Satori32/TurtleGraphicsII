#include <iostream>

#include "TurtleGraphics.h"
#include "EscapeSequence.h"

using namespace ESS;


struct RGBA16
{
	union {
		struct {
			std::uint16_t R : 5;
			std::uint16_t G : 5;
			std::uint16_t B : 5;
			std::uint16_t A : 1;
		};
		std::uint16_t C = 0;
	};
};

typedef TurtleGraphics<RGBA16> TG16;
typedef TurtleGraphics<std::uint8_t> TG8;

bool Show(TG8& TG) {
	for (auto& o : TG.GetSurface()) {
		for (auto& C : o) {
			if (C == 0) { std::cout << ' '; }
			else {
				std::cout << C;
			}
		}
		std::cout << std::endl;
	}
	return true;
}

int main() {
	TG8 TG(79, 20);
	TG8::Color C = '*';
	TG.SetColor(C);
/** /
	//TG.Line(10, 10, 20, 20);
	TG.Turn(45);
	TG.Move(8);
	Show(TG);
/**/
	ClearShow();	
	Locate(0, 0);
	TG.SetOrigin(39, 9);
	TG.Angel(90);
	TG.Move(38);
	Show(TG);
	double L = 8;
	TG.SetPoint(0, 0);
	for (std::size_t i = 0; i < 360; i++) {
		ClearShow();
		Show(TG);
		Locate(0, 0);
		TG.Angel(i);
		TG.Move(L);
		TG.SetPoint(0, 0);

	}

	return 0;

}