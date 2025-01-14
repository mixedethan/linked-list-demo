#ifndef PROJECT1LINKEDLIST_LINKEDLIST_H
#define PROJECT1LINKEDLIST_LINKEDLIST_H

#include "iostream"
#include <string>
#include "vector"
using namespace std;

template <typename T>
class LinkedList{

public:
    struct Node{ //Nested class for nodes
        T data;
        Node* next;
        Node* prev;
    };
    LinkedList(){  //Default Constructor
        numOfNodes = 0;
        head = nullptr;
        tail = nullptr;
    }


    LinkedList(const LinkedList<T>& list){
        head = nullptr;
        tail = nullptr;
        numOfNodes = 0;

        for (unsigned int i = 0; i < list.NodeCount(); i++)
            AddTail(list.GetNode(i) -> data);
    }
    ~LinkedList(){ //Destructor
        Clear();
    }


    //Behaviors
    void PrintForward() const{
        Node* currentNode = head;

        while(currentNode != nullptr){
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }
    void PrintReverse() const{
        Node* currentNode = tail;

        while(currentNode != nullptr){
            cout << currentNode->data << endl;
            currentNode = currentNode->prev;
        }
    }
    void PrintForwardRecursive(const Node* node) const{
        if (node == NULL){
            return;
        }
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
    void PrintReverseRecursive(const Node* node) const{
        if (node == NULL){
            return;
        }
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }

    //Accessors
    unsigned int NodeCount() const{
        return numOfNodes;
    }
    void FindAll(vector<Node*>& outData, const T& value) const
    {
        Node* searchNode = head;

        while (searchNode!= NULL)
        {
            if (searchNode->data == value)
            {
                outData.push_back(searchNode);
            }

            searchNode = searchNode->next;
        }
    }
    const Node* Find(const T& data) const{
        Node* tempNode = head;
        while (tempNode != NULL)
        {
            if (tempNode->data == data)
            {
                return tempNode;
            }
            else
            {
                tempNode = tempNode->next;
            }
        }
        tempNode = nullptr;
        return tempNode;
    }
    Node* Find(const T& data)
    {
        Node* checkNode = head;

        while (checkNode != NULL)
        {
            if (checkNode->data == data)
            {
                return checkNode;
            }
            else
            {
                checkNode = checkNode->next;
            }
        }

        checkNode = nullptr;
        return checkNode;
    }
    const Node* GetNode(unsigned int index) const
    {
        if (index >= numOfNodes)
        {
            throw out_of_range("Index out of range");
        }
        else
        {
            Node* locate = head;
            unsigned int indexCount = 0;

            while (indexCount != index)
            {
                locate = locate->next;
                indexCount++;
            }

            return locate;
        }

    }
    Node* GetNode(unsigned int index)
    {
        if (index >= numOfNodes)
        {
            throw out_of_range("Index out of bounds");
        }
        else
        {
            Node* locate = head;
            unsigned int indexCount = 0;

            while (indexCount != index)
            {
                locate = locate->next;
                indexCount++;
            }
            return locate;
        }
    }
    Node* Head(){
        return head;
    } //Returns head
    const Node* Head() const{
        return head;};
    Node* Tail(){
        return tail;
    } //Returns tail
    const Node* Tail() const{
        return tail;
    }

    //Insertion
    void AddHead(const T& data){
        Node* newPtr = new Node();  // create a new node
        newPtr->data = data; // assign in with passed in data
        newPtr->next = nullptr;
        newPtr->prev = nullptr; // the new head will have no prev node

        if (head != NULL)
        {
            head->prev = newPtr; // newHead becomes prev to head
            if (numOfNodes == 2) // this is head count before accounting for newHead
            {
                tail->prev = head;
            }
            newPtr->next = head; // head becomes next to newHead
            head = newPtr; // newHead becomes head
        }
        else // if LinkedList doesn't exist yet
        {
            head = newPtr; // newHead becomes head
            tail = newPtr;
            head->prev = nullptr;
            head->next = nullptr;
        }
        numOfNodes++;
    }
    void AddTail(const T& data){
        Node* tempNode = new Node(); //Temporary Node to store parameter data
        tempNode->data = data;
        tempNode->next = nullptr;
        tempNode->prev = nullptr;

        if(tail == nullptr){
            head = tempNode;
            tail = tempNode;
            tail->next = nullptr;
            tail->prev = nullptr;
        }
        else{
            tail->next = tempNode;
            if(numOfNodes == 1) {
                head->next = tempNode;
            }
            tempNode->prev = tail;
            tempNode->next = nullptr;
            tail = tempNode;
            tempNode = nullptr;
        }
        numOfNodes++;
    }
    void AddNodesHead(const T* data, unsigned int count){
        int index = (int)count - 1;

        for(int i = index; i>= 0; i--){
            AddHead(data[i]);
        }
    }
    void AddNodesTail(const T* data, unsigned int count){
        for (unsigned int i = 0; i < count; i++)
        {
            AddTail(data[i]);
        }
    }
    void Clear(){
        Node* tempHead = Head();
        Node* tempPointer;
        while(tempHead != nullptr){
            tempPointer = tempHead->next;
            delete tempHead;
            tempHead = tempPointer;
        }
        numOfNodes = 0;
        head = nullptr;
        tail = nullptr;
    }

    void InsertAfter(Node* node, const T& data){
            // Create a new Node with data
            Node * tempNode = new Node();
            tempNode->data = data;
            tempNode->prev = node;
            tempNode->next = node->next;
            node->next->prev = tempNode;
            node->next = tempNode;
            numOfNodes++;
        }
    void InsertBefore(Node* node, const T& data){
            // Create a new Node with data
            Node* tempNode = new Node();
            tempNode->data = data;
            tempNode->next = node;
            tempNode->prev = node->prev;
            node->prev->next = tempNode;
            node->prev = tempNode;
            numOfNodes++;
        }
    void InsertAt(const T& data, unsigned int index)
    {
        // if index is out of range
        if (index > numOfNodes)
        {
            throw out_of_range("Index out of range");
        }
        else
        {
            if (index == numOfNodes) 
            {
                AddTail(data);
            }
            else {                  
                Node* transferNode = new Node(); 
                transferNode->data = data; 

                Node* currentNode = GetNode(index); 

                if (currentNode == head) 
                {
                    transferNode->prev = nullptr;
                    transferNode->next = currentNode;
                    currentNode->prev = transferNode;
                    head = transferNode; 

                    numOfNodes++;
                }
                else if (currentNode == tail) 
                {
                    transferNode->prev = currentNode;
                    transferNode->next = nullptr;
                    currentNode->next = transferNode; 
                    tail = transferNode; 

                    numOfNodes++;
                }
                else
                {
                    Node* currentPrev = currentNode->prev;
                    
                    transferNode->next = currentNode; 
                    currentNode->prev = transferNode; 
                    transferNode->prev = currentPrev; 
                    currentPrev->next = transferNode; 

                    numOfNodes++;
                }
            }

        }
    }

    //Removal

    bool RemoveHead(){
        if (head == NULL){
            return false;
        }
        else{
            if (numOfNodes == 1)
            {
                Clear();
            }
            else{
                Node* newHeadPtr = head->next;
                newHeadPtr->prev = nullptr;
                delete head;
                head = newHeadPtr;
                numOfNodes--;
            }
            return true;
        }
    }
    bool RemoveTail(){
        if (tail == NULL){
            return false;
        }
        else{
            if (numOfNodes == 1)
            {
                Clear();
            }
            else{
                Node* newTailPtr = tail->prev;
                newTailPtr->next = nullptr;
                delete tail;
                tail = newTailPtr;
                numOfNodes--;
            }

            return true;
        }
    }
    unsigned int Remove(const T& data){
        unsigned int numRemoved = 0;
        if (numOfNodes == 0) // return 0 if no nodes in list
        {
            return numRemoved;
        }
        else
        {
            Node* currentNode = head;
            unsigned int index = 0;

            while (currentNode != nullptr)
            {
                if (currentNode->data == data)
                {
                    RemoveAt(index);
                    numRemoved++;
                    index = 0;
                    currentNode = head;
                }
                else
                {
                    index++;
                    currentNode = currentNode->next;
                }

            }
        }

        return numRemoved;
    }
    bool RemoveAt(unsigned int index){
        if (index >= numOfNodes) // can't remove nonexistent index
        {
            return false;
        }
        else
        {
            if (index == 0){
                RemoveHead();
                return true;
            }
            else if (index == numOfNodes - 1){
                RemoveTail();
                return true;
            }
            else if (index == numOfNodes - 1 && numOfNodes == 1)
            {
                Clear();
                return true;
            }
            else
            {
                unsigned int searchCount = 0;
                Node* searchNode = head;

                while (searchCount != index)
                {
                    searchNode = searchNode->next;
                    searchCount++;
                }
                Node* prevNode = searchNode->prev;
                Node* nextNode = searchNode->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                delete searchNode;
                numOfNodes--;

                return true;
            }

        }
    }

    //Operators
    const T& operator[](unsigned int index) const{
        if (index >= numOfNodes)
            {
            throw out_of_range("Index out of range");
        }
        else
            {
            unsigned int searchIndex = 0;
            Node* searchNode = head;

            while (searchIndex != index)
            {
                searchNode = searchNode->next;
                searchIndex++;
            }
            return searchNode->data; \
        }
    }
    T& operator[](unsigned int index){
        if (index >= numOfNodes)
        {
            throw out_of_range("Index out of range");
        }
        else
        {
            unsigned int searchIndex = 0;
            Node* searchNode = head;

            while (searchIndex != index)
            {
                searchNode = searchNode->next;
                searchIndex++;
            }
            return searchNode->data;
        }
    }
    bool operator==(const LinkedList<T>& rhs) const{
        if (numOfNodes != rhs.NodeCount())
        {
            return false;
        }
        else
        {
            for (unsigned int i = 0; i < numOfNodes; i++)
            {
                if (GetNode(i)->data != rhs.GetNode(i)->data)
                    return false;
                else
                    continue;
            }
        }
        return true;
    }
    LinkedList<T>& operator=(const LinkedList<T>& rhs){
        numOfNodes = 0;
        for (unsigned int i = 0; i < rhs.numOfNodes; i++)
        {
            AddTail(rhs.GetNode(i)->data);
        }
        return *this;
    };

private:
    unsigned int numOfNodes;
    Node* head;
    Node* tail;
};
#endif