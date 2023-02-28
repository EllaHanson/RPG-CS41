#include <memory>
#include "Actor.h"

using namespace std;

template<typename T>
class CircularList {
    struct  Node {
        T data;
        Node* next;
        Node() {
            next = nullptr;
        }
        Node(T newData, Node* newNext) {
            data = newData;
            next = newNext;
        }
        T get_data() const {
            return data;
        }
        Node* get_next() const {
            return next;
        }
        void set_data(T newData) {
            data = newData;
        }
        void set_next(Node* newNext) {
            next = newNext;
        }
    };
    Node* head;
    Node* tail;
    Node* prev;
    int size;
  public:
    CircularList() {
        head = nullptr;
        tail = nullptr;
        prev = nullptr;
        size = 0;
    }
    CircularList(const CircularList<T>& other) {
         head = nullptr;
        tail = nullptr;
        prev = nullptr;
        size = 0;
        for (Node* temp = other.head; temp; temp = temp->next) {
            push_back(temp->data);
        }
    }
    CircularList& operator=(const CircularList<T>& other) {
        if (other.get_head() == nullptr) {
            head = tail = nullptr;
        }
        for (Node* temp = other.head; temp; temp = temp->next) {
            push_back(temp->data);
        }
    }
    ~CircularList() {
        Node* temp = head;
        while (temp) {
            Node* copy = temp;
            temp = temp->get_next();
            delete copy;
        }
    }

    int get_size() const {
        return size;
    }

    Node* get_head() const {
        return head;
    }

    void push_back(const T& data) {
        Node* newNode = new Node(data, nullptr);
        if (head == nullptr) {
            head = newNode;
            tail->set_next(head);
            size++;
        } else {
            tail->set_next(newNode);
            tail = newNode;
            tail->set_next(head);
          size++;
        }
    }

    void printList() {
        if (head == NULL) {
            cout << "List is empty!" << endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " " ;
            current = current->next;
        }
    }




};
