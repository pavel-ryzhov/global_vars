#include<string>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<string> CharArray;

class NumberAnalyser	
{
	CharArray NumberPicture;
	int ProjectBlack(vector<int> &);
	void FindSpace(vector<int> &, int &, int &);
	int FindMinBrightness(int, int);
	int VectorMin(vector<int> &);
	//void Output (int, int);
public:
	void ReadPicture();
	int Analyse();	
	
};

class DigitAnalyser
{
	CharArray DigitPicture;
	void Edge(int, int, int, int);
	void MaxMin(int &, int &, int &, int &);
	void AddFrame();
	void Skeletonization();
	void Blacken();
	void North();
	void South();
	void West();
	void East();
	bool Connectivity(int, int);
	bool Neighbourhood(int, int);
	bool DeleteDark();
	void Expansion();
	bool RemoveBlackFrame();
	bool Zero();
	bool One();
	void OneBottom(int &, int &);
	void OneTop(int &, int &);
	bool Two();
	bool TwoBottomLeft(int &, int &);
	bool TwoBottomRight(int &, unsigned int &);
	bool TwoRight(int &, int &);
	bool Three();
	bool ThreeGoPoint(int &, int &);
	bool Four();
	bool FourBottom(int &);
	bool Five();
	bool Six();
	bool SixTop(int &);
	bool Seven();
	bool SevenBottom(int, int, int);
	bool Eight();
	void EightDiagram(vector<int> &);
	int EightTopMax(const vector<int> &, int &);
	int EightBottomMax(const vector<int> &, int &);
	int EightMin(const vector<int> &, int, int);
	bool EightBetweenZeros(const vector<int> &, int, int);
	bool Nine();
	bool NineMask(int);
	bool ConnectedComponents(CharArray &);
	void Separate(CharArray &, int, int);
	int CountPictureBlack(CharArray &);
public:
	void LoadPicture(CharArray &);
	void Output ();
	void AnalyseDigit();
	
};
/*
void NumberAnalyser::Output (int Begin, int End)
{
	for (int i = 0; i<NumberPicture.size();i++)
	{
		for (int j = Begin;j<=End;j++)
			cout<<NumberPicture[i][j];
		cout<<endl;
	}
	cout<<endl;
}
*/
void NumberAnalyser::ReadPicture()
{
	string Str = "";
	while (!cin.eof())
	{
		getline(cin, Str);
		if (Str.size() != 0)
			NumberPicture.push_back(Str);
		Str = "";
	}
}

int NumberAnalyser::ProjectBlack(vector<int> &BlackDiagram)
{
	int NumberOfBlack = 0;
	BlackDiagram.assign(NumberPicture[0].size(),0);

	for (int ColumnNumber = 0; ColumnNumber < NumberPicture[0].size(); ColumnNumber++)
	{			
		for (int RowNumber = 0; RowNumber < NumberPicture.size(); RowNumber++)
		{
			if (NumberPicture[RowNumber][ColumnNumber] == '@')
				BlackDiagram[ColumnNumber]++;
		}
	}
	return 0;
}

void NumberAnalyser::FindSpace(vector<int> &BlackDiagram, int &FrontSpace, int &EndSpace)
{
	if (FrontSpace == 0)
	{
		while ((FrontSpace < BlackDiagram.size()-1)&&(BlackDiagram[FrontSpace]==0))
			FrontSpace++;
	}
	else
	{
		FrontSpace = EndSpace;
	}
	while ((FrontSpace < BlackDiagram.size()-1)&&(BlackDiagram[FrontSpace] > 0))
		FrontSpace++;
		EndSpace = FrontSpace;
	while ((EndSpace < BlackDiagram.size()-1)&&(BlackDiagram[EndSpace] == 0))
		EndSpace++;
	
}

int NumberAnalyser::VectorMin(vector<int> &Diagram)
{
	int IndexOfMin = 0;
	int Min = Diagram[0];
	for (int i = 1; i < Diagram.size(); i++)
		if (Diagram[i]<Min)	
		{
			Min = Diagram[i];
			IndexOfMin = i;
		};
	return IndexOfMin;
}

int NumberAnalyser::FindMinBrightness(int FrontSpace, int EndSpace)
{
	int NumberOfColor = 0;
	int IndexOfMin = 0;
	vector<int> Diagram;
	Diagram.assign(EndSpace-FrontSpace,0);

	for (int ColumnNumber = FrontSpace; ColumnNumber < EndSpace; ColumnNumber++)
	{			
		for (int RowNumber = 0; RowNumber < NumberPicture.size(); RowNumber++)
		{
			if (NumberPicture[RowNumber][ColumnNumber] == '#')
				Diagram[ColumnNumber-FrontSpace]+=3;
			if (NumberPicture[RowNumber][ColumnNumber] == '%')
				Diagram[ColumnNumber-FrontSpace]+=1;
		}
	}
	IndexOfMin = VectorMin(Diagram)+ FrontSpace;

	return IndexOfMin;
}

int NumberAnalyser::Analyse()
{
	vector<int> BlackDiagram;
	CharArray DigitPicture;
	DigitAnalyser Digit;
	int FrontDigit = 0, EndDigit = 0, FrontSpace = 0, EndSpace = 0;
	ProjectBlack(BlackDiagram);
	while (EndSpace<NumberPicture[0].size()-1)
	{
		
		FindSpace(BlackDiagram, FrontSpace, EndSpace);
		if (EndSpace<NumberPicture[0].size()-1)
		{
			EndDigit = FindMinBrightness(FrontSpace, EndSpace);
		}
		else
		{
			EndDigit = NumberPicture[0].size()-1;
		}
		for (int RowNumber = 0; RowNumber < NumberPicture.size(); RowNumber++)
		{
			DigitPicture.push_back(NumberPicture[RowNumber].substr(FrontDigit, EndDigit-FrontDigit));
		}
		//Output(FrontDigit,EndDigit-1);
		//cout<<"    3"<<endl;
	
		Digit.LoadPicture(DigitPicture);
		Digit.AnalyseDigit();
		FrontDigit = EndDigit+1;
		DigitPicture.clear();
		//cout<<"    4"<<endl;
	
	}
	return 0;
}

void DigitAnalyser::LoadPicture(CharArray & ExtractedDigit)
{
	DigitPicture = ExtractedDigit;
}


void DigitAnalyser::Output()
{
	for (int i = 0; i < DigitPicture.size(); i++)
		cout<<DigitPicture[i]<<endl;
}



void DigitAnalyser::MaxMin(int &VerticalMin, int &VerticalMax, 
						   int &HorizontalMin, int &HorizontalMax)
{
	int RowNumber = 0, ColumnNumber = 0;
	bool NoEnd = true;
	for (VerticalMin = 0; (VerticalMin < DigitPicture.size())&&(NoEnd); VerticalMin++)
		for (ColumnNumber = 0; (ColumnNumber < DigitPicture[VerticalMin].size())&&NoEnd; 
			ColumnNumber++)
			if (DigitPicture[VerticalMin][ColumnNumber]!='.')
				NoEnd = false;
	VerticalMin--;
	
	NoEnd = true;
	for (VerticalMax = DigitPicture.size()-1; (VerticalMax >= 0 )&&(NoEnd); VerticalMax--)
		for (ColumnNumber = 0; (ColumnNumber < DigitPicture[VerticalMax].size())&&NoEnd; 
			ColumnNumber++)
			if (DigitPicture[VerticalMax][ColumnNumber]!='.')
				NoEnd = false;
	VerticalMax++;
	
	NoEnd = true;
	for (HorizontalMin = 0; (HorizontalMin < DigitPicture[0].size())&&(NoEnd); 
		HorizontalMin++)
		for (RowNumber = 0; (RowNumber < DigitPicture.size())&&(NoEnd); RowNumber++)		
			if (DigitPicture[RowNumber][HorizontalMin]!='.')
				NoEnd = false;
	HorizontalMin--;
	NoEnd = true;
	for (HorizontalMax = DigitPicture[0].size()-1; (HorizontalMax >= 0)&&(NoEnd); 
		HorizontalMax--)
		for (RowNumber = 0; (RowNumber < DigitPicture.size())&&(NoEnd); RowNumber++)		
			if (DigitPicture[RowNumber][HorizontalMax]!='.')
				NoEnd = false;
	HorizontalMax++;		
}
void DigitAnalyser::Edge(int VerticalMin, int VerticalMax, 
						   int HorizontalMin, int HorizontalMax)
{
	CharArray::iterator DPIter;
	if (VerticalMax < (DigitPicture.size() - 1))
	{
		DPIter = DigitPicture.begin();
		DPIter += VerticalMax + 1;
		DigitPicture.erase(DPIter, DigitPicture.end());
	}
	if ((VerticalMin > 0)&&(VerticalMin < DigitPicture.size()))
	{
		DPIter = DigitPicture.begin();
		DPIter += VerticalMin;
		DigitPicture.erase(DigitPicture.begin(), DPIter);
	}
	for (int RowNumber = 0; RowNumber < DigitPicture.size(); RowNumber++)
	{
		DigitPicture[RowNumber] = DigitPicture[RowNumber].substr(HorizontalMin, HorizontalMax - HorizontalMin + 1);
	}
}

void DigitAnalyser::AddFrame()
{
	string PointString;
	for (int RowNumber = 0; RowNumber < DigitPicture.size(); RowNumber++)
	{
		DigitPicture[RowNumber] = '.' + DigitPicture[RowNumber] + '.';
	}
	PointString.assign(DigitPicture[0].size(),'.');
	DigitPicture.push_back(PointString);
	DigitPicture.insert(DigitPicture.begin(),PointString);
}	

void DigitAnalyser::Blacken()
{
	for (int RowNumber = 0; RowNumber < DigitPicture.size(); RowNumber++)
		for (int ColumnNumber = 0; ColumnNumber < DigitPicture[RowNumber].size(); 
			ColumnNumber++)
			if (DigitPicture[RowNumber][ColumnNumber]== '%')
				DigitPicture[RowNumber][ColumnNumber] = '.';
			else if (DigitPicture[RowNumber][ColumnNumber]!= '.')
				DigitPicture[RowNumber][ColumnNumber] = '@';
}

void DigitAnalyser::Skeletonization()
{
	bool NorthNoEnd = true, SouthNoEnd = true, WestNoEnd = true, EastNoEnd = true;
	while (NorthNoEnd||SouthNoEnd||WestNoEnd||EastNoEnd)
	{
		West();
		WestNoEnd = DeleteDark();
		East();
		EastNoEnd = DeleteDark();
		North();
		NorthNoEnd = DeleteDark();
		South();
		SouthNoEnd = DeleteDark();
		
	}
}

void DigitAnalyser::North()
{
	for (int ColumnNumber = 1; ColumnNumber < (DigitPicture[0].size()-1); ColumnNumber++)
		for (int RowNumber = 1; RowNumber < (DigitPicture.size()-1); RowNumber++)
			if ((DigitPicture[RowNumber][ColumnNumber] == '@')&&
				(DigitPicture[RowNumber-1][ColumnNumber] == '.'))
			{
				if (Connectivity(RowNumber, ColumnNumber)&&
					Neighbourhood(RowNumber, ColumnNumber))
					DigitPicture[RowNumber][ColumnNumber] = '#';
			}
}

void DigitAnalyser::South()
{
	for (int ColumnNumber = 1; ColumnNumber < (DigitPicture[0].size()-1); ColumnNumber++)
		for (int RowNumber = DigitPicture.size()-2; RowNumber > 0; RowNumber--)
			if ((DigitPicture[RowNumber][ColumnNumber] == '@')&&
				(DigitPicture[RowNumber+1][ColumnNumber] == '.'))
				if (Connectivity(RowNumber, ColumnNumber)&&
					Neighbourhood(RowNumber, ColumnNumber))
					DigitPicture[RowNumber][ColumnNumber] = '#';
}

void DigitAnalyser::West()
{
	for (int RowNumber = 1; RowNumber < (DigitPicture.size()-1); RowNumber++)
		for (int ColumnNumber = 1; ColumnNumber < (DigitPicture[RowNumber].size()-1); ColumnNumber++)
			if ((DigitPicture[RowNumber][ColumnNumber] == '@')&&
				(DigitPicture[RowNumber][ColumnNumber-1] == '.'))
				if (Connectivity(RowNumber, ColumnNumber)&&
					Neighbourhood(RowNumber, ColumnNumber))
					DigitPicture[RowNumber][ColumnNumber] = '#';
}

void DigitAnalyser::East()
{
	for (int RowNumber = 1; RowNumber < (DigitPicture.size()-1); RowNumber++)
		for (int ColumnNumber = (DigitPicture[RowNumber].size()-2); ColumnNumber > 0; ColumnNumber--)
			if ((DigitPicture[RowNumber][ColumnNumber] == '@')&&
				(DigitPicture[RowNumber][ColumnNumber+1] == '.'))
				if (Connectivity(RowNumber, ColumnNumber)&&
					Neighbourhood(RowNumber, ColumnNumber))
					DigitPicture[RowNumber][ColumnNumber] = '#';
}

bool DigitAnalyser::Neighbourhood(int RowNumber, int ColumnNumber)
{
	int BlackNumber = 0;
	for (int i = RowNumber - 1; i <= (RowNumber + 1); i++)
		for (int j = ColumnNumber - 1; j <= (ColumnNumber + 1); j++)
			if ((DigitPicture[i][j] != '.')&&!((i == RowNumber)&&(j == ColumnNumber)))
				BlackNumber++;
	return (BlackNumber > 1);
}

bool DigitAnalyser::Connectivity(int RowNumber, int ColumnNumber)
{
	bool LastColor;
	bool c11, c21, c31, c32, c33, c23, c13, c12; 
	int CountChanges = 0;
	c11 = DigitPicture[RowNumber-1][ColumnNumber-1]!='.';
	c21 = DigitPicture[RowNumber][ColumnNumber-1]!='.';
	c31 = DigitPicture[RowNumber+1][ColumnNumber-1]!='.';
	c32 = DigitPicture[RowNumber+1][ColumnNumber]!='.';
	c33 = DigitPicture[RowNumber+1][ColumnNumber+1]!='.';
	c23 = DigitPicture[RowNumber][ColumnNumber+1]!='.';
	c13 = DigitPicture[RowNumber-1][ColumnNumber+1]!='.';
	c12 = DigitPicture[RowNumber-1][ColumnNumber]!='.';
	LastColor = c11;
	if (LastColor != c21)
	{	
		CountChanges++;
		LastColor = c21;
	}
	if (LastColor != c31)
	{	
		CountChanges++;
		LastColor = c31;
	}
	if (LastColor != c32)
	{	
		CountChanges++;
		LastColor = c32;
	}
	if (LastColor != c33)
	{	
		CountChanges++;
		LastColor = c33;
	}
	if (LastColor != c23)
	{	
		CountChanges++;
		LastColor = c23;
	}
	if (LastColor != c13)
	{	
		CountChanges++;
		LastColor = c13;
	}
	if (LastColor != c12)
	{	
		CountChanges++;
		LastColor = c12;
	}
	if (LastColor != c11)
	{	
		CountChanges++;
		LastColor = c11;
	}
	if (!c11&&c12&&c21)
	{
		CountChanges -= 2;
	}
	if (!c33&&c32&&c23)
	{
		CountChanges -= 2;
	}
	if (!c31&&c32&&c21)
	{
		CountChanges -= 2;
	}
	if (!c13&&c12&&c23)
	{
		CountChanges -= 2;
	}
	return (CountChanges < 4);
}

bool DigitAnalyser::DeleteDark()
{
	bool Existance = false;
	for (int RowNumber = 0; RowNumber < DigitPicture.size(); RowNumber++)
		for (int ColumnNumber = 0; ColumnNumber < DigitPicture[RowNumber].size(); ColumnNumber++)
			if (DigitPicture[RowNumber][ColumnNumber] == '#')
			{
				DigitPicture[RowNumber][ColumnNumber] = '.';
				Existance = true;
			}
	return Existance;	
}

void DigitAnalyser::Expansion()
{
	int CountInsidePoints = 0;
	for (int RowNumber = 1; RowNumber < (DigitPicture.size()-1); RowNumber++)
		for (int ColumnNumber = 1; ColumnNumber < (DigitPicture[RowNumber].size()-1); ColumnNumber++)
			if ((DigitPicture[RowNumber][ColumnNumber] == '.')&&
				(((DigitPicture[RowNumber-1][ColumnNumber] == '@')&&
				(DigitPicture[RowNumber+1][ColumnNumber] == '@'))||
				((DigitPicture[RowNumber][ColumnNumber-1] == '@')&&
				(DigitPicture[RowNumber][ColumnNumber+1] == '@'))))
			{
				CountInsidePoints++;
				DigitPicture[RowNumber][ColumnNumber] = '#';
			}
/*
	if ((double)CountInsidePoints/(double)DigitPicture.size() > 0.5)
		for (int RowNumber = 1; RowNumber < (DigitPicture.size()-1); RowNumber++)
			for (int ColumnNumber = 1; ColumnNumber < (DigitPicture[RowNumber].size()-1); ColumnNumber++)
				if (DigitPicture[RowNumber][ColumnNumber] == '@')
				{
					if (DigitPicture[RowNumber-1][ColumnNumber] == '.')
						DigitPicture[RowNumber-1][ColumnNumber] = '#';
					if (DigitPicture[RowNumber+1][ColumnNumber] == '.')
						DigitPicture[RowNumber+1][ColumnNumber] = '#';
					if (DigitPicture[RowNumber][ColumnNumber-1] == '.')
						DigitPicture[RowNumber][ColumnNumber-1] = '#';
					if (DigitPicture[RowNumber][ColumnNumber+1] == '.')
						DigitPicture[RowNumber][ColumnNumber+1] = '#';
				}
				*/
}

bool DigitAnalyser::Zero()
{
	int RowNumberFirst = 1, ColumnNumberFirst = 1;
	int LastPointRow = 0, LastPointColumn = 0;
	int NextPointRow = 0, NextPointColumn = 0;
	int PointRow = 0, PointColumn = 0;
	int BlackNumber = 0;
	for (RowNumberFirst = 1; (RowNumberFirst < (DigitPicture.size()-1))&&
		(DigitPicture[RowNumberFirst-1][ColumnNumberFirst] == '.'); RowNumberFirst++)
		for (ColumnNumberFirst = 1; (ColumnNumberFirst < (DigitPicture[RowNumberFirst].size()-1))&&
			(DigitPicture[RowNumberFirst][ColumnNumberFirst] == '.'); ColumnNumberFirst++);
	RowNumberFirst--;
	PointRow = RowNumberFirst;
	PointColumn = ColumnNumberFirst;
	
	do
	{	
		BlackNumber = 0;
		for (int i = PointRow - 1; i <= (PointRow + 1); i++)
			for (int j = PointColumn - 1; j <= (PointColumn + 1); j++)
				if ((DigitPicture[i][j] != '.')&&!((i == PointRow)&&(j == PointColumn)))
				{
					BlackNumber++;
					if (i != LastPointRow || j != LastPointColumn)
					{
						NextPointRow = i;
						NextPointColumn = j;
					}
				}
		if (BlackNumber != 2) 
			return false;
		LastPointRow = PointRow;
		LastPointColumn = PointColumn;
		PointRow = NextPointRow;
		PointColumn = NextPointColumn;
		//cout<<PointRow<<' '<<PointColumn<<' '<<(!(PointRow == RowNumberFirst && PointColumn == ColumnNumberFirst))<<endl;
	} while (!(PointRow == RowNumberFirst && PointColumn == ColumnNumberFirst));
	return true;
}


bool DigitAnalyser::One()
{
	int CountBlack = 0;
	int StartColumn = 0, BottomColumn = 0, BottomRow = 0;
	int TopRow = 0, TopColumn = 0;
	int StartRow = DigitPicture.size()/2;
	for (int ColumnNumber = 1; ColumnNumber < DigitPicture[StartRow].size(); ColumnNumber++)
		if (DigitPicture[StartRow][ColumnNumber] == '@')
		{
			StartColumn = ColumnNumber;
			CountBlack++;
		}
	//	cout<<1111111<<endl;
	if (CountBlack != 1)
		return false;
	BottomColumn = StartColumn;
	BottomRow = StartRow;
	TopColumn = StartColumn;
	TopRow = StartRow;
	
	OneBottom(BottomRow, BottomColumn);
	OneTop(TopRow, TopColumn);

	//cout<<BottomRow<< ' '<<TopRow<<' '<< (double)(DigitPicture.size()-2)/4<<' '<<DigitPicture.size()<<endl;
	if (DigitPicture.size()- 1 - BottomRow > (double)(DigitPicture.size()-2)/4)
		return false;
	if (TopRow - 1 > (double)(DigitPicture.size()-2)/4)
		return false;
	
	return true;

}

void DigitAnalyser::OneBottom(int &Row, int &Column)
{
	bool Strightness = true, LastLeft = true;
	int CountStright = 5,
	CountBlack = 0;
	if (DigitPicture[Row+1][Column-1] == '@')
		CountBlack++;
	if (DigitPicture[Row+1][Column] == '@')
		CountBlack++;
	if (DigitPicture[Row+1][Column+1] == '@')
		CountBlack++;
	while (Strightness && CountBlack == 1)
	{
		if (DigitPicture[Row+1][Column-1] == '@')
		{
			if (CountStright >= 5 || !LastLeft)
			{
				Row++;
				Column--;
				if (!LastLeft)
					CountStright++;
				else
					CountStright = 1;
			}
			else
				Strightness = false;
			LastLeft = true;
		}
		if (DigitPicture[Row+1][Column] == '@')
		{
			Row++;
			CountStright++;
			
		}
		if (DigitPicture[Row+1][Column+1] == '@')
		{
			if (CountStright >= 5 || LastLeft)
			{
				Row++;
				Column++;
				if (LastLeft)
					CountStright++;
				else
					CountStright = 1;
			}
			else
				Strightness = false;
			LastLeft = false;
		}
		
		CountBlack = 0;
		if (DigitPicture[Row+1][Column-1] == '@')
			CountBlack++;
		if (DigitPicture[Row+1][Column] == '@')
			CountBlack++;
		if (DigitPicture[Row+1][Column+1] == '@')
			CountBlack++;
		
	}

}

void DigitAnalyser::OneTop(int &Row, int &Column)
{
	bool Strightness = true, LastLeft = true;
	int CountStright = 5,
	CountBlack = 0;
	if (DigitPicture[Row-1][Column-1] == '@')
		CountBlack++;
	if (DigitPicture[Row-1][Column] == '@')
		CountBlack++;
	if (DigitPicture[Row-1][Column+1] == '@')
		CountBlack++;
	while (Strightness && CountBlack == 1)
	{
		if (DigitPicture[Row-1][Column-1] == '@')
		{
			if (CountStright >= 5 || !LastLeft)
			{
				Row--;
				Column--;
				if (!LastLeft)
					CountStright++;
				else
					CountStright = 1;
			}
			else
				Strightness = false;
			LastLeft = true;
		}
		if (DigitPicture[Row-1][Column] == '@')
		{
			Row--;
			CountStright++;
			
		}
		if (DigitPicture[Row-1][Column+1] == '@')
		{
			if (CountStright >= 5 || LastLeft)
			{
				Row--;
				Column++;
				if (LastLeft)
					CountStright++;
				else
					CountStright = 1;
			}
			else
				Strightness = false;
			LastLeft = false;
		}
		CountBlack = 0;
		if (DigitPicture[Row-1][Column-1] == '@')
			CountBlack++;
		if (DigitPicture[Row-1][Column] == '@')
			CountBlack++;
		if (DigitPicture[Row-1][Column+1] == '@')
			CountBlack++;
				
	}

}


bool DigitAnalyser::Two()
{
	int Row = 1, Column = 0;
	int StartRow = 0, StartColumn = 0;
	int EndRow = 0, EndColumn = 0;
	string::size_type StartBlack = 0, EndBlack = 0;
	StartBlack = DigitPicture[Row].find_first_of('@');
	EndBlack = DigitPicture[Row].find_last_of('@');
	while (StartBlack!=string::npos &&
		StartBlack == EndBlack)
	{
		Row++;
		StartBlack = DigitPicture[Row].find_first_of('@');
		EndBlack = DigitPicture[Row].find_last_of('@');
	}
	if (StartBlack==string::npos)
		return false;
	while (StartBlack!=string::npos &&
		StartBlack < EndBlack)
	{
		Row++;
		StartBlack = DigitPicture[Row].find_first_of('@');
		EndBlack = DigitPicture[Row].find_last_of('@');
	}
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (StartBlack==string::npos)
		return false;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (!TwoBottomRight(Row, StartBlack))
		return false;
	StartRow = Row;
	StartColumn = StartBlack;
	EndRow = StartRow;
	EndColumn = StartColumn;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (!TwoBottomLeft(EndRow, EndColumn))
		return false;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (EndRow - StartRow < DigitPicture.size()/5)
		return false;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if ((EndRow - StartRow)/(StartColumn -  EndColumn) > 2 * DigitPicture.size()/DigitPicture[0].size())
		return false;
	StartRow = EndRow;
	StartColumn = EndColumn;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (StartRow <= 2/3*DigitPicture.size())
		return false;
	if (!TwoRight(EndRow, EndColumn))
		return false;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	if (EndColumn - StartColumn < (3/5)*DigitPicture[0].size())
		return false;
	//cout<<StartRow<<' '<<StartColumn<<endl<<endl<<EndRow<<' '<<EndColumn<<endl;
	return true;
	
}

bool DigitAnalyser::TwoBottomLeft(int &Row, int &Column)
{
	bool Left, LeftBottom, Bottom, RightBottom;
	int CountBlack;
	Left = DigitPicture[Row][Column-1] == '@';
	LeftBottom = DigitPicture[Row+1][Column-1] == '@';
	Bottom = DigitPicture[Row+1][Column] == '@';
	RightBottom = DigitPicture[Row+1][Column+1] == '@';
	//Way = Right || RightBottom || Bottom || LeftBottom;
	CountBlack = 0;
	CountBlack = Left + LeftBottom + Bottom + RightBottom;
	while (CountBlack == 1 && !RightBottom)
	{
		if (LeftBottom)
		{
			Column--;
			Row++;
		}
		if (Left)
		{
			Column--;
		}
		if (Bottom)
		{
			Row++;
		}
		Left = DigitPicture[Row][Column-1] == '@';
		LeftBottom = DigitPicture[Row+1][Column-1] == '@';
		Bottom = DigitPicture[Row+1][Column] == '@';
		RightBottom = DigitPicture[Row+1][Column+1] == '@';
		//Way = Right || RightBottom || Bottom || LeftBottom;
		CountBlack = 0;
		CountBlack = Left + LeftBottom + Bottom + RightBottom;
	}
	if (CountBlack == 1 && RightBottom)
		return true;
	if (CountBlack == 2 && RightBottom)
		return true;
	if (CountBlack == 2 && Bottom && LeftBottom)
	{	
		Row++;
		return true;
	}
	return false;
}

bool DigitAnalyser::TwoBottomRight(int &Row, unsigned int &Column)
{
	bool Right, RightBottom, Bottom, LeftBottom;
	int CountBlack;
	Right = DigitPicture[Row][Column+1] == '@';
	RightBottom = DigitPicture[Row+1][Column+1] == '@';
	Bottom = DigitPicture[Row+1][Column] == '@';
	LeftBottom = DigitPicture[Row+1][Column-1] == '@';
	//Way = Right || RightBottom || Bottom || LeftBottom;
	CountBlack = 0;
	CountBlack = Right + RightBottom + Bottom + LeftBottom;
	while (CountBlack == 1 && !LeftBottom)
	{
		if (RightBottom)
		{
			Column++;
			Row++;
		}
		if (Right)
		{
			Column++;
		}
		if (Bottom)
		{
			Row++;
		}
		Right = DigitPicture[Row][Column+1] == '@';
		RightBottom = DigitPicture[Row+1][Column+1] == '@';
		Bottom = DigitPicture[Row+1][Column] == '@';
		LeftBottom = DigitPicture[Row+1][Column-1] == '@';
		//Way = Right || RightBottom || Bottom || LeftBottom;
		CountBlack = 0;
		CountBlack = Right + RightBottom + Bottom + LeftBottom;
	}
	if (CountBlack != 1)
		return false;
	else
		return true;
}

bool DigitAnalyser::TwoRight(int &Row, int &Column)
{
	bool Way = true;
	while(Way)
	{
		Way = false;
		if (DigitPicture[Row-1][Column+1] == '@')
		{
			Row--;
			Column++;
			Way = true;
		}	
		if (DigitPicture[Row][Column+1] == '@')
		{
			Column++;	
			Way = true;
		}
		if (DigitPicture[Row+1][Column+1] == '@')
		{
			Row++;
			Column++;
			Way = true;
		}
		if (DigitPicture[Row+1][Column] == '@')
		{
			return false;
		}
	}
	return true;
}

bool DigitAnalyser::Three()
{
	string::size_type EndBlack = 0, LastEndBlack = 0;
	EndBlack = DigitPicture[1].find_last_of('@');
	int Row = 1, Column = 0, RowMin = 0;
	unsigned int TopMax, Min, BottomMax;
	while (EndBlack >= LastEndBlack && EndBlack != string::npos)
	{
		Row++;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		
	}
	//cout<<"     1"<<endl;
	if (EndBlack == string::npos)
		return false;
	TopMax = LastEndBlack;
	//cout<<"     2"<<endl;
	while (EndBlack <= LastEndBlack && EndBlack != string::npos)
	{
		Row++;
		if (LastEndBlack - EndBlack > 3)
			return false;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		
		
	}
	//cout<<"     3"<<endl;
	if (EndBlack == string::npos)
		return false;
	Min = LastEndBlack;
	RowMin = Row - 1;
	//cout<<"     4"<<endl;
	if (TopMax - Min < 1)
		return false;
	//cout<<"     5"<<endl;
	while (EndBlack >= LastEndBlack && EndBlack != string::npos)
	{
		Row++;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
	}
	if (EndBlack == string::npos)
		return false;
	BottomMax = LastEndBlack;
	if (BottomMax - Min < 2)
		return false;
	Column = LastEndBlack;
	Row--;
	if (!ThreeGoPoint(Row, Column))
		return false;
	if (RowMin >= Row)
		return false;
	
	return true;
}

bool DigitAnalyser::ThreeGoPoint(int &Row, int &Column)
{
	int LastRow = 0, LastColumn = 0;
	int NextRow = 0, NextColumn = 0;
	int RowFirst = Row, ColumnFirst = Column;
	int BlackNumber = 0;
	for (int j = Column - 1; j <= (Column + 1); j++)
		if (DigitPicture[Row-1][j] != '.')
		{
			LastColumn = j;
			LastRow = Row-1;
		}
	if (LastColumn == 0)
		return false;
			
	//cout<<Row<<' '<<Column<<' '<<LastRow<<' '<<Last' '<<Column
	do
	{	
		BlackNumber = 0;
		for (int i = Row - 1; i <= (Row + 1); i++)
			for (int j = Column - 1; j <= (Column + 1); j++)
				if ((DigitPicture[i][j] != '.')&&!((i == Row)&&(j == Column)))
				{
					BlackNumber++;
					if (i != LastRow || j != LastColumn)
					{
						NextRow = i;
						NextColumn = j;
					}
				}
		if (BlackNumber > 2) 
			return false;
		if (BlackNumber == 1) 
			return true;
		
		LastRow = Row;
		LastColumn = Column;
		Row = NextRow;
		Column = NextColumn;
		//cout<<Row<<' '<<Column<<' '<<(!(Row == RowNumberFirst && Column == ColumnNumberFirst))<<endl;
	} while (!(Row == RowFirst && Column == ColumnFirst));
	if (Row == RowFirst && Column == ColumnFirst)
		return false;
	return true;
}

bool DigitAnalyser::Four()
{
	string::size_type StartBlack = 0, EndBlack = 0;
	string::size_type LastEndBlack = 0, LastStartBlack = 0;
	int CountBlack = 0;
	int Row = 1, Column = 0, RowMin = 0;
	
	LastEndBlack = DigitPicture[1].find_last_of('@');
	LastStartBlack = DigitPicture[1].find_first_of('@');
	EndBlack = DigitPicture[2].find_last_of('@');
	StartBlack = DigitPicture[2].find_first_of('@');
	if (EndBlack == string::npos)
		return false;
	//if (EndBlack > LastEndBlack + 1 || StartBlack < LastStartBlack - DigitPicture[0].size()/7)
	//	return false;
	for (Column = 1; Column < (DigitPicture[1].size()-1);Column++)
		if (DigitPicture[1][Column] == '@')
			CountBlack++;
	//if (CountBlack > DigitPicture[0].size()/6)
	//	return false;
		
	
	//unsigned int TopMax, Min, BottomMax;
	while (CountBlack == 1)
	{
		Row++;
		CountBlack = 0;
		for (Column = 1; Column < (DigitPicture[Row].size()-1);Column++)
			if (DigitPicture[Row][Column] == '@')
				CountBlack++;
	}
	if (CountBlack = 0)
		return false;
	EndBlack = DigitPicture[Row].find_last_of('@');
	StartBlack = DigitPicture[Row].find_first_of('@');
	
	while (EndBlack > StartBlack && EndBlack != string::npos)
	{
		Row++;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
			
	}
	if (EndBlack == string::npos)
		return false;
	if (!FourBottom(Row))
		return false;
	return true;
}

bool DigitAnalyser::FourBottom(int &Row)
{
	string LittleMask;
	string::size_type StartBlack = 0, EndBlack = 0;
	bool ExistBlack = true;
	int LengthStroke = 0;
	LittleMask = DigitPicture[Row];
	for (int i = Row - 1; i > (double)Row - (double)Row/6 && ExistBlack; i--)
	{
		ExistBlack = false;
		for (int Column = 1; Column < DigitPicture[i].size() - 1; Column++)
			if (DigitPicture[i][Column] == '@')
			{
				ExistBlack = true;
				LittleMask[Column]='@';
			}
	}

	EndBlack = LittleMask.find_last_of('@');
	StartBlack = LittleMask.find_first_of('@');
	if (EndBlack - StartBlack < 3/5 * LittleMask.size())
		return false;
	if (LittleMask.substr(StartBlack, EndBlack - StartBlack +1).find('.')!=
		string::npos)
		return false;
	StartBlack = EndBlack;
	while (EndBlack == StartBlack && EndBlack != string::npos)
	{
		Row++;
		LengthStroke++;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
			
	}
	if (DigitPicture.size()- Row > (double)DigitPicture.size()/4)
		return false;
	if (LengthStroke < 2)
		return false;
	return true;

}

bool DigitAnalyser::Five()
{
	string::size_type StartBlack = 0, EndBlack = 0;
	string::size_type LastStartBlack = 0, LastEndBlack = 0;
	EndBlack = DigitPicture[1].find_last_of('@');
	StartBlack = DigitPicture[1].find_first_of('@');
	int Row = 1, BottomPointColumn = 0, BottomPointRow = 0;
	//unsigned int TopMax, Min, BottomMax;
	while (EndBlack == StartBlack && EndBlack != string::npos)
	{
		Row++;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
	}
	//cout<<"     1"<<endl;
	if (EndBlack == string::npos)
		return false;
	LastStartBlack = StartBlack;
	LastEndBlack = EndBlack;
	while (EndBlack > StartBlack && EndBlack != string::npos)
	{
		Row++;
		LastStartBlack = StartBlack;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
	}
	//cout<<"     2"<<endl;
	if (EndBlack == string::npos)
		return false;
	//cout<<"     2"<<endl;
	
	if (EndBlack > (LastEndBlack + LastStartBlack) / 2)
		return false;
	while (EndBlack == StartBlack && EndBlack != string::npos)
	{
		Row++;
		LastStartBlack = StartBlack;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
	}
	//cout<<"     3"<<endl;
	if (EndBlack == string::npos)
		return false;
	if (LastEndBlack > (EndBlack + StartBlack) / 2)
		return false;

	while (EndBlack > StartBlack && EndBlack != string::npos)
	{
		Row++;
		LastStartBlack = StartBlack;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
	}
	//cout<<"     4"<<endl;
	
	if (EndBlack == string::npos)
		return false;
	if (EndBlack < (LastEndBlack + LastStartBlack) / 2)
		return false;
	BottomPointColumn = EndBlack;
	BottomPointRow = Row;
	//cout<<"     6"<<endl;
	
	if (!ThreeGoPoint(BottomPointRow, BottomPointColumn))
		return false;
	if (BottomPointRow < Row ||
		(double)(EndBlack - BottomPointColumn) / (BottomPointRow - Row) < 0.2)
		return false;
	return true;
	
}


bool DigitAnalyser::Six()
{
	string::size_type StartBlack = 0, EndBlack = 0;
	int Row = DigitPicture.size() - 3;
	int StartRow = Row;
	int Length = 0, LastLength = 0;
	EndBlack = DigitPicture[Row].find_last_of('@');
	StartBlack = DigitPicture[Row].find_first_of('@');
	int MaxBlack = DigitPicture[Row+1].find_last_of('@');
	int MinBlack = DigitPicture[Row+1].find_first_of('@');
	Length = EndBlack - StartBlack;
	LastLength = MaxBlack - MinBlack;
	//cout<<"     1"<<endl;
	if (EndBlack == string::npos ||
		DigitPicture[Row+1].substr(MinBlack, MaxBlack - MinBlack + 1).find('.') !=
		string::npos)
		return false;
	if (DigitPicture[Row].substr(StartBlack, EndBlack - StartBlack + 1).find('.') ==
		string::npos)
		return false;
	while (EndBlack > StartBlack && EndBlack != string::npos &&
		Length >= LastLength)
	{
		if (MaxBlack < EndBlack)
			MaxBlack = EndBlack;
		if (MinBlack > StartBlack)
			MinBlack = StartBlack;
		Row--;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
		LastLength = Length;
		Length = EndBlack - StartBlack;
	}
	//cout<<"     2"<<endl;
	if (EndBlack == StartBlack || EndBlack == string::npos)
		return false;
	//cout<<"     3"<<endl;
	
	while (EndBlack > StartBlack && EndBlack != string::npos)// &&		Length <= LastLength)
	{
		if (MaxBlack < EndBlack)
			MaxBlack = EndBlack;
		if (MinBlack > StartBlack)
			MinBlack = StartBlack;
		Row--;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
		LastLength = Length;
		Length = EndBlack - StartBlack;
	}
	//cout<<"     4"<<endl;
	
	if (EndBlack == string::npos)// || Length > LastLength)
		return false;
	//cout<<"     5"<<MaxBlack<<' '<<MinBlack<<' '<<EndBlack<<endl;
	
	if ((double)(MaxBlack - MinBlack) / 3 < (double)(EndBlack - MinBlack))
		return false;
	//cout<<"     6"<<endl;
	if (StartRow - Row <= 3)
		return false;
	if (!SixTop(Row))
		return false;
	return true;
	
}

bool DigitAnalyser::SixTop(int &Row)
{
	Row--;
	string::size_type EndBlack = DigitPicture[Row].find_last_of('@');
	string::size_type StartBlack = DigitPicture[Row].find_first_of('@');
	if (EndBlack != StartBlack || EndBlack == string::npos)
		return false;
	Row--;
	string::size_type LastStartBlack = StartBlack;
	StartBlack = DigitPicture[Row].find_first_of('@');
	while (StartBlack >= LastStartBlack && StartBlack != string::npos)
	{
		Row--;
		LastStartBlack = StartBlack;
		StartBlack = DigitPicture[Row].find_first_of('@');
	}
	if (StartBlack < LastStartBlack && StartBlack != string::npos)
		return false;
	return true;
}

bool DigitAnalyser::Seven()
{
	int Column = 0, Row = 0, CountBlack = 1, CountRow = 0, CountTopBlack = 0;
	int MaxBlack = 0, MaxBlackRow = 0;
	while (CountBlack < 3 && CountBlack > 0)
	{
		Row++;
		CountBlack = 0;
		for (Column = 0; Column < DigitPicture[Row].size(); Column++)
			if (DigitPicture[Row][Column] == '@')
				CountBlack++;
	}
	if (CountBlack == 0)
		return false;
	CountTopBlack += CountBlack;
	while (CountBlack >= 3 && CountRow < 2)
	{
		Row++;
		CountBlack = 0;
		CountRow++;
		for (Column = 0; Column < DigitPicture[Row].size(); Column++)
			if (DigitPicture[Row][Column] == '@')
			{
				CountBlack++;
				if (Column > MaxBlack)
				{
					MaxBlack = Column;
					MaxBlackRow = Row;
				}
			}
		CountTopBlack += CountBlack;
	}
	//cout<<"    "<<CountTopBlack<<"    "<<DigitPicture[0].size()<<endl;
	if (CountBlack == 0 || CountTopBlack < DigitPicture[0].size() * 5 / 8 - 1)
		return false;
	while (CountBlack >= 2)
	{
		Row++;
		CountBlack = 0;
		for (Column = 0; Column < DigitPicture[Row].size(); Column++)
			if (DigitPicture[Row][Column] == '@')
			{
				CountBlack++;
				if (Column > MaxBlack)
				{
					MaxBlack = Column;
					MaxBlackRow = Row;
				}
			}
		
	}
	if (CountBlack == 0 ||
		Row > DigitPicture.size()/3)
		return false;
	if (!SevenBottom(Row, MaxBlack, MaxBlackRow))
		return false;
	return true;
}

bool DigitAnalyser::SevenBottom(int Row, int MaxBlack, int MaxBlackRow)
{
	int CountBlack = 1;
	int Column, EndBlack = 0, LastEndBlack = 0;
	for (Column = 0; Column < DigitPicture[Row].size(); Column++)
		if (DigitPicture[Row][Column] == '@')
			EndBlack = Column;		
	LastEndBlack = EndBlack;
	while (CountBlack == 1 && LastEndBlack >= EndBlack)
	{
		Row++;
		CountBlack = 0;
		LastEndBlack = EndBlack;
		for (Column = 0; Column < DigitPicture[Row].size(); Column++)
			if (DigitPicture[Row][Column] == '@')
			{
				CountBlack++;
				EndBlack = Column;
			}
	}
	//cout<<"    1 "<<CountBlack<<' '<<Row<<endl;
	
	//cout<<"    1 "<<MaxBlack<<' '<<LastEndBlack<<' '<<Row<<' '<<MaxBlackRow<<endl;
	
	if ((double)(MaxBlack - LastEndBlack)/(Row - MaxBlackRow) <= 0.2 ||
		Row - MaxBlackRow < (double)DigitPicture.size()/3)
		return false;
	if (CountBlack == 0)
		if (Row >= DigitPicture.size() - 3)
			return true;
		else
			return false;
	string::size_type FrontBlack = 0, BackBlack = 0;
	BackBlack = DigitPicture[Row].find_last_of('@');
	FrontBlack = DigitPicture[Row].find_first_of('@');
	while (BackBlack - LastEndBlack <= (double)DigitPicture[0].size()/4 &&
		LastEndBlack - FrontBlack <= (double)DigitPicture[0].size()/4 && 
		BackBlack != string::npos)
	{
		Row++;
		BackBlack = DigitPicture[Row].find_last_of('@');
		FrontBlack = DigitPicture[Row].find_first_of('@');

		
	}
	if (BackBlack == string::npos)
		if (Row < DigitPicture.size() - 3)
			return false;
		else
			return true;

	//cout<<"    1"<<BackBlack<<' '<<LastEndBlack<<' '<<DigitPicture[0].size()<<endl;
	if (BackBlack - LastEndBlack > (double)DigitPicture[0].size()/4 ||
		LastEndBlack - FrontBlack > (double)DigitPicture[0].size()/4) 
		return false;

	return true;
}

bool DigitAnalyser::Eight()
{
	vector<int> InteriorDiagram;
	EightDiagram(InteriorDiagram);
	int TopMaxRow = 0;
	int Min, TopZero = 0, BottomZero = 0;
	int TopMax = EightTopMax(InteriorDiagram, TopMaxRow);
	int BottomMaxRow = 0;
	int BottomMax = EightBottomMax(InteriorDiagram, BottomMaxRow);
	//cout<<"    1 "<<endl; 
	if (TopMax < DigitPicture[0].size()/4 ||
		BottomMax < DigitPicture[0].size()/4)
		return false;
	//cout<<"    2 "<<endl;
	if (TopMaxRow >= (double)DigitPicture.size() * 9 / 20 ||
		BottomMaxRow <= (double)DigitPicture.size() * 11 / 20)
		return false;
	Min = EightMin(InteriorDiagram, TopMaxRow, BottomMaxRow);
	//cout<<"    3 "<<endl;
	if (Min >= TopMax - 1 ||
		Min >= BottomMax - 1)
		return false;
	//cout<<"    4 "<<endl;
	if (Min > 0)
		return true;
	TopZero = TopMaxRow;
	BottomZero = BottomMaxRow;
	while (InteriorDiagram[TopZero]>0)
		TopZero++;
	while (InteriorDiagram[BottomZero]>0)
		BottomZero--;
	//cout<<"    5 "<<endl;
	if (BottomZero - TopZero > 4)
		return false;
	//cout<<"    6 "<<endl;
	if (!EightBetweenZeros(InteriorDiagram, TopZero, BottomZero))
		return false;
	//cout<<"    7 "<<endl;
	if (DigitPicture[BottomZero].find_first_of('@') - DigitPicture[BottomZero + 1].find_first_of('@') > 3 ||
		DigitPicture[BottomZero + 1].find_last_of('@') - DigitPicture[BottomZero].find_last_of('@') > 3 ||
		DigitPicture[TopZero].find_first_of('@') - DigitPicture[TopZero - 1].find_first_of('@') > 3 ||
		DigitPicture[TopZero - 1].find_last_of('@') - DigitPicture[TopZero].find_last_of('@') > 3)
		return false;
	return true;
}

void DigitAnalyser::EightDiagram(vector<int> &Diagram)
{
	string::size_type BeginBlack = 0, EndBlack = 0;
	Diagram.assign(DigitPicture.size(), 0);
	for (int Row = 0; Row < Diagram.size(); Row++)
	{
		BeginBlack = DigitPicture[Row].find_first_of('@');
		EndBlack = DigitPicture[Row].find_last_of('@');
		if (BeginBlack != string::npos)
		{
			for (int Column = BeginBlack + 1; Column < EndBlack; Column++)
				if (DigitPicture[Row][Column] == '.')
					Diagram[Row]++;
		}
	}
}

int DigitAnalyser::EightTopMax(const vector<int> &Diagram, int &RowMax)
{
	int Max = 0;
	RowMax = Diagram.size()/2;
	for (int Row = 1; Row <= Diagram.size()/2; Row++)
		if (Diagram[Row]>Max)
		{
			Max = Diagram[Row];
			RowMax = Row;
		}
	return Max;
}

int DigitAnalyser::EightBottomMax(const vector<int> &Diagram, int &RowMax)
{
	int Max = 0;
	RowMax = Diagram.size()/2;
	for (int Row = Diagram.size()-1; Row >= Diagram.size()/2; Row--)
		if (Diagram[Row]>Max)
		{
			Max = Diagram[Row];
			RowMax = Row;
		}
	return Max;
}
int DigitAnalyser::EightMin(const vector<int> &Diagram, int Start, int Finish)
{
	int Min = DigitPicture[0].size();
	for (int Row = Start; Row <= Finish; Row++)
		if (Diagram[Row] < Min)
			Min = Diagram[Row];
	return Min;
}
bool DigitAnalyser::EightBetweenZeros(const vector<int> &Diagram,
									  int Start, int Finish)
{
	for (int Row = Start; Row <= Finish; Row++)
		if (Diagram[Row] > 0)
			return false;
	return true;
}
bool DigitAnalyser::Nine()
{
	string::size_type EndBlack = 0, LastEndBlack = 0, StartBlack = 0;
	EndBlack = DigitPicture[1].find_last_of('@');
	StartBlack = DigitPicture[1].find_first_of('@');
	
	int Row = 1, Column = 0, Groth = 0, RowStart = 0;
	//unsigned int TopMax, Min, BottomMax;
	int Width = EndBlack - StartBlack;
	while (EndBlack >= LastEndBlack && EndBlack != string::npos)
	{
		Row++;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
		if (Width < EndBlack - StartBlack)
			Width = EndBlack - StartBlack;
	}
	//cout<<"     1"<<endl;
	if (EndBlack == string::npos)
		return false;
	//TopMax = LastEndBlack;
	//cout<<"     2"<<endl;
	if (Width <= DigitPicture[0].size()/2)
		return false;
	//RowMem = Row;
	//EndBlackMem = EndBlack;
	while (EndBlack != string::npos)
	{
		Row++;
		if (LastEndBlack < EndBlack)
			Groth += EndBlack - LastEndBlack;
		LastEndBlack = EndBlack;
		EndBlack = DigitPicture[Row].find_last_of('@');
	}
	//cout<<"     3"<<endl;
	if (Groth > 2)
		return false;
	Row = 1;
	EndBlack = DigitPicture[Row].find_last_of('@');
	StartBlack = DigitPicture[Row].find_first_of('@');
	
	while (StartBlack == EndBlack && EndBlack != string::npos)
	{
		Row++;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
		
	}
	
	if (EndBlack == string::npos)
		return false;
	//EndBlack = EndBlackMem;
	
	while (StartBlack < EndBlack && EndBlack != string::npos)
	{
		Row++;
		EndBlack = DigitPicture[Row].find_last_of('@');
		StartBlack = DigitPicture[Row].find_first_of('@');
		
	}
	if (Row <= DigitPicture.size()/3 ||
		EndBlack == string::npos)
		return false;
	//string LittleMask = DigitPicture[0];
	if (!NineMask(Row - 1))
		return false;
	Row++;
	RowStart = Row;
	EndBlack = DigitPicture[Row].find_last_of('@');
	Column = EndBlack;
	
	
	if (!ThreeGoPoint(Row, Column))
		return false;
	if (RowStart >= Row ||
		Column >= EndBlack - 1)
		return false;
	
	return true;
}

bool DigitAnalyser::NineMask(int RowBottom)
{
	int CountBlack = 0;
	string Mask = DigitPicture[0];
	for (int Row = RowBottom; Row > (RowBottom + 1) / 2 ; Row--)
		for (int Column = 0; Column < DigitPicture[Row].size(); Column++)
			if (DigitPicture[Row][Column] == '@')
				Mask[Column] = '@';
	for (int Column = 0; Column < DigitPicture[0].size(); Column++)
		if (Mask[Column] == '@')
			CountBlack++;
	if (CountBlack < (double)5/6 * (Mask.size() - 2) )
		return false;
	
	return true;
}


bool DigitAnalyser::RemoveBlackFrame()
{
	int Row = 0, Column = 0;
	if (DigitPicture.size()< 3)
		return false;
	if (DigitPicture[0].size()< 5)
		return false;
	
	for (Column = DigitPicture[0].size()/4; Column <= 3*DigitPicture[0].size()/4; Column++)
		if (DigitPicture[0][Column] != '@' ||
			DigitPicture[DigitPicture.size() - 1][Column] != '@')
			return false;
	for (Row = DigitPicture.size()/4; Row <= 3*DigitPicture.size()/4; Row++)
		if (DigitPicture[Row][0] != '@' ||
			DigitPicture[Row][DigitPicture[Row].size() - 1] != '@')
			return false;
	CharArray::iterator Iter;
	Iter = DigitPicture.begin();
	Iter += DigitPicture.size()/7;
	DigitPicture.erase(DigitPicture.begin(), Iter);
	Iter = DigitPicture.end();
	Iter -= DigitPicture.size()/7;
	DigitPicture.erase(Iter, DigitPicture.end());
	for (Row = 0; Row < DigitPicture.size(); Row++)
		DigitPicture[Row] = DigitPicture[Row].substr(DigitPicture[Row].size()/4 , DigitPicture[Row].size()/2);
	return true;
	
}



bool DigitAnalyser::ConnectedComponents(CharArray & Digits)
{
	DigitPicture.clear();
	string PointString (Digits[0].size(),'.');
	int Column = 0, Row = 0;
	DigitPicture.assign(Digits.size(), PointString);
	while ( Column < Digits[0].size() - 1 && 
		Digits[Row][Column] == '.') 
	{
		Column++;
		Row = 0;
		while (Row  < Digits.size() - 1 && 
			Digits[Row][Column] == '.')
		{
			Row++;
		}
	}
	Separate (Digits, Row, Column);
	//cout<<' '<<1<<endl;
	if (Column == Digits[0].size() - 1)
		return false;
	//cout<<' '<<2<<endl;
	if ((double)CountPictureBlack(Digits) <= (double)CountPictureBlack(DigitPicture)/10)
		return false;
	//cout<<' '<<3<<endl;
	
	return true;
}
void DigitAnalyser::Separate(CharArray &Digits, int Row, int Column)
{
	Digits[Row][Column] = '.';
	DigitPicture[Row][Column] = '@';
	
	for (int i = Row - 1; i <= (Row + 1); i++)
			for (int j = Column - 1; j <= (Column + 1); j++)
				if (Digits[i][j] == '@')
				{
					Separate(Digits, i, j);
				}
}

int DigitAnalyser::CountPictureBlack(CharArray & Picture)
{
	int Count = 0;
	for(int Row = 0; Row < Picture.size(); Row++)
		for(int Column = 0; Column < Picture[Row].size(); Column++)
			if (Picture[Row][Column] == '@')
				Count++;
	return Count;
}

void DigitAnalyser::AnalyseDigit()
{
	int VerticalMin = 0, VerticalMax = 0, HorizontalMin = 0, HorizontalMax = 0;
	CharArray Digits;
	bool NotEnd;
//	cout<<"    1"<<endl;
	//Output();

	MaxMin(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
	Edge(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
	AddFrame();
	Blacken();
	Expansion();
	AddFrame();
	//Output();

	Blacken();
	Skeletonization();
	MaxMin(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
	//Output();
	//cout<<VerticalMin<<' '<<VerticalMax<<' '<<HorizontalMin<<' '<<HorizontalMax<<endl;
	
	Edge(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
	RemoveBlackFrame();
	
//	cout<<"    2"<<endl;
	AddFrame();
	/*{
		MaxMin(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
		Edge(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
	}*/
	//Output();
	
	Digits = DigitPicture;
	do 
	{
		NotEnd = ConnectedComponents(Digits);
		MaxMin(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
		Edge(VerticalMin, VerticalMax, HorizontalMin, HorizontalMax);
		AddFrame();
		//Output();
		
		if (VerticalMax - VerticalMin < 4 &&
			HorizontalMax - HorizontalMin < 4)
		{}
		else if (Zero())
			cout<<0;
		
		else if (Five())
			cout<<5;
		else if (Six())
			cout<<6;
		else if (Seven())
			cout<<7;
		else if (Nine())
			cout<<9;
		else if (Three())
			cout<<3;
		else if (Two())
			cout<<2;
		else if (One())
			cout<<1;
		else if (Four())
			cout<<4;
		else if (Eight())
			cout<<8;
		
		
	} while (NotEnd);
}

int main()
{
	NumberAnalyser MyAnalyser;
	MyAnalyser.ReadPicture();
	MyAnalyser.Analyse();
	return 0;
}
