#pragma once
#include "utils.h"
#include "structs.h"

namespace rdebug
{
	void Print(const Rectf& rect, const std::string& name = "");
	void Print(const Point2f& pos, const std::string& name = "");
	void Print(const Color4f& col, const std::string& name = "");
	void Print(const Circlef& circ, const std::string& name = "");
	void Print(const Ellipsef& ell, const std::string& name = "");
	void Print(const Texture& txt, const std::string& name = "");
}