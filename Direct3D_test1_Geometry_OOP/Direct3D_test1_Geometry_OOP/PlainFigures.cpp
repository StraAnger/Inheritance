#include "PlainFigures.h"
#include <iostream>


#define PLAINFIGURES_TAKE_PARAMETRS std::string& color,bool isFilled
#define PLAINFIGURES_GIVE_PARAMETRS 

class PlainFigures
{
	std::string color;
	bool isFilled;

public:

	//Get&Set

	const std::string& get_color() const
	{
		return this->color;
	}

	bool get_isFilled() const
	{
		return this->isFilled;
	}

    void set_color(std::string color)
	{
		this->color=color;
	}

	void set_isFilled(bool isFilled)
	{
		this->isFilled=isFilled;
	}



	//Constructors

	PlainFigures(PLAINFIGURES_TAKE_PARAMETRS)
	{
		set_color(color);
		set_isFilled(isFilled);
		std::cout << "PFConstructor:\t" << this << std::endl;
	}
	
	//Destructor

	virtual ~PlainFigures()
	{
		std::cout << "PFDestructor:\t" << this << std::endl;
	}


	//Operators

	//Methods

};