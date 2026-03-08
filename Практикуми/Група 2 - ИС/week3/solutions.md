# Решения

### Задача 1
```cpp
int main()
{
	std::ifstream ifs("main.cpp");
	if (!ifs.is_open())
	{
		std::cout << "Error...";
		return -1;
	}
	while (!ifs.eof())
	{
		char buffer[100];
		ifs.getline(buffer, 100);
		std::cout << buffer << '\n';
	}
}
```