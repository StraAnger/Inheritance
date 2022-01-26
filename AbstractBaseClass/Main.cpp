#include <iostream>


class Vehicle
{
	int speed;
public:
	virtual void Move() = 0; // Чисто виртуальный метод
	// Именно этот метод и делает класс абстрактным
};


// В иерархию транспортных средств добавить Катер, Яхту, Самолет и вертолет,
// и построить диаграмму классов;

// https://www.thinkaviation.net/category-class-type/

class GroundVehicle :private Vehicle {};  //может быть пустым или просто { }

class MarineVehicle :private Vehicle {};

class FlyingVehicle :private Vehicle {};

class MotorizedMarineVehicle :private MarineVehicle {};

class NonMotorizedMarineVehicle :private MarineVehicle {};

class RotorcraftVehicle :private FlyingVehicle {};

class AirplaneVehicle :private FlyingVehicle {};

class Airpalne :public AirplaneVehicle
{
public:

	void Move()
	{
		std::cout << "Airplane is flying in the sky\n";
	}

};

class Helicopter :public RotorcraftVehicle
{
public:

	void Move()
	{
		std::cout << "Helicopter is hovering in the air\n";
	}

};


class MotorBoat :public MotorizedMarineVehicle
{
public:

	void Move()
	{
		std::cout << "MotorBoat is gliding on water\n";
	}

};

class Yacht :public NonMotorizedMarineVehicle
{
public:

	void Move()
	{
		std::cout << "MotorBoat is swimming in water\n";
	}

};

class Car :public GroundVehicle
{
public:

	void Move()
	{
		std::cout << "Car is driving on 4 wheels\n";
	}

};

class Bike :public GroundVehicle
{
public:
	void Move()
	{
		std::cout << "Car is driving on 2 wheels\n";
	}

};


int main()
{
	// Vehicle V; // Abstract
	// GroungVehicle gv; // Abstract
	Car BMW;
	BMW.Move();
	Bike Harley_Devidson;
	Yacht PrincessVictoria;
	PrincessVictoria.Move();
	MotorBoat Progress4;
	Progress4.Move();
	Airpalne Cessna182;
	Cessna182.Move();
	Helicopter KA50BlackShark;
	KA50BlackShark.Move();

	return 0;
}