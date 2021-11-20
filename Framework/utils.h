#pragma once
#include "structs.h"
#include <vector>

namespace utils
{

	const float g_Pi{ 3.1415926535f };

#pragma region OpenGLDrawFunctionality
	void ClearBackground(float r, float g, float b);
	void ClearBackground();
	// Choose a floating point value for each color component between 0.0f and 1.0f. The a (alpha) is optional.
	// Usage: SetColor(1.0f, 0.0f, 0.0f); set the drawing color to red
	void SetColor(float r, float g, float b, float a = 1);
	// Pass a Color4f object to the function
	void SetColor(const Color4f& color);

	// Draws a line by connecting the two points specified by (x1,y1) and (x2,y2)
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	// Draws a line by connecting the two points specified by p1 and p1
	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f);

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth = 1);
	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3);
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const Point2f& bottomLeft, float width, float height);
	void FillRect(const Rectf& rect);

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const Ellipsef& ellipse, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const Ellipsef& ellipse);
	void FillEllipse(const Point2f& center, float radX, float radY);

	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Draws an arc. The angle parameters are in radians, not in degrees.
	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	// Fills an arc. The angle parameters are in radians, not in degrees.
	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle);

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f);
	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const std::vector<Point2f>& vertices);
	void FillPolygon(const Point2f* pVertices, size_t nrVertices);
#pragma endregion OpenGLDrawFunctionality

#pragma region MyAdditions
	int GenerateRandom(int minValue, int maxValue);

	Color4f RandomColor();

	void DrawSquares(const Point2f& BottomLeft, float size, float numberOfSquares = 1);
	void DrawSquares(float x, float y, float size, float numberOfSquares = 1);

	void DrawEquilateralTriangle(float x, float y, float size, bool isFilled = 0);
	void DrawEquilateralTriangle(const Point2f& bottomLeft, float size, bool isFilled = 0);

	void DrawPentagram(const Point2f& centerpoint, float radius, float startingAngle = 0, float thickness = 1);
	void DrawPentagram(float x, float y, float radius, float startingAngle = 0, float thickness = 1);

	void DrawLinearGradient(float x, float y, float width, float height, const Color4f& left, const Color4f& right);
	void DrawLinearGradient(const Point2f& bl, float width, float height, const Color4f& left, Color4f& right);
	void DrawLinearGradient(const Rectf& rectf, const Color4f& left, const Color4f& right);

	void DrawDotGrid(float x, float y, float radius, float rows = 3, float columns = 3, float dotSpace = 0);
	void DrawDotGrid(const Point2f& bottomLeft, float radius, float rows = 3, float columns = 3, float dotSpace = 0);

#pragma endregion MyAdditions

#pragma region TextureFunctionality

	struct Texture
	{
		GLuint id;
		float width;
		float height;
	};
	bool TextureFromFile(const std::string& path, Texture& texture);
	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor, Texture& texture);
	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture);
	void TextureFromSurface(const SDL_Surface* pSurface, Texture& textureData);
	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect = {});
	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect = {});
	void DeleteTexture(Texture& texture);
#pragma endregion TextureFunctionality

#pragma region CollisionFunctionality 
	// Also my adittions
	//
	// GetDistance
	//
	float GetDistance(float x1, float y1, float x2, float y2);
	float GetDistance(Point2f p1, Point2f p2);
	float GetDistance(Point2f p1, float x2, float y2);
	float GetDistance(float x1, float y1, Point2f p2);
	//
	// IsPointInCircle
	//
	bool IsPointInCircle(const Circlef& circle, const Point2f& point);
	// Overloading
	bool IsPointInCircle(const Circlef& circle, float pointX, float pointY);
	bool IsPointInCircle(const Point2f& center, float radius, const Point2f& point);
	bool IsPointInCircle(const Point2f& center, float radius, float pointX, float pointY);
	bool IsPointInCircle(float centerX, float centerY, float radius, const Point2f& point);
	bool IsPointInCircle(float centerX, float centerY, float radius, float pointX, float pointY);
	//
	// IsPointInRect
	//
	bool IsInsideRect(float rectX, float rectY, float rectW, float rectH, float pointX, float pointY);
	bool IsInsideRect(const Point2f& rectXY, float rectW, float rectH, const Point2f& point);
	bool IsInsideRect(float rectX, float rectY, float rectW, float rectH, const Point2f& point);
	bool IsInsideRect(const Point2f& rectXY, float rectW, float rectH, float pointX, float pointY);
	bool IsInsideRect(const Rectf& rect, const Point2f& point);
	bool IsInsideRect(const Rectf& rect, float pointX, float pointY);
	//
	// IsOverlapping
	//
	// Case Rect
	bool IsOverlapping(const Rectf& first, const Rectf& second);
	// Overloading
	bool IsOverlapping(const Point2f& firstBottomLeft, float firstWidth, float firstHeight, const Point2f& secondBottomLeft, float secondWidth, float secondHeight);
	bool IsOverlapping(float firstPointX, float firstPointY, float firstWidth, float firstHeight, float secondPointX, float secondPointY, float secondWidth, float secondHeight);
	// Case Circle
	bool IsOverlapping(const Circlef& first, const Circlef& second);
	// Overloading
	bool IsOverlapping(const Point2f& firstCenter, float firstRadius, const Point2f& secondCenter, float secondRadius);
	bool IsOverlapping(float firstCenterX, float firstCenterY, float firstRadius, float secondCenterX, float secondCenterY, float secondRadius);
#pragma endregion CollisionFunctionality
}