#pragma once

#include <memory>
#include <string>
#include <vector>

// Среди доступных вам файлов вас в первую очередь будет интересовать файл Common.h.

struct Point {
	int x;
	int y;
};

struct Size {
	int width;
	int height;
};

// Вычислить целочисленную форму эллипса можно по-разному, поэтому для определённости воспользуйтесь
// предоставленной функцией IsPointInEllipse()
inline bool IsPointInEllipse(Point p, Size size) {
	double x = (p.x + 0.5) / (size.width / 2.0) - 1;
	double y = (p.y + 0.5) / (size.height / 2.0) - 1;

	return x * x + y * y <= 1;
}

using Image = std::vector<std::string>;

// Существуют два вида фигур: прямоугольник и эллипс. Они указаны в перечислении ShapeType.
enum class ShapeType {
	Rectangle,
	Ellipse
	};

class ITexture {
public:
	virtual ~ITexture() = default;

	virtual Size GetSize() const = 0;

	virtual const Image& GetImage() const = 0;
};

// В нём приведён интерфейс IShape, который описывает фигуру.
// Интерфейс IShape позволяет запрашивать и задавать ряд свойств фигуры: позицию, размер и текстуру.
class IShape {
public:
	virtual ~IShape() = default;

	// Также он позволяет клонировать фигуру с помощью метода Clone().
	// Это похоже на то, как если бы вы выбрали в редакторе графики фигуру и нажали Ctrl+C и Ctrl+V.
	// Идея в том, что склонированная фигура использует ту же самую текстуру, что и оригинал.
	// Это удобно, т.к. в общем случае текстура может занимать много памяти.
	// Разумеется, в дальнейшем склонированной фигуре можно задать новую текстуру.
	virtual std::unique_ptr<IShape> Clone() const = 0;

	virtual void SetPosition(Point) = 0;
	virtual Point GetPosition() const = 0;

	virtual void SetSize(Size) = 0;
	virtual Size GetSize() const = 0;

	virtual void SetTexture(std::shared_ptr<ITexture>) = 0;
	virtual ITexture* GetTexture() const = 0;

	// Кроме того, интерфейс IShape позволяет отрисовать текущую фигуру на заданном изображении с помощью метода Draw().
	virtual void Draw(Image&) const = 0;
};

std::unique_ptr<IShape> MakeShape(ShapeType shape_type);
