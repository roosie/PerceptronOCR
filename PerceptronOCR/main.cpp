#include "PerceptronOCR.h"

int main(int argc, char *argv[])
{
	Perceptron *ocr_test = new Perceptron("ocr_train.txt", "ocr_test.txt");
	cout << "Welcome to Roosevelt's Perceptron OCR" << endl;
	char c;
	int i = 0;
	while (1)
	{
		ocr_test->trainOCRAverage();
		ocr_test->testOCRAverage();
	}
	/*
	while (1)
	{
		cout << "Enter 1 to test; 2 to train" << endl;
		cin >> c;
		if (c == '1')
		{
			ocr_test->testOCR();
		}
		else if (c == '2')
		{
			ocr_test->trainOCR();
		}
	}
	*/
	return 0;
}