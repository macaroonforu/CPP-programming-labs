//
//  ShapeList.cpp
//  Lab4

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below
#include "ShapeList.h"
#include "Shape.h"

// sets head to nullptr
    ShapeList::ShapeList(){
        head = NULL; 
    }

// deletes all list nodes starting with head plus associated Shapes
    ShapeList::~ShapeList(){
        ShapeNode* p; 
        while(head!=NULL){
            p=head; //set p as first item in list 
            head= p->getNext(); //set head as next item in list 
            delete p;  // shapeNode destructor deletes shape that p is pointing to, but then you have to also delete the node p itself 
        }
    }  

    //Think about the situation in which we may have a shapnode that points to nothing                    
    
// returns the head pointer
    ShapeNode* ShapeList::getHead() const{
        return head; 
    }

// sets the head pointer to ptr
    void ShapeList::setHead(ShapeNode* ptr){
        head = ptr; 
    }
    
// finds a shape node with the specified shape name, returns a pointer to the node if found, otherwise returns nullptr if the node is not found
    ShapeNode* ShapeList::find(string name) const{
        for(ShapeNode* cur = head; cur!=NULL; cur = cur->getNext()){
            if(cur->getShape()->getName()==name){
                return cur; 
            }
        }
        return NULL; 
    }

// inserts the node pointed to by s at the end of the list; s should never be nullptr
    void ShapeList::insert(ShapeNode* s){
        ShapeNode* cur = head; 
        ShapeNode* prev = NULL; 
        while(cur!=NULL){
            prev = cur; 
            cur = cur->getNext(); 
        } //After this while loop, cur is NULL and prev is the last node 
        s->setNext(cur); //will set the node we are inserting's next to NULL 
        if(prev==NULL){
            head = s;  
        }
        else{
            prev->setNext(s);
        }
    }

// removes the node with the shape called name, returns a pointer to the removed node or nullptr is a node with name does not exist
//Do we have to account for the cases of an empty list? 
    ShapeNode* ShapeList::remove(string name){
        ShapeNode* cur = head; 
        ShapeNode* prev = NULL;  
        while((cur!=NULL) && (cur->getShape()->getName()!= name)){
                prev = cur; 
                cur = cur->getNext(); 
        }
        if (cur!=NULL){
            if(prev==NULL){
                head = cur->getNext();
                return cur;  
            }
            else{ //doesn't cur still point to the next node in the group it used to belong to? 
                prev->setNext(cur->getNext()); 
                return cur; 
            }
        }
        return NULL; 
    }   
                                                                         
// prints the list
    void ShapeList::print() const{
        ShapeNode* n = head; 
        while(n!=NULL){
            n->print();  
            n = n->getNext(); 
        }
    }                 


