class Stack {
  private:
    int *array;
    int top;
    int max;

  public:
    Stack();
    ~Stack();

    void push(int);
    int pop();
    int get();

    int size();
    bool isEmpty();
    bool isFull();
};
