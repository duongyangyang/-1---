#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstring>
using namespace std;

int matrix[4][4]; //数组变量，大部分操作会在此变量进行。
int first_matrix[4][4]; //数组变量，保留开始的矩阵为了最后要输出。
int ar_r[4]; int ar_gr[4]; int ar_y[4]; int ar_bl[4]; //数组变量，使用在max_pooling操作，把4x4矩阵分成4个数组来找最大值。
int red, green, yellow, blue; //整数变量，使用在max_pooling操作，每个数组的最大值。

void create(){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = rand()%20; //使用rand()随机生成一个整数。然后把要%20操作为了题目要求元素都是20以内。
            while (matrix[i][j] < 0){  //如果生成的整数小于零，我们再次生成新的整数直到得到正整数（题目要求自然数）。
                matrix[i][j] = rand()%20; 
            } 
            first_matrix[i][j] = matrix[i][j]; //把生成的矩阵保留在另一个变量，为了以后要输出
        }
    }
}

void print(int print_matrix[4][4]){ //print_matrix[4][4]是要输出的矩阵
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cout << setw(3) << right << print_matrix[i][j]; //setw(3)和right 为了满徐每个元素占3个字符宽，均为右对齐的输出要求
        }
        cout << endl;
    }
}

void compr_w(){ //向上操作
    int row = 0;
    for (int j = 0; j < 4; j++){
        for(int i = 1; i < 4; i++){
            matrix[row][j] = matrix [row][j] + matrix[i][j]; //把在row行j列的元素的价值变成j列上所有元素的和。
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (i != row)      //把不在row行的元素元素变成0。
                matrix[i][j] = 0;
        }
    }
}

void compr_s(){ //向上操作
    int row = 3;
    for (int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){
            matrix[row][j] = matrix [row][j] + matrix[i][j]; //把在row行j列的元素的价值变成j列上所有元素的和。
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (i != row)      //把不在row行的元素元素变成0。
                matrix[i][j] = 0;
        }
    }
}

void compr_a(){ //向左操作
    int col = 0;
    for (int j = 0; j < 4; j++){
        for(int i = 1; i < 4; i++){
            matrix[j][col] = matrix [j][col] + matrix[j][i]; //把在j行col列的元素的价值变成j列上所有元素的和。
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (j != col)      //把不在col列的元素元素变成0。
                matrix[i][j] = 0;
        }
    }
}

void compr_d(){ //向右操作
    int col = 3;
    for (int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){
            matrix[j][col] = matrix [j][col] + matrix[j][i]; //把在j行col列的元素的价值变成j列上所有元素的和。
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (j != col)      //把不在col列的元素元素变成0。
                matrix[i][j] = 0;
        }
    }
}

void rotate(){
    int a = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (i > j) //如果没有这个条件，会造成loop: a_ij -> a_ji -> a_ij，矩阵不变。
                swap(matrix[i][j], matrix[j][i]); //转换a_ij和a_ji元素。
        }
    }
}

void separate(){ //构造四个一维数组，不要用二维数组因为目标只是找到最大值。
    int count = 0; 
    for (int i = 0; i <= 1; i++){ //构造red数组
        for (int j = 0; j <= 1; j++){
            ar_r[count] = matrix[i][j]; 
            count++;
        }
    }
    count = 0;
    for (int i = 0; i <= 1; i++){ //构造green数组
        for (int j = 2; j <= 3; j++){
            ar_gr[count] = matrix[i][j];
            count++;
        }
    }
    count = 0;
    for (int i = 2; i <= 3; i++){ //构造yellow数组
        for (int j = 0; j <= 1; j++){
            ar_y[count] = matrix[i][j];
            count++;
        }
    }
    count = 0;
    for (int i = 2; i <= 3; i++){ //构造blue数组
        for (int j = 2; j <= 3; j++){ 
            ar_bl[count] = matrix[i][j];
            count++;
        }
    }
}

int find_max(int array[4]){ //Bubble sort 找最大值
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3 - i; j++)
        {
            if (array [j] > array [j+1])
            {
                swap (array [j], array [j+1]);
            }
        }
    }
    return array[3];
}

int main()
{
    srand(time(NULL)); //rand()的结果每次都是同样的，所以不满足题目要求。srand(time(NULL))可以处理这个问题。
    create(); //构造矩阵。
    string inp; cin >> inp; //输入操作指令。
    if (inp == "compression"){ //Compression指令会要求输入参数。
        string _4inp; cin >> _4inp;
        if (_4inp == "a") {compr_a();} //按照参数，运行相应的操作。
        if (_4inp == "d") {compr_d();}
        if (_4inp == "w") {compr_w();}
        if (_4inp == "s") {compr_s();}
    }
    if (inp == "rotate"){ //Rotate指令会直接运行rotate()。
        rotate();
    }
    if (inp == "max_pooling"){ //Max_pooling指令
        separate(); //先运行分块操作（实际上是造成四个一维数组）
        red = find_max(ar_r); //分别寻找每个数组的最大值
        green = find_max(ar_gr);
        yellow = find_max(ar_y);
        blue = find_max(ar_bl);
    }
    //输出
    print(first_matrix); //输出最开始的矩阵
    cout << "--------------" << endl; //分割
    if (inp == "max_pooling"){ //Max_pooling输出2x2矩阵所以不能用以上的print()。
        cout << setw(3) << right << red << setw(3) << right << green << endl
        << setw(3) << right << yellow << setw(3) << right << blue;
    } else {print(matrix);}//其他操作都构成另一个4x4矩阵，用print()输出。
    
    return 0;
}