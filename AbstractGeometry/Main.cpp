#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
#include <math.h>

namespace AbstractGeometry
{
	// Создаём тип данных

	enum Color
	{
		red = 0x000000FF, // 4 по 2 - это RGBA
		green = 0x0000FF00, // 4 по 2 - это RGBA
		blue = 0x00FF0000, // 4 по 2 - это RGBA



		some_color = 0,
		console_red = 0xCC,
		console_green = 0xAA,
		console_blue = 0x99,
		console_default = 0x07

	};


	class Shape
	{
	protected:

		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:

		void set_start_x(unsigned int start_x)
		{
			if (start_x > 300)start_x = 300;
			this->start_x = start_x;
		}

		void set_start_y(unsigned int start_y)
		{
			if (start_y > 300)start_y = 300;
			this->start_y = start_y;
		}

		void set_line_width(unsigned int line_width)
		{
			if (line_width > 20)line_width = 20;
			this->line_width = line_width;
		}

		Shape(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}


		virtual void info() const
		{
			std::cout << "Area:\t" << get_area() << std::endl;
			std::cout << "Perimeter:\t" << get_perimetr() << std::endl;
			for (int i = 0; i < 10000; ++i) {
				draw();
			}
		}

		virtual ~Shape() {}

		virtual double get_area() const = 0;
		virtual double get_perimetr() const = 0;
		virtual void draw() const = 0;


	};


	class LocalSquare : public Shape
	{
		double side;

	public:

		double get_side() const
		{
			return side;
		}

		void set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
		}

		LocalSquare(
			double side,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~LocalSquare() {}

		double get_area() const
		{
			return side * side;
		}

		double get_perimetr() const
		{
			return side * 4;
		}

		void draw() const
		{

			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side); // Рисует квадрат


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

		void info() const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Side:\t" << side << std::endl;
			Shape::info();
		}

	};



	class LocalRectangle : public Shape
	{
		double sideA;
		double sideB;

	public:

		double get_sideA() const
		{
			return sideA;
		}

		double get_sideB() const
		{
			return sideB;
		}

		void set_sideA(double sideA)
		{
			if (sideA <= 0)sideA = 10;
			this->sideA = sideA;
		}

		void set_sideB(double sideB)
		{
			if (sideB <= 0)sideB = 20;
			this->sideB = sideB;
		}

		LocalRectangle(
			double sideA, double sideB,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_sideA(sideA);
			set_sideB(sideB);
		}
		~LocalRectangle() {}

		double get_area() const
		{
			return sideA * sideB;
		}

		double get_perimetr() const
		{
			return (sideA + sideB) * 2;
		}

		void draw() const
		{

			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + sideA, start_y + sideB); // Рисует прямоугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

		void info() const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "SideA: "<<sideA<< std::endl;
			std::cout << "SideB: "<<sideB<< std::endl;
			Shape::info();
		}

	};


	class LocalCircle : public Shape
	{
		double _radius;

	public:

		double get_radius() const
		{
			return _radius;
		}

		void set_radius(double radius)
		{
			if (radius <= 0)radius = 100;
			this->_radius = radius;
		}

		LocalCircle(
			double radius,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}

		~LocalCircle() {}

		double get_area() const
		{
			return M_PI * _radius * _radius;
		}

		double get_perimetr() const
		{
			return M_PI * _radius * 2;
		}

		void draw() const
		{

			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			Ellipse(hdc, start_x, start_y, start_x + 2 * _radius, start_y + 2 * _radius); // Рисует прямоугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

		void info() const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Radius: " << _radius << std::endl;
			Shape::info();
		}

	};

	class LocalTriangle : public Shape
	{
		double _sideA;
		double _sideB;
		double _sideC;

	public:

		double get_sideA() const
		{
			return _sideA;
		}

		double get_sideB() const
		{
			return _sideB;
		}

		double get_sideC() const
		{
			return _sideC;
		}

		void set_sideA(double _sideA)
		{
			if (_sideA <= 0)_sideA = 20;
			this->_sideA = _sideA;
		}

		void set_sideB(double _sideB)
		{
			if (_sideB <= 0)_sideB = 30;
			this->_sideB = _sideB;
		}

		void set_sideC(double _sideC)
		{
			if (_sideC <= 0)_sideC = 40;
			this->_sideC = _sideC;
		}

		LocalTriangle(
			double _sideA, double _sideB, double _sideC,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_sideA(_sideA);
			set_sideB(_sideB);
			set_sideC(_sideC);
		}

		~LocalTriangle() {}

		double get_area() const
		{
			int p = 0.5 * (_sideA + _sideB + _sideC);
			return sqrt( p*(p-_sideA)*(p-_sideB)*(p-_sideC));
		}

		double get_perimetr() const
		{
			return _sideA + _sideB + _sideC;
		}

		void draw() const
		{

			POINT ptVertex[3];

			ptVertex[0].x = 100;
			ptVertex[0].y = 300;
			ptVertex[1].x = 150;
			ptVertex[1].y = 200;
			ptVertex[2].x = 50;
			ptVertex[2].y = 200;
			

			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			Polygon(hdc, ptVertex, 3); // Рисует треугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

	};


	class EquilateralTriangle : public LocalTriangle
	{
		double _side;
		
	public:

		double get_side() const
		{
			return _side;
		}
				
		void set_side(double _side)
		{
			if (_side <= 0)_side = 20;
			this->_side = _side;
		}

		EquilateralTriangle(
			double _side,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:LocalTriangle(_side,_side,_side,color, start_x, start_y, line_width)
		{
			set_side(_side);			
		}

		~EquilateralTriangle() {}

		double get_area() const
		{
			int p = 0.5 * 3*_side;
			return sqrt(p * (p - _side) * (p - _side) * (p - _side));
		}

		double get_perimetr() const
		{
			return 3*_side;
		}

		void draw() const
		{

			POINT ptVertex[3];

			ptVertex[0].x = 100;
			ptVertex[0].y = 100;
			ptVertex[1].x = 150;
			ptVertex[1].y = 200;
			ptVertex[2].x = 50;
			ptVertex[2].y = 200;


			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			Polygon(hdc, ptVertex, 3); // Рисует треугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

	};


	class IsoscalesTriangle : public LocalTriangle
	{
		double _sideAB;
		double _sideC;

	public:

		double get_side() const
		{
			return _sideAB;
			return _sideC;
		}

		void set_sideAB(double _sideAB)
		{
			if (_sideAB <= 0)_sideAB = 20;
			this->_sideAB = _sideAB;
		}

		void set_sideC(double _sideC)
		{
			if (_sideC <= 0)_sideC = 30;
			this->_sideC = _sideC;
		}

		IsoscalesTriangle(
			double _sideAB, double _sideC,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:LocalTriangle(_sideAB, _sideAB, _sideC, color, start_x, start_y, line_width)
		{
			set_sideAB(_sideAB);
			set_sideC(_sideC);
		}

		~IsoscalesTriangle() {}

		double get_area() const
		{
			int p = 0.5 * (2 *_sideAB + _sideC);
			return sqrt(p * (p - _sideAB) * (p - _sideAB) * (p - _sideC));
		}

		double get_perimetr() const
		{
			return 2 * _sideAB + _sideC;
		}

		void draw() const
		{

			POINT ptVertex[3];

			ptVertex[0].x = 100;
			ptVertex[0].y = 100;
			ptVertex[1].x = 150;
			ptVertex[1].y = 200;
			ptVertex[2].x = 50;
			ptVertex[2].y = 200;


			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			Polygon(hdc, ptVertex, 3); // Рисует треугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

	};


	class RightTriangle : public LocalTriangle
	{
		double _sideA;
		double _sideB;
		double _sideC;

	public:

		double get_sideA() const
		{
			return _sideA;
		}

		double get_sideB() const
		{
			return _sideB;
		}

		double get_sideC() const
		{
			return _sideC;
		}

		void set_sideA(double _sideA)
		{
			if (_sideA <= 0)_sideA = 20;
			this->_sideA = _sideA;
		}

		void set_sideB(double _sideB)
		{
			if (_sideB <= 0)_sideB = 30;
			this->_sideB = _sideB;
		}

		void set_sideC(double _sideC)
		{
			if (_sideC <= 0)_sideC = 40;
			this->_sideC = _sideC;
		}

		RightTriangle(
			double _sideA, double _sideB, double _sideC,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:LocalTriangle(_sideA,_sideB,_sideC,color, start_x, start_y, line_width)
		{
			set_sideA(_sideA);
			set_sideB(_sideB);
			set_sideC(_sideC);
		}

		~RightTriangle() {}

		double get_area() const
		{
			int p = 0.5 * (_sideA + _sideB + _sideC);
			return sqrt(p * (p - _sideA) * (p - _sideB) * (p - _sideC));
		}

		double get_perimetr() const
		{
			return _sideA + _sideB + _sideC;
		}

		void draw() const
		{

			POINT ptVertex[3];

			ptVertex[0].x = 100;
			ptVertex[0].y = 100;
			ptVertex[1].x = 150;
			ptVertex[1].y = 200;
			ptVertex[2].x = 50;
			ptVertex[2].y = 200;


			HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
			// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
			SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
			HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);// Выбираем созданную кисть.
			// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			Polygon(hdc, ptVertex, 3); // Рисует треугольник


			//Удаляем созданную кисть и карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			// Освобождаем контекст устройства
			ReleaseDC(hConsole, hdc);
		}

	};



}
int main()
{


	AbstractGeometry::LocalSquare newSquare(50, AbstractGeometry::Color::green, 150, 500, 5);
	newSquare.info();
	AbstractGeometry::LocalRectangle newRectangle(100, 50, AbstractGeometry::Color::red, 300, 500, 5);
	newRectangle.info();
	AbstractGeometry::LocalCircle newCircle(25, AbstractGeometry::Color::blue, 50, 500, 5);
	newCircle.info();
	AbstractGeometry::LocalTriangle newTriangle(20, 20, 20, AbstractGeometry::Color::green, 600, 500, 5);
	newTriangle.info();

	return 0;
}