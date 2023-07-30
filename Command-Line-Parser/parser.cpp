//  parser.cpp
//  lab3


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape **shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool typeValid(string type);
bool locSizeValid(string locString, int& loc);
bool nameValid(string name);
bool coordinatesValid(string line, int x_size, int y_size);
bool angleValid(string angleString, int& angle);
bool nameValidRotateMove(string name); 
Shape *shapeSearcher(string name);

int main(){
    shapesArray = NULL; 
    string line;
    string command;
    cout << "> ";       // Prompt for input
    getline(cin, line); // Get a line from standard input
    while (!cin.eof()){
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream(line);
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if (command == "maxShapes"){
            string xtraInputCheck, maxShapesString; 
            lineStream>>maxShapesString; 
            if(lineStream.fail()){
                cout<<"Error: too few arguments"<<endl; 
                lineStream.clear(); 
            }
            else{
                if(locSizeValid(maxShapesString, max_shapes)){
                    lineStream>>xtraInputCheck; 
                    if(lineStream.fail()){
                    if (shapesArray!=NULL){ // deleting previous array if one already existed
                        for (int i = 0; i < shapeCount; i++){
                            if (shapesArray[i] != NULL){
                                delete shapesArray[i];
                                shapesArray[i] = NULL;
                            }
                        }
                        delete[] shapesArray;
                        shapesArray = NULL;
                        shapeCount = 0;
                        }
                        shapesArray = new Shape *[max_shapes]; 
                        for (int i = 0; i < max_shapes; i++){ // initializing all pointers to NULL
                            shapesArray[i] = NULL;
                        }
                        std::cout << "New database: max shapes is " << max_shapes << endl;
                    } 
                    else{
                        cout<<"Error: too many arguments"<<endl; 
                        lineStream.clear(); 
                    }
                }
            }
        }
        else if (command == "create"){
            string name, type, x_locString, y_locString, x_sizeString, y_sizeString, xtraInputCheck;
            int x_loc, y_loc, x_size, y_size;
            lineStream >> name;
            if (lineStream.fail()){
                if (lineStream.eof()){
                    cout << "Error: too few arguments" << endl;
                    lineStream.clear();
                }
            }
            else{
                if (nameValid(name)){
                    lineStream >> type;
                    if (lineStream.fail()){
                        cout << "Error: too few arguments" << endl;
                        lineStream.clear();
                    }
                    else{
                        if (typeValid(type)){
                            lineStream >> x_locString;
                            if (lineStream.fail()){
                                if (lineStream.eof()){
                                    cout << "Error: too few arguments" << endl;
                                    lineStream.clear();
                                }
                            }
                            else{
                                if (locSizeValid(x_locString, x_loc)){
                                    lineStream >> y_locString;
                                    if (lineStream.fail()){
                                        cout << "Error: too few arguments" << endl;
                                        lineStream.clear();
                                    }
                                    else{
                                        if (locSizeValid(y_locString, y_loc)){
                                            lineStream >> x_sizeString;
                                            if (lineStream.fail()){
                                                cout << "Error: too few arguments" << endl;
                                                lineStream.clear();
                                            }
                                            else{
                                                if (locSizeValid(x_sizeString, x_size)){
                                                    lineStream >> y_sizeString;
                                                    if (lineStream.fail()){
                                                        cout << "Error: too few arguments" << endl;
                                                        lineStream.clear();
                                                    }
                                                    else{
                                                        if (locSizeValid(y_sizeString, y_size)){
                                                            if (coordinatesValid(type, x_size, y_size)){
                                                                lineStream >> xtraInputCheck;
                                                                if (!lineStream.fail()){
                                                                    cout << "Error: too many arguments" << endl;
                                                                    lineStream.clear();
                                                                }
                                                                else{
                                                                    if (shapeCount < max_shapes){
                                                                        // cout<<name<<endl<<type<<endl<<x_loc<<endl<<x_size<<endl<<y_size<<endl<<y_loc<<endl<<endl;
                                                                        shapesArray[shapeCount] = new Shape(name, type, x_loc, x_size, y_loc, y_size);
                                                                        shapeCount++;
                                                                        // cout<<"Shape count: "<<shapeCount<<endl;
                                                                        cout << "Created " << name << ": " << type << " " << x_loc << " " << y_loc << " " << x_size << " " << y_size << endl;
                                                                        // cout<<"Shape count is now "<<shapeCount<<endl;
                                                                    }
                                                                    else{
                                                                        cout << "Error: shape array is full" << endl;
                                                                        lineStream.clear();
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (command == "move"){
            string name, xlocString, ylocString, type;
            int x_loc, y_loc;
            lineStream >> name;
            string xtraInputCheck;
            if (lineStream.fail()){
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
            }
            else{
                if(nameValidRotateMove(name)){
                    if (shapeSearcher(name) == NULL){
                        cout << "Error: shape " << name << " "<< "not found" << endl;
                        lineStream.clear();
                    }
                    else{
                        lineStream >> xlocString;
                        if (lineStream.fail()){
                            cout << "Error: too few arguments" << endl;
                            lineStream.clear();
                        }
                        else{
                            if (locSizeValid(xlocString, x_loc)){
                                lineStream >> ylocString;
                                if (lineStream.fail()){
                                    cout << "Error: too few arguments" << endl;
                                    lineStream.clear();
                                }
                                else{
                                    if (locSizeValid(ylocString, y_loc)){
                                        lineStream>>xtraInputCheck; 
                                        if(lineStream.fail()){
                                            type = shapeSearcher(name)->getType();
                                            shapeSearcher(name)->setXlocation(x_loc);
                                            shapeSearcher(name)->setYlocation(y_loc);
                                            cout << "Moved " << name << " "<< "to " << x_loc << " " << y_loc << endl;
                                        }
                                        else{
                                            cout << "Error: too many arguments" << endl;
                                            lineStream.clear();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    lineStream.clear(); 
                }
            }
        }
        else if (command == "rotate"){
            string name, angleString, xtraInputCheck;
            int angle;
            lineStream >> name;
            if (lineStream.fail()){
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
            }
            else{
                if(nameValidRotateMove(name)){
                    if (shapeSearcher(name) == NULL){
                    cout << "Error: shape " << name << " "<< "not found" << endl;
                    lineStream.clear();
                    }
                    else{
                        lineStream >> angleString;
                        if(lineStream.fail()){
                            cout<<"Error: too few arguments"<<endl; 
                        }
                        else{
                            if (angleValid(angleString, angle)){
                                lineStream >> xtraInputCheck;
                                if (!lineStream.fail()){
                                    cout << "Error: too many arguments" << endl;
                                    lineStream.clear();
                                }
                                else{
                                    shapeSearcher(name)->setRotate(angle);
                                    cout << "Rotated " << name << " " << "by " << angle << " degrees" << endl;
                                }
                            }
                        }
                    }
                }
                else{
                    lineStream.clear(); 
                }
            }
        }
        else if (command == "draw"){
            string name, XtraInput;
            lineStream >> name;
            if (lineStream.fail()){
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
            }
            else{
                if (name == "all"){
                    lineStream >> XtraInput;
                    if (!lineStream.fail()){
                        cout << "Error: too many arguments" << endl;
                        lineStream.clear();
                    }
                    else{
                        cout << "Drew all shapes" << endl;
                        for (int i = 0; i < shapeCount; i++){
                            if (shapesArray[i] != NULL){
                                shapesArray[i]->draw();
                            }
                        }
                    }
                }
                else{
                    if(nameValidRotateMove(name)){
                        if (shapeSearcher(name) == NULL){
                            cout << "Error: shape " << name << " "<< "not found" << endl;
                            lineStream.clear();
                        }
                        else{
                            lineStream >> XtraInput;
                            if (!lineStream.fail()){
                                cout << "Error: too many arguments" << endl;
                                lineStream.clear();
                            }
                            else{
                                cout << "Drew ";
                                shapeSearcher(name)->draw();
                            }
                        }
                    }
                }
            }
        }
        else if (command == "delete"){
            string name, Xtrainput;
            lineStream >> name;
            if (lineStream.fail()){
                cout << "Error: too few arguments" << endl;
                lineStream.clear();
            }
            else{
                if (name == "all"){
                    lineStream >> Xtrainput;
                    if (!lineStream.fail()){
                        cout << "Error: too many arguments" << endl;
                        lineStream.clear();
                    }
                    else{
                        for (int i = 0; i < shapeCount; i++){
                            if (shapesArray[i] != NULL){
                                delete shapesArray[i];
                                shapesArray[i] = NULL;
                            }
                        }
                        shapeCount = 0;
                        cout << "Deleted: all shapes" << endl;
                    }
                }
                else{
                    if(nameValidRotateMove(name)){
                        if (shapeSearcher(name) == NULL){
                            cout << "Error: shape " << name << " "<< "not found" << endl;
                            lineStream.clear();
                        }
                        else{
                            lineStream >> Xtrainput;
                            if (!lineStream.fail()){
                                cout << "Error: too many arguments" << endl;
                                lineStream.clear();
                            }
                            else{
                                int position = 0;
                                for (int i = 0; i < shapeCount; i++){
                                    if (shapesArray[i] != NULL){
                                        if (shapesArray[i]->getName()==name){
                                            position = i;
                                            break;
                                        }
                                    }
                                }
                                delete shapesArray[position];
                                shapesArray[position] = NULL;
                                cout << "Deleted shape " << name << endl;
                            }
                        }
                    }
                }
            }
        }
        else{
            cout << "Error: invalid command" << endl;
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line);
    } // End input loop until EOF.
    return 0;
}
// CHECKS IF TYPE IS VALID
bool typeValid(string type){
    if (type == "circle" || type == "rectangle" || type == "triangle" || type == "ellipse"){
        return true;
    }
    else{
        cout << "Error: invalid shape type" << endl;
        return false;
    }
}
// CHECKS IF THE LOC OR SIZE IS VALID
bool locSizeValid(string locString, int &loc){
    for(int i=0; i<locString.length(); i++){
        if(locString[i]<'0'||locString[i]>'9'){
            if(locString[0]!='-' && locString[0]!='+'){
                cout<<"Error: invalid argument"<<endl; 
                return false; 
            }
        }
    }
    int tester; 
    stringstream locArgument(locString);
    locArgument>>tester; 
    if(tester<0){
        cout<<"Error: invalid value"<<endl; 
        return false; 
    } 
    loc=tester; 
    return true;  
}
// CHECKS IF THE NAME IS VALID
bool nameValid(string name){
    for (int i = 0; i < 7; i++){
        if (keyWordsList[i] == name){
            cout << "Error: invalid shape name" << endl;
            return false;
        }
    }
    for (int i = 0; i < 4; i++){
        if (shapeTypesList[i] == name){
            cout << "Error: invalid shape name" << endl;
            return false;
        }
    }
    for (int i = 0; i < shapeCount; i++){
        if (shapesArray[i] != NULL){
            if ((shapesArray[i]->getName()) == name){
                cout << "Error: shape "<<name<<" exists" << endl;
                return false;
            }
        }
    }
    return true;
}
//Check if name is a reserved keyword when employed in functions that use a name but not create 
bool nameValidRotateMove(string name){
    for (int i = 0; i < 7; i++){ 
        if (keyWordsList[i] == name){
            cout << "Error: invalid shape name" << endl;
            return false;
        }
    }
    for (int i = 0; i < 4; i++){
        if (shapeTypesList[i] == name){
            cout << "Error: invalid shape name" << endl;
            return false;
        }
    }
    return true; 
}
// CHECKSS IF THE COORDINATES ARE VALID
bool coordinatesValid(string type, int x_size, int y_size){
    if (type == "circle"){
        if (x_size == y_size){
            return true;
        }
        else{
            cout << "Error: invalid value" << endl;
            return false;
        }
    }
    return true;
}
// CHECKS IF THE ANGLE IS VALID
bool angleValid(string angleString, int &angle){
    for(int i=0; i<angleString.length(); i++){
        if(angleString[i]<'0'||angleString[i]>'9'){
            if(angleString[0]!='-'&& angleString[0]!='+'){
                    cout<<"Error: invalid argument"<<endl; 
                    return false; 
            }
        }
    }
    int tester; 
    stringstream angleArgument(angleString);
    angleArgument>>tester; 
    if(tester<0||tester>360){
        cout<<"Error: invalid value"<<endl; 
        return false; 
    } 
    angle=tester; 
    return true;  
}
// SEARCHES FOR A SHAPE BY NAME IN THE ARRAY AND RETURNS THE SHAPE
Shape *shapeSearcher(string name){
    for (int i = 0; i < shapeCount; i++){
        if (shapesArray[i] != NULL){ // only want function to check in a non-NULL entry
            if (shapesArray[i]->getName() == name){
                return shapesArray[i];
            }
        }
    }
    return NULL;
}
