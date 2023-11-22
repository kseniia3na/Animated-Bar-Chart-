/* 
    Project 3 - Animated Bar Chart (bar.h)

    Kseniia Nastahunina

    This class is base class for other in this project. It is used for creating and 
    comparing class objects in further implementation.

*/

#include <iostream>
#include <string>
#include "myrandom.h" // used in graders, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    string name;
    int value;
    string category;

 public:
 
    /*Default constructr. Sets all privat members to its default values.*/
    Bar() {
        name = "";
        value = 0;
        category = "";
        
    };

    /* Parameterized constructor. Sets all private members to the passed parameters.*/
    Bar(string name, int value, string category) {
        
        this->name = name;
        this->value = value;
        this->category = category;
        
    }

    /* Destructor.*/
    virtual ~Bar() {
        
    }

    /* Getter for privat member name. Returns string name.*/
	string getName() {
        return name;  
	}

    /* Getter for privat member value. Returns int value.*/
	int getValue() {
        return value;
	}

    /* Getter for privat member category. Returns string category.*/
	string getCategory() {
        return category;
	}

	/*Operator overload function. Compares two bar objects. Returns true if
    the first bar object is less than the second.*/
	bool operator<(const Bar &other) const {
        if(this->value < other.value){
            return true;
            }
        return false;
	}

    /*Operator overload function. Compares two bar objects. Returns true if
    the first bar object is less or equal than the second.*/
	bool operator<=(const Bar &other) const {
        if(this->value <= other.value){
            return true;
            }
        return false;
	}

    /*Operator overload function. Compares two bar objects. Returns true if
    the first bar object is greater than the second.*/
	bool operator>(const Bar &other) const {
        if(this->value > other.value){
            return true;
            }
        return false;
	}

    /*Operator overload function. Compares two bar objects. Returns true if
    the first bar object is greater or equal than the second.*/
	bool operator>=(const Bar &other) const {
        if(this->value >= other.value){
            return true;
            }
        return false;
	}
};

