#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

void circle(const std::vector<std::string>& val);
void printVec(std::vector<std::vector<std::string>>& pool);
void printVec(std::vector<std::vector<std::string>>& pool, int index, int value);
void printVec(std::vector<std::vector<std::string>>& pool, int index1, int index2, int value1, int value2);
void printAnyVec(std::vector<std::vector<std::string>>& pool, int value);

std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while(stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

int main(int argc, char const *argv[])
{
	try
	{
		std::ifstream input("D:/cpp_works/homework02/ip_filters.txt", std::ios_base::in);
		std::vector<std::vector<std::string> > ip_pool;
		ip_pool.reserve(1000);
		
		for(std::string line; std::getline(input, line);)
		{
			std::vector<std::string> v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}


		std::sort( ip_pool.begin(), ip_pool.end(), [](const std::vector<std::string>& i, const std::vector<std::string>& b)
					{
						for(auto it = i.cbegin(), it2 = b.cbegin(); it != i.cend() && it2 != b.cend(); ++it, ++it2)
						{
							auto comp1 = std::stoi(*it);
							auto comp2 = std::stoi(*it2);
							if (comp1 == comp2 ) { continue; }
							return comp1 > comp2;
						}
						return false;
					} );


		printVec(ip_pool);
		printVec(ip_pool, 0, 1);
		printVec(ip_pool, 0, 1, 46, 70);
		printAnyVec(ip_pool, 46);

	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}


void circle(const std::vector<std::string>& val)
{
	for(const auto& val1 :val)
	{
		if (&val1 != &val.at(0))
		{
			std::cout << ".";

		}
		std::cout << val1;
	}
	std::cout << std::endl;
}

void printVec(std::vector<std::vector<std::string>>& pool)
{
	for(const auto& val : pool)
	{
		circle(val);
	}
}

void printVec(std::vector<std::vector<std::string>>& pool, int index, int value)
{
	for(const auto& val : pool)
	{
		if(std::stoi(val.at(index)) == value)
		{
			circle(val);
		}
	}
}

void printVec(std::vector<std::vector<std::string>>& pool, int index1, int index2, int value1, int value2)
{
	for(const auto& val : pool)
	{
		if(std::stoi(val.at(index1)) == value1 && std::stoi(val.at(index2)) == value2)
		{
			circle(val);
		}
	}
}

void printAnyVec(std::vector<std::vector<std::string>>& pool, int value)
{
	for(const auto& val : pool)
	{
		if( std::any_of(val.cbegin(), val.cend(), [&value](const std::string& i){return std::stoi(i) == value;}) )
		{
			circle(val);
		}
	}
}