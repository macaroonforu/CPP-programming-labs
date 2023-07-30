//
//  Shape.cpp
//  lab3


#include "Shape.h"
#include <iostream> 

// Build a Shape object with its properties (Constructor)
    Shape::Shape(string n, string t, int x_loc, int x_sz, int y_loc, int y_sz){
        name = n; 
        type = t; 
        x_location = x_loc; 
        y_location = y_loc; 
        x_size = x_sz; 
        y_size = y_sz; 
        rotation = 0; 
    }

// Accessors
    string Shape::getType(){// Returns the type 
        return type; 
    }     
    string Shape::getName(){// Returns the name of the shape
        return name; 
    }             
    int Shape::getXlocation(){// Returns location of the shape on the x-axis
        return x_location; 
    }          
    int Shape::getYlocation(){// Returns location of the shape on the y-axis
        return y_location; 
    }        
    int Shape::getXsize(){// Returns the size of the shape in the x-dimension
        return x_size; 
    }               
    int Shape::getYsize(){// Returns the size of the shape in the y-dimension
        return y_size; 
    }     

    // Mutators
    void Shape::setType(string t){ // Sets the type (see globals.h)No error checking done inside the method. The calling program must ensure the type is correct
         type = t;                           
    }             
    void Shape::setName(string n){       // Sets the name of the shape
        name = n; 
    } 
    void Shape::setXlocation(int x_loc){ // Sets location of the shape on the x-axis
        x_location = x_loc; 
    }
    void Shape::setYlocation(int y_loc){ // Sets location of the shape on the y-axis
        y_location = y_loc; 
    }
    void Shape::setXsize(int x_sz){     // Sets size of the shape in the x-dimension
        x_size= x_sz; 
    }
    void Shape::setYsize(int y_sz){      // Sets size of the shape in the y-dimension       
        y_size = y_sz; 
    }  
    void Shape::setRotate(int angle){
        rotation = angle; 
    }
  
    // Utility methods
    void Shape::draw(){   // Draws a shape; for this assignment it only prints the information of the shape
        cout<< name<<": " << type << " " << x_location << " " << y_location  << " " << x_size << " " << y_size<<endl; 
    }




