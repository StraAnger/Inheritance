#include <iostream>

#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, unsigned int age //принимаемые параметры конструктора Human
#define HUMAN_GIVE_PARAMETRS last_name, first_name, age //передаваемые параметры конструктора Human

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//					Constructors:
	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		std::cout << "HConstructor:\t" << this << std::endl;
	}
	virtual ~Human()
	{
		std::cout << "HDestructor:\t" << this << std::endl;
	}

	//				Methods:
	virtual void print()const
	{
		std::cout << last_name << " " << first_name << " " << age << " y.o." << std::endl;
	}
};

#define EMPLOYEE_TAKE_PARAMETRS  const std::string& position
#define EMPLOYEE_GIVE_PARAMETRS  position

class Employee :public Human  //Наследование
{
	std::string position;
public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;

	Employee(HUMAN_TAKE_PARAMETRS,EMPLOYEE_TAKE_PARAMETRS):Human(HUMAN_GIVE_PARAMETRS) //Делегирование
	{
		set_position(position);
		std::cout << "EConstructor:\t" << this << std::endl;
	}
	~Employee()
	{
		std::cout << "EDestructor:\t" << this << std::endl;
	}
	void print()const
	{
		Human::print();
		std::cout << position;
		std::cout << std::endl;
	}

};

#define PERMANENTEMPLOYEE_TAKE_PARAMETRS double salary 
#define PERMANENTEMPLOYEE_GIVE_PARAMETRS salary 

class PermanentEmployee :public Employee
{
	double salary;
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}

	PermanentEmployee
	(
		HUMAN_TAKE_PARAMETRS,
		EMPLOYEE_TAKE_PARAMETRS,
		PERMANENTEMPLOYEE_TAKE_PARAMETRS
	) : Employee(HUMAN_GIVE_PARAMETRS, EMPLOYEE_GIVE_PARAMETRS)
	{
		set_salary(salary);
		std::cout << "PEConstructor:\t" << this << std::endl;
	}
	~PermanentEmployee()
		{
			std::cout << "PEDestructor:\t" << this << std::endl;
		}

		void print()const
		{
			Employee::print();
			std::cout << salary;
			std::cout << std::endl;
		}


};

#define HOURLYEMPLOYEE_TAKE_PARAMETRS double rate,int hours 
#define HOURLYEMPLOYEE_GIVE_PARAMETRS rate,hours

class HourlyEmployee :public Employee
{
	double rate;//тариф
	int hours;//кол-во отработанных часов
public:
	double get_rate()const
	{
		return rate;
	}
	double get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate*hours;
	}
	
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(double hours)
	{
		this->hours = hours;
	}


	HourlyEmployee
	(
		HUMAN_TAKE_PARAMETRS,
		EMPLOYEE_TAKE_PARAMETRS,
		HOURLYEMPLOYEE_TAKE_PARAMETRS
	) : Employee(
		HUMAN_GIVE_PARAMETRS, 
		EMPLOYEE_GIVE_PARAMETRS
	)
	{
		set_rate(rate);
		set_hours(hours);
		std::cout << "HEConstructor:\t" << this << std::endl;
	}
	~HourlyEmployee()
	{
		std::cout << "HEDestructor:\t" << this << std::endl;
	}

	void print()const
	{
		Employee::print();
		std::cout <<"тариф "<< rate<<", отработано "<<hours<<" часов."<<" Итого:"<<get_salary();
	    std::cout << std::endl;
	}


};

int main()
{
	std::string str = "Hello";


	setlocale(LC_ALL, "");

	Employee* department[] =
	{
		new PermanentEmployee("Rosenberg","Ken",30,"Lawyer",2000),
		new PermanentEmployee("Diaz","Ricardo",50,"Boss",50000),
		new HourlyEmployee("Vercetty","Tomas",30,"Security",500,8)

	};


	double total_salary = 0;
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		std::cout << "\n-------------------------------------------\n";
		department[i]->print();
		total_salary += department[i]->get_salary();
		
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "Общая зарплата всего отдела: " << total_salary << std::endl;
	std::cout << "\n-------------------------------------------\n";

	for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		delete department[i];
	}

	return 0;
}