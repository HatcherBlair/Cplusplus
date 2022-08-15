/*Hatcher Blair
* SNHU CS-210 Project3
* 08/02/2022
* This program takes sales data from a file and lets the user print out a table of the file, search for a specific item,
* or export that data into a file
*/


#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

//Prints the selection menu and returns the user input
int PrintMenu() {
	//Printing the menu
	std::cout << "1: List all items purchased and frequency of purchase" << endl;
	std::cout << "2: List the number of times a specific item was purchased" << endl;
	std::cout << "3: Exort sales data into a file" << endl;
	std::cout << "4: Exit the program" << endl;
	std::cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;

	//getting the input
	string inputString;
	cin >> inputString;

	//Returning the input as int
	return stoi(inputString);
}

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("pythonModule");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonModule");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonModule");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	//While loop to iterate while input does not equal 4
	bool exit = TRUE;

	//Declaring variables to be used in the switch
	int frequency;
	string searchValue;

	while (exit) {

		//Printing the menu and getting user input
		int selection = PrintMenu();

		//Logic to figure out what to do with that input
		switch (selection) {
		case 1:
			//Printing the list of all items purchased
			std::cout << "Printing a list of all items purchased and their frequency..." << endl;
			CallProcedure("printTable");
			break;

		case 2:
			//Searching for the input string
			std::cout << "What item would you like to search for?" << endl;
			cin >> searchValue;
			frequency = callIntFunc("findItem", searchValue);
			if (frequency == -1) {
				cout << "Item not found" << endl;
			}
			else {
				cout << searchValue << " was purchased " << frequency << " times." << endl << endl;
			}
			break;

		case 3:
			//Exporting list of items to a file
			CallProcedure("exportData");
			break;

		case 4:
			//Exiting the program
			std::cout << "Good Bye" << endl;
			exit = FALSE;
			break;

		default:
			//Default case for invalid inputs
			std::cout << "Please enter a valid input" << endl << endl;
			break;
		}
	}
}