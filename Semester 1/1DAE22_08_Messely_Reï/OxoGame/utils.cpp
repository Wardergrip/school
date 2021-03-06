#include "pch.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
#include <algorithm>
#include <iostream>
#include "utils.h"

namespace utils
{
#pragma region OpenGLDrawFunctionality
	void ClearBackground(float r, float g, float b)
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void ClearBackground()
	{
		ClearBackground(185.0f / 255.0f, 211.0f / 255.0f, 238.0f / 255.0f);
	}
	void SetColor(float r, float g, float b, float a)
	{
		glColor4f(r, g, b, a);
	}

	void SetColor(const Color4f& color)
	{
		glColor4f(color.r, color.g, color.b, color.a);
	}

	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
		}
		glEnd();
	}

	void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth)
	{
		DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
	}

	void DrawRect(float left, float bottom, float width, float height, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth)
	{
		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3)
	{
		glBegin(GL_TRIANGLES);
		{
			glVertex2f(p1.x, p1.y);
			glVertex2f(p2.x, p2.y);
			glVertex2f(p3.x, p3.y);
		}
		glEnd();
	}

	void DrawRect(const Point2f& bottomLeft, float width, float height, float lineWidth)
	{
		DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
	}

	void DrawRect(const Rectf& rect, float lineWidth)
	{
		DrawRect(rect.left, rect.bottom, rect.width, rect.height, lineWidth);
	}

	void FillRect(float left, float bottom, float width, float height)
	{
		glBegin(GL_POLYGON);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}

	void FillRect(const Point2f& bottomLeft, float width, float height)
	{
		FillRect(bottomLeft.x, bottomLeft.y, width, height);
	}

	void FillRect(const Rectf& rect)
	{
		FillRect(rect.left, rect.bottom, rect.width, rect.height);
	}

	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth)
	{
		DrawEllipse(center.x, center.y, radX, radY, lineWidth);
	}

	void DrawEllipse(const Ellipsef& ellipse, float lineWidth)
	{
		DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth);
	}

	void FillEllipse(float centerX, float centerY, float radX, float radY)
	{
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
		}
		glEnd();
	}

	void FillEllipse(const Ellipsef& ellipse)
	{
		FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
	}

	void FillEllipse(const Point2f& center, float radX, float radY)
	{
		FillEllipse(center.x, center.y, radX, radY);
	}

	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}

		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		{
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();

	}

	void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
	{
		DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
	}

	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
	{
		if (fromAngle > tillAngle)
		{
			return;
		}
		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			glVertex2f(centerX, centerY);
			for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
			{
				glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
			}
			glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
		}
		glEnd();
	}

	void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle)
	{
		FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
	}

	void DrawPolygon(const std::vector<Point2f>& vertices, bool closed, float lineWidth)
	{
		DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
	}

	void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth)
	{
		glLineWidth(lineWidth);
		closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}

	void FillPolygon(const std::vector<Point2f>& vertices)
	{
		FillPolygon(vertices.data(), vertices.size());
	}

	void FillPolygon(const Point2f* pVertices, size_t nrVertices)
	{
		glBegin(GL_POLYGON);
		{
			for (size_t idx{ 0 }; idx < nrVertices; ++idx)
			{
				glVertex2f(pVertices[idx].x, pVertices[idx].y);
			}
		}
		glEnd();
	}
#pragma endregion OpenGLDrawFunctionality

#pragma region MyAdditions
	int GenerateRandom(int minValue, int maxValue)
	{
		int random{};
		random = (rand() % (maxValue + 1 - minValue) + minValue);
		return random;
	}

	Color4f RandomColor()
	{
		Color4f randomColor{ GenerateRandom(0,255) / 255.0f, GenerateRandom(0,255) / 255.0f, GenerateRandom(0,255) / 255.0f, 1.0f };
		return randomColor;
	}

	void DrawSquares(float x, float y, float size, float numberOfSquares)
	{
		float step{ (size / numberOfSquares) * 0.5f };
		for (int i{ 0 }; i < numberOfSquares; i++)
		{
			DrawRect(x + i * step, y + i * step, size - 2 * i * step, size - 2 * i * step);
		}
	}
	void DrawSquares(const Point2f& BottomLeft, float size, float numberOfSquares)
	{
		DrawSquares(BottomLeft.x, BottomLeft.y, size, numberOfSquares);
	}

	void DrawEquilateralTriangle(float x, float y, float size, bool isFilled)
	{
		const Point2f bl{ x,y };
		const Point2f br{ bl.x + size, bl.y };
		const Point2f middle{ x + size * float(cos(1.04719755)), y + size * float(sin(1.04719755)) };
		if (isFilled == true)
		{
			FillTriangle(bl, br, middle);
		}
		else
		{
			DrawTriangle(bl, br, middle);
		}
	}
	void DrawEquilateralTriangle(const Point2f& bottomLeft, float size, bool isFilled)
	{
		DrawEquilateralTriangle(bottomLeft.x, bottomLeft.y, size, isFilled);
	}

	void DrawPentagram(float x, float y, float radius, float startingAngle, float thickness)
	{
		float angle{ startingAngle };
		const Point2f p1{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
		angle += 0.4f * float(M_PI);
		const Point2f p2{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
		angle += 0.4f * float(M_PI);
		const Point2f p3{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
		angle += 0.4f * float(M_PI);
		const Point2f p4{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
		angle += 0.4f * float(M_PI);
		const Point2f p5{ x + (cos(angle) * radius), y + (sin(angle) * radius) };
		DrawLine(p1, p3, thickness);
		DrawLine(p1, p4, thickness);
		DrawLine(p2, p4, thickness);
		DrawLine(p2, p5, thickness);
		DrawLine(p3, p5, thickness);
	}
	void DrawPentagram(const Point2f& centerpoint, float radius, float startingAngle, float thickness)
	{
		DrawPentagram(centerpoint.x, centerpoint.y, radius, startingAngle, thickness);
	}

	void DrawLinearGradient(float x, float y, float width, float height, const Color4f& left, const Color4f& right)
	{
		const float stepR{ (left.r - right.r) / width };
		const float stepG{ (left.g - right.g) / width };
		const float stepB{ (left.b - right.b) / width };
		const float stepA{ (left.a - right.a) / width };
		for (int i{ 0 }; i <= width; i++)
		{
			SetColor(left.r - (stepR * i), left.g - (stepG * i), left.b - (stepB * i), left.a - (stepA * i));
			FillRect(x + i, y, 1, height);
		}
	}
	void DrawLinearGradient(const Point2f& bl, float width, float height, const Color4f& left, const Color4f& right)
	{
		DrawLinearGradient(bl.x, bl.y, width, height, left, right);
	}
	void DrawLinearGradient(const Rectf& rectf, const Color4f& left, const Color4f& right)
	{
		DrawLinearGradient(rectf.bottom, rectf.left, rectf.width, rectf.height, left, right);
	}

	void DrawDotGrid(float x, float y, float radius, float rows, float columns, float dotSpace)
	{
		if (dotSpace == 0)
		{
			dotSpace = 2 * radius;
		}
		for (int i{ 0 }; i < rows; i++)
		{
			for (int a{ 0 }; a < columns; a++)
			{
				FillEllipse(x + a * dotSpace, y + i * dotSpace, radius, radius);
			}
		}
	}
	void DrawDotGrid(const Point2f& bottomLeft, float radius, float rows, float columns, float dotSpace)
	{
		DrawDotGrid(bottomLeft.x, bottomLeft.y, radius, rows, columns, dotSpace);
	}
	int GetIndex(int rowIdx, int colIdx, int nrCols)
	{
		return (rowIdx * nrCols + colIdx);
	}
#pragma endregion MyAdditions

#pragma region textureImplementations

	bool TextureFromFile(const std::string& path, Texture& texture)
	{
		//Load file for use as an image in a new surface.
		SDL_Surface* pLoadedSurface = IMG_Load(path.c_str());
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromFile: SDL Error when calling IMG_Load: " << SDL_GetError() << std::endl;
			return false;
		}

		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture)
	{
		// Create font
		TTF_Font* pFont{};
		pFont = TTF_OpenFont(fontPath.c_str(), ptSize);
		if (pFont == nullptr)
		{
			std::cout << "TextureFromString: Failed to load font! SDL_ttf Error: " << TTF_GetError();
			std::cin.get();
			return false;
		}

		// Create texture using this fontand close font afterwards
		bool textureOk = TextureFromString(text, pFont, textColor, texture);
		TTF_CloseFont(pFont);

		return textureOk;
	}

	bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& color, Texture& texture)
	{
		//Render text surface
		SDL_Color textColor{};
		textColor.r = Uint8(color.r * 255);
		textColor.g = Uint8(color.g * 255);
		textColor.b = Uint8(color.b * 255);
		textColor.a = Uint8(color.a * 255);

		SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
		//SDL_Surface* pLoadedSurface = TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);
		if (pLoadedSurface == nullptr)
		{
			std::cerr << "TextureFromString: Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
			return false;
		}

		// copy to video memory
		TextureFromSurface(pLoadedSurface, texture);

		//Free loaded surface
		SDL_FreeSurface(pLoadedSurface);

		return true;
	}

	void TextureFromSurface(const SDL_Surface* pSurface, Texture& texture)
	{
		//Get image dimensions
		texture.width = float(pSurface->w);
		texture.height = float(pSurface->h);

		// Get pixel format information and translate to OpenGl format
		GLenum pixelFormat{ GL_RGB };
		switch (pSurface->format->BytesPerPixel)
		{
		case 3:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGB;
			}
			else
			{
				pixelFormat = GL_BGR;
			}
			break;
		case 4:
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGBA;
			}
			else
			{
				pixelFormat = GL_BGRA;
			}
			break;
		default:
			std::cerr << "TextureFromSurface error: Unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";;
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Generate an array of textures.  We only want one texture (one element array), so trick
		//it by treating "texture" as array of length one.
		glGenTextures(1, &texture.id);

		//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
		//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// check for errors.
		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			std::cerr << "TextureFromSurface, error binding textures, Error id = " << e << '\n';
			texture.width = 0;
			texture.height = 0;
			return;
		}

		//Specify the texture's data.  This function is a bit tricky, and it's hard to find helpful documentation.  A summary:
		//   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
		//               0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
		//                         not cached smaller copies)
		//         GL_RGBA:    Specifies the number of color components in the texture.
		//                     This is how OpenGL will store the texture internally (kinda)--
		//                     It's essentially the texture's type.
		//      surface->w:    The width of the texture
		//      surface->h:    The height of the texture
		//               0:    The border.  Don't worry about this if you're just starting.
		//     pixelFormat:    The format that the *data* is in--NOT the texture! 
		//GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
		//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
		//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
		//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
		// surface->pixels:    The actual data.  As above, SDL's array of bytes.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

		//Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
		//*smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
		//each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
		//further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
		//them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void DeleteTexture(Texture& texture)
	{
		glDeleteTextures(1, &texture.id);
	}

	void DrawTexture(const Texture& texture, const Point2f& dstBottomLeft, const Rectf& srcRect)
	{
		Rectf dstRect{ dstBottomLeft.x, dstBottomLeft.y, srcRect.width, srcRect.height };
		DrawTexture(texture, dstRect, srcRect);
	}


	void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect)
	{
		// Determine texture coordinates using srcRect and default destination width and height
		float textLeft{};
		float textRight{};
		float textTop{};
		float textBottom{};

		float defaultDstWidth{};
		float defaultDstHeight{};
		if (!(srcRect.width > 0.0f && srcRect.height > 0.0f)) // No srcRect specified
		{
			// Use complete texture
			textLeft = 0.0f;
			textRight = 1.0f;
			textTop = 0.0f;
			textBottom = 1.0f;

			defaultDstHeight = texture.height;
			defaultDstWidth = texture.width;
		}
		else // srcRect specified
		{
			// Convert to the range [0.0, 1.0]
			textLeft = srcRect.left / texture.width;
			textRight = (srcRect.left + srcRect.width) / texture.width;
			textTop = (srcRect.bottom - srcRect.height) / texture.height;
			textBottom = srcRect.bottom / texture.height;

			defaultDstHeight = srcRect.height;
			defaultDstWidth = srcRect.width;
		}

		// Determine vertex coordinates
		float vertexLeft{ dstRect.left };
		float vertexBottom{ dstRect.bottom };
		float vertexRight{};
		float vertexTop{};
		if (!(dstRect.width > 0.0f && dstRect.height > 0.0f)) // If no size specified use default size
		{
			vertexRight = vertexLeft + defaultDstWidth;
			vertexTop = vertexBottom + defaultDstHeight;
		}
		else
		{
			vertexRight = vertexLeft + dstRect.width;
			vertexTop = vertexBottom + dstRect.height;
		}

		// Tell opengl which texture we will use
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// set the texture mode https://open.gl/textures
		float color[] = { 1.0f, 0.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		// Draw
		glEnable(GL_TEXTURE_2D);
		{
			glBegin(GL_QUADS);
			{
				glTexCoord2f(textLeft, textBottom);
				glVertex2f(vertexLeft, vertexBottom);

				glTexCoord2f(textLeft, textTop);
				glVertex2f(vertexLeft, vertexTop);

				glTexCoord2f(textRight, textTop);
				glVertex2f(vertexRight, vertexTop);

				glTexCoord2f(textRight, textBottom);
				glVertex2f(vertexRight, vertexBottom);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);

	}
#pragma endregion textureImplementations

#pragma region CollisionFunctionality
	// Also my adittions

	//
	// GetDistance
	//
	float GetDistance(float x1, float y1, float x2, float y2)
	{
		return sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
	}
	// Overloading
	float GetDistance(Point2f p1, Point2f p2)
	{
		return GetDistance(p1.x, p1.y, p2.x, p2.y);
	}
	float GetDistance(Point2f p1, float x2, float y2)
	{
		return GetDistance(p1.x, p1.y, x2, y2);
	}
	float GetDistance(float x1, float y1, Point2f p2)
	{
		return GetDistance(x1, y1, p2.x, p2.y);
	}
	//
	// IsPointInCircle
	//
	bool IsPointInCircle(const Circlef& circle, const Point2f& point) 
	{
		if (GetDistance(circle.center, point) <= circle.radius) return true;
		return false;
	}
	// Overloading 
	bool IsPointInCircle(const Circlef& circle, float pointX, float pointY)
	{
		const Point2f point{ pointX,pointY };
		return IsPointInCircle(circle, point);
	}
	bool IsPointInCircle(const Point2f& center, float radius, const Point2f& point)
	{
		const Circlef circle{ center,radius };
		return IsPointInCircle(circle, point);
	}
	bool IsPointInCircle(const Point2f& center, float radius, float pointX, float pointY)
	{
		const Circlef circle{ center,radius };
		const Point2f point{ pointX,pointY };
		return IsPointInCircle(circle, point);
	}
	bool IsPointInCircle(float centerX, float centerY, float radius, const Point2f& point)
	{
		const Point2f center{ centerX,centerY };
		const Circlef circle{ center,radius };
		return IsPointInCircle(circle, point);
	}
	bool IsPointInCircle(float centerX, float centerY, float radius, float pointX, float pointY)
	{
		const Point2f center{ centerX,centerY };
		const Circlef circle{ center,radius };
		const Point2f point{ pointX,pointY };
		return IsPointInCircle(circle, point);
	}
	//
	// IsInsideRect
	// 
	bool IsInsideRect(float rectX, float rectY, float rectW, float rectH, float pointX, float pointY)
	{
		if ((pointX > rectX) && (pointX < rectX + rectW) && (pointY > rectY) && (pointY < rectY + rectH))
		{
			return true;
		}
		return false;
	}
	// Overloading
	bool IsInsideRect(const Point2f& rectXY, float rectW, float rectH, const Point2f& point)
	{
		return IsInsideRect(rectXY.x, rectXY.y, rectW, rectH, point.x, point.y);
	}
	bool IsInsideRect(float rectX, float rectY, float rectW, float rectH, const Point2f& point)
	{
		return IsInsideRect(rectX, rectY, rectW, rectH, point.x, point.y);
	}
	bool IsInsideRect(const Point2f& rectXY, float rectW, float rectH, float pointX, float pointY)
	{
		return IsInsideRect(rectXY.x, rectXY.y, rectW, rectH, pointX, pointY);
	}
	bool IsInsideRect(const Rectf& rect, const Point2f& point) 
	{
		return IsInsideRect(rect.left, rect.bottom, rect.width, rect.height, point.x, point.y);
	}
	bool IsInsideRect(const Rectf& rect, float pointX, float pointY)
	{
		return IsInsideRect(rect.left, rect.bottom, rect.width, rect.height, pointX, pointY);
	}
	//
	// IsOverlapping
	//
	// Case Rect
	bool IsOverlapping(const Rectf& first, const Rectf& second)
	{
		const Point2f l1{first.left, first.bottom + first.height};
		const Point2f r1{first.left + first.width, first.bottom};
		const Point2f l2{second.left, second.bottom + second.height};
		const Point2f r2{second.left + second.width, second.bottom};
		if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y) return false;
		if (l1.x >= r2.x || l2.x >= r1.x) return false;
		if (r1.y >= l2.y || r2.y >= l1.y) return false;

		return true;
	}
	// Overloading
	bool IsOverlapping(const Point2f& firstBottomLeft, float firstWidth, float firstHeight, const Point2f& secondBottomLeft, float secondWidth, float secondHeight) 
	{
		const Rectf first{ firstBottomLeft.x,firstBottomLeft.y,firstWidth,firstHeight };
		const Rectf second{ secondBottomLeft.x,secondBottomLeft.y,secondWidth,secondHeight };
		return IsOverlapping(first, second);
	}
	bool IsOverlapping(float firstPointX, float firstPointY, float firstWidth, float firstHeight, float secondPointX, float secondPointY, float secondWidth, float secondHeight)
	{
		const Rectf first{ firstPointX,firstPointY,firstWidth,firstHeight };
		const Rectf second{ secondPointX,secondPointY,secondWidth,secondHeight };
		return IsOverlapping(first, second);
	}
	// Case Circle
	bool IsOverlapping(const Circlef& first, const Circlef& second)
	{
		if (GetDistance(first.center, second.center) >= first.radius + second.radius) return false;
		return true;
	}
	// Overloading
	bool IsOverlapping(const Point2f& firstCenter, float firstRadius, const Point2f& secondCenter, float secondRadius)
	{
		const Circlef first{firstCenter,firstRadius};
		const Circlef second{ secondCenter,secondRadius };
		return IsOverlapping(first, second);
	}
	bool IsOverlapping(float firstCenterX, float firstCenterY, float firstRadius, float secondCenterX, float secondCenterY, float secondRadius)
	{
		const Point2f firstCenter{ firstCenterX,firstCenterY };
		const Point2f secondCenter{ secondCenterX,secondCenterY };
		const Circlef first{ firstCenter,firstRadius };
		const Circlef second{ secondCenter, secondRadius };
		return IsOverlapping(first, second);
	}
#pragma endregion CollisionFunctionality

#pragma region Vector
	Point2f VectorToPoint(const Vector2f& vector)
	{
		const Point2f point{ vector.x,vector.y };
		return point;
	}
	Vector2f PointToVector(const Point2f& point)
	{
		const Vector2f vector{ point.x,point.y };
		return vector;
	}
	
	void DrawVector(const Vector2f& vector, const Point2f& startingPoint)
	{
		const Point2f vectorPoint{startingPoint.x + vector.x, startingPoint.y + vector.y};
		const float vectorAngle{ atan2(vector.x, vector.y) };
		const float arrowAngle{ g_Pi / 6 };
		const float arrowLength{ 10 };
		const Point2f p1{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle - arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle - arrowAngle) };
		const Point2f p2{ vectorPoint.x + arrowLength * cosf(1.5f * g_Pi - vectorAngle + arrowAngle), vectorPoint.y + arrowLength * sinf(1.5f * g_Pi - vectorAngle + arrowAngle) };
		DrawLine(startingPoint, vectorPoint);
		FillTriangle(vectorPoint, p1, p2);
	}
	
	std::string ToString(const Vector2f& vector)
	{
		return "[" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + "]";
	}
	
	Vector2f Add(const Vector2f& a, const Vector2f& b)
	{
		const Vector2f result{ a.x + b.x, a.y + b.y };
		return result;
	}
	Vector2f Substract(const Vector2f& a, const Vector2f& b)
	{
		const Vector2f result{ a.x - b.x, a.y - b.y };
		return result;
	}

	float DotProduct(const Vector2f& a, const Vector2f& b)
	{
		return (a.x * b.x + a.y * b.y);
	}
	float CrossProduct(const Vector2f& a, const Vector2f& b)
	{
		// a crossProduct b = length a *  length b * sin(angleBetween) * n
		const float n{ 1 }; // n = unitvector
		const float angleBetween{ acos(DotProduct(a,b) / (Length(a) * Length(b))) };
		return (Length(a) * Length(b) * sin(angleBetween) * n);
		// Negative angles do not compute well
	}

	float Length(const Vector2f& vector)
	{
		return float((sqrt(pow(vector.x, 2) + pow(vector.y, 2))));
	}
	Vector2f Scale(const Vector2f& vector, float scalar)
	{
		const Vector2f result{ vector.x * scalar, vector.y * scalar };
		return result;
	}
	Vector2f Normalize(const Vector2f& vector)
	{
		const Vector2f result{ vector.x / Length(vector),vector.y / Length(vector) };
		return result;
	}

	float AngleBetween(const Vector2f& a, const Vector2f& b)
	{
		return (atan2(CrossProduct(a, b), DotProduct(a, b)));
	}
	bool AreEqual(const Vector2f& a, const Vector2f& b)
	{
		const float margin{ 0.001f };
		if ((a.x <= (b.x - margin)) && (a.x >= (b.x + margin)))
		{
			if ((a.y <= (b.y - margin)) && (a.y >= (b.y + margin))) return true;
		}
		return false;
	}
#pragma endregion Vector

}