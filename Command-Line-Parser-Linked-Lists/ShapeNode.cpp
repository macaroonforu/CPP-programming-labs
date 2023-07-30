//
//  ShapeNode.cpp
//  Lab4


#include "ShapeNode.h"
#include "Shape.h"

// sets myShape and next to nullptr
    ShapeNode::ShapeNode(){
        myShape = NULL; 
        next = NULL;  
    }     

// deletes the shape pointed to by myShape and sets everything 
    ShapeNode::~ShapeNode(){
        delete myShape; 
        myShape = NULL; 
        next = NULL; 
    }

// returns myShape
    Shape* ShapeNode::getShape() const{
        return myShape; 
    }

// sets myShape to ptr
    void ShapeNode::setShape(Shape* ptr){
        myShape = ptr; 
    }

 // returns next
    ShapeNode* ShapeNode::getNext() const{
        return next; 
    }

// sets next to ptr
    void ShapeNode::setNext(ShapeNode* ptr){
        next = ptr; 
    }

// prints the ShapeNode
    void ShapeNode::print() const{
        myShape->draw(); 
    }         

