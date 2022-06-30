#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#pragma comment(linker, "/STACK:2000000")
#include <chrono>
#include <sstream>
#include "strutils.h"
using namespace std;


//Ege Demirci - CS300 - Searching and Sorting Algorithms


//Main phonebook struct that will be used for the data.
struct phonebook{
	string userName;
	string phone;
	string city;
	bool operator < (const phonebook & rhs) const{
		return userName < rhs.userName;
	}
	bool operator > (const phonebook& rhs) const{
		return userName > rhs.userName;
	}
	bool operator == (const phonebook& rhs) const{
		return userName == rhs.userName;
	}
	bool operator <= (const phonebook& rhs) const{
		return userName <= rhs.userName;
	}
	bool operator >= (const phonebook& rhs) const{
		return userName >= rhs.userName;
	}
};


bool partialSearch = true; /*Global bool variable to check partial search. If key includes space then it's true.*/

//Insertion sort algorithm.
template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
	for (int p = 1;  p < a.size(); p++){
		Comparable tmp = a[p]; // loop over the elements
		for (j = p; j > 0 &&  tmp < a[j-1]; j--){
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}
//Insertion sort algorithm that will be used in quicksort algorithm.
template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right ){
	for ( int p = left + 1; p <= right; p++ ){
		Comparable tmp = a[ p ];
		int j;
		for ( j = p; j > left && tmp < a[ j - 1 ]; j-- ){
				a[ j ] = a[ j - 1 ];
		}
		a[j] = tmp;
	}
}


inline int leftChild( int i )
{
	return 2*i+1;
}

//Percdown that will be used in heapsort.
template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n ){
	int child;
	Comparable tmp;
	for (tmp=a[i] ; leftChild(i) < n; i = child ){
		child = leftChild(i);
		if ( child != n-1 && a[ child  ] < a[ child+1 ] )
			child++;
		if ( a[child ] > tmp )
			a[i] = a[ child ];
		else
			break;
	} 
	a[ i ] = tmp;
}

//Heap sort algorithm.
template <class Comparable>
void heapSort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());
	// sort
	for (int j = a.size()-1; j >0; j--)
	{
		Swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}


//*** Standard swap*/
template <class Comparable>
inline void Swap( Comparable & obj1, Comparable & obj2 ){
	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;
}
//Will be used in quicksort.
//** Return median of left, center, and right.*  
//Order these and hide the pivot.*/
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right ){
	int center = ( left + right ) / 2;
	if ( a[ center ] < a[ left ] )
		Swap( a[ left ], a[ center ] );
	if ( a[ right ] < a[ left ] )
		Swap( a[ left ], a[ right ] );
	if ( a[ right ] < a[ center ] )
		Swap( a[ center ], a[ right ] );

// Place pivot at position right - 1
	Swap( a[ center ], a[ right - 1 ] );
	return a[ right - 1 ];
}

//Quick sort algorithm.
template <class Comparable>
void quickSort(vector<Comparable>& a, int left, int right) {
	if (left + 10 <= right) {
		Comparable pivot = median3(a, left, right);
		// Begin partitioning
		int i = left, j = right - 1;
		for (;;){
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		Swap(a[i], a[right - 1]);   // Restore pivot
		quickSort(a, left, i - 1);       // Sort small elements
		quickSort(a, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}


//Driver function for quicksort.
 template <class Comparable>
 void quickSort( vector<Comparable> & a )
 {
	quickSort( a, 0, a.size( ) - 1 );
 }
 
 //Inplace merge sort. 
template <class Comparable>
void merge(int start, int center, int end, vector<Comparable> & a)
{
    int sec_start = center + 1; //start from center+1/
	if (a[center] <= a[sec_start]){ //if center is already smaller than sec_start then no need to continue.
        return;
    }
    while (sec_start <= end && start <= center) {
		if (a[start] <= a[sec_start]) { //go until a[start]= a[sec_start]
            start = start + 1;
        }
        else{
            Comparable obj = a[sec_start];
			int start_index = sec_start;
            while (start_index != start) { //shifting process
                a[start_index] = a[start_index - 1];
                start_index = start_index - 1;
            }
            a[start] = obj; // swapping process
            start = start + 1; center = center + 1 ; sec_start = sec_start + 1;
        }
    }
}

//Recursive merge sort.
template <class Comparable>
void mergeSort(int left, int right, vector<Comparable> & a)
{
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(left, middle,a);
        mergeSort(middle + 1, right,a);
        merge(left, middle, right, a);
    }
}

//Driver function for merge sort.
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	mergeSort( 0, a.size( ) - 1, a);
}


//Binary search algorithm that find all the occurences and can do partial/full search/
vector<int> binarySearch(const vector<phonebook>& list, const string & key){
	int low = 0; // leftmost possible entry
	int high = list.size()-1;      // rightmost possible entry
	int mid;            // middle of current range
	vector<int> listOfIndexes;
	if(partialSearch == true){ //key doesn't include space character.
		while (low <= high){   
			mid = (low + high)/2;
			string partialElt = list[mid].userName.substr(0, key.length());
			if (partialElt == key){       // found key, exit search
				int temp = mid;
				while(temp >= 0 && list[temp].userName.substr(0, key.length()) == key){ //go back to the firstoccurence and append all the indexes.
					listOfIndexes.push_back(temp);
					temp--;
				}
				temp = mid + 1;
				while ( temp < list.size() && list[temp].userName.substr(0, key.length()) == key){ //then append all the right indexes.
					listOfIndexes.push_back(temp);
					temp += 1;
				}
				return listOfIndexes; //return the list of indexes of key.
			}
			else if (partialElt < key){   // key in upper half
				low = mid + 1;
			}
			else{                    // key in lower half
				high = mid - 1;
			}
		}
	}
	else if (partialSearch == false){ //same process as above but now it's full search.
		low = 0; // leftmost possible entry
		high = list.size()-1;      // rightmost possible entry
		while (low <= high){   
            int mid = (low + high) / 2;
			if (list[mid].userName == key){      // found key, exit search
				int temp = mid;
				while(temp >= 0 && list[temp].userName == key){
					listOfIndexes.push_back(temp);
					temp--;
				}
				temp = mid + 1;
				while ( temp < list.size() && list[temp].userName == key){
					listOfIndexes.push_back(temp);
					temp += 1;
				}
				return listOfIndexes;
			}
			else if (list[mid].userName < key){   // key in upper half
				low = mid + 1;
			}
			else{                       // key in lower half
				high = mid - 1;
			}
		}
    }
    return listOfIndexes;                      // not in list
}

//Sequential search algorithm that find all the occurences and can do full/partial search.
vector<int> sequentialSearch(const vector<phonebook>& list, const string & key){
	vector<int> listOfIndexes;
	if(partialSearch == true){
		for (int i=0; i < list.size();i++){
			string partialElt = list[i].userName.substr(0, key.length()); //first key.length() element of the key.
			if( partialElt == key){
				listOfIndexes.push_back(i); 
			}
		}
	}
	if(partialSearch == false){
		for (int i=0; i < list.size();i++){
			if( list[i].userName == key){
				listOfIndexes.push_back(i);
			}
		}
	}
	return listOfIndexes;
} 

//Helper function to print phonebook vector.
void printPhonebook(vector<phonebook> phoneBook){
	for(int i=0; i<phoneBook.size();i++){
		cout << phoneBook[i].userName << " " << phoneBook[i].phone << " " << phoneBook[i].city << endl; 
	}
}
//Helper function to print phonebook vector which uses indexes.
void printFromIndexes(const vector<int> & idxlist, const vector<phonebook> & phoneBook){
	for(int i=0; i < idxlist.size(); i++){
		cout << phoneBook[idxlist[i]].userName << " " << phoneBook[idxlist[i]].phone << " " << phoneBook[idxlist[i]].city << endl;
	}
}

//Helper function to print times.
void printTimes(long long quickTime, long long heapTime , long long insertionTime, long long mergeTime){
	cout << "Quick Sort Time: " << quickTime << " Nanoseconds" << endl;
	cout << "Insertion Sort Time: "<< insertionTime << " Nanoseconds"<< endl;
	cout << "Merge Sort Time: " << mergeTime <<  " Nanoseconds"<< endl;
	cout << "Heap Sort Time: "<< heapTime << " Nanoseconds"<< endl;

}

//Helper function to print speedups.
void printSpeedUps(long long quickTime, long long heapTime , long long insertionTime, long long mergeTime,
				   long long secTime, long long bsTime){
	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << (double)secTime / bsTime << endl << endl;
	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << insertionTime / (double)quickTime << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << mergeTime / (double)quickTime << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << heapTime / (double)quickTime << endl;

}
int main(){
	string filename,line,s,firstName,lastName, phoneNumber, city,searchword;
	ifstream input;
	vector<int> BSindex, SQindex;
	long long quickTime=0,heapTime = 0, insertionTime = 0, mergeTime = 0,bstTime = 0 , seqTime = 0;
	cout << "Please enter the contact file name:" << endl;
	cin>>filename;
	cout << "Please enter the word to be queried:" << endl;
	cin.ignore();
	getline(cin,searchword);
	cout << endl;

	int spaceIdx = searchword.find(" ");
	if (spaceIdx != string::npos){ //If searchword includes space then it's full search.
		partialSearch = false;
	}
	vector<phonebook> mainPhonebook;
	input.open(filename.c_str());
	while(getline(input, line)){ //Data processing.
		phonebook newUser;
		istringstream linestream(line);
		linestream >> firstName >> lastName >> phoneNumber >> city;
		string username = firstName + " " + lastName;
		newUser.userName = UpperString(username); newUser.phone = UpperString(phoneNumber); newUser.city = city;
		mainPhonebook.push_back(newUser);
	}
	vector<phonebook> quicksort = mainPhonebook;
	vector<phonebook> insertionsort = mainPhonebook;
	vector<phonebook> mergesort = mainPhonebook;
	vector<phonebook> heapsort = mainPhonebook;
	vector<phonebook> copy;
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	auto startHeap = chrono::high_resolution_clock::now();
	for(int i=0; i<19; i++){ //HEAPSORT, 20 ITERATION FOR BETTER RESULTS.
		copy = heapsort;
		heapSort(copy);
	}	
	heapSort(heapsort);
    auto heap = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startHeap);
	heapTime = heap.count() / 20.0;

	auto startInsert = chrono::high_resolution_clock::now();
	for(int i=0; i<19; i++){
		copy = insertionsort; //INSERTIONSORT, 20 ITERATION FOR BETTER RESULTS.
		insertionSort(copy);
	}
	insertionSort(insertionsort);
    auto insert = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startInsert);
	insertionTime = insert.count() / 20.0;

	auto startMerge = chrono::high_resolution_clock::now();
	for(int i=0; i<19; i++){
		copy = mergesort; //MERGESORT, 20 ITERATION FOR BETTER RESULTS.
		mergeSort(copy);
	}
	mergeSort(copy);
    auto merge = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startMerge);
	mergeTime = merge.count() / 20.0;


	auto startQuick = chrono::high_resolution_clock::now();
	for(int i=0; i<19; i++){
		copy = quicksort; //QUICKSORT, 20 ITERATION FOR BETTER RESULTS.
		quickSort(copy);
	}
	quickSort(quicksort);
    auto quick = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startQuick);
	quickTime = quick.count() / 20.0;


	printTimes(quickTime,heapTime,insertionTime,mergeTime);  //print all the times.
	cout << endl;
	cout << "Searching for " << searchword << endl;
	cout << "======================================" << endl;
	int N = 1000; //SEARCHING ALGORITHMS, 1000 ITERATION FOR BETTER MEASURE.
		auto startBinary = chrono::high_resolution_clock::now(); //BINARY
		ToUpper(searchword);
		for(int i=0; i < N; i++){
			BSindex = binarySearch(quicksort,searchword); //indexes are mixed.
			quickSort(BSindex); //so sort them.
		}
		if(BSindex.size() == 0){
			cout << searchword << " does NOT exist in the dataset" << endl;
		}
		else{
			printFromIndexes(BSindex,quicksort);
		}
	auto endBinary = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startBinary);
	bstTime = endBinary.count() / N;
	cout << "Binary Search Time: " << bstTime << endl << endl;
	cout << "Search results for Sequential Search: " << endl;
		auto startSequential = chrono::high_resolution_clock::now(); //SEQUENTIAL
		ToUpper(searchword);
		for(int i=0; i < N; i++){
			SQindex = sequentialSearch(quicksort,UpperString(searchword));
		}
		if(SQindex.size() == 0){
			cout << searchword << " does NOT exist in the dataset" << endl;
		}
		else{
			printFromIndexes(SQindex,quicksort);
		}
	auto endSequential = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startSequential);
	seqTime = endSequential.count() / N;
	cout << "Sequential Search Time: " << seqTime << endl<< endl;
	printSpeedUps(quickTime,heapTime,insertionTime,mergeTime,seqTime,bstTime); //print all the speedups
}