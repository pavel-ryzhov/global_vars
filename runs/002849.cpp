#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>


// Класс реализующий метод дешифрования сообщений t9
// на основании заранее сформированного словаря
class T9Processor
{
public:
    void PushDictionaryWord(const std::string& word, int frequency)
    {
        dictionary_.push_back(CodedWord(word, Word2Code(word), frequency));
    }

    // метод выполняющий подготовку и нидексацию словаря
    void BuildDictionaryIndex()
    {
        dictionary_.sort(FrequncyGreaterPred);
        dictionary_.sort(AlphaLessPred);

        for (DictionaryIter it = dictionary_.begin(); it != dictionary_.end(); )
        {
            DictionaryIter head_it = it;
            while (++it != dictionary_.end() && 
                    it->numbers_code == head_it->numbers_code)
            {}
            index_.push_back(head_it);
        }
    }

    // метод выполняющий дешифрование сообщения
    //   message - сообщение в кодах t9
    //   out - дешифрованное сообщение
    void DecodeMessage(const std::string& message, std::string& out)
    {
        out.clear();

        std::string word_code;
        int asterisk = 0;

        // парсинг сообщения и вызов функций подбора
        std::string::const_iterator it = message.begin();
        while (it != message.end())
        {
            if (*it >= '2' && *it <= '9')
            {
                word_code.clear();
                do { 
                    word_code += *it; 
                } while (++it != message.end() && *it >= '2' && *it <= '9');
                
                asterisk = 0;
                while (it != message.end() && *it == '*') {
                    ++asterisk;
                    ++it;
                }

                out += Code2Word(word_code, asterisk);
            }
            else if (it != message.end() && *it == '1')
            {
                asterisk = 0;
                while (++it != message.end() && *it == '*') {
                    ++asterisk;
                }

                out += Code2Separator(asterisk);
            }
            else
            {
                out += *it;
                ++it;
            }
        }
    }

private:
    // структура слова в словаре
    //   word - текст слова
    //   numbers_code - слово в кодах t9
    //   frequency - частота
    struct CodedWord
    {
        CodedWord(const std::string& word_str, const std::string& word_code, int base_freq)
            :   word(word_str),
                numbers_code(word_code),
                frequency(base_freq)
        {}

        std::string word;
        std::string numbers_code;
        int frequency;
    };

private:
    typedef std::list<CodedWord> Dictionary;
    typedef Dictionary::iterator DictionaryIter;
    typedef std::vector<DictionaryIter> Index;

    // словарь, содержит слова отсортированные лексикографически по их
    // кодовым формам, слова имеющие одинаковые кодовые формы идут по
    // убыванию частоты
    Dictionary dictionary_;
    // индекс, содержит словарные итераторы на самые высокочастотные слова для всех 
    // кодовых форм
    Index index_;

private:
    std::string Word2Code(const std::string& word)
    {
        const char alpha_code_table[] = "222333"
                                        "444555666"
                                        "77778889999";
        std::string code;
        for (std::string::const_iterator it = word.begin(); it != word.end(); ++it) {
            code += alpha_code_table[*it - 'a'];
        }
        return code;
    }

    // метод поиска по словарю слова с заданным кодом
    //   code - кодовое представление слова для поиска
    //   asterisk - смещение от наиболее популярного слова с данным кодом
    std::string Code2Word(const std::string& code, int asterisk)
    {
        Index::iterator it = std::lower_bound(index_.begin(), index_.end(), code, IndexPred);
        if (it != index_.end())
        {
            DictionaryIter words_grp_iter = *it;
            DictionaryIter freq_grp_iter = *it;
            DictionaryIter prev_freq_grp_iter = *it;
            while (asterisk--)
            {
                ++words_grp_iter;
                if (words_grp_iter == dictionary_.end() || words_grp_iter->numbers_code != code)
                {
                    words_grp_iter = *it;
                    freq_grp_iter = *it;
                }
                else if (words_grp_iter->frequency != freq_grp_iter->frequency)
                {
                    prev_freq_grp_iter = freq_grp_iter;
                    freq_grp_iter = words_grp_iter;
                }
            }

            // увеличивается частота и производится 
            // смена порядка если нужно
            words_grp_iter->frequency++;
            if (words_grp_iter->frequency >= prev_freq_grp_iter->frequency) {
                freq_grp_iter = prev_freq_grp_iter;
            }

            if (words_grp_iter != freq_grp_iter)
            {
                if (*it == freq_grp_iter) {
                    *it = words_grp_iter;
                }
                dictionary_.splice(freq_grp_iter, dictionary_, words_grp_iter);
            }

            return words_grp_iter->word;
        }

        return std::string("error");
    }

    char Code2Separator(int asterisk)
    {
        const char separators_table[] = ".,?";
        return separators_table[asterisk % 3];
    }

    // предикат для поиска закодированного слова по индексу
    static bool IndexPred(DictionaryIter& indexed_iter, const std::string& base_code) {
        return indexed_iter->numbers_code < base_code;
    }

    // предикат для сортировки словаря в алфавитном порядке по закодированной форме
    static bool AlphaLessPred(const CodedWord& first, const CodedWord& second) {
        return first.numbers_code < second.numbers_code;
    }

    // предикат для сортировки словаря по убыванию частоты
    static bool FrequncyGreaterPred(const CodedWord& first, const CodedWord& second) {
        return first.frequency > second.frequency;
    }
};

int main()
{
    T9Processor processor;

    int words_count;
    std::cin >> words_count;

    std::string word_buf;
    int word_frequency;
    while (words_count--)
    {
        std::cin >> word_buf >> word_frequency;
        processor.PushDictionaryWord(word_buf, word_frequency);
    }
    processor.BuildDictionaryIndex();

    std::string message_code;
    std::string message_text;
    std::cin.ignore(1, '\n');
    std::getline(std::cin, message_code);

    processor.DecodeMessage(message_code, message_text);
    std::cout << message_text;
}

