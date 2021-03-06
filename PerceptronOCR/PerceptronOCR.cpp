#include "PerceptronOCR.h"

void Perceptron::testOCR()
{
	int len = test.size();
	int k = 0;
	int i = 0;
	char c = 0;
	for (i = 0; i < len; i++)
	{
		c = guess(test[i]);
		if (c > 0)
		{
			k++;
		}
	}
	printf("count: %d; incorrect: %d\n", i, k);
}
void Perceptron::trainOCR()
{
	int len = train.size();
	int k = 0;
	int i = 0;
	char c = 0;
	for (i = 0; i < len; i++)
	{
		c = guess(train[i]);
		if (c > 0)
		{
			update(train[i]->c, c, train[i]);
			k++;
		}
	}
	printf("count: %d; incorrect: %d\n", i, k);
}
void Perceptron::testOCRAverage()
{
	int len = test.size();
	int k = 0;
	int i = 0;
	char c = 0;
	for (i = 0; i < len; i++)
	{
		c = guessAveraged(test[i]);
		if (c > 0)
		{
			k++;
		}
	}
	printf("count: %d; incorrect: %d\n", i, k);
}
void Perceptron::trainOCRAverage()
{
	int len = train.size();
	int k = 0;
	int i = 0;
	char c = 0;
	for (i = 0; i < len; i++)
	{
		c = guessAveraged(train[i]);
		if (c > 0)
		{
			update(train[i]->c, c, train[i]);
			k++;
		}
	}
	printf("count: %d; incorrect: %d\n", i, k);
}
char Perceptron::guess(img* curr)
{
	int conf[26] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int max = 0;
	int len = 128;
	char temp;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 2; j < len ; j++)
		{
			auto temp =  curr->image+j;
			if ((weights['a' + i]->w[j - 2] > 0 ) && (temp->at(0) == '1'))
			{
				conf[i]++;
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (conf[i] > conf[max])
		{
			max = i;
		}
	}

	//check 

	if ('a' + max == curr->c)
	{
		return -1;
	}
	return max+'a';
}
char Perceptron::guessAveraged(img* curr)
{
	int conf[26] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int max = 0;
	int len = 128;
	char temp;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 2; j < len; j++)
		{
			auto temp = curr->image + j;
			if ((weights['a' + i]->w[j - 2] > 0) && (temp->at(0) == '1'))
			{
				conf[i] += weights['a' + i]->w[j - 2];
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (conf[i] > conf[max])
		{
			max = i;
		}
	}

	//check 

	if ('a' + max == curr->c)
	{
		return -1;
	}
	return max + 'a';
}
void Perceptron::update(char real, char guess, img* curr)
{
	for (int i = 0; i < 128; i++)
	{
		weights[guess]->w[i] -= curr->w[i];
		weights[real]->w[i] += curr->w[i];
	}
}