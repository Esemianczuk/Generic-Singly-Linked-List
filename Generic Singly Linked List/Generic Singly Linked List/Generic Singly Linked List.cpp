/*
Created by Eric Semianczuk on 11/11/16
Copyright (C) 2016 Eric Semianczuk. 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "GSLinkedList.h"

int main()
{
	//Create list object

	GSLinkedList<int> list;
	//Add elements to list
	list.addFront(1);
	list.addFront(3);
	list.addFront(4);
	list.addFront(5);
	std::cout << "List created with following elements: " << std::endl;
	//Prints every element in list
	list.outputAll();


	GSLinkedList<int> list1(5,6,7,8,9);
	std::cout << std::endl << "List1 created with following elements: " << std::endl;
	list1.outputAll();


	//Calls copy constructor, copies data from list1 to list2
	GSLinkedList<int> list2 = list1;
	std::cout << std::endl << "Constructed list2 to be = to list1, list2's elements are as follows: " << std::endl;
	list2.outputAll();

	//Calls copy move constructor, moves data from list2 to list3
	GSLinkedList<int> list3 = std::move(list2);
	std::cout << std::endl << "Constructed list3 with the moved resources of list2, elements are as follows: " << std::endl;
	list3.outputAll();

	//Calls overloaded assignment operator, copies data from list3 to list
	list = list3;
	std::cout << std::endl << "Assigned data from list3 to list, elements are as follows: " << std::endl;
	list.outputAll();

	//Calls overloaded assignment move operator, moves resources from list3 to list
	list = std::move(list3);
	std::cout << std::endl << "Moved resources from list3 to list, elements are as follows: " << std::endl;
	list.outputAll();

	//Calls overloaded addition operator, appends list1 to list
	list + list1;
	std::cout << std::endl << "Added (appended) elements from list1 to list, elements are as follows: " << std::endl;
	list.outputAll();

	bool listGrter = list < list1;
	std::cout << std::endl << "Are the amount of elements in list less then the amount in list1? " << listGrter << std::endl;
	//Calls destructor for list2, frees all resources allocated in list2
	list2.~GSLinkedList();
	std::cout << std::endl << "Called destructor on list2, list2 is empty: " << list2.empty() <<  std::endl;

	std::cin.get();
	return 0;
}