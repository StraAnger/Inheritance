#include <iostream>
#include <fstream>


//#define WRITE_TO_FILE


int main()
{
#ifdef WRITE_TO_FILE
	std::cout << "Hello World" << std::endl;

	std::ofstream fout("file.txt", std::ios::app);
	//app- добавить, дописать
	fout << "Hello World" << std::endl;

	fout.close();

	system("notepad file.txt");

#endif // WRITE_TO_FILE

	const int SIZE = 10240; // 256- маленький для больших файлов 10240 - 10К буфер для большого файла
	char buffer[SIZE]{};

	std::ifstream fin; //создаём поток

	fin.open("file.txt"); //открываем поток

	if (fin.is_open())
	{
		//читаем файл

		while (!fin.eof())  //пока не конец файла (end of file)
		{
			//fin >> buffer; //до пробела читает
			fin.getline(buffer, SIZE); //до конца строки
			std::cout << buffer << std::endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << std::endl;
	}

	fin.close(); //закрываем поток
	return 0;
}