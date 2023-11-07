#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

struct Node 
{
    int data;
    Node* prev;
    Node* next;
    Node* evenNext;
    Node* evenPrev;
    Node* oddNext;
    Node* oddPrev;
};

class DoublyLinkedList 
{
private:
    Node* head;
    Node* evenHead;
    Node* oddHead;
public:
    DoublyLinkedList() : head(nullptr), evenHead(nullptr), oddHead(nullptr) {}

    ~DoublyLinkedList() 
    {
        Node* current = head;
        while (current != nullptr) 
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insert(int value) 
    {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        newNode->evenNext = nullptr;
        newNode->evenPrev = nullptr;
        newNode->oddNext = nullptr;
        newNode->oddPrev = nullptr;

        // Insert into the main list
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr && temp->data < value) {
                temp = temp->next;
            }

            if (temp == head && temp->data > value) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            else if (temp->next == nullptr && temp->data < value) {
                temp->next = newNode;
                newNode->prev = temp;
            }
            else {
                newNode->prev = temp->prev;
                newNode->next = temp;
                temp->prev->next = newNode;
                temp->prev = newNode;
            }
        
        }

        // Insert into even or odd list
        if (value % 2 == 0) 
        {
            insertNodeToList(newNode, evenHead, &Node::evenPrev, &Node::evenNext);
        }
        else 
        {
            insertNodeToList(newNode, oddHead, &Node::oddPrev, &Node::oddNext);
        }
    }

    void insertNodeToList(Node* newNode, Node*& listHead, Node* (Node::* prevPtr), Node* (Node::* nextPtr)) 
    {
        Node* temp = listHead;
        Node* prevNode = nullptr;

        while (temp != nullptr && temp->data < newNode->data) 
        {
            prevNode = temp;
            temp = temp->*nextPtr;
        }

        if (prevNode != nullptr) 
        {
            prevNode->*nextPtr = newNode;
        }
        else 
        {
            listHead = newNode;
        }

        newNode->*prevPtr = prevNode;
        newNode->*nextPtr = temp;

        if (temp != nullptr) 
        {
            temp->*prevPtr = newNode;
        }
    }
  






    void printList(char order) 
    {
        Node* temp;
        if (order == 'A') 
        {
            temp = head;
        }
        else if (order == 'D') 
        {
            temp = head;
            while (temp->next != nullptr) 
            {
                temp = temp->next;
            }
        }
        else 
        {
            std::cout << "Invalid order parameter!";
            return;
        }

        std::cout << "Doubly Linked List: ";
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            if (order == 'A') 
            {
                temp = temp->next;
            }
            else
            {
                temp = temp->prev;
            }
        }
        std::cout << std::endl;
    }

    void printEvenList()
    {
        Node* temp = evenHead;
        std::cout << "Even Numbers: ";
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            temp = temp->evenNext;
        }
        std::cout << std::endl;
    }

    void printOddList() 
    {
        Node* temp = oddHead;
        std::cout << "Odd Numbers: ";
        while (temp != nullptr) 
        {
            std::cout << temp->data << " ";
            temp = temp->oddNext;
        }
        std::cout << std::endl;
    }
};

int main() 
{
    std::ofstream outputFile("integer.dat");

    if (!outputFile) 
    {
        std::cerr << "Error: Unable to create or open the file." << std::endl;
        return 1;
    }

    std::srand(std::time(0));

  
    for (int i = 0; i < 10; ++i) 
    {
        int randomInt = std::rand() % 100 + 1;
        outputFile << randomInt << std::endl;
    }

    outputFile.close();

    std::ifstream inputFile("integer.dat");
    if (!inputFile) 
    {
        std::cerr << "Error: File not found or unable to open." << std::endl;
        return 1;
    }

    DoublyLinkedList list;

    int value;
    while (inputFile >> value)
    {
        if (value <= 0) 
        {
            std::cerr << "Error: Invalid positive integer in the file - " << value << std::endl;
        }
        else 
        {
            list.insert(value);
        }
    }

    char order;
    std::cout << "Enter 'A' for ascending order or 'D' for descending order: ";
    std::cin >> order;
    list.printList(order);

    list.printEvenList();
    list.printOddList();

    inputFile.close();

    return 0;
}