#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <exception>

class ZDexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Zero dimension exception!";
  }
} ZeroDimException;

struct Array{
    
    int** arr;
    uint8_t rows;
    uint8_t cols;
    
    void fillData(){
        srand(time(NULL));
        for (uint8_t i = 0; i < rows; ++i){
            for (uint8_t j = 0; j < cols; ++j){
                arr[i][j] = rand() % 100;
            }
        }
    }
    
    void printArray(){
        for (uint8_t i = 0; i < rows; ++i){
            std::cout << "[";
            for (uint8_t j = 0; j < cols; ++j){
                std::cout << arr[i][j] << ", ";
            }
            std::cout << "]" << std::endl;
        }
        std::cout << std::endl;
    }

    bool equalDims(const Array& a2){
        if (rows != a2.rows || cols != a2.cols){
            return false;
        }
        return true;
    }

    bool equal(const Array& a2){
        if (!equalDims(a2)){
            return false;
        }
        for (uint8_t i = 0; i < rows; ++i){
            for (uint8_t j = 0; j < cols; ++j){
                if (arr[i][j] != a2.arr[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    
    bool add(const Array& a2){
        if (!equalDims(a2)){
            return false;
        }
        for (uint8_t i = 0; i < rows; ++i){
           for (uint8_t j = 0; j < cols; ++j){
               arr[i][j] += a2.arr[i][j];
            }
        }
        return true;
    }
 
    bool subtract(const Array& a2){
        if (!equalDims(a2)){
            return false;
        }
        for (uint8_t i = 0; i < rows; ++i){
           for (uint8_t j = 0; j < cols; ++j){
               arr[i][j] -= a2.arr[i][j];
            }
        }
        return true;
    }

    Array* transpose(){
        Array* pa = new Array(cols,rows); 
        for (uint8_t i = 0; i < rows; ++i){
            for (uint8_t j = 0; j < cols; ++j){
                pa->arr[j][i] = arr[i][j];
            }
        }
        return pa;
    }

    Array() = delete;
    
    Array(const uint8_t _rows, const uint8_t _cols){
        //std::cout << "constructor" << std::endl;
        try{
            if (_rows == 0 || _cols == 0){
                throw ZeroDimException;
            }
            rows = _rows;
            cols = _cols;
            arr = new int*[rows];
            for (uint8_t i = 0; i < rows; ++i){
                arr[i] = new int[cols];
            }
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
        } 
    }

    ~Array() {
        //std::cout << "destructor" << std::endl;
        delete[]arr;
    }
};

int main()
{
    constexpr uint8_t rows = 3;
    constexpr uint8_t cols = 3;
    
    //test equal() #1   
    Array a1(rows,cols);
    Array a2(rows,cols);

    int number = 10;

    for (uint8_t i = 0; i < a1.rows; ++i){
        for (uint8_t j = 0; j < a1.cols; ++j){
            a1.arr[i][j] = number;
            a2.arr[i][j] = number;
            number++;
        }
    }
    std::cout << "a1:" << std::endl;
    a1.printArray();
    std::cout << "a2:" << std::endl;
    a2.printArray();  
    std::cout << "Test1. a1 equals a2? : " <<  a1.equal(a2) << std::endl;
    
    //test equal() #2
    a1.fillData();
    std::cout << "Fill a1 with random numbers:" << std::endl;
    a1.printArray();
    std::cout << "Test2. a1 equals a2? : " <<  a1.equal(a2) << std::endl;
    
    //test equal() #3
    Array a3(rows, cols+1);
    a3.fillData();
    std::cout << "a3:" << std::endl;
    a3.printArray();
    std::cout << "Test3. a1 equals a3? : " <<  a1.equal(a3) << std::endl << std::endl;
    
    //demo add() and subtract()
    std::cout << "a1.add(a2);" << std::endl;
    a1.add(a2);
    a1.printArray();
    std::cout << "a1.subtract(a2);" << std::endl;
    a1.subtract(a2);
    a1.printArray();

    Array* pa;
    pa = a3.transpose();
    std::cout << "Transposed a3:" << std::endl;
    (*pa).printArray();
    delete pa;
}

