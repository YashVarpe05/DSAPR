#include <iostream>
using namespace std;

class CircularQueue
{
private:
    int *queue;
    int front, rear, size;

public:
    CircularQueue(int n)
    {
        size = n;
        queue = new int[size];
        front = rear = -1;
    }

    ~CircularQueue()
    {
        delete[] queue;
    }

    bool isFull()
    {
        return (front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1));
    }

    bool isEmpty()
    {
        return front == -1;
    }

    void enqueue(int value)
    {
        if (isFull())
        {
            cout << "Queue is Full\n";
            return;
        }
        if (front == -1)
        {
            front = rear = 0;
        }
        else if (rear == size - 1 && front != 0)
        {
            rear = 0;
        }
        else
        {
            rear++;
        }
        queue[rear] = value;
        cout << value << " enqueued\n";
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return;
        }
        cout << queue[front] << " dequeued\n";
        if (front == rear)
        {
            front = rear = -1;
        }
        else if (front == size - 1)
        {
            front = 0;
        }
        else
        {
            front++;
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return;
        }
        cout << "Queue elements: ";
        if (rear >= front)
        {
            for (int i = front; i <= rear; i++)
            {
                cout << queue[i] << " ";
            }
        }
        else
        {
            for (int i = front; i < size; i++)
            {
                cout << queue[i] << " ";
            }
            for (int i = 0; i <= rear; i++)
            {
                cout << queue[i] << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    CircularQueue cq(5);

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);
    cq.display();

    cq.dequeue();
    cq.dequeue();
    cq.display();

    cq.enqueue(60);
    cq.enqueue(70);
    cq.display();

    return 0;
}

/*
1. INITIALIZE(size):
   - Create array of size
   - Set front = rear = -1

2. IS_FULL:
   Return TRUE if:
   - (front = 0 AND rear = size-1) OR
   - rear = (front-1) % (size-1)

3. IS_EMPTY:
   Return TRUE if front = -1

4. ENQUEUE(value):
   IF queue is full:
      Return
   IF front = -1:
      front = rear = 0
   ELSE IF rear = size-1 AND front ≠ 0:
      rear = 0
   ELSE:
      rear++
   queue[rear] = value

5. DEQUEUE:
   IF queue is empty:
      Return
   IF front = rear:
      front = rear = -1
   ELSE IF front = size-1:
      front = 0
   ELSE:
      front++

Complexity:
- All operations: O(1)
- Space: O(n)
*/