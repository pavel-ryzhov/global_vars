#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <map>

using namespace std;

//preferences
#define SIZE 500
#define leftLimit 3
#define rightLimit 0.019
#define topBottomLimit 0.145
#define emptyLimit 1
#define circleDistr 0.3
#define distrLimit 0.81
#define finalsKoef 0.03
#define finalsLimit 0.15




class DigitSample
{
private:
	double horDistr[3];
	double verDistr[3];
	double quartersDistr[4];
	unsigned circles;
public:
	DigitSample()
	{
		horDistr[0] = 0; horDistr[1] = 0; horDistr[2] = 0;
		verDistr[0] = 0; verDistr[1] = 0; verDistr[2] = 0;
		quartersDistr[0] = 0; quartersDistr[1] = 0; quartersDistr[2] = 0; quartersDistr[3] = 0;
		circles = 0;	
	}
	DigitSample(double horLeft, double horMiddle, double horRight, double verTop, double verMiddle, double verBottom,
		double firstQ, double secondQ, double thirdQ, double fourthQ, unsigned _circles)
	{
		horDistr[0] = horLeft; horDistr[1] = horMiddle; horDistr[2] = horRight;
		verDistr[0] = verTop; verDistr[1] = verMiddle; verDistr[2] = verBottom;
		quartersDistr[0] = firstQ; quartersDistr[1] = secondQ; quartersDistr[2] = thirdQ; quartersDistr[3] = fourthQ;
		circles = _circles;
	}
	void setHorDistr(double left, double middle, double right)
	{
		horDistr[0] = left;
		horDistr[1] = middle;
		horDistr[2] = right;
	}
	double getHorDistr(unsigned i) { return horDistr[i]; }
	void setVerDistr(double top, double middle, double bottom)
	{
		verDistr[0] = top;
		verDistr[1] = middle;
		verDistr[2] = bottom;
	}
	double getVerDistr(unsigned i) { return verDistr[i]; }
	void setQuatersDistr(double first, double second, double third, double fourth)
	{
		quartersDistr[0] = first;
		quartersDistr[1] = second;
		quartersDistr[2] = third;
		quartersDistr[3] = fourth;
	}
	double getQuatersDistr(unsigned i) { return quartersDistr[i]; }
	void setCircles(unsigned _circles)
	{
		circles = _circles;
	}
	unsigned getCircles() { return circles; }
};

vector< DigitSample > sampleDigits;

class ScannedDigit: public DigitSample
{
private:
	unsigned borders[2][2];
	double pixels;
	double sum;
	map < unsigned, double > finals;
public:
	ScannedDigit()
	{
		pixels = 0;
		sum = 0;
	}
	void setLeftBorder(unsigned left) { borders[0][0] = left; }
	void setRightBorder(unsigned right) { borders[1][0] = right; }
	void setTopBorder(unsigned top) { borders[0][1] = top; }
	void setBottomBorder(unsigned bottom) { borders[1][1] = bottom; }
	unsigned getLeftBorder() { return borders[0][0]; }
	unsigned getRightBorder() { return borders[1][0]; }
	unsigned getTopBorder() { return borders[0][1]; }
	unsigned getBottomBorder() { return borders[1][1]; }
	void setPixels(double _pixels) { pixels = _pixels; }
	double getPixels() { return pixels; }
	void addFinal(unsigned digit, double distr, bool flag)
	{
		if (finals[digit] != 0)
			finals[digit] += distr;
		else
			finals[digit] = distr;
		if (flag)
			sum += distr;
	}
	double getFinal(unsigned digit) { return finals[digit]; }
	double getSum() { return sum; }
	map < unsigned, double > getFinals() { return finals; }
};
vector< ScannedDigit > scannedDigits;

void readFile(string* data, unsigned* sizeX, unsigned* sizeY)
{
	int i = 0;
	string buf;

	while (1)
	{	
		getline(cin, buf);
		if (buf == "") break;
		data[i] += buf;
		++i;
	}
	*sizeY = i;
	*sizeX = data[i - 1].length();
}

void deleteGrey(string* data, bool dataBit[SIZE][SIZE], unsigned sizeX, unsigned sizeY, double pixelInVert[SIZE])
{
	for (unsigned i = 0; i < sizeY; i++)
	{
		for (unsigned j = 0; j < sizeX; j++)
		{
			if (i == 0) pixelInVert[j] = 0;
			if ( (data[i][j] == '.') || ( data[i][j] == '#' ) || (data[i][j] == '%' ) )
				dataBit[i][j] = false;
			else 
			{
				dataBit[i][j] = true;
				pixelInVert[j] += 1;
			}
		}
	}
}

void findDigits(bool dataBit[SIZE][SIZE], unsigned sizeX, unsigned sizeY, double pixelInVert[SIZE])
{
	bool endSeek = false;
	double sum = 0, average = 0, countNotEmpty = 0;
	ScannedDigit digit;
	unsigned countEmpty = 0;
	
	for (unsigned i = 0; i < sizeX; i++)
	{
		sum += pixelInVert[i];
		if ( (pixelInVert[i] > 0) && (!endSeek) ) countNotEmpty += 1;
		if ( (pixelInVert[i] == 0) && (!endSeek) ) ++countEmpty;
		if (countNotEmpty == 1) average = sum;
		if ( (countEmpty >= emptyLimit) && (pixelInVert[i] > 2) && (!endSeek))
		{
			endSeek = true;
			digit.setLeftBorder(i);
			countNotEmpty = 0;
			countEmpty = 0;
			average = 0;
			sum = pixelInVert[i];
		}
		else if ( (pixelInVert[i] - average > leftLimit) && (!endSeek) )
		{
			endSeek = true;
			digit.setLeftBorder(i);
			countNotEmpty = 0;
			countEmpty = 0;
			average = 0;
			sum = pixelInVert[i];
		}
		else if ( (pixelInVert[i] / sum <= rightLimit) && (endSeek) )
		{
			endSeek = false;
			digit.setRightBorder(i - 1);
			digit.setPixels(sum - pixelInVert[i]);
			scannedDigits.push_back(digit);
			sum = 0;	
			if (scannedDigits.size() == 3) break;
		}
		if (countNotEmpty > 0) average = sum / countNotEmpty;
	}

	
	for (unsigned k = 0; k < scannedDigits.size(); k++)
	{
		sum = 0;
		for (unsigned i = 0; i < sizeY; i++)
		{
			for (unsigned j = scannedDigits[k].getLeftBorder(); j < scannedDigits[k].getRightBorder(); j++)
				if (dataBit[i][j])
					sum += 1;
			if (sum / scannedDigits[k].getPixels() >= topBottomLimit) 
			{
				sum = 0;
				scannedDigits[k].setTopBorder(i - 4);
				break;
			}	
		}
	
		sum = 0;
		for (unsigned i = sizeY - 1; i >= 0; i--)
		{
			for (unsigned j = scannedDigits[k].getLeftBorder(); j < scannedDigits[k].getRightBorder(); j++)
				if (dataBit[i][j])
					sum += 1;

			if (sum / scannedDigits[k].getPixels() >= topBottomLimit) 
			{
				sum = 0;
				scannedDigits[k].setBottomBorder(i + 4);
				break;
			}	
		}
	}
}

void countPixels(bool dataBit[SIZE][SIZE], unsigned sizeY)
{
	double sum = 0, lastLine = 0;
	unsigned i = 0;
	for (unsigned k = 0; k < scannedDigits.size(); k++)
	{
		while (i <= scannedDigits[k].getTopBorder())
		{
			for (unsigned j = scannedDigits[k].getLeftBorder(); j <= scannedDigits[k].getRightBorder(); j++)
			{
				if (dataBit[i][j])
				{
					if (i != scannedDigits[k].getTopBorder()) sum += 1;
					lastLine += 1;
				}
			}
			if ((i == scannedDigits[k].getTopBorder()) && (lastLine == 0)) 
			{
				scannedDigits[k].setTopBorder(i + 1);
				sum += lastLine;
			}
			lastLine = 0;
			++i;
		}
		scannedDigits[k].setPixels(scannedDigits[k].getPixels() - sum);
		sum = 0;
		i = sizeY - 1;
		
		while (i >= scannedDigits[k].getBottomBorder())
		{
			for (unsigned j = scannedDigits[k].getLeftBorder(); j <= scannedDigits[k].getRightBorder(); j++)
			{
				if (dataBit[i][j])
				{
					if (i != scannedDigits[k].getBottomBorder()) sum += 1;
					lastLine += 1;
				}
			}
			if ((i == scannedDigits[k].getBottomBorder()) && (lastLine == 0)) 
			{
				scannedDigits[k].setBottomBorder(i - 1);
				sum += lastLine;
			}
			lastLine = 0;
			--i;
		}
		scannedDigits[k].setPixels(scannedDigits[k].getPixels() - sum);
		sum = 0;
		i = 0;
	}
}

void analyseQuarters(bool dataBit[SIZE][SIZE])
{
	unsigned horMiddle, verMiddle, quarterNumber = 0;
	unsigned width, hight;
	double quarter[4] = {0, 0, 0, 0}; 
	double tempDiff = 0;
	
	for (unsigned k = 0; k < scannedDigits.size(); k++)
	{
		width = scannedDigits[k].getRightBorder() - scannedDigits[k].getLeftBorder() + 1;
		hight = scannedDigits[k].getBottomBorder() - scannedDigits[k].getTopBorder() + 1;
		if ( (width <= 6) || (hight <= 6) )
			scannedDigits[k].addFinal(1, 0, true);
		else 
		{
			verMiddle = scannedDigits[k].getLeftBorder() + width / 2;
			horMiddle = scannedDigits[k].getTopBorder() + hight / 2;

			for (unsigned i = scannedDigits[k].getTopBorder(); i <= scannedDigits[k].getBottomBorder(); i++ )
			{
				for (unsigned j = scannedDigits[k].getLeftBorder(); j <= scannedDigits[k].getRightBorder(); j++)
				{
					if (dataBit[i][j])
					{
						if (i > horMiddle)
							quarterNumber += 2;
						if (j > verMiddle)
							++quarterNumber;
						quarter[quarterNumber] += 1;
						quarterNumber = 0;
					}
				}
			}
			
			scannedDigits[k].setQuatersDistr(quarter[0]/scannedDigits[k].getPixels(), quarter[1]/scannedDigits[k].getPixels(),
				quarter[2]/scannedDigits[k].getPixels(), quarter[3]/scannedDigits[k].getPixels());
			for (unsigned i = 0; i < 10; i++)
			{
				for (unsigned j = 0; j < 4; j++)
				{
					tempDiff += fabs(scannedDigits[k].getQuatersDistr(j) - sampleDigits[i].getQuatersDistr(j));
				}
				scannedDigits[k].addFinal(i, tempDiff, true);
				tempDiff = 0;
			}
			quarter[0] = 0; quarter[1] = 0;
			quarter[2] = 0; quarter[3] = 0;
		}

	}
}

void analyseVerAndHor(bool dataBit[SIZE][SIZE])
{
	unsigned begSecondHor, endSecondHor, begSecondVer, endSecondVer;
	double hor[3] = {0, 0, 0}, ver[3] = {0, 0, 0}; 
	double tempDiff = 0;
	
	for (unsigned k = 0; k <  scannedDigits.size(); k++)
	{
		if (scannedDigits[k].getFinals().size() == 10)
		{
			begSecondHor = scannedDigits[k].getLeftBorder() + 
				(scannedDigits[k].getRightBorder() - scannedDigits[k].getLeftBorder() + 1) / 3;
			endSecondHor = scannedDigits[k].getRightBorder() - 
				(scannedDigits[k].getRightBorder() - scannedDigits[k].getLeftBorder() + 1) / 3;
			begSecondVer = scannedDigits[k].getTopBorder() + 
				(scannedDigits[k].getBottomBorder() - scannedDigits[k].getTopBorder() + 1) / 3;
			endSecondVer = scannedDigits[k].getBottomBorder() - 
				(scannedDigits[k].getBottomBorder() - scannedDigits[k].getTopBorder() + 1) / 3;
			
			for (unsigned i = scannedDigits[k].getTopBorder(); i <= scannedDigits[k].getBottomBorder(); i++ )
			{
				for (unsigned j = scannedDigits[k].getLeftBorder(); j <= scannedDigits[k].getRightBorder(); j++)
				{
					if (dataBit[i][j])
					{
						if (i < begSecondVer) ver[0] += 1;
						else if (i <= endSecondVer) ver[1] += 1;
						else ver[2] += 1;

						if (j < begSecondHor) hor[0] += 1;
						else if (j <= endSecondHor) hor[1] += 1;
						else hor[2] += 1;
					}
				}
			}

			scannedDigits[k].setVerDistr(ver[0]/scannedDigits[k].getPixels(), ver[1]/scannedDigits[k].getPixels(),
				ver[2]/scannedDigits[k].getPixels());
			scannedDigits[k].setHorDistr(hor[0]/scannedDigits[k].getPixels(), hor[1]/scannedDigits[k].getPixels(),
				hor[2]/scannedDigits[k].getPixels());
			
			for (unsigned i = 0; i < 10; ++i)
			{
				for (unsigned j = 0; j < 3; ++j)
				{
					tempDiff += fabs(scannedDigits[k].getVerDistr(j) - sampleDigits[i].getVerDistr(j));
					tempDiff += fabs(scannedDigits[k].getHorDistr(j) - sampleDigits[i].getHorDistr(j));
				}
				scannedDigits[k].addFinal(i, tempDiff, true);
				tempDiff = 0;
			}
			ver[0] = 0; ver[1] = 0; ver[2] = 0;
			hor[0] = 0; hor[1] = 0; hor[2] = 0;
		}
	}
}

void findCircles(bool dataBit[SIZE][SIZE])
{
	bool circle = false, flag = false, top = false, bottom = false;
	unsigned circleLines = 0, countMaxes = 0;
	double hight = 0,  middle = 0;
	double countPixels = 0, countEmptys = 0, possibleEmptyExcess = 0;
	double leftBorder = 0, rightBorder = 0, topBorder = 0, circleRightBorder = 0, circleLeftBorder = 0, 
		distr = 0, lastRB = 0, lastLB = 0, lastCRB = 0, lastCLB = 0;
	vector< pair< double, unsigned > > distrEmpty;
	vector< pair< double, unsigned > > localMins, localMaxes;

	for (unsigned k = 0; k < scannedDigits.size(); k++)
	{
		if (scannedDigits[k].getFinals().size() == 10)
		{
			for (unsigned i = scannedDigits[k].getTopBorder(); i <= scannedDigits[k].getBottomBorder(); i++ )
			{
				for (unsigned j = scannedDigits[k].getLeftBorder(); j <= scannedDigits[k].getRightBorder(); j++)
				{
					if (dataBit[i][j])
					{
						if (leftBorder == 0)
							leftBorder = j;
						if (j > 0) 
							if ( !dataBit[i][j - 1] ) 
								circleRightBorder = j - 1; 
						if (j == scannedDigits[k].getRightBorder())
							rightBorder = j + 1;
						if (possibleEmptyExcess > 0) 
							possibleEmptyExcess = 0;
					}
					else if (leftBorder != 0)
					{
						if (j > 0)
							if (dataBit[i][j - 1])
								rightBorder = j;
						if (j > 0)
							if ( (dataBit[i][j - 1]) && (circleLeftBorder == 0) )
								circleLeftBorder = j;
						possibleEmptyExcess += 1;
						countEmptys += 1;
					}
				}
				if (countEmptys > 0)
					countEmptys -= possibleEmptyExcess;
				possibleEmptyExcess = 0;
				distr = countEmptys / (rightBorder - leftBorder);
				countEmptys = 0;

				if (!circle)
				{
					if (distr <= circleDistr)
					{
						topBorder = i;
						lastLB = leftBorder;
						lastRB = rightBorder;
					}
					else if ( (topBorder != 0)  && ( ((circleLeftBorder - lastLB >= -1) && (lastRB - circleRightBorder >= 0) && (lastLB - leftBorder >= -1) && (rightBorder - lastRB >= -1/*поменяли вместо 0*/)) || 
						((lastLB - circleLeftBorder >= 0)&&(circleRightBorder - lastRB > - 1)) ) )
					{
						circle = true;
						distrEmpty.push_back(make_pair(distr, i));
						++circleLines;
					}
					else
					{
						topBorder = 0;
						lastLB = 0;
						lastRB = 0;
					}
				}
				else
				{
					if (distr > circleDistr)
					{
						distrEmpty.push_back(make_pair(distr, i));
						++circleLines;
						lastCLB = circleLeftBorder;
						lastCRB = circleRightBorder;
					}
					else if ((lastCLB - leftBorder >= -1) && (rightBorder - lastCRB >= -1))
					{
						circle = false;
						circleLines = 0;
						topBorder = i;
						lastLB = leftBorder;
						lastRB = rightBorder;
					}
					else
					{
						lastCLB = 0;
						lastCRB = 0;
						distrEmpty.resize(distrEmpty.size() - circleLines);
						circleLines = 0;
						circle = false;
					}
				}
				rightBorder = leftBorder = circleLeftBorder = circleRightBorder = 0;
			}

			if (distrEmpty.size() <= 3)
			{
				scannedDigits[k].setCircles(0);
			}
			else
			{
				localMaxes.push_back(distrEmpty[0]);
				localMins.push_back(distrEmpty[0]);
				for (unsigned t = 1; t < distrEmpty.size(); t++)
				{
					if (distrEmpty[t].first > localMaxes[countMaxes].first)
					{
						localMaxes.erase(--localMaxes.end());
						localMaxes.push_back(distrEmpty[t]);
						localMins[0] = make_pair(distrLimit * distrEmpty[t].first, distrEmpty[t].second);
						if ((!flag) && (countMaxes == 1) ) flag = true;
					}
					else if (distrEmpty[t].first < localMins[0].first)
					{
						localMins.erase(--localMins.end());
						localMins.push_back(distrEmpty[t]);
						if (localMaxes.size() == 1)
						{
							localMaxes.push_back(distrEmpty[t]);
							countMaxes = 1;
						}
						else if (!flag)
							localMaxes[countMaxes] = distrEmpty[t];
					}
					if ( (t == distrEmpty.size() - 1) && (localMins.size() > 1) )
						localMins.resize(1);
				}
				if (!flag) localMaxes.resize(1);
			}
			
			if (localMaxes.size() == 2) 
			{
				scannedDigits[k].setCircles(2);
				scannedDigits[k].addFinal(8, - finalsKoef * scannedDigits[k].getSum(), false);
			}
			else if (localMaxes.size() == 1)
			{
				scannedDigits[k].setCircles(1);
				middle = (scannedDigits[k].getBottomBorder() + scannedDigits[k].getTopBorder()) / 2;
				hight = scannedDigits[k].getBottomBorder() - scannedDigits[k].getTopBorder() + 1;
				
				if (localMaxes[0].second >= middle + finalsLimit * hight) 
					bottom = true;
				else if (localMaxes[0].second <= middle - finalsLimit * hight)
					top = true;

				if (top)
					scannedDigits[k].addFinal(9, - finalsKoef * scannedDigits[k].getSum(), false);
				else if (bottom)
					scannedDigits[k].addFinal(6, - finalsKoef * scannedDigits[k].getSum(), false);
				else
				{
					scannedDigits[k].addFinal(0, - 0.7 * finalsKoef * scannedDigits[k].getSum(), false);
					scannedDigits[k].addFinal(4, - 0.5 * finalsKoef * scannedDigits[k].getSum(), false);
					scannedDigits[k].addFinal(8, - 0.3 * finalsKoef * scannedDigits[k].getSum(), false);
					scannedDigits[k].addFinal(9, - 0.4 *finalsKoef * scannedDigits[k].getSum(), false);
					scannedDigits[k].addFinal(6, - 0.4 *finalsKoef * scannedDigits[k].getSum(), false);
				}
				top = bottom = false;
			}
			else
			{
				scannedDigits[k].setCircles(0);
				scannedDigits[k].addFinal(1, - finalsKoef * scannedDigits[k].getSum(), false);
				scannedDigits[k].addFinal(2, - finalsKoef * scannedDigits[k].getSum(), false);
				scannedDigits[k].addFinal(3, - finalsKoef * scannedDigits[k].getSum(), false);
				scannedDigits[k].addFinal(4, - 0.4 * finalsKoef * scannedDigits[k].getSum(), false);
				scannedDigits[k].addFinal(5, - finalsKoef * scannedDigits[k].getSum(), false);
				scannedDigits[k].addFinal(7, - finalsKoef * scannedDigits[k].getSum(), false);
			}
			distrEmpty.clear();
			localMaxes.clear();
			localMins.clear();
			countMaxes = 0;
			flag = false;
		}
	}
}

void processResults()
{
	pair< double, unsigned >  min;
	min.first = 100;
	for (unsigned k = 0; k < scannedDigits.size(); k++)
	{
		if (scannedDigits[k].getFinals().size() == 1)
				cout << '1';
		else
		{
			for (unsigned j = 0; j < 10; j++) 
				if (scannedDigits[k].getFinal(j) < min.first)
					min = make_pair(scannedDigits[k].getFinal(j), j);
			cout << min.second;
			min.first = 100;
		}
	}
}	


int main()
{
	unsigned  sizeX, sizeY;
	string data[SIZE];
	bool dataBit[SIZE][SIZE];
	double pixelInVert[SIZE];
	
	DigitSample sample0(0.42, 0.12, 0.46, 0.28, 0.42, 0.3, 0.25, 0.25, 0.25, 0.25, 1);
	sampleDigits.push_back(sample0);
	DigitSample sample1(0.036364, 0.49091, 0.47273, 0.32121, 0.36364, 0.31515, 0.2, 0.33939, 0.1697, 0.29091, 0);
	sampleDigits.push_back(sample1);
	DigitSample sample2(0.28785, 0.35835, 0.35379, 0.36562, 0.19739, 0.43698, 0.21326, 0.27748, 0.28824, 0.22102, 0);
	sampleDigits.push_back(sample2);
	DigitSample sample3(0.25286, 0.22101, 0.52614, 0.32765, 0.30296, 0.36939, 0.18579, 0.334455, 0.17898, 0.30078, 0);
	sampleDigits.push_back(sample3);
	DigitSample sample4(0.21421, 0.41165, 0.37414, 0.23626, 0.37989, 0.38384, 0.19084, 0.24937, 0.22658, 0.33321, 1);
	sampleDigits.push_back(sample4);
	DigitSample sample5(0.27639, 0.34589, 0.37772, 0.33939, 0.34631, 0.31429, 0.31514, 0.27056, 0.14852, 0.26578, 0);
	sampleDigits.push_back(sample5);
	DigitSample sample6(0.35515, 0.31002, 0.33483, 0.27027, 0.39331, 0.33641, 0.30891, 0.22854, 0.25606, 0.20649, 1);
	sampleDigits.push_back(sample6);
	DigitSample sample7(0.24819, 0.5384, 0.21341, 0.53986, 0.20147, 0.25866, 0.29992, 0.34430, 0.33536, 0.02042, 0);
	sampleDigits.push_back(sample7);
	DigitSample sample8(0.37437, 0.29136, 0.33427, 0.29831, 0.40908, 0.29261, 0.23, 0.23, 0.27, 0.27, 2);
	sampleDigits.push_back(sample8);
	DigitSample sample9(0.34529, 0.23365, 0.42106, 0.32751, 0.40969, 0.2628, 0.28288, 0.27216, 0.20168, 0.24328, 1);
	sampleDigits.push_back(sample9);
	
	readFile(data, &sizeX, &sizeY);
	deleteGrey(data, dataBit, sizeX, sizeY, pixelInVert);
	findDigits(dataBit, sizeX, sizeY, pixelInVert);
	countPixels(dataBit, sizeY);
	analyseQuarters(dataBit);
	analyseVerAndHor(dataBit);
	findCircles(dataBit);
	processResults();

	return 0;


}