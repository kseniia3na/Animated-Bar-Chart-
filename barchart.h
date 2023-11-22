/* 
    Project 3 - Animated Bar Chart (barchart.h)

    Kseniia Nastahunina

    This class is used for creating bars and graph charts using colormap.

*/


#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in graders, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");


//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
//
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};



//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string frame;
    
 public:
    
    /*Default constructr. Sets all privat members to its default values.*/
    BarChart() {
        
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }
    
    /* Parameterized constructor. Sets all private members to the passed parameters and 
    allocate memory for inputed number of bars.*/
    BarChart(int n) {
        
        bars = new Bar[n];
        capacity = n;
        size = 0;
        frame = "";
        
    }

    /* Called automatically by C++ to create an BarChart that contains
    a copy of an existing BarChart.  Example: this occurs when passing
    BarChart as a parameter by value.*/
    BarChart(const BarChart& other) {
        
        this->bars = other.bars;
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;
        
        for(int i = 0; i < other.size; i++){
            this->bars[i] = other.bars[i];
        }
    }
    
    /*Equal operator overload. Checks if two BarChart objects are the same and returns
    the BarChart objects if ths is true.*/
    BarChart& operator=(const BarChart& other) {

        if(this == &other){
            return *this;
        }

        delete [] bars;

        
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame;

        for (int i = 0; i < other.size; ++i){
            this->bars[i] = other.bars[i];
            }
        return *this;
    }

    /*Frees memory and resets all private member variables to default values.*/

    void clear() {

        delete [] bars;
        bars = nullptr;
        capacity = 0;
        size = 0;
        frame = "";
    }
    
    /* Destructor of BarChart Class.
    Called automatically by C++ to free the memory associated by the BarChart.*/
    virtual ~BarChart() {

       if(bars != nullptr){
        delete[] bars;
       }
        
    }
    
    /* Sets strigng frame to inpuetd value. */
    void setFrame(string frame) {
        this->frame = frame;
    }
    
    /* Getter for string frame. Returns the frame of the BarChart object.*/
    string getFrame() {
        return frame; 
    }

    /* Getter for int capacity. Returns the capacity of the BarChart object.*/
    int getCapacity(){
        return capacity;
    }

    /* Getter for int size. Returns the size (number of bars) of the 
    BarChart object.*/
    //
    int getSize() {
        
        return size;  
    }

    /* Adds a Bar to the BarChart. Returns true if successful. 
    Returns false if there is not room */

    bool addBar(string name, int value, string category) {
        
        // TO DO:  Write this function.
        if(size < capacity && value > -1){
            Bar newBar = Bar(name, value, category);
            bars[size] = newBar;
            size++;
            return true;
        }
        return false; 
    }    
    
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        if(i < 0 || i >= size){
            throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i]; 
    }
    
    
    /* Used for printing the BarChart object.
    Recommended for debugging purposes.  output is any stream (cout,
    file stream, or string stream).*/
    void dump(ostream &output) {

        sort(bars, bars+size, [](Bar &i, Bar &j) -> bool{return i.getValue() < j.getValue();});
        //sorts the bars in increasing order
        output << "frame: " << getFrame() << endl;
        
       for(int i = getSize()-1; i >= 0; --i){ //prints the bar in decreasing order
            output << bars[i].getName() << " ";
            output << bars[i].getValue() << " ";
            output << bars[i].getCategory() << endl;
        }
    }
    
    /*Used for printing out the bar.
    output is any stream (cout, file stream, string stream)
    colorMap maps category -> color
    top is number of bars you'd like plotted on each frame (top 10? top 12?)*/
    void graph(ostream &output, map<string, string> &colorMap, int top) {
        int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
        sort(bars, bars+size, [](Bar &i, Bar &j) -> bool{return i.getValue() > j.getValue();});
        //sorts the bar in decrasing order
        string color = WHITE; //sets default color to WHITE (since i use dark theme)
        int maxValue = bars[0].getValue();
        string barstr = "";
        for (int i = 0; i < size; i++){
            if (i == top){
                break;
            }

            Bar currentBar = bars[i];
            map<string,string>::iterator colorIterator = colorMap.find(currentBar.getCategory());
            if (colorIterator != colorMap.end()){ //if category exists
                color = colorIterator->second;
            }
            int currentLen = currentBar.getValue() * lenMax / maxValue; // sets new length for the next box
            for (int i = 0; i <= currentLen; i++) {
                barstr += BOX;
                
            }
            output << color << barstr << " " <<  bars[i].getName() << " " << bars[i].getValue() << endl;
            barstr = "";
            color = WHITE; // resets back to default color for the next bar
        }
        
    }
    
};

