#include "LinkedQueue.h"
#include <fstream>

class Maze
{
private:
	int width; // �̷��� ����
	int height; // �̷��� ����
	int** map; // �̷� ��
	int exitRow; // �ⱸ ��
	int exitCol; // �ⱸ ��
	LinkedQueue queue; // ť
	LinkedQueue shortQueue; // ���� ���
public:
	Maze()
	{
		init(0, 0);
	}

	~Maze()
	{
		reset();
	}

	// �̷θ� ���� �Ҵ� �Լ�
	void init(int w, int h)
	{
		map = new int* [h];
		for (int i = 0; i < h; i++)
			map[i] = new int[w];
	}

	// �̷� �� ���� ���� �Լ�
	void reset()
	{
		for (int i = 0; i < height; i++)
			delete[]map[i];
		delete[]map;
	}

	// �̷� ������ �о���� �Լ�
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

	// ��ΰ� �����ִ��� Ȯ���ϴ� �Լ�
	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c<0 || r >= width || c>height) // ������ ������� �Ǵ� ����
			return false;
		else // ����ִ� ����̰ų� ���������� ���
			return(map[c][r] == 1 || map[c][r] == 9);
	}

	// ���� �̷θ� ȭ�鿡 ����ϴ� �Լ�
	void print()
	{
		cout << "��ü �̷��� ũ�� = " << width << " * " << height << endl;
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
					cout << "��";
				}
				else if (map[i][j] == 3)
				{
					cout << "��";
				}
				else if (map[i][j] == 7)
				{
					cout << "��"; // ������ ���
				}
				else if (map[i][j] == 5)
				{
					cout << "��";
				}
				else if (map[i][j] == 9)
				{
					cout << "��";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	// �̷� Ž�� �Լ�
	void searchExit()
	{
		while (queue.isEmpty() == false) // ť�� ������� �ʴ� ����
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

	// ���� ��θ� ã�� �Լ�
	bool isShortestPath(int r, int c)
	{
		if (r < 0 || c < 0 || r >= width || c >= height)
			return false;
		else
			return(map[c][r] == 7 || map[c][r] == 9); // �̹� ã�� ����̰ų� �ⱸ�϶��� true
	}

	// ������� ǥ�� �Լ�
	void ShortestPath()
	{

	}
};