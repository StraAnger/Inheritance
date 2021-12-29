#include <iostream>
#include <string>

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:

	const std::string& get_last_name() const
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

	//constructors

	Human(const std::string last_name, const std::string first_name, unsigned int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		std::cout << "HConstructor:\t" << this << std::endl;
	}

	~Human()
	{
		std::cout << "HDestructor:\t" << this << std::endl;
	}

	//Methods

	void print() const
	{
		std::cout << last_name << " " << first_name << " " << age << " y.o." << std::endl;
	}

};


class Student : public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}

	const std::string& get_group()const
	{
		return group;
	}

	double get_rating()const
	{
		return rating;
	}

	double get_attendance() const
	{
		return attendance;
    }

	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}

	void set_group(const std::string& group)
	{
		this->group = group;
	}

	void set_rating(double rating)
	{
		this->rating = rating;
	}

	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//Constructors

	Student
	(
		const std::string last_name, const std::string first_name, unsigned int age,
		const std::string& speciality,const std::string& group, double rating, double attendance
	) :Human(last_name,first_name,age)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		std::cout << "SConstructor:\t" << this << std::endl;

	}

	~Student()
	{
		std::cout << "SDestructor:\t" << this << std::endl;
	}


	void print()const
	{
		Human::print();
		std::cout << speciality << " " << group << " " << rating << " " << attendance << std::endl;
	}

};

class Graduate : public Student
{
	std::string diplomaTheme;

public:
	const std::string& get_diplomaTheme()const
	{
		return diplomaTheme;
	}

	void set_diplomaTheme(const std::string& diplomaTheme)
	{
		this->diplomaTheme = diplomaTheme;
	}

	//Constructors

	Graduate
	(
		const std::string last_name, const std::string first_name, unsigned int age,
		const std::string& speciality, const std::string& group, double rating, double attendance,
		const std::string& diplomaTheme

	) :Student( last_name, first_name, age,speciality, group, rating, attendance)
	{
		set_diplomaTheme(diplomaTheme);
		std::cout << "SConstructor:\t" << this << std::endl;

	}

	~Graduate()
	{
		std::cout << "SDestructor:\t" << this << std::endl;
	}


	void print()const
	{
		Student::print();
		std::cout << diplomaTheme << std::endl;
	}

};


class Teacher : public Human
{
	std::string speciality;
	unsigned int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}

	unsigned int get_experience()const
	{
		return experience;
	}

	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}

	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}


	//Constructors

	Teacher
	(
		const std::string last_name, const std::string first_name, unsigned int age,
		const std::string& speciality, unsigned int experience
	) :Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experience(experience);
		std::cout << "SConstructor:\t" << this << std::endl;

	}

	~Teacher()
	{
		std::cout << "SDestructor:\t" << this << std::endl;
	}


	void print()const
	{
		Human::print();
		std::cout << speciality << " " << experience<< std::endl;
	}

};


int main()
{
	Human human("Connor", "John", 18);
	human.print();

	Student stud("Pinkman", "Jessie", 25,"Chemistry", "WW_123", 85, 95);
	stud.print();

	Graduate grad("Skywalker", "Luke", 18, "Force in modern universe", "WW_123", 70, 99,"Could the Empire Strikes Back again?");
	grad.print();

	Teacher teach("Nukem", "Duke", 35, "Kick-asser", 100);
	teach.print();


	return 0;
}