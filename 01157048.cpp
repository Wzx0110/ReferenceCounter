#include <iostream>
using namespace std;

class int_array_cell{
private:
    int _counter;
    int *_memory;

public:
    int_array_cell(int *_memory){ // Constructor
        this->_memory = _memory;
         _counter = 1;
         cout << "int_array_cell is allocated" << endl;
    }
     ~int_array_cell(){ // Destructor
        delete[] _memory;
        cout << "int_array_cell counter 0: deleted" << endl;
    }
    int getCounter(){
        return _counter;
    }
    int dereference(){
        _counter -= 1;
        return _counter;
    }
    void reference(){
        _counter += 1;
        cout << "int_array_cell counter is increased: counter " << _counter << endl;
    }
};

class counter_ptr{
private:
    char *_name;
    int_array_cell *_cell_ptr;

public:
    counter_ptr(char *_name, int *_cell_ptr){ // Constructor with two parameters
        this->_name = _name;
        this->_cell_ptr = new int_array_cell(_cell_ptr); 
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << this->_cell_ptr->getCounter() << endl; 
    }

    counter_ptr(char *_name){ // Constructor with one parameter
        this->_name = _name;
        this->_cell_ptr = nullptr; 
        cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
    }

     ~counter_ptr(){ // Destructor
        cout << "counter_ptr " << _name << " is deleted" << endl;
        if(_cell_ptr != nullptr){                   
            int counter = _cell_ptr->dereference(); 
            if(counter <= 0){                       
                delete _cell_ptr;
            }
            else{                                    
                cout << "int_array_cell counter is decreased: counter " << counter << endl;
            }
        }
    }

    void operator=(int *memory){ // Operator Overloading with memory
       int counter =  _cell_ptr->dereference();
        if(counter == 0){
            delete _cell_ptr;
        }
        else{
            cout << "int_array_cell counter is decreased: counter " << counter << endl;
        }
        _cell_ptr = new int_array_cell(memory);
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->getCounter() << endl; 
    }

    void operator=(counter_ptr &otherPtr){ // Operator Overloading with other pointer
        _cell_ptr = otherPtr._cell_ptr;
        _cell_ptr->reference();                    
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->getCounter() << endl;
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
    //for (int i = 0; i < 10; i++)
        //b[i] = i; // 需要撰寫 counter_ptr operator[]寫值(回傳資料的參考 return type: int &)
    //for (int i = 0; i < 10; i++)
        //cout << b[i] << ' '; // 需要撰寫 counter_ptroperator[]讀值(回傳資料)
    //cout << endl;
    // stdout 輸出: 0 1 2 3 4 5 6 7 8 9
    //counter_ptr c("c");
    // stdout 輸出: counter_ptr c is not assigned to an int_array_cell
    //c = b;
    // stdout 輸出: int_array_cell counter is increased: counter 2
    // stdout 輸出: counter_ptr c is assigned to an int_array_cell: counter 2
    //b.release(); // 需要撰寫 counter_ptr release function: 不使用記憶體
    // stdout 輸出: int_array_cell counter is decreased: counter 1
    // stdout 輸出: counter_ptr b is not assigned to an int_array_cell}
    // c leaves it scope://需要撰寫 counter_ptr destructor
    // stdout 輸出: counter_ptr c is deleted// stdout 輸出: int_array_cell counter 0: deleted
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