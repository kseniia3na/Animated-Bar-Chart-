/* 
    Project 3 - Animated Bar Chart (barchartanimate.h)

    Kseniia Nastahunina

    This class is final implementation of animation charts. The class is used for 
    reading information from txt file and storing into previously implemented
    barchart and print out the sorted animation.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used by graders, do not remove
#include "barchart.h"
  
using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string title;
    string xlabel;
    string source;

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        
        barcharts = new BarChart[4]; //sets default capacity to 4, will grow when required
        size = 0;
        capacity = 4;
        this -> title = title;
        this -> xlabel = xlabel;
        this -> source = source;
        
    }
    /*The functions below is used for testing purposes.*/
    string getTitle(){
        return title;
    }
    string getxlabel(){
        return xlabel;
    }
    string getSource(){
        return source;
    }
    int getCapacity(){
        return capacity;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if(barcharts != nullptr){
            delete [] barcharts;
        }
        
    }
    /* The function doubles the capacity of barchars when the size of the array 
    equal to its capacity. Used in addFrame function.*/
    void doubleCap(){
        int newCapacity = capacity * 2;
        BarChart* newBarcharts = new BarChart[newCapacity];

        // copy the elements from barcharts to the new array:
        for (int i = 0; i < size; ++i){
            newBarcharts[i] = barcharts[i];
        }

        // now delete barcharts, and update private data members to point to new array
        // and reflect new capacity:
        delete[] barcharts;
        barcharts = newBarcharts;
        capacity = newCapacity;
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        

        string line;
        getline(file, line);
        int numBars = 0;
        int colorCount = 0;

        if(line.empty()){
            getline(file, line);
            if(!line.empty()){
                if(size == capacity){
                    doubleCap();
                }
                numBars = stoi(line); //gets number of bars and converts string into int
                barcharts[size] = BarChart(numBars); //adds to barchrt array
                for(int i = 0; i < numBars; i++){
                    getline(file, line);
                    string stringElement;
                    stringstream x(line);
                    vector<string> elements; //used to store elements of the current line
                    while(getline(x, stringElement, ',')){ //parsing elements of the line by delim ","
                        elements.push_back(stringElement);
                    }
                    //takes elements of the vector and stores/converts into needed values 
                    string frame = elements[0]; 
                    string name = elements[1];
                    int value = stoi(elements[3]);
                    string category = elements[4];

                    barcharts[size].setFrame(frame);
                    
                    map<string,string>::iterator colorIterator = colorMap.find(category);
                    if (colorIterator == colorMap.end()){ //if category doesn't exist
                        colorMap[category] = COLORS[colorCount];
                        colorCount++;
                        if(colorCount == COLORS.size()){
                            colorCount = 0;
                        }
                    }

                    barcharts[size].addBar(name, value, category); //adds elements to bar
                    elements.clear(); //clears vector for the next line
                }
                size++; //increases the size of barchars
            }
        }
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {

		unsigned int microsecond = 50000;
        
        if(endIter != -1){
            
            for(int i = 0 ; i < endIter; i++){ //prints the inputed number of charts
                cout << title << endl << source << endl; //prints out the header of the chart
                barcharts[i].graph(output, colorMap, top);
                cout << WHITE << xlabel << endl;
                cout << "Frame: " << barcharts[i].getFrame() << endl;
                if(i != endIter - 1){
                    output << CLEARCONSOLE;
                }
                usleep(3 * microsecond);
            }
        }
        else{
            for(int i = 0; i < size; i++){ //prints all charts
                cout << title << endl << source << endl; //prints out the header of the chart
                barcharts[i].graph(output, colorMap, top);
                cout << WHITE << xlabel << endl;
                cout << "Frame: " << barcharts[i].getFrame() << endl;
                if(i != size - 1){
                    output << CLEARCONSOLE;
                }
                usleep(3 * microsecond);
                
            }
            
        } 
	}


    /*Creative Componenet. For use with cities.txt. Prints animation for the range ofentered dates from
    user's input in application.cpp*/
    
	void animateForCitiesWithDates(ostream &output, int top, int start, int end) {

		unsigned int microsecond = 50000;
        int begin = start - 1500;
        int stop = end - 1500;
        cout << begin << " " << stop << endl;

            
        for(int i = begin; i <= stop; i++){ //prints the inputed number of charts
            cout << "The most populous cities in the world from " << start << " to " << end << endl;
            cout << source << endl; //prints out the header of the chart
            barcharts[i].graph(output, colorMap, top);
            cout << WHITE << xlabel << endl;
            cout << "Frame: " << barcharts[i].getFrame() << endl;
            if(i != stop){
                output << CLEARCONSOLE;
            }
            usleep(3 * microsecond);
        }
    }

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize(){
        
        return size;
        
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){

        if(i < 0 || i >= size){
            throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};
