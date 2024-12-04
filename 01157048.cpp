#include <iostream>
using namespace std;

// Class to manage an integer array with reference counting
class int_array_cell{
private:
    int _counter; // Reference counter
    int *_memory; // Pointer to the dynamically allocated memory

public:
    // Constructor: Initializes memory and reference counter
    int_array_cell(int *_memory){
        this->_memory = _memory;
         _counter = 1; // Initial counter set to 1
         cout << "int_array_cell is allocated" << endl;
    }
    // Destructor: Frees memory
     ~int_array_cell(){
        delete[] _memory; // Free dynamically allocated memory
        cout << "int_array_cell counter 0: deleted" << endl;
    }
    // Returns the current reference count
    int getCounter(){
        return _counter;
    }
    // Decreases reference count and returns the updated count
    int dereference(){
        _counter -= 1;
        return _counter;
    }
    // Increases reference count
    void reference(){
        _counter += 1;
        cout << "int_array_cell counter is increased: counter " << _counter << endl;
    }
    // Returns a reference to the value at the specified index in memory
    int &getValueFromMemory(int index){
        return _memory[index];
    }
};

// Class for a reference-counted pointer to int_array_cell
class counter_ptr{
private:
    char *_name; // Name of the pointer
    int_array_cell *_cell_ptr; // Pointer to the int_array_cell

public:
    // Constructor: Initializes pointer with memory and an int_array_cell
    counter_ptr(char *_name, int *_cell_ptr){
        this->_name = _name;
        this->_cell_ptr = new int_array_cell(_cell_ptr); // Allocate new int_array_cell
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << this->_cell_ptr->getCounter() << endl; 
    }
    // Constructor: Initializes pointer without memory
    counter_ptr(char *_name){
        this->_name = _name;
        this->_cell_ptr = nullptr; // No memory assigned
        cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
    }
    // Destructor: Frees the int_array_cell if no other references exist
     ~counter_ptr(){
        cout << "counter_ptr " << _name << " is deleted" << endl;
        if(_cell_ptr != nullptr){                   
            int counter = _cell_ptr->dereference(); // Decrease reference count
            if(counter <= 0){                       
                delete _cell_ptr; // If counter is 0, delete the memory
            }
            else{                                    
                cout << "int_array_cell counter is decreased: counter " << counter << endl;
            }
        }
    }
    // Releases memory and sets pointer to nullptr
    void release(){                                  
        if(_cell_ptr != nullptr){                  
            int counter = _cell_ptr->dereference(); // Decrease reference count
            if(counter <= 0){                      
                delete _cell_ptr; // Delete if counter is 0
            }
            else{                                   
                cout << "int_array_cell counter is decreased: counter " << counter << endl;
            }
            _cell_ptr = nullptr; // Set pointer to nullptr
        }
        cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
    }
    // Assignment operator: Assign new memory to the counter_ptr
    void operator=(int *memory){ 
       int counter =  _cell_ptr->dereference(); // Decrease reference count
        if(counter == 0){
            delete _cell_ptr; // Delete memory if no references are left
        }
        else{
            cout << "int_array_cell counter is decreased: counter " << counter << endl;
        }
        _cell_ptr = new int_array_cell(memory); // Assign new memory
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->getCounter() << endl; 
    }
    // Assignment operator: Copy reference from another counter_ptr 
    void operator=(counter_ptr &otherPtr){ 
        _cell_ptr = otherPtr._cell_ptr; // Share the same int_array_cell
        _cell_ptr->reference(); // Increase reference count                    
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->getCounter() << endl;
    }
    // Array subscript operator: Access memory by index
    int &operator[](int index){             
        return _cell_ptr->getValueFromMemory(index); // Return value at index
    }
    
};

int main()
{
    // PART 一  (35分)
    counter_ptr b("b", new int[10]); // 需要撰寫counter_ptr constructor(建構子) 接受兩個參數
    // stdout 輸出: int_array_cell is allocated
    // stdout 輸出: counter_ptr b is assigned to an int_array_cell: counter 1
    {
        b = new int[100]; // 需要撰寫counter_ptr operator=
        // stdout 輸出: int_array_cell counter 0: deleted
        // stdout 輸出: int_array_cell is allocated
        // stdout輸出: counter_ptr b is assigned to an int_array_cell: counter 1
        counter_ptr a("a");
        // 需要撰寫 counter_ptrconstructor(建構子)接受一個參數
        //  stdout 輸出: counter_ptr a is notassigned to an int_array_cell
        a = b; // 需要撰寫 counter_ptr operator=
        // stdout 輸出: int_array_cell counter is increased: counter 2
        // stdout 輸出: counter_ptr a is assigned to an int_array_cell: counter 2
    }
    // a leaves it scope://需要撰寫 counter_ptrdestructor
    // stdout 輸出: counter_ptr a is deleted
    // stdout 輸出: int_array_cell counter is decreased: counter 1
    // PART 二  (35分)
    for (int i = 0; i < 10; i++)
        b[i] = i; // 需要撰寫 counter_ptr operator[]寫值(回傳資料的參考 return type: int &)
    for (int i = 0; i < 10; i++)
        cout << b[i] << ' '; // 需要撰寫 counter_ptroperator[]讀值(回傳資料)
    cout << endl;
    // stdout 輸出: 0 1 2 3 4 5 6 7 8 9
    counter_ptr c("c");
    // stdout 輸出: counter_ptr c is not assigned to an int_array_cell
    c = b;
    // stdout 輸出: int_array_cell counter is increased: counter 2
    // stdout 輸出: counter_ptr c is assigned to an int_array_cell: counter 2
    b.release(); // 需要撰寫 counter_ptr release function: 不使用記憶體
    // stdout 輸出: int_array_cell counter is decreased: counter 1
    // stdout 輸出: counter_ptr b is not assigned to an int_array_cell}
    // c leaves it scope://需要撰寫 counter_ptr destructor
    // stdout 輸出: counter_ptr c is deleted
    // stdout 輸出: int_array_cell counter 0: deleted
    // stdout 輸出: counter_ptr b is delete
}
			// c leaves it scope:	//需要撰寫 counter_ptr destructor
			// stdout 輸出: counter_ptr c is deleted
			// stdout 輸出: int_array_cell counter 0: deleted
			// stdout 輸出: counter_ptr b is deleted
/*
PART 三 (30分)
	1) 用 template 改寫 class counter_ptr int_array_cell
	2) 重覆 PART 一  二 的測試
*/