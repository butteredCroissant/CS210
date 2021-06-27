/*
Carlie White
Project Three
CS210
June 2021
*/
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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

/*
Description:
	This function will be used to test whether the user input is an integer.
Example:
	User enters 'beans'
	User enters 1
Return:
	Will print 'invalid input' and go back to the beginning of the loop.
	Will continue on to the program
*/
bool checkInput(string input) {
	// Using a for loop in order to capture the length of the user input. 
	for (int i = 0; i <= input.length(); i++)
		if (isdigit(input[i]) == false)
			return false;
		else
			return true;
}
void main()
{
	// Initialize variables that will be used
	string user; // Creates a string for the intial user input to test if it's an int
	int userInput = 0; // This allows for the user to enter the while loop
	string product;

	// Enter a while loop so that the program will keep going until quit. 
	while (userInput == 0) {
		// Menu options
		cout << "1: List of all items purchase and the number of items purchased" << endl;
		cout << "2: Number of times a specific item was purchased" << endl;
		cout << "3: Histogram of all items purchased" << endl;
		cout << "4: Exit program" << endl;

		// Get the user input as string
		cin >> user;

		// Branch taken if input is not an integer
		if (!checkInput(user)) {
			cout << "Invalid input" << endl;
		}
		// Branch taken if input is an integer
		else {
			int i = std::stoi(user); // Converts string to integer
			userInput = i;

			/*
			Creates a list of all items purchased and their amount and returns to
			the beginning of the loop
			*/
			if (userInput == 1) {
				CallProcedure("printsomething");
				userInput = 0;
			}

			/*
			Allows the user to search for a product and returns the amount of
			times it was purchased.
			*/
			else if (userInput == 2) {
				cout << "Please enter a product: ";
				cin >> product;
				cout << callIntFunc("PrintMe", product) << endl;
				userInput = 0;
			}

			/*
			Creates a new file in Python. Then, in C++, the file is read and
			displays a histogram of the products on the screen.
			*/
			else if (userInput == 3) {
				string myText;
				int numStars;
				char star = '*';
				CallProcedure("Histogram");
				cout << "Information sent!" << endl;
				// Open file
				ifstream MyReadFile("frequency.dat");
				// Get each line in file
				while (getline(MyReadFile, myText)) {
					// Converts the value of each product to an integer
					numStars = std::stoi(myText.substr(myText.find(":") + 1));
					// Finds the product name
					myText = myText.substr(0, myText.find(":"));
					// Prints the histogram using a built-in function to display stars
					cout << myText << " " << std::string(numStars, star) << endl;
				}

				userInput = 0;
			}
			else if (userInput == 4) {
				break;
			}
			// Branch is taken if the user enters a integer, but its still not an option
			else {
				cout << "Not a valid entry, please enter an option from the menu";
				userInput = 0;
			}
		}

	}
}
