#include <iostream>
using namespace std;

int main()
{
    // 局部变量声明
    char var = 'A';

    //错误
    //switch (var)
    //{
    //case 'A':
    //    int cnt = 0; // 定义变量
    //    cout << "Excellent." << endl << cnt;
    //    break;  
    //case 'B':
    //case 'C':
    //    break;
    //
    //default:
    //    cout << "Bad." << endl;
    //}

    //不是不能定义变量，只是需要将变量定义在块内，
    //以确保变量在下面的case位于作用域之外，此外不能在下面的case中使用该变量
    switch (var)
    {
    case 'A':
    {
        int cnt = 0; // 定义变量
        cout << "Excellent." << endl << cnt;
    }
        break;
    case 'B':
    case 'C':
        break;

    default:
        cout << "Bad." << endl;
    }

    return 0;
}

