//
//  ShapeNode.h
//  Lab4


#ifndef ShapeNode_h
#define ShapeNode_h

#include "Shape.h"

// This class represents a node in the ShapeList linked list
// Each ShapeNode has two members: a poiter to a Shape object
// and a pointer to the next node in the list

class ShapeNode {
private:
    Shape* myShape;
    ShapeNode* next;
public:
    ShapeNode();                   // sets myShape and next to nullptr
    ~ShapeNode();                  // deletes the shape pointed to by myShape
    Shape* getShape() const;       // returns myShape
    void setShape(Shape* ptr);     // sets myShape to ptr
    ShapeNode* getNext() const;    // returns next
    void setNext(ShapeNode* ptr);  // sets next to ptr
    void print() const;            // prints the ShapeNode
};

#endif /* ShapeNode_h */
