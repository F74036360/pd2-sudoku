#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Sudoku
{
	public:
		void GiveQuestion();//出題 
		void ReadIn();//解他人的題目 
		 int Solve();//解題 
	private:
		void random();
		void Isu();//初始化題目數獨矩陣 
		 int checkQ();
		 int check(int tput);//驗證填入數字是否正確 
		void AfterRand();//隨機出題後填回數獨矩陣 
		void printQ();//印出數獨 
		void divide();//將數獨矩陣分割成行列及宮 
	     int su_num[144];//數獨矩陣 
		int i,j,k,r;//計數用 
		int row[12][12];//列 
		int column[12][12];//行 
		int divide_row[48][3];//分列來取得宮 
		int B[16][9];  //宮 
		void change();
};
