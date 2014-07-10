#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

class board
{
public:
	int values[4][4];

	int score = 0;


	int move(int rec)
	{
		board tempu;
		board tempd;
		board templ;
		board tempr;
		int ueval = 0;
		int deval = 0;
		int leval = 0;
		int reval = 0;
		int highest = 0;

		if (rec == 1) return 1;

		
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					templ.values[i][j] = values[i][j];
					tempr.values[i][j] = values[i][j];
					tempu.values[i][j] = values[i][j];
					tempd.values[i][j] = values[i][j];
				}
			}

			templ.left();
			tempr.right();
			tempu.up();
			tempd.down();

			ueval = tempu.eval();
			deval = tempu.eval();
			leval = tempu.eval();
			reval = tempu.eval();

			highest = ueval;
			if (leval > highest)
				highest = leval;
			if (reval > highest)
				highest = reval;
			if (deval > highest)
				highest = deval;


			if (isuppossible() && highest == ueval)
			{
				up();
				move(rec-1);
				goto jump;
			}
			if (isleftpossible() && highest == leval)
			{
				left();
				move(rec - 1);
				goto jump;
			}
			if (isrightpossible() && highest == reval)
			{
				right();
				move(rec - 1);
				goto jump;
			}
			if (isdownpossible() && highest == deval)
			{
				down();
				move(rec - 1);
				goto jump;
			}

		jump:
			return 1;
	}

	int eval()
	{
		int score = 0;

		if (rowchromatic(highestrow()))
		{
			score = score + 3;
		}
		if (colchromatic(highestcol()))
		{
			score = score + 3;
		}

		score = score + numadjtilesrow(highestrow());
		score = score + numadjtilescol(highestcol());
		
		return score;
	}

	int numadjtilesrow(int row)
	{
		int num = 0;
		for (int j = 0; j < 4; j++)
		{
			if (values[row][j] == values[row + 1][j] && values[row][j] != 0)
				num++;
		}
		return num;

	}

	int numadjtilescol(int col)
	{
		int num = 0;
		for (int i = 0; i < 4; i++)
		{
			if (values[i][col] == values[i][col + 1] && values[i][col] != 0)
				num++;
		}
		return num;

	}

	bool isrowempty(int row)
	{
		if (values[row][0] == 0 && values[row][1] == 0 && values[row][2] == 0 && values[row][3] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool iscolempty(int col)
	{
		if (values[0][col] == 0 && values[1][col] == 0 && values[2][col] == 0 && values[3][col] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isrowlocked(int row)
	{
		int j = 0;

		while (j < 3)
		{
			if (values[row][j] = values[row][j + 1])
				return false;
			j++;
		}

		return true;
	}

	bool iscollocked(int col)
	{
		int i = 0;

		while (i < 3)
		{
			if (values[i][col] = values[i+1][col])
				return false;
			i++;
		}

		return true;
	}
	
	bool rowchromatic(int row)
	{
		if (values[row][0] == 0 || values[row][1] == 0 || values[row][2] == 0 || values[row][3] == 0)
			return false;
		if (values[row][0] > values[row][1] && values[row][1] > values[row][2] && values[row][2] > values[row][3])
		{
			return true;
		}
		if (values[row][0] < values[row][1] && values[row][1] < values[row][2] && values[row][2] < values[row][3])
		{
			return true;
		}
		return false;
	}
	
	int highestrow() /*has bias towards lower rows*/
	{
		int highest = 0;
		int highrow = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (values[i][j]>highest)
				{
					highest = values[i][j];
					highrow = i;
				}
					
			}
		}
		return highrow;
	}

	int highestcol() /*has bias towards lower cols*/
	{
		int highest = 0;
		int highcol = 0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (values[i][j]>highest)
				{
					highest = values[i][j];
					highcol = j;
				}

			}
		}
		return highcol;
	}
	
	bool colchromatic(int col)
	{
		if (values[0][col] == 0 || values[1][col] == 0 || values[2][col] == 0 || values[3][col] == 0)
			return false;
		if (values[0][col] > values[1][col] && values[1][col] > values[2][col] && values[2][col] > values[3][col])
		{
			return true;
		}
		if (values[0][col] < values[1][col] && values[1][col] < values[2][col] && values[2][col] < values[3][col])
		{
			return true;
		}

		return false;

	}

	int countemptyspaces()
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (values[i][j] == 0)
					count++;
			}
		}
		return count;
	}

	void clear()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				values[i][j] = 0;
			}
		}
	}

	void printboard()
	{
		int len = 0;
		cout << "________________________\n";

		for (int i = 0; i < 4; i++)
		{
			cout << "|     |     |     |     |\n|";
			for (int j = 0; j < 4; j++)
			{
				len = to_string(values[i][j]).length();
				if (values[i][j] == 0)
				{
					cout << "     |";
				}
				else
				{
					switch (len)
					{
					case 0:
						cout << "     |";
						break;
					case 1:
						cout << "  " << values[i][j] << "  |";
						break;
					case 2:
						cout << " " << values[i][j] << "  |";
						break;
					case 3:
						cout << " " << values[i][j] << " |";
						break;
					case 4:
						cout << " " << values[i][j] << "|";
						break;
					case 5:
						cout << "" << values[i][j] << "|";
						break;
				}
				
				}
			}
			cout << "\n|_____|_____|_____|_____|\n";
		}
	}

	void spawn()
	{
		srand(time(NULL));
		bool placed = false;
		int i = 0;
		int j = 0;

		if (countemptyspaces() == 0)
			placed = true;

		while (placed == false)
		{
			i = rand() % 4;
			j = rand() % 4;
			if (values[i][j] == 0)
			{
				if (rand() % 10 == 0)
				{
					values[i][j] = 4;
				}
				else
				{
					values[i][j] = 2;
				}
				placed = true;
			}
		}
	}

	bool over()
	{
		board templ;
		board tempr;
		board tempu;
		board tempd; 

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				templ.values[i][j] = values[i][j];
				tempr.values[i][j] = values[i][j];
				tempu.values[i][j] = values[i][j];
				tempd.values[i][j] = values[i][j];
			}
		}

		templ.left();
		tempr.right();
		tempu.up();
		tempd.down();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (templ.values[i][j] != values[i][j])
					return false;
				if (tempr.values[i][j] != values[i][j])
					return false;
				if (tempu.values[i][j] != values[i][j])
					return false;
				if (tempd.values[i][j] != values[i][j])
					return false;
			}
		}
		return true;

	}

	void left()
	{
		int i = 0;
		int j = 0;
		bool combined = false;
		while (i < 4)
		{
			j = 1;
			combined = false;
			if (values[i][0] == values[i][1] && values[i][2] == values[i][3] && values[i][0] != 0 && values[i][2] !=0)
			{
				j = 5;
				values[i][0] = values[i][0] * 2;
				values[i][1] = values[i][2] * 2;
				values[i][2] = 0;
				values[i][3] = 0;
				combined = true;
				score = score + values[i][0] + values[i][1];
			}
			while (j < 4)
			{
				if (values[i][j] == 0||j==0|| values[i][j-1]!=0)
				{
					j++;
				}
				else
				{
					if (values[i][j - 1] == 0)
					{
						while (values[i][j - 1] == 0 && j !=0)
						{
							values[i][j - 1] = values[i][j];
							values[i][j] = 0;
							j--;
						}
					}
				}
				
			}
			if (values[i][0] == values[i][1] && !combined)
			{
				values[i][0] = values[i][0] * 2;
				values[i][1] = values[i][2];
				values[i][2] = values[i][3];
				values[i][3] = 0;
				score = score + values[i][0];
				goto jump;
			}
			if (values[i][1] == values[i][2])

			{
				values[i][1] = values[i][1] * 2;
				values[i][2] = values[i][3];
				values[i][3] = 0;
				score = score + values[i][1];
				goto jump;
			}
			if (values[i][2] == values[i][3])
			{
				values[i][2] = values[i][2] * 2;
				values[i][3] = 0;
				score = score + values[i][2];
				goto jump;
			}

			jump:
			i++;
		}

	}

	void right()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				temp.values[i][3 - j] = values[i][j];
		}
		temp.left();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				values[i][3 - j] = temp.values[i][j];
		}

		score = score + temp.score;
	}

	void up()
	{
		int i = 0;
		int j = 0;
		bool combined = false;

		while (j < 4)
		{
			i = 1;
			combined = false;
			if (values[0][j] == values[1][j] && values[2][j] == values[3][j] && values[0][j] != 0 && values[2][j] != 0)
			{
				i = 5;
				values[0][j] = values[0][j] * 2;
				values[1][j] = values[1][j] * 2;
				values[2][j] = 0;
				values[3][j] = 0;
				score = score + values[0][j] + values[1][j];
				combined = true;
			}
			while (i < 4)
			{
				if (values[i][j] == 0 || i == 0 || values[i-1][j] != 0)
				{
					i++;
				}
				else
				{
					if (values[i-1][j] == 0)
					{
						while (values[i-1][j] == 0 && i != 0)
						{
							values[i-1][j] = values[i][j];
							values[i][j] = 0;
							i--;
						}
					}
				}

			}
			if (values[0][j] == values[1][j] && !combined)
			{
				values[0][j] = values[0][j] * 2;
				values[1][j] = values[2][j];
				values[2][j] = values[3][j];
				values[3][j] = 0;
				score = score + values[0][j];
				goto jump;
			}
			if (values[1][j] == values[2][j])
			{
				values[1][j] = values[1][j] * 2;
				values[2][j] = values[3][j];
				values[3][j] = 0;
				score = score + values[1][j];
				goto jump;
			}
			if (values[2][j] == values[3][j])
			{
				values[2][j] = values[2][j] * 2;
				values[3][j] = 0;
				score = score + values[2][j];
				goto jump;
			}
		jump:
			j++;
		}
		
	}

	void down()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				temp.values[3-i][j] = values[i][j];
		}
		temp.up();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				values[3-i][j] = temp.values[i][j];
		}
		score = score + temp.score;
	}

	bool isuppossible()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp.values[i][j] = values[i][j];
			}
		}

		temp.up();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (temp.values[i][j] != values[i][j])
					return true;
			}
		}
		return false;

	}

	bool isdownpossible()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp.values[i][j] = values[i][j];
			}
		}

		temp.down();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (temp.values[i][j] != values[i][j])
					return true;
			}
		}
		return false;

	}

	bool isrightpossible()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp.values[i][j] = values[i][j];
			}
		}

		temp.right();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (temp.values[i][j] != values[i][j])
					return true;
			}
		}
		return false;

	}

	bool isleftpossible()
	{
		board temp;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp.values[i][j] = values[i][j];
			}
		}

		temp.left();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (temp.values[i][j] != values[i][j])
					return true;
			}
		}
		return false;

	}
}