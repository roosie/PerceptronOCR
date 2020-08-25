//Roosevlet Young
//Percetron using voted/average guessing to deteremine OCR data character
//Refactor in C++ of similar previous code created in Python for Data Mining 315 at Washington State University under Professor Doppa 

#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <iostream>
#include <fstream>

#define BUFSIZE 256

using namespace std;

class img
{
public: 
	img(string x)
	{
		int len = x.length();
		int spaceCount = 0;
		int j = 0;
		for (int i = 0; i < len; i++)
		{
			if (spaceCount == 1)
			{
				image[j] = x[i];
				j++;
			}
			if (spaceCount == 2)
			{
				c = x[i];
				break;
			}
			if (x[i] == '\t')
			{
				spaceCount++;
			}
		}
		for (int i = 0; i < 256; i++)
		{
			w[i] = image[i + 2].c_str()[0] - 48;
		}
	}
	img(char newC, string newImg)
	{
		c = newC;
		int i;
		for (i = 0; newImg[i] && i < 256; i++)
		{
			image[i] = newImg[i];
		}
		image[i] = '\0';
		for (int i = 0; i < 256; i++)
		{
			w[i] = image[i+2].c_str()[0] - 48;
		}
	}
	char c;
	string image[256];
	int w[256];
};

class Perceptron
{
public:
	Perceptron(string testFile, string trainFile)
	{
		string buf;
		ifstream input(testFile);
		string defaultIMG = "im00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		while (getline(input, buf))
		{
			if (buf[0] != '\t')
			{
				test.push_back(new img(buf));
			}
		}
		input.close();
		ifstream input2(trainFile);
		while (getline(input2, buf))
		{
			if (buf[0] != '\t')
			{
				train.push_back(new img(buf));
			}
		}
		input2.close();

		for (int i = 0; i < 27 ; i++)
		{
			weights['a' + i] = new img('a' + i, defaultIMG);
		}
	}
	void trainOCR();
	void testOCR();
	void trainOCRAverage();
	void testOCRAverage();
	char guess(img*);
	char guessAveraged(img*);
	void update(char, char, img* curr);
private:
	unordered_map<int, img*> weights;
	vector<img*> train;
	vector<img*> test;
};