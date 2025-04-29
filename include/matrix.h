#pragma once

#include <iostream>
#include <cmath>
#include <malloc.h>
#include <iomanip>

using namespace std;

typedef struct {
    int rows, cols;
    double** mass;
} Matrix;

Matrix create(int rows, int cols);                                 //создание (в случае ошибки возвращает {-1;-1;NULL}
void deleteMatrix(Matrix* matrix);                                 //удаление
Matrix input();                                                    //ввода 
void print(Matrix matrix);                                         //вывод
Matrix* save(Matrix* matrix1, Matrix* rezult);                      //сохранение в 1
bool minusMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult);  //разность матриц (true если успешно)
bool sumMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult);    //сумма матриц (true если успешно)
bool myltplyMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult);//перемножение матриц (true если успешно)
bool myltplyNum(Matrix matrix, Matrix* rezult);                     //умножение на число (true если успешно)
bool sumMinusNum(Matrix matrix, Matrix* rezult);                    //Сложение/вычитание матрицы с числом (true если успешно)
bool Trans(Matrix matrix, Matrix* rezult);                          //транспонирование
double opredelitel(Matrix matrix);                                  //Определитель
Matrix ObratnMatrix(Matrix matrix, bool opred);                     //обратная матрица (в случае ошибки возвращает {-1;-1;NULL}
int MenuMatrix();

