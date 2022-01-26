#include <iostream>
#include <Windows.h>

// Создаём тип данных

enum Color
{
	red   = 0x000000FF, // 4 по 2 - это RGBA
	green = 0x0000FF00, // 4 по 2 - это RGBA
	blue  = 0x00FF0000, // 4 по 2 - это RGBA



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

	virtual ~Shape() {}

	virtual double get_area() const = 0;
	virtual double get_perimetr() const = 0;
	virtual void draw() const = 0;


};


class localSquare : public Shape
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

	localSquare(
		double side,
		Color color,
		unsigned int start_x, unsigned int start_y,
		unsigned int line_width)
		:Shape(color, start_x, start_y, line_width)
	{
		set_side(side);
	}
	~localSquare() {}

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

		Rectangle(hdc, start_x, start_y, start_x + side, start_y + side); // Рисует квадрат


		//Удаляем созданную кисть и карандаш
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// Освобождаем контекст устройства
		ReleaseDC(hConsole, hdc);
	}

};



class localRectangle : public Shape
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

	localRectangle(
		double sideA, double sideB,
		Color color,
		unsigned int start_x, unsigned int start_y,
		unsigned int line_width)
		:Shape(color, start_x, start_y, line_width)
	{
		set_sideA(sideA);
		set_sideB(sideB);
	}
	~localRectangle() {}

	double get_area() const
	{
		return sideA * sideB;
	}

	double get_perimetr() const
	{
		return (sideA+ sideB) * 2;
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

		Rectangle(hdc, start_x, start_y, start_x + sideA, start_y + sideB); // Рисует прямоугольник


		//Удаляем созданную кисть и карандаш
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// Освобождаем контекст устройства
		ReleaseDC(hConsole, hdc);
	}

};


class localCircle : public Shape
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

	localCircle(
		double radius,
		Color color,
		unsigned int start_x, unsigned int start_y,
		unsigned int line_width)
		:Shape(color, start_x, start_y, line_width)
	{
		set_radius(radius);
	}

	~localCircle() {}

	double get_area() const
	{
		return 3.14*_radius*_radius;
	}

	double get_perimetr() const
	{
		return 3.14* _radius * 2;
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

		Ellipse(hdc, start_x, start_y, start_x+2*_radius, start_y + 2 * _radius); // Рисует прямоугольник


		//Удаляем созданную кисть и карандаш
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// Освобождаем контекст устройства
		ReleaseDC(hConsole, hdc);
	}

};

class localTriangle : public Shape
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
		if (_sideB <= 0)_sideB = 20;
		this->_sideB = _sideB;
	}
	
	void set_sideC(double _sideC)
	{
		if (_sideC <= 0)_sideC = 20;
		this->_sideC = _sideC;
	}
	 
	localTriangle(
		double _sideA,double _sideB,double _sideC,
		Color color,
		unsigned int start_x, unsigned int start_y,
		unsigned int line_width)
		:Shape(color, start_x, start_y, line_width)
	{
		set_sideA(_sideA);
		set_sideB(_sideB);
		set_sideC(_sideC);
	}

	~localTriangle() {}

	double get_area() const
	{
		return 0.5*_sideC*sqrt(_sideB * _sideB - (0.25 * _sideC * _sideC));
	}

	double get_perimetr() const
	{
		return _sideA+_sideB+_sideC;
	}

	void draw() const
	{

		POINT ptVertex[5];

		ptVertex[0].x = 180;
		ptVertex[0].y = 80;
		ptVertex[1].x = 100;
		ptVertex[1].y = 160;
		ptVertex[2].x = 120;
		ptVertex[2].y = 260;
		ptVertex[3].x = 240;
		ptVertex[3].y = 260;
		
		HWND hConsole = GetConsoleWindow(); // Получаем окно консоли, чтобы к нему можно было обратиться
		HDC hdc = GetDC(hConsole);// создаём контекст устройства для полученного окна- консоли
		HPEN hPen = CreatePen(PS_SOLID, line_width, color);// Создаём карандаш, который будет рисовать контур
		// PS_SOLID- сплошная линия, 5- толщина линии 5 пикс, RGB- цвет в RGB
		SelectObject(hdc, hPen);// Выбираем созданный карандаш, чтобы им можно было рисовать
		HBRUSH hBrush = CreateSolidBrush(color); // Создаём кисть. Кисть закрашивает замкнутые фигуры.
		SelectObject(hdc, hBrush);// Выбираем созданную кисть.
		// Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

		Polygon(hdc,ptVertex , 3); // Рисует треугольник


		//Удаляем созданную кисть и карандаш
		DeleteObject(hPen);
		DeleteObject(hBrush);
		// Освобождаем контекст устройства
		ReleaseDC(hConsole, hdc);
	}

};


int main()
{


	localSquare Square(50, Color::green, 150, 500, 5);
	Square.draw();
	localRectangle newRectangle(100, 50, Color::red, 300, 500, 5);
	newRectangle.draw();
	localCircle newCircle(25, Color::blue, 450, 500, 5);
	newCircle.draw();
	localTriangle newTriangle(20, 20, 20, Color::blue, 600, 500, 5);
	newTriangle.draw();
		

	std::cout << "Square side:\t" << Square.get_side() << std::endl;
	std::cout << "Square area:\t" << Square.get_area() << std::endl;
	std::cout << "Square perimeter:\t" << Square.get_perimetr() << std::endl;
		
	std::cout << "Rectangle sideA:\t" << newRectangle.get_sideA() << std::endl;
	std::cout << "Rectangle sideB:\t" << newRectangle.get_sideB() << std::endl;
	std::cout << "Rectangle area:\t" << newRectangle.get_area() << std::endl;
	std::cout << "Rectangle perimeter:\t" << newRectangle.get_perimetr() << std::endl;
	
	std::cout << "Circlele radius:\t" << newCircle.get_radius() << std::endl;
	std::cout << "Circlele area:\t" << newCircle.get_area() << std::endl;
	std::cout << "Circlele length:\t" << newCircle.get_perimetr() << std::endl;
	
	std::cout << "Triangle side A:\t" << newTriangle.get_sideA() << std::endl;
	std::cout << "Triangle side B:\t" << newTriangle.get_sideB() << std::endl;
	std::cout << "Triangle side C:\t" << newTriangle.get_sideC() << std::endl;
	std::cout << "Triangle area:\t" << newTriangle.get_area() << std::endl;
	std::cout << "Triangle perimeter:\t" << newTriangle.get_perimetr() << std::endl;
	
	return 0;
}