template <typename T>
class MyArray {
    T data[100];
public:
    void set(int index, T value) { data[index] = value; }
    T get(int index) { return data[index]; }
};
