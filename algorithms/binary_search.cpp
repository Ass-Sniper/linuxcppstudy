#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <time.h>

using namespace std;

typedef unsigned int uint;

// Basic binary search, using three-way comparisons
template <class Comparable>
Comparable binarySearch(const vector<Comparable> & a, const Comparable & x)
{
	int low = 0;
	int high = a.size() - 1;
	int mid;

	while (low < high) {

		mid = (low + high) / 2;

		if (a[mid] < x) {
			low = mid + 1;
		} else if (a[mid] > x) {
			high = mid - 1;
		} else
			return mid;
	}

	// if x is not found, then return -1
	return -1;
}

// Binary search, using two-way comparisons
template <class Comparable = int>
Comparable binarySearch_improved(const vector<Comparable> & a, const Comparable & x)
{
	int low = 0;
	int high = a.size() - 1;
	int mid;

	while (low < high) {

		mid = (low + high) / 2;

		if (a[mid] < x) {
			low = mid + 1;
		} else {
			high = mid;
		}
	}

	return (low == high && a[low] == x) ? low : -1;
}

/*void generateRangeNumber(char* filename, const int min, const int max, const uint count)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    int value = 0;
    vector<int> tmp;
	for (uint i = 0; i < count; ++i) {
		value = distr(eng); 
		tmp.push_back(value);
	}
	std::sort(tmp.begin(), tmp.end());

	ofstream tofile(filename);
	tofile.open(filename, std::ofstream::out | std::ofstream::app);
	if (tofile.is_open())
	{
		int j = 0;
		for(std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it, j++) {
			tofile << *it;
			if (j%10 == 0) {
				tofile << "\n";
			}
			else
				tofile << ",";				
		}
		tofile.close();
	} else {
		cout << "Unable to open file";
	}

	// ofstream tofile(filename);
	// tofile.open(filename, ios::out | ios::app );
	// if (tofile.is_open())
	// {
	// 	for (uint j = 0; j < count; ++j) {
	// 		value = distr(eng); 
	// 		tofile << value;
	// 		if (j%10 == 0) {
	// 			tofile << "\n"
	// 		}
	// 		else
	// 			tofile << ","
	// 	}
	// 	tofile.close();
	// } else {
	// 	cout << "Unable to open file";
	// }
}*/

void generateRangeNumber(ofstream & tofile, const int min, const int max, const uint count)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    int value = 0;
    vector<int> tmp;
	for (uint i = 0; i < count; ++i) {
		value = distr(eng); 
		tmp.push_back(value);
	}
	std::sort(tmp.begin(), tmp.end());

	if (tofile.is_open())
	{
		int j = 0;
		for(std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it, j++) {
			tofile << *it;
			if (j%10 == 0) {
				tofile << "\n";
			}
			else
				tofile << ",";				
		}
		tofile.close();
	} else {
		cout << "Unable to open file";
	}
}

// Load data from file to vector
// @param: ifstream & fromfile cannot be const 
template <class Comparable>
void loadFromFile(ifstream & fromfile, vector<Comparable> & tovector)
{
	// int value;
	std::string line;
	std::string sdata;

	if (fromfile.is_open())
	{
		while(fromfile)
		{
			if (!std::getline(fromfile, line)) break;
			std::stringstream linestream(line);

			while(linestream)
			{
				if (!std::getline(linestream, sdata, ',')) break;
				// value = std::atoi(sdata.c_str());
				// tovector.push_back(value);
				tovector.push_back(std::stoi(sdata));
				sdata = "";
			}
			line = "";
		}
		if (!fromfile.eof())
		{
			cout<< "Empty file\n";
		}
		fromfile.close();
	} else {
		cout << "Error opening file\n";
	}

}

int main(int argc, char const *argv[])
{
	vector<int> arr;
	int searchvalue, ret;
	
	char filename[] = "binsearch_data.txt";
/* 	std::ofstream tofile(filename, std::ofstream::out | std::ofstream::app);
 	// random test data: program(user space stack) -> ofstream -> disk file
	generateRangeNumber(tofile, 1, 1000, 800);*/
	std::ifstream fromfile(filename, std::ifstream::in);
	// random test data: program(user space stack) <- ifstream <- disk file
	loadFromFile(fromfile, arr);

	cout<< "Please input the search number: ";
	cin >> searchvalue;

	clock_t startTime,finishTime;
    double totaltime;

    startTime = clock();
    ret = binarySearch(arr, searchvalue);
    finishTime = clock();
 	totaltime = (double)(finishTime-startTime)/CLOCKS_PER_SEC;
   	cout<< "Basic binary search execution time:"<< fixed << totaltime << "s" <<endl;
	if(ret >= 0) {
		cout<< "Found: " << searchvalue <<endl;
	} else {
		cout<< "Not found" <<endl; 
	}
   	cout<< "------------------------------------------" <<endl;

    startTime = clock();
    ret = binarySearch_improved(arr, searchvalue);
    finishTime = clock();
 	totaltime = (double)(finishTime-startTime)/CLOCKS_PER_SEC;
   	cout<< "Improved binary search execution time:"<< fixed << totaltime << "s" <<endl;
	if(ret >= 0) {
		cout<< "Found: " << searchvalue <<endl;
	} else {
		cout<< "Not found" <<endl; 
	}
   	cout<< "------------------------------------------" <<endl;

	return 0;
}