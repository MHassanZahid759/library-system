#include <iostream>
using namespace std;

class SimpleQueue {
private:
    int *arr;
    int front, rear, size;

public:
    SimpleQueue(int s) {
        size = s;
        arr = new int[size];
        front = rear = -1;
    }

    ~SimpleQueue() {
        delete[] arr;
    }

    bool isFull() {
        return rear == size - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full. Cannot enqueue." << endl;
            return;
        }

        if (isEmpty())
            front = 0;

        arr[++rear] = value;
        cout << value << " enqueued to the queue." << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }

        cout << arr[front] << " dequeued from the queue." << endl;

        if (front == rear)
            front = rear = -1;
        else
            front++;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Elements in the queue are: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    SimpleQueue sq(3);

    sq.enqueue(1);
    sq.enqueue(2);
    sq.enqueue(3);
    sq.display();

    sq.dequeue();
    sq.display();

    sq.enqueue(4);
    sq.enqueue(5);
    sq.enqueue(6); // This will display an error message since the queue is full.

    return 0;
}

