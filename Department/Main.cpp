#include <iostream>
#include <fstream>

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
	virtual std::ostream& print(std::ostream& os)const
	{
		//return os<< last_name << " " << first_name << " " << age << " y.o.";

		os.width(10);
		os << std::left;
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age << " y.o. ";
		return os;
	}
};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}


#define EMPLOYEE_TAKE_PARAMETRS  const std::string& position
#define EMPLOYEE_GIVE_PARAMETRS  position


//Абстрактный класс
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
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os)<<" ";

		os.width(10);
		os << std::left;
		os << position;
		return os;
		
	}

};

std::ostream& operator<<(std::ostream& os, const Employee& obj)
{
	os << (Human)obj;
	return os << obj.get_position();
}

#define PERMANENTEMPLOYEE_TAKE_PARAMETRS double salary 
#define PERMANENTEMPLOYEE_GIVE_PARAMETRS salary 

//Конкретный класс

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

		std::ostream& print(std::ostream& os)const
		{
			Employee::print(os) << " ";
			os.width(10);
			os << std::left;
			os << salary;
			return os;
			
		}


};

std::ostream& operator<<(std::ostream& os, const PermanentEmployee& obj)
{
	return os << (Employee&)obj << " " << obj.get_salary();
}

#define HOURLYEMPLOYEE_TAKE_PARAMETRS double rate,int hours 
#define HOURLYEMPLOYEE_GIVE_PARAMETRS rate,hours

//Конкретный класс

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

	std::ostream& print(std::ostream& os)const
	{
		Employee::print(os) << " ";
			    
		os.width(10);
		os << std::left;
		os <<" тариф " << rate;
		os.width(10);
		os <<" отработано " << hours<<" часов. ";
		os.width(3);
		os <<" Итого: "<< get_salary();
		return os;
	}


};


std::ostream& operator<<(std::ostream& os, const HourlyEmployee& obj)
{
	return os << (Employee&)obj << " " << " rate: " << obj.get_rate() << " hours: " << obj.get_hours()<<" Total: "<<obj.get_salary();
}

int main()
{

	std::string str = "Hello";


	setlocale(LC_ALL, "");
	//Generalisation- обобщение (UpCast)
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
		//department[i]->print();
		//std::cout << typeid(*department[i]).name() << std::endl;
		//Specialization (DownCast)
		//if (typeid(*department[i]) == typeid(PermanentEmployee))
		//{
		//	std::cout<<*dynamic_cast<PermanentEmployee*>(department[i])<<std::endl;
		//}

		//if (typeid(*department[i]) == typeid(HourlyEmployee))
		//{
		//	std::cout << *dynamic_cast<HourlyEmployee*>(department[i]) << std::endl;
		//}

		std::cout << *department[i] << std::endl;
		total_salary += department[i]->get_salary();
		
	}
	std::cout << "\n-------------------------------------------\n";
	std::cout << "Общая зарплата всего отдела: " << total_salary << std::endl;
	std::cout << "\n-------------------------------------------\n";

	std::ofstream fout("file.txt");
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		fout.width(30);
		fout << std::left;
		fout <<std::string(typeid(*department[i]).name())+ ":" << *department[i] << std::endl;
	}
	fout.close();
	system("start notepad file.txt");


	for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		delete department[i];
	}



	return 0;
}