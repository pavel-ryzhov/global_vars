#include <iostream>
#include <string>
#include <vector>

// слово в словаре
class TWord
{
private:
	std::string value; // само слово
	int density; // частота встречаемости
public:
	TWord();
	TWord(std::string, int);
	~TWord();
	std::string getValue();
	int getDensity();
	void incDensity();
};

// цифровая комбинация
class TDigit
{
private:
	std::string value; // комбинация
	std::vector<TWord*> words; // список слов для этой комбинации
	// список должен обновляться во время использования,
	// чтобы все слова в нём были отсортированы по приоритету:
	// сначала по наибольшей встречаемости,
	// потом по новизне, затем по алфавиту
public:
	TDigit();
	TDigit(std::string);
	~TDigit();
	std::string getValue();
	TWord* getWord(unsigned);
	void addWord(TWord*);
	std::vector<TWord*>::iterator begin();
	std::vector<TWord*>::iterator end();
};

// словарь - по цифровым комбинациям
class TDictionary
{
private:
	std::vector<TDigit*> combinations; // цифровые комбинации
	// функция сравнения для бинарного поиска
	//bool compare(const TDigit*, const TDigit*);
public:
	TDictionary();
	~TDictionary();
	void addWord(std::string, int);
	// преобразование слова в его цифровую комбинацию
	std::string convertToDigits(std::string);
	// поиск цифровой комбинации
	TDigit* findCombination(std::string/*, bool*/);
	void print();
};

// телефон с его системой ввода/вывода
class TTelephone
{
private:
	enum TState
	{
		Any,
		Symbol,
		SymbolStar,
		Digit,
		DigitStar
	} state; // состояние считывателя на данный момент
	std::string output; // строка на вывод
	TDictionary* dictionary; // прилагаемый словарь
	// преобразование слова из численного в буквенный вид
	// указывается количество звёздочек
	std::string convertWord(std::string, unsigned);
public:
	TTelephone();
	~TTelephone();
	void assignDictionary(TDictionary*);
	void fillDictionary();
	void getPhrase();
	void print();
};

TWord::TWord()
{

}

TWord::TWord(std::string word, int dens)
{
	value = word;
	density = dens;
}

int TWord::getDensity()
{
	return density;
}

std::string TWord::getValue()
{
	return value;
}

void TWord::incDensity()
{
	density++;
}

TWord::~TWord()
{

}

TDigit::TDigit()
{

}

TDigit::TDigit(std::string digits)
{
	value = digits;
}

std::string TDigit::getValue()
{
	return value;
}

// возвращает одно из записанных слов
// увеличивает его частоту использования
TWord* TDigit::getWord(unsigned stars)
{
	TWord* temp;

	if (words.size() <= stars)
		return 0;
	int i = stars;
	words[i]->incDensity();
	while (i != 0)
	{
		if (words[i - 1]->getDensity() <= words[i]->getDensity())
		{
			temp = words[i - 1];
			words[i - 1] = words[i];
			words[i] = temp;
			i--;
		}
		else
			break;
	}

	return words[i];
}

void TDigit::addWord(TWord* word)
{
	int d = word->getDensity();
	std::vector<TWord*>::iterator i = words.begin();
	while (i != words.end())
	{
		if ((*i)->getDensity() < d)
		{
			words.insert(i, word);
			return;
		}
		i++;
	}
	words.push_back(word);
}

std::vector<TWord*>::iterator TDigit::begin()
{
	return words.begin();
}

std::vector<TWord*>::iterator TDigit::end()
{
	return words.end();
}

TDigit::~TDigit()
{

}

TDictionary::TDictionary()
{

}

void TDictionary::print()
{
	std::vector<TDigit*>::iterator i = combinations.begin();
	std::vector<TWord*>::iterator j;

	while (i != combinations.end())
	{
		std::cout << (*i)->getValue() << " ";
		j = (*i)->begin();
		while (j != (*i)->end())
		{
			std::cout << (*j)->getValue() << " " << (*j)->getDensity() << " ";
			j++;
		}
		std::cout << std::endl;
		i++;
	}
}

void TDictionary::addWord(std::string word, int dens)
{
	TWord* newword = new TWord(word, dens);
	std::string number = convertToDigits(word);
	TDigit* digit = findCombination(number/*, true*/);
	if (digit == 0)
	{
		digit = new TDigit(number);
		combinations.push_back(digit);
	}
	digit->addWord(newword);
}

std::string TDictionary::convertToDigits(std::string word)
{
	std::string digits = "";
	std::string::iterator i = word.begin();
	while (i != word.end())
	{
		switch (*i)
		{
		case 'a': digits.append("2"); break;
		case 'b': digits.append("2"); break;
		case 'c': digits.append("2"); break;
		case 'd': digits.append("3"); break;
		case 'e': digits.append("3"); break;
		case 'f': digits.append("3"); break;
		case 'g': digits.append("4"); break;
		case 'h': digits.append("4"); break;
		case 'i': digits.append("4"); break;
		case 'j': digits.append("5"); break;
		case 'k': digits.append("5"); break;
		case 'l': digits.append("5"); break;
		case 'm': digits.append("6"); break;
		case 'n': digits.append("6"); break;
		case 'o': digits.append("6"); break;
		case 'p': digits.append("7"); break;
		case 'q': digits.append("7"); break;
		case 'r': digits.append("7"); break;
		case 's': digits.append("7"); break;
		case 't': digits.append("8"); break;
		case 'u': digits.append("8"); break;
		case 'v': digits.append("8"); break;
		case 'w': digits.append("9"); break;
		case 'x': digits.append("9"); break;
		case 'y': digits.append("9"); break;
		case 'z': digits.append("9"); break;
		}
		i++;
	}

	return digits;
}

// Поиск цифровой комбинации в словаре.
// addMode означает, что это поиск комбинации во время заполнения словаря.
// Так как словарь заполняется по алфавиту, то все цифровые комбинации
// также будут упорядочены по алфавиту. Искомая комбинация может находиться
// только в конце словаря. Это значительно ускорит поиск.
TDigit* TDictionary::findCombination(std::string digits/*, bool addMode*/)
{
	/*if (addMode)
	{
		std::vector<TDigit*>::reverse_iterator i = combinations.rbegin();
		if (i != combinations.rend())
		{
			std::cout << (*i)->getValue() << " " << digits << std::endl;
			if ((*i)->getValue() == digits)
				return *i;
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{*/
		/*TDigit *digit = std::binary_search(combinations.begin(),
				combinations.end(),	digits, compare);*/
		std::vector<TDigit*>::iterator i = combinations.begin();
		while (i != combinations.end())
		{
			if ((*i)->getValue() == digits)
				return *i;
			i++;
		}
	//}

	return 0;
}

/*bool TDictionary::compare(const TDigit* digit1, const TDigit* digit2)
{
	return (digit1->getValue() <= digit2->getValue());
}*/

TDictionary::~TDictionary()
{

}

TTelephone::TTelephone()
{

}

TTelephone::~TTelephone()
{

}

void TTelephone::assignDictionary(TDictionary* dict)
{
	dictionary = dict;
}

void TTelephone::fillDictionary()
{
	int i,
		c, // количество слов
		d; // частота слова
	std::string word; // вводимое слово

	std::cin >> c;
	for (i = 0; i < c; i++)
	{
		std::cin >> word;
		std::cin >> d;
		dictionary->addWord(word, d);
	}
}

void TTelephone::getPhrase()
{
	std::string input; // строка на ввод
	std::string::size_type i, // текущее положение поиска
		t1 = 0, t2 = 0; // начала отрезков

	// фраза не должна быть пустой
	do
	{
		getline(std::cin, input);
	} while (input.find_first_not_of('\n') == std::string::npos);
	output = "";
	// первичное состояние - ожидание любого символа
	state = Any;
	for (i = 0; i < input.length(); i++)
	{
		switch (input[i])
		{
		// если попался пробел
		case ' ':
			switch (state)
			{
			// если до этого набирались цифры,
			// отослать эту последовательность на преобразование
			// и добавить в строку вывода
			case Digit:
				output.append(convertWord(input.substr(t1, i - t1), 0));
				//output.append(input.substr(t1, i - t1));
				break;
			// если набирались звёздочки после цифр,
			// то же самое (но не забыть, сколько звёздочек)
			case DigitStar:
				output.append(convertWord(input.substr(t1, t2 - t1), i - t2));
				//output.append(input.substr(t1, t2 - t1));
				break;
			// если был набран знак препинания,
			// добавить этот знак в строку вывода
			// (это точно будет точка)
			case Symbol:
				output.append(".");
				break;
			// если набирались звёздочки после знака препинания,
			// то это либо запятая, либо вопросительный знак,
			// определяется по количеству звёздочек,
			// добавляется в строку вывода
			case SymbolStar:
				if (i - t1 == 1)
					output.append(",");
				else
					output.append("?");
				break;
			default:
				break;
			}
			// сам пробел тоже идёт на вывод
			output.append(" ");
			// состояние после пробела - ожидание любого символа
			state = Any;
			break;

		// если попалась звёздочка
		case '*':
			switch (state)
			{
			// если набирались цифры, то ввод закончен,
			// теперь набираются звёздочки
			case Digit:
				t2 = i;
				state = DigitStar;
				break;
			// если до этого был символ, то следующий режим -
			// выбор символа
			case Symbol:
				t1 = i;
				state = SymbolStar;
				break;
			// в остальных случаях никакая реакция не требуется
			default:
				break;
			}
			break;
		// если попалась "1"
		case '1':
			switch (state)
			{
			// если набирался символ, то этот символ выводится (точка)
			case Symbol:
				output.append(".");
				break;
			// если набирались звёздочки для символа, то выводится текущий
			// символ (запятая или вопросительный знак)
			case SymbolStar:
				if (i - t1 == 1)
					output.append(",");
				else
					output.append("?");
				break;
			// если набирались цифры, то закончить их набор,
			// отослать на вывод
			case Digit:
				output.append(convertWord(input.substr(t1, i - t1), 0));
				//output.append(input.substr(t1, i - t1));
				break;
			// если набирались звёздочки после цифр,
			// сделать то же самое, не забыв про количество звёздочек
			case DigitStar:
				output.append(convertWord(input.substr(t1, t2 - t1), i - t2));
				//output.append(input.substr(t1, t2 - t1));
				break;
			default:
				break;
			}
			// в любом случае теперь набирается символ
			state = Symbol;
			break;
		// если набираются любые другие символы - цифры
		// (считаем, что больше других символов не может быть введено)
		default:
			switch (state)
			{
			// если ничего не вводилось, просто переключаем режим ввода
			// на ввод цифр
			case Any:
				t1 = i;
				break;
			// если вводился знак препинания, вывести его
			// и переключить режим ввода
			case Symbol:
				output.append(".");
				t1 = i;
				break;
			case SymbolStar:
				if (i - t1 == 1)
					output.append(",");
				else
					output.append("?");
				t1 = i;
				break;
			default:
				break;
			}
			// состояние - вводятся цифры
			state = Digit;
			break;
		}
	}
	// строка закончилась, но не нужно ли нам что-нибудь вывести?
	switch (state)
	{
	// вводились цифры - вывести
	case Digit:
		output.append(convertWord(input.substr(t1, i - t1), 0));
		//output.append(input.substr(t1, i - t1));
		break;
	case DigitStar:
		output.append(convertWord(input.substr(t1, t2 - t1), i - t2));
		//output.append(input.substr(t1, t2 - t1));
		break;
	// вводился знак препинания - вывести
	case Symbol:
		output.append(".");
		break;
	case SymbolStar:
		if (i - t1 == 1)
			output.append(",");
		else
			output.append("?");
		break;
	default:
		break;
	}
}

std::string TTelephone::convertWord(std::string input, unsigned stars)
{
	TDigit *digit = dictionary->findCombination(input/*, false*/);
	if (digit)
	{
		return digit->getWord(stars)->getValue();
	}
	else
		return "";
}

void TTelephone::print()
{
	std::cout << output << std::endl;
}

int main()
{
	TDictionary dictionary;
	TTelephone telephone;

	telephone.assignDictionary(&dictionary);
	telephone.fillDictionary();
	//dictionary.print();
	telephone.getPhrase();
	telephone.print();

	return 0;
}
