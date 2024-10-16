#include <iostream>

#include <set>

#include "Algorithm.h"

void print(const std::set<int> container)
{
	for (const auto& item : container)
		std::cout << item << " ";
	std::cout << std::endl;
}

int main()
{
	std::set<int> example;

	//insert elements
	example.insert(1);
	example.insert(1);
	example.insert(1);
	//example.insert(7);
	example.insert(3);
	example.insert(18);
	example.insert(6);
	example.insert(9);
	example.insert(90);
	example.insert(999);



	std::set<int>::iterator itCountBegin = example.begin();
	std::set<int>::iterator itCountEnd = example.end();
	int size=sss::count(itCountBegin, itCountEnd);
	std::cout << "Size of container: " << size << std::endl;


	print(example);
	std::cout << "Amount of elements: " << example.size() << std::endl;   //count all elements


	std::set<int>::iterator itFind;
	itFind = example.find(7);   //find element
	if(itFind!=example.end())
		example.erase(itFind);    //delete element
	print(example);

	/*std::set <int>::iterator it1 = example.begin();
	std::set<int>::iterator it2 = example.end();

	example.erase(it1, it2);
	print(example);

	std::cout << "Amount of elements: " << example.size() << std::endl;  */

	std::cout << "Amount of 1 in container: " << example.count(1) << std::endl;  //count number of specific elements

	for (std::set<int>::iterator it = example.lower_bound(3); it != example.upper_bound(6); it++)  //lower_bound - not less than key, upper_bound - not greater tnah key
		std::cout << *it << " ";
	std::cout << std::endl;

	std::pair< std::set<int>::iterator, std::set<int>::iterator> pair = example.equal_range(1);   
	for (std::set<int>::iterator it = pair.first; it != pair.second; it++)
		std::cout << *it << " ";


	example.clear();  //clear set
	print(example);
	std::cout << "Set is empty: " << example.empty() << std::endl;


	return 0;
}