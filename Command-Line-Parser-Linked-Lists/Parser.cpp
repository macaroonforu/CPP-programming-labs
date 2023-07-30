//
//  parser.cpp
//  Lab4



#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

bool nameValid(string name);
bool nameNotInDB(string name, GroupList* glist);
ShapeNode* shapeNodeSearcher(string name, GroupList* glist); 
GroupNode* groupNodeSearcherGroupName(string name, GroupList* glist); 
GroupNode* groupNodeSearcherShapeName(string name, GroupList* glist); 


int main() {
    // Create the groups list
    gList = new GroupList();
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if(command=="shape"){
            string name, type; 
            int x_loc, y_loc, x_sz, y_sz; 
            lineStream>>name; 

            if(nameValid(name)){
                if(nameNotInDB(name, gList)){
                    lineStream>>type; 
                    lineStream>>x_loc; 
                    lineStream>>y_loc; 
                    lineStream>>x_sz; 
                    lineStream>>y_sz; 
                    Shape* newShape = new Shape(name, type, x_loc, x_sz, y_loc, y_sz); //creating the new shape
                    ShapeNode* newShapeNode = new ShapeNode(); //creating the new shape node 
                    newShapeNode->setShape(newShape); //setting the shape contained within the ShapeNode to the one we just created 
                    poolGroup->getShapeList()->insert(newShapeNode); //this is the shape list contained within pool 
                    newShape->draw();
                }
                else{
                    cout<<"error: name "<<name<<" exists"<<endl; 
                    lineStream.clear(); 
                }
            }
            else{
                lineStream.clear(); 
            }
        }

        else if(command=="group"){
            string name;
            lineStream>>name; 
            if(nameValid(name)){
                if(nameNotInDB(name, gList)){
                    GroupNode* newGroupNode = new GroupNode(name); //Create the new Group Node 
                    gList->insert(newGroupNode); //Insert it at the end of the Group List 
                    cout<<name<<": group"<<endl; 
                }
                else{
                    cout<<"error: name "<<name<<" exists"<<endl; 
                    lineStream.clear(); 
                }    
            }
            else{
                lineStream.clear(); 
            }
        }

        else if(command =="draw"){
            cout<<"drawing: "<<endl; 
            gList->print(); 
        }

        else if(command=="move"){
            string shapeName, groupName; 
            lineStream>>shapeName; 
            lineStream>>groupName; 
            if(nameValid(shapeName)){
                if(nameValid(groupName)){
                    if(!(nameNotInDB(shapeName, gList))){ //if the shape name IS in the database, check if group name in DB
                        //cout<<"Shape " <<shapeName<< " found in database"<<endl; 
                        if(nameNotInDB(groupName, gList)){
                            cout<<"error: group "<<groupName<<" not found"<<endl; 
                            lineStream.clear(); 
                        }
                        else{ //at this point, both shape name and group name have been found in the database. 
                            GroupNode* groupMovingFrom = groupNodeSearcherShapeName(shapeName, gList);
                            GroupNode* groupMovingTo = groupNodeSearcherGroupName(groupName, gList);
                            ShapeNode* removedNode = groupMovingFrom->getShapeList()->remove(shapeName);
                            groupMovingTo->getShapeList()->insert(removedNode); 
                            cout<<"moved "<<shapeName<<" to "<<groupName<<endl;
                            lineStream.clear();  
                        }
                    }
                    else{ 
                        //cout<<"entered this loop"<<endl; 
                        cout<<"error: shape "<<shapeName<<" not found"<<endl;
                        lineStream.clear();  
                    }
                }
                else{
                    lineStream.clear(); 
                }
            }
            else{
                lineStream.clear(); 
            }
        }

        else if(command=="delete"){
            string toDelete; 
            lineStream>>toDelete; 
            ShapeNode* shapeToDelete= shapeNodeSearcher(toDelete, gList); 
            if(nameValid(toDelete)){
                if(shapeToDelete==NULL){
                    GroupNode* groupToDelete = groupNodeSearcherGroupName(toDelete, gList); 
                    if(groupToDelete==NULL){
                        cout<<"error: shape "<<toDelete<<" not found"<<endl; 
                        lineStream.clear(); 
                    }
                    else{
                        //code to delete a group
                        GroupNode* groupToDelete = groupNodeSearcherGroupName(toDelete, gList); 
                        ShapeNode* p = groupToDelete->getShapeList()->getHead(); //access first node of shapelist from group we want to delete 
                        //while loop to insert all nodes into pool 
                        //cout<<"Group to delete: "<<endl; 
                        //groupToDelete->print(); 
                
                        while(p!=NULL){ //if this first node is not null, 
                            p = groupToDelete->getShapeList()->remove(p->getShape()->getName()); 
                            poolGroup->getShapeList()->insert(p); //insert this node into the end of pool 
                            p = groupToDelete->getShapeList()->getHead(); //traverse onto the next shapenode in the group's list 
                        }

                        //cout<<"pool group after insertion: "<<endl; 
                        //poolGroup->print(); 

                        //Code to delete the groupNode 
                        gList->remove(toDelete); //remove this groupNode from the glist
                        delete groupToDelete;  //deleete this group node 
                        groupToDelete = NULL; //set it to null just in case 
                        cout<<toDelete<<": deleted"<<endl; 
                    }
                }
                else{
                    //Code to delete a shape
                    GroupNode* groupContainingShape = groupNodeSearcherShapeName(toDelete, gList); 
                    ShapeNode* shapeToDelete =  shapeNodeSearcher(toDelete, gList); 
                    //cout<<"Group Containing shape's shape list before deleting: "<<endl; 
                    //groupContainingShape->getShapeList()->print(); 
                    groupContainingShape->getShapeList()->remove(toDelete); 
                    delete shapeToDelete;
                    //cout<<"Group containing shape's shape list after deleting"<<endl; 
                    //groupContainingShape->getShapeList()->print(); 
                    //poolGroup->getShapeList()->insert(shapeToDelete); 
                    cout<<toDelete<<": deleted"<<endl; 
                }

            }
            else{
                lineStream.clear(); 
            }
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
    }  // End input loop until EOF.
    return 0;
}

bool nameValid(string name){
    for (int i = 0; i < 6; i++){
        if (keyWordsList[i] == name){
            cout<<"error: invalid name"<<endl; 
            return false;
        }
    }
    for (int i = 0; i < 3; i++){
        if (shapeTypesList[i] == name){
            cout <<"error: invalid name"<< endl;
            return false;
        }
    }
    return true;
}

bool nameNotInDB(string name, GroupList* glist){
    GroupNode* p = glist->getHead();
    while(p!=NULL){
        if(p->getName()==name){ //MATCHING GROUP NODE NAME
            return false; 
        }
        else{ //TRAVERSE SHAPELIST ASSOCIATED WITH THAT GROUPNODE
            ShapeList* s = p->getShapeList(); 
            if(s!=NULL){
                if(s->find(name)!=NULL){ //!NULL MEANS MATCHING SHAPE NAME
                    return false; 
                }
            }
        }   
        p = p->getNext(); //GO ONTO NEXT GROUP NODE 
    } 
    return true; 
} 

ShapeNode* shapeNodeSearcher(string name, GroupList* glist){ //returns the shape node associated with that shape name 
    GroupNode*p = glist->getHead(); 
    while(p!=NULL){
        ShapeNode* s = p->getShapeList()->getHead(); 
        if(p->getShapeList()->find(name)!=NULL){
            s = p->getShapeList()->find(name); 
            //s->setNext(NULL); 
            return s; 
        }
        else{
            p = p->getNext(); 
        }
    }
    return NULL; 
}

//returns the groupnode associated with that shape name 
GroupNode* groupNodeSearcherShapeName(string name, GroupList* glist){
    GroupNode* p = glist->getHead(); 
    while(p!=NULL){ //p is initially pool 
        ShapeNode* s = p->getShapeList()->find(name); //pool's shapelist 
        if(s!=NULL){ 
            return p; 
        }
        else{
            p= p->getNext(); 
        }
    }
    return NULL; 
}

//returns the groupnode associated with that group name 
GroupNode* groupNodeSearcherGroupName(string name, GroupList* glist){ 
    GroupNode* p = glist->getHead(); 
    while(p!=NULL){
        if(p->getName()==name){
            return p; 
        }
        p = p->getNext(); 
    }
    return NULL; 
}
