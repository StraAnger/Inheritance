#include <iostream>
#include <fstream>


//#define WRITE_TO_FILE


int main()
{
#ifdef WRITE_TO_FILE
	std::cout << "Hello World" << std::endl;

	std::ofstream fout("file.txt", std::ios::app);
	//app- ��������, ��������
	fout << "Hello World" << std::endl;

	fout.close();

	system("notepad file.txt");

#endif // WRITE_TO_FILE

	const int SIZE = 10240; // 256- ��������� ��� ������� ������ 10240 - 10� ����� ��� �������� �����
	char buffer[SIZE]{};

	std::ifstream fin; //������ �����

	fin.open("file.txt"); //��������� �����

	if (fin.is_open())
	{
		//������ ����

		while (!fin.eof())  //���� �� ����� ����� (end of file)
		{
			//fin >> buffer; //�� ������� ������
			fin.getline(buffer, SIZE); //�� ����� ������
			std::cout << buffer << std::endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found" << std::endl;
	}

	fin.close(); //��������� �����
	return 0;
}