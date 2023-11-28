#include <iostream>
using namespace std;

class HashTable
{
    private:
        struct node
        {
            int value;
            int index;
            string name;
            node* next;
            node* collisionNode;
        };
        node* head;
        node* tail;
        int uniqueInstances;
        int totalSize;

    public:
        HashTable();
        ~HashTable();

        int insertNode(int nodeValue, int nodeIndex, string nodeName);

        int hashFunction(int value);

        void printTable();

        // getters
        int getUniqueInstances();
        int getTotalSize();
};

HashTable::HashTable()
{
    head = nullptr;
    tail = nullptr;
    uniqueInstances = 0;
    totalSize = 0;
}

HashTable::~HashTable()
{
    cout << "Beginning Deconstructor...\n";

    node* iteratorNode = head;

    while(iteratorNode != nullptr)
    {
        cout << "Entering iterator while...\n";
        if(iteratorNode->collisionNode == nullptr)
        {
            cout << "Collision Node is nullptr...\n";
            node* tempNodeDelete = iteratorNode;
            iteratorNode = iteratorNode->next;
            delete tempNodeDelete;
            cout << "Node Deleted.\n";
        }
        else
        {
            cout << "Collision node is populated...\n";
            node* collisionIterator = iteratorNode->collisionNode;
            while(collisionIterator != nullptr)
            {
                cout << "Entering Collision While...\n";
                node* tempCollisionDelete = collisionIterator;
                collisionIterator = collisionIterator->next;
                delete tempCollisionDelete;
            }
            cout << "All collision nodes deleted.\n";
            delete collisionIterator;
            iteratorNode->collisionNode = nullptr;
            delete iteratorNode->collisionNode;
            iteratorNode = iteratorNode->next;
        }
    }
    head = nullptr;
    tail = nullptr;
    delete head;
    delete tail;
    delete iteratorNode;

    cout << "Deconstructor Executed. Ending Program...\n";
}

int HashTable::getUniqueInstances()
{
    return uniqueInstances;
}

int HashTable::getTotalSize()
{
    return totalSize;
}

int HashTable::hashFunction(int value)
{
    int hashValue = ((value * -3) + (value += (17 * (value + 7)) - 13 + ( value % 2)));
    return hashValue;
}

int HashTable::insertNode(int nodeValue, int nodeIndex, string nodeName)
{
    node* newNode = new node;
    newNode->value          = hashFunction(nodeValue);
    newNode->index          = nodeIndex;
    newNode->name           = nodeName;
    newNode->next           = nullptr;
    newNode->collisionNode  = nullptr;

    int returnValue = 0;

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
        totalSize++;
        uniqueInstances++;
        return 1;
    }
    else if(head->value > newNode->value)
    {
        newNode->next = head;
        head = newNode;
        totalSize++;
        uniqueInstances++;
        return 2;
    }
    else if(tail->value < newNode->value)
    {
        tail->next = newNode;
        tail = newNode;
        totalSize++;
        uniqueInstances++;
        return 3;
    }
    else
    {
        node* iteratorNode = head;
        node* prevIteratorNode = iteratorNode;

        while(iteratorNode != nullptr)
        {
            if(iteratorNode->value > newNode->value)
            {
                prevIteratorNode->next = newNode;
                newNode->next = iteratorNode;
                totalSize++;
                returnValue = 4;
                break;
            }
            else if(iteratorNode->value == newNode->value)
            {                
                if(iteratorNode->collisionNode == nullptr)
                {
                    iteratorNode->collisionNode = newNode;
                    returnValue = 6;
                }
                else
                {
                    node* iteratorCollisionNode = iteratorNode->collisionNode;

                    while(iteratorCollisionNode->next != nullptr)
                    {
                        iteratorCollisionNode = iteratorCollisionNode->next;
                    }

                    iteratorCollisionNode->next = newNode;

                    iteratorCollisionNode = nullptr;
                    delete iteratorCollisionNode;
                    returnValue = 7;
                }

                totalSize++;
                break;
            }

            prevIteratorNode = iteratorNode;
            iteratorNode = iteratorNode->next;
        }

        iteratorNode = nullptr;
        prevIteratorNode = nullptr;
        delete iteratorNode;
        delete prevIteratorNode;

        return returnValue;
    }
}

void HashTable::printTable()
{
    if(head == nullptr)
    {
        cout << "Empty Table.\n";
        return;
    }

    node* iteratorNode = head;

    while(iteratorNode != nullptr)
    {
        cout << "Hash Value: " << iteratorNode->value << endl;
        cout << "Index: " << iteratorNode->index << endl;
        cout << "Name: " << iteratorNode->name << endl; 
        if(iteratorNode->collisionNode != nullptr)
        {
            node* collisionNodeIterator = iteratorNode->collisionNode;

            cout << "\nCollision(s) Present on this Node. Printing Collisions..." << endl;

            while(collisionNodeIterator != nullptr)
            {
                cout << "Hash Value: " << collisionNodeIterator->value << endl;
                cout << "Index: " << collisionNodeIterator->index << endl;
                cout << "Name: " << collisionNodeIterator->name << endl << endl;
                collisionNodeIterator = collisionNodeIterator->next;
            }
            collisionNodeIterator = nullptr;
            delete collisionNodeIterator;
            cout << "END OF COLLISIONS ON THIS NODE\n\n";
        }
        else
        {
            cout << "\n";
        }
        iteratorNode = iteratorNode->next;
    }

    iteratorNode = nullptr; // may not be required, but doing so to be safe.
    delete iteratorNode;
}


int main()
{
    HashTable Test1;

    cout << "Result: " << Test1.insertNode(13, 1, "TEST 1") << endl;
    cout << "Result: " << Test1.insertNode(13, 2, "TEST 2") << endl;
    cout << "Result: " << Test1.insertNode(13, 3, "TEST 3") << endl;
    cout << "Result: " << Test1.insertNode(12, 4, "TEST 4") << endl;
    cout << "Result: " << Test1.insertNode(14, 5, "TEST 5") << endl;
    cout << "Result: " << Test1.insertNode(13, 6, "TEST 6") << endl;
    cout << "Result: " << Test1.insertNode(15, 7, "TEST 7") << endl;
    cout << "Result: " << Test1.insertNode(20, 8, "TEST 8") << endl;
    cout << "Result: " << Test1.insertNode(17, 9, "TEST 9") << endl;
    cout << "Result: " << Test1.insertNode(16, 10, "TEST 10") << endl;
    cout << "Result: " << Test1.insertNode(13, 11, "TEST 11") << endl;
    cout << "Result: " << Test1.insertNode(20, 12, "TEST 12") << endl;
    cout << "Result: " << Test1.insertNode(13, 13, "TEST 13") << endl;

    Test1.printTable();

    return 0;
}
