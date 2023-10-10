// Dz OOP 10.10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
using namespace std;

class Exception {
protected:
    string message;

public:
    Exception(string m) : message(m) {}
    virtual string GetMessage() const 
    {
        return message;
    }
};

class ArraySizeException : public Exception
{
public:
    ArraySizeException(string message) : Exception(message) {}
};

class ArrayDataException : public Exception
{
private:
    int rows;   
    int columns;

public:

    ArrayDataException(int rows, int cols, string message) : Exception(message), rows(rows), columns(cols) {}        
        
    int getRows() const 
    {
        return rows;
    }

    int getCols() const
    {
        return columns;
    }
};

class ArrayValueCalculator
{
private:
    string** arr;
    int rows;
    int columns;

public:
    ArrayValueCalculator(string** array, int rows, int columns) : arr(array), rows(rows), columns(columns) {}

   int doCalc()
{
    int sum = 0;
    int elem = 0;   
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            try
            {
                elem = stoi(arr[i][j]);
                sum += elem;
            }
            catch (...)
            {
                throw ArrayDataException(i, j, "Ошибка в элементе [" + to_string(i) + "][" +to_string(j) + "]: " + arr[i][j]);
            }
        }
    }
    return sum; 
}
};

int main()
{
    setlocale(LC_ALL, "");  
    try
    {
        int rows = 4;
        int columns = 4;

        string** arr = new string * [rows];
        for (int i = 0; i < rows; i++)
        {
            arr[i] = new string[columns];
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                arr[i][j] = to_string(rand() % 10);
            }
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }

        if (rows != 4 || columns != 4)
        {
            throw ArraySizeException("Некорректный размер массива. Размер должен быть 4x4.");
        }

        ArrayValueCalculator SumArr(arr, rows, columns);
        int sum = SumArr.doCalc();
        cout << "Сумма: " << sum << endl;

        for (int i = 0; i < rows; i++)
        {
            delete[] arr[i];
        }
        delete[] arr;
    }
    catch (ArraySizeException err)  
    {
        cout << err.GetMessage() << endl;
    }
    catch (ArrayDataException err) 
    {
        cout << err.GetMessage() << endl;   
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
