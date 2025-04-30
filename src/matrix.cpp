#include "matrix.h"

int MenuMatrix()
{   
    Matrix matrix1 = { 0,0,NULL };
    Matrix matrix2 = { 0,0,NULL };
    Matrix rezult = { 0,0,NULL };
    int command;
    do
    {
        cout << endl << endl << "--------------------------------------------------------------";
        cout << endl << "(0)Вернуться в Главное меню (1)Ввести первую матрицу (2)Ввести вторую матрицу";
        cout << endl << "(3)Сложение матриц (4)Вычитание матриц (5)Умножение матриц";
        cout << endl << "(6)Умножение матрицы на число (7)Сложение/вычитание матрицы с числом ";
        cout << endl << "(8)Транспонирование матрицы  (9)Определитель (10)Обратная матрица";
        cout << endl << "--------------------------------------------------------------" << endl;
        cin >> command;
        switch (command)
        {
        case 1: {                                   //Ввод1
            int command2 = -1;
            if (matrix1.mass != NULL)
            {
                cout << endl << "Сейчас ваша первая матрица: ";
                print(matrix1);
                do
                {
                    cout << endl << "(0)Оставить как есть (1)Ввести заново: ";
                    cin >> command2;
                    if ((command2 != 0) && (command2 != 1))
                    {
                        cout << "неверная комманда";
                        continue;
                    }
                } while ((command2 != 0) && (command2 != 1));
            }
            if ((command2 == 1) || matrix1.mass == NULL)
            {
                matrix1 = input();
                cout << endl << "Первая матрица: ";
                print(matrix1);
            }
            break;
        }

        case 2: {                                   //Ввод2
            int command2 = -1;
            if (matrix2.mass != NULL)
            {
                cout << endl << "Сейчас ваша вторая матрица: ";
                print(matrix2);
                do
                {
                    cout << endl << "(0)Оставить как есть (1)Ввести заново: ";
                    cin >> command2;
                    if ((command2 != 0) && (command2 != 1))
                    {
                        cout << "неверная комманда";
                        continue;
                    }
                } while ((command2 != 0) && (command2 != 1));
            }
            if ((command2 == 1) || matrix2.mass == NULL)
            {
                matrix2 = input();
                cout << endl << "Вторая матрицы: ";
                print(matrix2);
            }
            command2 = -1;
            break;
        }

        case 3: {                                               //Сложение матриц
            rezult = create(matrix1.rows, matrix2.cols);
            if (rezult.mass == NULL)
                break;
           
            if (sumMatrix(matrix1, matrix2, &rezult))
            {
                cout << endl << endl << "=  ";
                print(rezult);
                Matrix* ptr = save(&matrix1, &rezult);
                matrix1 = *ptr;
            }
            break;
        }

        case 4: {                                               //Разность матриц
            rezult = create(matrix1.rows, matrix2.cols);
            if (rezult.mass == NULL)
                break;

            if (minusMatrix(matrix1, matrix2, &rezult))
            {
                cout << endl << endl << "=  ";
                print(rezult);
                Matrix* ptr = save(&matrix1, &rezult);
                matrix1 = *ptr;
            }
            break;
        }

        case 5: {                                               //Умножение матриц
            rezult = create(matrix1.rows, matrix2.cols);
            if (rezult.mass == NULL)
                break;

            if (myltplyMatrix(matrix1, matrix2, &rezult))
            {
                cout << endl << endl << "= ";
                print(rezult);
                Matrix* ptr = save(&matrix1, &rezult);
                matrix1 = *ptr;
            }
            break;
        }
        case 6: {                                              //Умножение на число
            char command;
            do
            {
                cout << endl << "Выберите матрицу для умножения (1)Первая (2)Вторая: ";
                cin >> command;
                if ((command != '1') && (command != '2'))
                    cout << endl << "Неверная команда";
            } while ((command != '1') && (command != '2'));

            if (command == '1')
            {
                rezult = create(matrix1.rows, matrix1.cols);
                if (rezult.mass == NULL)
                    break;

                if (myltplyNum(matrix1, &rezult))
                {
                    cout << endl << endl << "= ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            if (command == '2')
            {
                rezult = create(matrix2.rows, matrix2.cols);
                if (rezult.mass == NULL)
                    break;

                if (myltplyNum(matrix2, &rezult))
                {
                    cout << endl << endl << "= ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            break;
        }

        case 7: {                                              //Сложение/вычитание матрицы с числом
            char command;
            do
            {
                cout << endl << "Выберите матрицу для операции (1)Первая (2)Вторая: ";
                cin >> command;
                if ((command != '1') && (command != '2'))
                    cout << endl << "Неверная команда";
            } while ((command != '1') && (command != '2'));

            if (command == '1')
            {
                rezult = create(matrix1.rows, matrix1.cols);
                if (rezult.mass == NULL)
                    break;

                if (sumMinusNum(matrix1, &rezult))
                {
                    cout << endl << endl << "= ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            if (command == '2')
            {
                rezult = create(matrix2.rows, matrix2.cols);
                if (rezult.mass == NULL)
                    break;

                if (sumMinusNum(matrix2, &rezult))
                {
                    cout << endl << endl << "= ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            break;
        }
        case 8: {                                              //транспонирование
            char command;
            do
            {
                cout << endl << "Выберите матрицу для операции (1)Первая (2)Вторая: ";
                cin >> command;
                if ((command != '1') && (command != '2'))
                    cout << endl << "Неверная команда";
            } while ((command != '1') && (command != '2'));

            if (command == '1')
            {
                rezult = create(matrix1.cols, matrix1.rows);
                if (rezult.mass == NULL)
                    break;

                if (Trans(matrix1, &rezult))
                {
                    cout << endl << endl << "Транспонированная матрица ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            if (command == '2')
            {
                rezult = create(matrix2.cols, matrix2.rows);
                if (rezult.mass == NULL)
                    break;

                if (Trans(matrix2, &rezult))
                {
                    cout << endl << endl << "Транспонированная матрица ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
                break;
            }
            break;
        }

        case 9: {                                              //определитель
            char command;
            do
            {
                cout << endl << "Выберите матрицу для операции (1)Первая (2)Вторая: ";
                cin >> command;
                if ((command != '1') && (command != '2'))
                    cout << endl << "Неверная команда";
            } while ((command != '1') && (command != '2'));

            if (command == '1')
            {
                double opred = opredelitel(matrix1);
                if (!isnan(opred))
                    cout << endl << endl << "Определитель равен " << opred;
                else
                    cout << endl << "Ошибка вычислений";
                break;
            }
            if (command == '2')
            {
                double opred = opredelitel(matrix2);
                if (!isnan(opred))
                    cout << endl << endl << "Определитель равен " << opred;
                else
                    cout << endl << "Ошибка вычислений";
                break;
            }
            break;
        }
        case 10: {                                              //обратная матрица (в случае ошибки возвращает {-1;-1;NULL}
            char command; bool opr = false;
            do
            {
                cout << endl << "Выберите матрицу для операции (1)Первая (2)Вторая: ";
                cin >> command;
                if ((command != '1') && (command != '2'))
                    cout << endl << "Неверная команда";
            } while ((command != '1') && (command != '2'));

            if (command == '1')
            {
                double opred = opredelitel(matrix1);
                if (!isnan(opred) && !(opred > -0.000001 && opred < 0.000001))
                    opr = true;
                rezult = ObratnMatrix(matrix1, opr);
                if (rezult.mass != NULL)
                {
                    cout << endl << endl << "Обратная матрицы:  ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
            }
            if (command == '2')
            {
                double opred = opredelitel(matrix2);
                if (!isnan(opred) && !(opred > -0.000001 && opred < 0.000001))
                    opr = true;
                rezult = ObratnMatrix(matrix2, opr);
                if (rezult.mass != NULL)
                {
                    cout << endl << endl << "Обратная матрицы:  ";
                    print(rezult);
                    Matrix* ptr = save(&matrix1, &rezult);
                    matrix1 = *ptr;
                }
            }
            break;
        }
        case 0:
            break;

        default:
            cout << "Ошибка ввода ";
            break;
        }
    } while (command != 0);

    deleteMatrix(&matrix1);
    deleteMatrix(&matrix2);
    return 0;
}
Matrix ObratnMatrix(Matrix matrix, bool opred)
{
    Matrix rezult = { -1,-1,NULL };
    if (matrix.mass == NULL)
    {
        cout << endl << "Матрица не введена ";
        return rezult;
    }
    if (matrix.rows != matrix.cols)
    {
        cout << endl << "Матрица должна быть квадратной";
        return rezult;
    }
    if (!opred)
    {
        cout << endl << "Невозможно выполнить операцию. Определитель равен 0";
        return rezult;
    }
    int n = matrix.rows;

    Matrix dopmatrix = create(n, 2 * n);
    if (dopmatrix.mass == NULL)
        return dopmatrix;

    for (int i = 0;i < n;i++)
        for (int j = 0; j < n; j++)
            dopmatrix.mass[i][j] = matrix.mass[i][j];

    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < 2 * n;j++)
        {
            if (i == (j - n))
                dopmatrix.mass[i][j] = 1;

            else
                dopmatrix.mass[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int rowmax = i;
        for (int max = i + 1; max < n; max++)
        {
            if (abs(dopmatrix.mass[max][i]) > abs(dopmatrix.mass[rowmax][i]))
                rowmax = max;
        }

        if (rowmax != i)
        {
            double* temp = dopmatrix.mass[i];
            dopmatrix.mass[i] = dopmatrix.mass[rowmax];
            dopmatrix.mass[rowmax] = temp;
        }

        double glav = dopmatrix.mass[i][i];
        if (glav > -0.000001 && glav < 0.000001)
        {
            cout << endl << "Невозможно выполнить операцию.";
            deleteMatrix(&dopmatrix);
            return rezult;
        }

        for (int j = 0; j < 2 * n; j++)
            dopmatrix.mass[i][j] /= glav;

        for (int k = 0; k < n; k++)
        {
            if (k != i)
            {
                double num = dopmatrix.mass[k][i];
                for (int j = 0; j < 2 * n; j++)
                    dopmatrix.mass[k][j] -= num * dopmatrix.mass[i][j];
            }
        }
    }

    rezult = create(n, n);
    if (rezult.mass == NULL)
    {
        deleteMatrix(&dopmatrix);
        return rezult;
    }

    for (int i = 0;i < n;i++)
        for (int j = 0; j < n; j++)
            rezult.mass[i][j] = dopmatrix.mass[i][j + n];

    deleteMatrix(&dopmatrix);
    return rezult;
}

double opredelitel(Matrix matrix)
{
    if (matrix.mass == NULL)
    {
        cout << endl << "Матрица не введена";
        return NAN;
    }
    if (matrix.rows != matrix.cols)
    {
        cout << endl << "Матриа должна быть квадратной";
        return NAN;
    }

    int n = matrix.rows; double opred = 0.0;

    if (n == 1)
        return matrix.mass[0][0];

    if (n == 2)
        return (matrix.mass[0][0] * matrix.mass[1][1] - matrix.mass[0][1] * matrix.mass[1][0]);

    for (int i = 0;i < n;i++)
    {
        Matrix minor = create(n - 1, n - 1);
        if (minor.mass == NULL)
            return NAN;

        for (int j = 1; j < n; j++)
        {
            int minorcols = 0;
            for (int k = 0; k < n; k++)
            {
                if (k == i)
                    continue;
                minor.mass[j - 1][minorcols] = matrix.mass[j][k];
                minorcols++;;
            }
        }
        double minorOpred = opredelitel(minor);
        if (isnan(minorOpred))
        {
            deleteMatrix(&minor);
            return NAN;
        }

        if (i % 2 == 0)
            opred += matrix.mass[0][i] * minorOpred;
        else
            opred += matrix.mass[0][i] * minorOpred * (-1);

        deleteMatrix(&minor);
    }

    return opred;
}

bool Trans(Matrix matrix, Matrix* rezult)
{
    if (matrix.mass == NULL)
    {
        cout << endl << "Матрица не введена";
        return false;
    }
    for (int i = 0; i < matrix.cols; i++)
        for (int j = 0; j < matrix.rows;j++)
            (*rezult).mass[i][j] = matrix.mass[j][i];

    return true;
}

bool sumMinusNum(Matrix matrix, Matrix* rezult)
{
    if (matrix.mass == NULL)
    {
        cout << endl << "Матрица не введена";
        return false;
    }

    bool correct = false; double num; char command;
    do
    {
        cout << endl << "Введите число: ";
        cin >> num;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Введено не число :(";
            continue;
        }

        cout << endl << "Выберите комманду (+)Прибавить (-)Вычесть: ";
        cin >> command;
        if (cin.fail() || (command != '+' && command != '-'))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Ошибка ввода";
            continue;
        }
        correct = true;

    } while (!correct);

    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            if (command == '+')    (*rezult).mass[i][j] = matrix.mass[i][j] + num;
            else if (command == '-')    (*rezult).mass[i][j] = matrix.mass[i][j] - num;
        }
    }

    print(matrix);
    if (command == '+')
        cout << endl << endl << "+";
    else if (command == '-')
        cout << endl << endl << "-";
    cout << endl << num;

    return true;
}

bool myltplyNum(Matrix matrix, Matrix* rezult)
{
    if (matrix.mass == NULL)
    {
        cout << endl << "Матрица не введена";
        return false;
    }

    bool correct = false; double num;
    do
    {
        cout << endl << "Введите число: ";
        cin >> num;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Введено не число :(";
            continue;
        }
        correct = true;
    } while (!correct);

    for (int i = 0; i < matrix.rows; i++)
        for (int j = 0; j < matrix.cols; j++)
            (*rezult).mass[i][j] = matrix.mass[i][j] * num;

    print(matrix); cout << endl << endl << "*" << endl << num;

    return true;
}

bool myltplyMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult)
{
    if (matrix1.mass == NULL)
    {
        cout << endl << "Первая матрица не введена";
        return false;
    }
    if (matrix2.mass == NULL)
    {
        cout << endl << "Вторая матрица не введена";
        return false;
    }
    if ((matrix2.rows != matrix1.cols))
    {
        cout << endl << "Размерности матриц не соответствуют необходимой операции";
        return false;
    }
    for (int i = 0; i < (*rezult).rows; i++)
    {
        for (int j = 0; j < (*rezult).cols; j++)
        {
            (*rezult).mass[i][j] = 0;
            for (int k = 0; k < matrix1.cols; k++)
            {
                (*rezult).mass[i][j] += matrix1.mass[i][k] * matrix2.mass[k][j];
            }
        }
    }
    print(matrix1); cout << endl << endl << "*"; print(matrix2);
    return true;
}

bool minusMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult)
{
    char command;
    if (matrix1.mass == NULL)
    {
        cout << endl << "Первая матрица не введена";
        return false;
    }
    if (matrix2.mass == NULL)
    {
        cout << endl << "Вторая матрица не введена";
        return false;
    }
    if ((matrix1.rows != matrix2.rows) || (matrix1.cols != matrix2.cols))
    {
        cout << endl << "Размерности матриц не соответствуют необходимой операции";
        return false;
    }

    do
    {
        cout << endl << "Вычесть из первой вторую (1)";
        cout << endl << "Вычесть из второй первую (2)";
        cout << endl << "Введите комманду: ";
        cin >> command;
        if ((command != '1') && (command != '2'))
            cout << endl << "Неверная команда";
    } while ((command != '1') && (command != '2'));

    if (command == '1')
    {
        print(matrix1); cout << endl << endl << "-"; print(matrix2);
        for (int i = 0; i < matrix1.rows; i++)
            for (int j = 0; j < matrix1.cols; j++)
                (*rezult).mass[i][j] = matrix1.mass[i][j] - matrix2.mass[i][j];
    }
    else // command must be '2' here because of the do-while loop
    {
        print(matrix2); cout << endl << endl << "-"; print(matrix1);
        for (int i = 0; i < matrix1.rows; i++)
            for (int j = 0; j < matrix1.cols; j++)
                (*rezult).mass[i][j] = matrix2.mass[i][j] - matrix1.mass[i][j];
    }
    
    return true;
}

bool sumMatrix(Matrix matrix1, Matrix matrix2, Matrix* rezult)
{
    if (matrix1.mass == NULL)
    {
        cout << endl << "Первая матрица не введена";
        return false;
    }
    if (matrix2.mass == NULL)
    {
        cout << endl << "Вторая матрица не введена";
        return false;
    }
    if ((matrix1.rows != matrix2.rows) || (matrix1.cols != matrix2.cols))
    {
        cout << endl << "Размерности матриц не соответствуют операции сложения";
        return false;
    }

    for (int i = 0; i < matrix1.rows; i++)
        for (int j = 0; j < matrix1.cols; j++)
            (*rezult).mass[i][j] = matrix1.mass[i][j] + matrix2.mass[i][j];

    print(matrix1); cout << endl << endl << "+"; print(matrix2);
    return true;
}

Matrix* save(Matrix* matrix1, Matrix* rezult)
{
    char command;
    cout << endl << "Сохранить результат вычислений в первую матрицу?   (0)Нет(1)Да:    ";
    cin >> command;
    if (command == '0')
    {
        deleteMatrix(rezult);
        return matrix1;
    }
    else if (command == '1')
    {
        deleteMatrix(matrix1);
        return rezult;
    }
    else {
        cout << endl << "Неверная комманда. Результат вычислений не сохранён";
        deleteMatrix(rezult);
        return matrix1;
    }
}

Matrix create(int rows, int cols)
{
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.mass = (double**)malloc(rows * sizeof(double*));
    if (matrix.mass == NULL)
    {
        cout << endl << "Ошибка выделения памяти";
        matrix.rows = -1;
        matrix.cols = -1;
        return matrix;
    }
    for (int i = 0; i < rows; i++)
    {
        matrix.mass[i] = (double*)malloc(cols * sizeof(double));
        if (matrix.mass[i] == NULL)
        {
            cout << endl << "Ошибка выделения памяти";
            for (int j = 0; j < i; j++)
                free(matrix.mass[i]);
            free(matrix.mass);
            matrix.rows = -1;
            matrix.cols = -1;
            matrix.mass = NULL;
            return matrix;
        }
    }
    return matrix;
}

void deleteMatrix(Matrix* matrix)
{
    if ((*matrix).mass != NULL && matrix != NULL) {
        for (int i = 0; i < (*matrix).rows;i++)
            free((*matrix).mass[i]);
        (*matrix).rows = 0;
        (*matrix).cols = 0;
        free((*matrix).mass);
        (*matrix).mass = NULL;
    }
}

Matrix input()
{
    int rows, cols;
    bool correct = false;
    do
    {
        cout << endl << "Введите количество строк: ";
        cin >> rows;
        if (rows < 1 || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Ошибка ввода. Возможно, количество строк меньше 1 :(";
            continue;
        }
        cout << endl << "Введите количество столбцов: ";
        cin >> cols;
        if (cols < 1 || cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl << "Ошибка ввода. Возможно количество столбцов меньше 1 :(";
            continue;
        }
        correct = true;
    } while (!correct);

    Matrix matrix = create(rows, cols);
    if (matrix.mass == NULL)
    {
        cout << endl << "Ошибка создания матрицы";
        return matrix;
    }

    cout << endl << "Ввод элементов массива: ";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            correct = false;
            do
            {
                cout << endl << "[" << i + 1 << "]" << "[" << j + 1 << "] = ";
                cin >> matrix.mass[i][j];
                if (cin.fail())
                {
                    cout << endl << "Ошибка ввода";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                correct = true;
            } while (!correct);

        }
    }
    return matrix;
}

void print(Matrix matrix)
{
    cout << endl;
    for (int i = 0; i < matrix.rows; i++)
    {
        cout << "|";
        for (int j = 0; j < matrix.cols;j++)
            cout << "  " << setw(7) << fixed << setprecision(2) << matrix.mass[i][j];
        cout << setw(7) << "| " << endl;
    }
}