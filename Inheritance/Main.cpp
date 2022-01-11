//Academy
#include<iostream>
#include<string>
using namespace std;

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
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual void print()const
	{
		cout << last_name << " " << first_name << " " << age << " y.o." << endl;
	}
};

#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS speciality, group, rating, attendance

class Student :public Human
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
	double get_attendance()const
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

	//					Constructors:
	Student
	(
		HUMAN_TAKE_PARAMETRS,
		STUDENT_TAKE_PARAMETRS
	) :Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETRS const const std::string& speciality, unsigned int experience
#define TEACHER_GIVE_PARAMETRS speciality, experience


class Teacher :public Human
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
	//				Constructor
	Teacher
	(
		HUMAN_TAKE_PARAMETRS,
		TEACHER_TAKE_PARAMETRS
	)
		:Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}
	//					Methods
	void print()const
	{
		Human::print();
		cout << speciality << " " << experience << endl;
	}
};

class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const
	{
		return subject;
	}
	void set_subject(const std::string& subject)
	{
		this->subject = subject;
	}
	//						Constructors:
	Graduate(
		HUMAN_TAKE_PARAMETRS,
		STUDENT_TAKE_PARAMETRS,
		const std::string& subject) :Student(HUMAN_GIVE_PARAMETRS, STUDENT_GIVE_PARAMETRS)
	{
		set_subject(subject);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}
	//						Methods:
	void print()const
	{
		Student::print();
		cout << subject << endl;
	}
};

//Resharper

//#define INHERITANCE_CHECK

void main()
{
#ifdef INHERITANCE_CHECK
	setlocale(LC_ALL, "");
	Human human("Connor", "John", 18);
	human.print();

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_123", 85, 95);
	stud.print();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();

	Graduate grad("Shreder", "Hank", 40, "Cryminalistic", "WW_123", 90, 75, "How to catch Heizenberg");
	grad.print();
#endif // INHERITANCE_CHECK

	//Generalization (up-cast)

	Human* group[] =
	{
		new Student("Pinkman", "Jessie", 25, "Chemistry", "WW_123", 85, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Shreder", "Hank", 40, "Cryminalistic", "WW_123", 90, 75, "How to catch Heizenberg"),
		new Student("Vercetti", "Tomas", 30, "City business", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 55, "Weapons distribution", 30),
		new Student("Montana", "Antonio", 30, "Cryminalistic", "Vice", 90, 80),

	};


	//оператор sizeof- возвращает размер в байтах выдаЄт

	std::cout << sizeof(group) / sizeof(Human*) << std::endl;//¬ычисл€ем размер массива в элементах- делем размер массива в байтах на размер элекмента в байтах.

	//Specialisation- уточнение ( Down-cast- приведение базового типа к дочернему)

	for (int i = 0; i < sizeof(group)/sizeof(Human*); ++i) 
	{
		std::cout << "\n--------------------------------" << std::endl;
		std::cout << typeid(*group[i]).name() << std::endl; //TRRI -Runtime Type Information
		group[i]->print();
		std::cout << "\n--------------------------------" << std::endl;
	}

////////////////////////////////////////////
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); ++i)
	{

		delete group[i];
	}


}