#include "Common.h"
#include <memory>

using namespace std;

// проверка точек
bool IsPointInSize(Point p, Size s) {
	return p.x >= 0 && p.y >= 0 && p.x < s.width && p.y < s.height;
}

Size GetImageSize(const Image& image) {
	auto width = static_cast<int>(image.empty() ? 0 : image[0].size());
	auto height = static_cast<int>(image.size());
	return {width, height};
}

class Shape : public IShape {
public:
	void SetPosition(Point p) override {
		position = p;
	}
	Point GetPosition() const override {
		return position;
	}

	void SetSize(Size s) override {
		size = s;
	}
	Size GetSize() const override {
		return size;
	}

	void SetTexture(shared_ptr<ITexture> t) override {
		texture = move(t);
	}
	ITexture* GetTexture() const override {
		return texture.get();
	}

	void Draw(Image& image) const override {
		Point p;
		auto image_size = GetImageSize(image);
		for (p.y = 0; p.y < size.height; ++p.y) {
			for (p.x = 0; p.x < size.width; ++p.x) {
				if (IsPointInShape(p)) {
					char pixel = '.';
					if (texture && IsPointInSize(p, texture->GetSize())) {
						pixel = texture->GetImage()[p.y][p.x];
					}
					Point dp = {position.x + p.x, position.y + p.y};
					if (IsPointInSize(dp, image_size)) {
						image[dp.y][dp.x] = pixel;
					}
				}
			}
		}
	}

private:
	// Вызывается только для точек в ограничивающем прямоугольнике
	// Точка передаётся в локальных координатах
	virtual bool IsPointInShape(Point) const = 0;

	shared_ptr<ITexture> texture;
	Point position = {};
	Size size = {};
};

class Rectangle : public Shape {
public:
	unique_ptr<IShape> Clone() const override {
		return make_unique<Rectangle>(*this);
	}

private:
	bool IsPointInShape(Point) const override {
		return true;
	}
};

class Ellipse : public Shape {
public:
	unique_ptr<IShape> Clone() const override {
		return make_unique<Ellipse>(*this);
	}

private:
	bool IsPointInShape(Point p) const override {
		return IsPointInEllipse(p, GetSize());
	}
};

// Ваша задача реализовать функцию MakeShape, которая создаёт фигуру заданного вида.
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
	switch (shape_type) {
		case ShapeType::Rectangle:
		return make_unique<Rectangle>();
		case ShapeType::Ellipse:
		return make_unique<Ellipse>();
	}
	return nullptr;
}
