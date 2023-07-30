//
//  GroupList.cpp
//  Lab4


// sets head to nullptr
    GroupList::GroupList(){
        head = NULL; 
    } 

 // deletes all list nodes, including all the ShapeList attached to each GroupNode
     GroupList::~GroupList(){
        GroupNode* p; 
        while(head!=NULL){
            p= head; 
            head = p->getNext(); 
            delete p; 
        }
    }    

// returns the head pointer                       
    GroupNode*  GroupList::getHead() const{
        return head; 
    } 

// sets the head pointer to ptr
    void  GroupList::setHead(GroupNode* ptr){
        head = ptr; 
    }    

// inserts the node pointed to by s at the end of the list
    void  GroupList::insert(GroupNode* s){
        GroupNode* cur = head; 
        if(head==NULL && s!= NULL){
            head = s; 
        }
        else{
            while(cur->getNext()!=NULL && s!= NULL){
                cur = cur->getNext(); 
            }
            s->setNext(cur->getNext()); 
            cur->setNext(s);
        }
    }  

// removes the group with the name "name" from the list and returns a pointer to the removed GroupNode returns nullptr if name is not found on list
    GroupNode*  GroupList::remove(string name){
        if(head->getName()==name){ //case that first node matches name 
            GroupNode* removedNode = head; //remember the first node as we need to return it 
            head = head->getNext();  
            return removedNode; 
        }
        GroupNode* n = head; 
        while(n->getNext()!=NULL && n->getNext()->getName()!= name){
            n = n->getNext(); 
        } //After this while loop, we are either right before the node to be deleted or the last node, meaning name was not in list 
        if(n->getNext()!=NULL){ //if not last node... 
            GroupNode* temp = n->getNext(); //temp is the node to be removed 
            n->setNext(temp->getNext()); //make n (node before deleted node) 's next the deleted node's next, effectively skipping over it. 
            return temp; 
        }
        return NULL; 
    }  
                                      
// prints the list, one GroupNode at a time                             
    void  GroupList::print() const{
        GroupNode* n = head; 
        while(n!=NULL){
            n->print();  
            n = n->getNext(); 
        }
    }        



