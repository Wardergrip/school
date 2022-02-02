#include "rdebug.h"
#include "pch.h"
#include <iostream>

using namespace utils;
namespace rdebug
{
	void Print(const Rectf& rect, const std::string& name = "")
	{
		std::cout << "Rectf " << name << " [X:" << rect.left << " Y:" << rect.bottom << " W:" << rect.width << " H:" << rect.height << " ]\n";
	}

	void Print(const Point2f& pos, const std::string& name = "")
	{
		std::cout << "Point2f " << name << " [X:" << pos.x << " Y:" << pos.y << " ]\n";
	}

	void Print(const Color4f& col, const std::string& name = "")
	{
		std::cout << "Color4f " << name << " [R:" << col.r << " G:" << col.g << " B:" << col.b << " A:" << col.a << " ]\n";
	}

	void Print(const Circlef& circ, const std::string& name = "")
	{
		std::cout << "Circlef " << name << " [X:" << circ.center.x << " Y:" << circ.center.y << " R:" << circ.radius << " ]\n";
	}

	void Print(const Ellipsef& ell, const std::string& name = "")
	{
		std::cout << "Ellipsef " << name << " [X:" << ell.center.x << " Y:" << ell.center.y << " Rx:" << ell.radiusX << " Ry:" << ell.radiusY << " ]\n";
	}

	void Print(const Texture& txt, const std::string& name)
	{
		std::cout << "Texture " << name << " [ID:" << txt.id << " W:" << txt.width << " H:" << txt.height << " ]\n";
	}
}