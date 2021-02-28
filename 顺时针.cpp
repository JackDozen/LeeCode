#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

#define _UP_  		0
#define _RIGHT_  	1
#define _BOTTOM_  	2
#define _LEFT_  	3

// 目的是按照顺时针的方向打印下标
/*
	* style 打印类型
	* arr	传入的下标数组
	* t_m	列数引用
	* t_n	行数引用

*/
int* run(int style, int* arr, int& t_m, int& t_n)
{
	int* outArr = nullptr;

	if (style == _UP_ || style == _BOTTOM_)
	{
		outArr = (int*)malloc(t_m * sizeof(int));
	}
	if (style == _RIGHT_ || style == _LEFT_)
	{
		outArr = (int*)malloc(t_n * sizeof(int));
	}
	int n = 0;
	switch (style)
	{
	case _UP_:
		cout << "UP >";
		for (int i = 0; i < t_m; i++) {

			cout << setw(2) << arr[i] << " ";
			outArr[n] = arr[i];
			n++;
		}
		t_n--;
		break;
	case _RIGHT_:
		cout << "RIGHT >";

		for (int i = 0; i < t_n; i++) {

			cout << setw(2) << arr[(i + 1) * (t_m - 1) + i] << " ";
			outArr[n] = arr[(i + 1) * (t_m - 1) + i];
			n++;
		}
		t_m--;
		break;
	case _BOTTOM_:
		cout << "BOTTOM >";

		for (int i = t_m - 1; i >= 0; i--) {

			cout << setw(2) << arr[(t_n - 1) * t_m + i] << " ";
			outArr[n] = arr[(t_n - 1) * t_m + i];
			n++;
		}
		t_n--;
		break;
	case _LEFT_:
		cout << "LEFT >";

		for (int i = t_n - 1; i >= 0; i--) {

			cout << setw(2) << arr[t_m * i] << " ";
			outArr[n] = arr[t_m * i];
			n++;
		}
		t_m--;

		break;
	default:
		break;
	}

	return outArr;
}

// m 为列数， n 为行数
vector<int> function(int m, int n)
{
	int before_Count = m * n;

	// 输出下标数组
	int* pOutArr = (int*)malloc(m * n * sizeof(int));

	// 输出下标数组(temp)
	vector<int> outArr;

	// 原下标
	vector<int> outArr_Before;

	// 变化下标数组
	int* arr = (int*)malloc(m * n * sizeof(int));

	// 下标赋值	  
	int _n = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			arr[(i * m) + j] = _n;
			outArr_Before.push_back(_n);
			_n++;
		}
	}

	//void run(int style, int* arr, int& t_m, int& t_n)

	// 跑的类型(上，右，下，左)
	int run_style = 0;

	int temocount = outArr.size();
	while (m != 0 && n != 0)
	{
		int* temp = run(run_style, arr, m, n);
		cout << endl;
		temocount = outArr.size();

		if (run_style == _UP_ || run_style == _BOTTOM_)
		{
			for (int i = 0; i < m; i++)
			{
				outArr.push_back(temp[i]);
			}
		}
		else if (run_style == _RIGHT_ || run_style == _LEFT_)
		{
			for (int i = 0; i < n; i++)
			{
				outArr.push_back(temp[i]);
			}
		}

		run_style++;
		if (run_style == 4)
		{
			run_style = 0;
		}

		// n 重新赋值为 0
		_n = 0;
		// 释放以重新赋值下标
		free(arr);

		// 此处想法上来说 m 与 n 的值已经发生改变
		arr = (int*)malloc(m * n * sizeof(int));

		// 升序
		sort(temp, temp + outArr.size() - temocount);

		int j = 0;

		vector<int>::iterator i = outArr_Before.begin();

		while (i < outArr_Before.end())
		{
			if (*i == temp[j])
			{
				//cout << " delete " << *i << endl;
				i = outArr_Before.erase(i);
				j++;
			}
			else {
				i++;
			}

			if (j == before_Count - m * n)
			{
				break;
			}
		}
		cout << endl;

		free(temp);
		temp = nullptr;

		// 重新赋值下标
		for (int i = 0; i < outArr_Before.size(); i++)
		{
			arr[i] = outArr_Before.at(i);
		}
	}

	for (int i = 0; i < m * n; i++) {
		pOutArr[i] = outArr.at(i);
	}

	return outArr;

}

int main()
{
	int m = 6;
	int n = 5;
	vector<int> pValue = function(m, n);

	string strArr[30] = { "a1", "a2", "a3", "a4", "a5", "a6",
						  "b1", "b2", "b3", "b4", "b5", "b6",
						  "c1", "c2", "c3", "c4", "c5", "c6",
						  "d1", "d2", "d3", "d4", "d5", "d6",
						  "e1", "e2", "e3", "e4", "e5", "e6" };

	for (int i = 0; i < m * n; i++)
	{
		cout << strArr[i] << " ";
		if ((i + 1) % m == 0)
		{
			cout << endl;
		}
	}
	cout << endl << endl;

	// 对应下标
	cout << "index:" << endl;
	for (int i = 0; i < m * n; i++)
	{
		cout << setw(2) << i << " ";
		if ((i + 1) % m == 0)
		{
			cout << endl;
		}
	}
	cout << endl << endl;

	for (int i = 0; i < m * n; i++)
	{
		cout << setw(2) << pValue[i] << "  ";
	}

	cout << endl << endl;

	for (int i = 0; i < m * n; i++)
	{
		cout << strArr[pValue[i]] << "  ";
	}
}
