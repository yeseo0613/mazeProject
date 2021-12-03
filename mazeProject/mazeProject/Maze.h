#include "LinkedQueue.h"
#include <fstream>

class Maze
{
private:
	int width; // 미로의 넓이
	int height; // 미로의 높이
	int** map; // 미로 맵
	int exitRow; // 출구 행
	int exitCol; // 출구 열
	LinkedQueue queue; // 큐
	LinkedQueue shortQueue; // 최적 경로
public:
	Maze()
	{
		init(0, 0);
	}

	~Maze()
	{
		reset();
	}

	// 미로맵 동적 할당 함수
	void init(int w, int h)
	{
		map = new int* [h];
		for (int i = 0; i < h; i++)
			map[i] = new int[w];
	}

	// 미로 맵 동적 해제 함수
	void reset()
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	// 미로 파일을 읽어오는 함수
	void load(const char* file)
	{
		ifstream fin(file, ios::in);
		fin >> width >> height;
		init(width, height);
		int temp;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fin >> temp;
				map[i][j] = temp;
				if (map[i][j] == 5)
				{
					queue.enqueue(j, i);
					shortQueue.enqueue(j, i);
				}
				else if (map[i][j] == 9)
				{
					exitCol = i;
					exitRow = j;
				}
			}
			cout << endl;
		}
		fin.close();
	}

	// 경로가 막혀있는지 확인하는 함수
	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c<0 || r >= width || c>height) // 범위를 벗어나는지 판단 여부
			return false;
		else // 비어있는 경로이거나 도착지점일 경우
			return(map[c][r] == 1 || map[c][r] == 9);
	}

	// 현재 미로를 화면에 출력하는 함수
	void print()
	{
		cout << "전체 미로의 크기 = " << width << " * " << height << endl;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == 1)
				{
					cout << "  ";
				}
				else if (map[i][j] == 0)
				{
					cout << "■";
				}
				else if (map[i][j] == 3)
				{
					cout << "☆";
				}
				else if (map[i][j] == 7)
				{
					cout << "□"; // 지나온 경로
				}
				else if (map[i][j] == 5)
				{
					cout << "○";
				}
				else if (map[i][j] == 9)
				{
					cout << "◎";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// 미로 탐색 함수
	void searchExit()
	{
		while (queue.isEmpty() == false) // 큐가 비어있지 않는 동안
		{
			int r = queue.firstRow();
			int c = queue.firstCol();
			queue.dequeue();

			map[c][r] = 7;
			if (exitRow == r && exitCol == c)
			{
				return;
			}
			else
			{
				map[c][r] = 7;
				if (isValidLoc(r - 1, c))
				{
					queue.enqueue(r - 1, c);
				}
				if (isValidLoc(r + 1, c))
				{
					queue.enqueue(r + 1, c);
				}
				if (isValidLoc(r, c -  1))
				{
					queue.enqueue(r, c - 1);
				}
				if (isValidLoc(r, c + 1))
				{
					queue.enqueue(r, c + 1);
				}
			}
		}
	}

	// 최적 경로를 찾는 함수
	bool isShortestPath(int r, int c)
	{
		if (r < 0 || c < 0 || r >= width || c >= height)
			return false;
		else
			return(map[c][r] == 7 || map[c][r] == 9); // 이미 찾은 경로이거나 출구일때만 true
	}

	// 최적경로 표시 함수
	void ShortestPath()
	{

	}
};