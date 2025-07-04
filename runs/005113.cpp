#include <iostream>
#include <string>
#include <map>
#include <list>
#include <new>
#include <stdexcept>

typedef struct
{
  std::string value;
  size_t freq;
}Item;

inline bool is_alpha(char c)
{
  return ('2'<=c)&&(c<='9');
}

inline void output(const std::list<Item>::iterator& s_, \
                   const std::list<Item>::iterator& w_, \
                   std::string& key_, \
                   std::map<std::string,std::list<Item> >& dic_)
{
  std::cout<<w_->value;
  ++(w_->freq);
  if(s_!=w_)
  {
    dic_[key_].insert(s_,*w_);
    dic_[key_].erase(w_);
  }
  key_.clear();
}



class Pr
{
public:
  bool operator()(Item& lhs,Item& rhs)
  {
    if(lhs.freq==rhs.freq)
      return lhs.value<rhs.value;
    else
      return rhs.freq<lhs.freq;
  }
};

int main(int argc, char *argv[])
{
  static const size_t MAX_WORD_LENGTH=20;
  static const char keys[]= \
            {'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6',\
           /*'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',*/
             '7','7','7','7','8','8','8','9','9','9','9'};
           /*'p','q','r','s','t','u','v','w','x','y','z'*/

  size_t n_word;
  const char* const alha_key=keys-static_cast<size_t>('a');
  char buf;
  std::string key;
  Item item;
  std::map<std::string,std::list<Item> > dic;

  try
  {
    item.value.reserve(MAX_WORD_LENGTH);
    key.reserve(MAX_WORD_LENGTH);
    std::cin>>n_word;
    while(n_word--)
    {
      std::cin>>item.value>>item.freq;
      //Переводим слово в последовательность нажатых клавиш
      for(std::string::iterator ch=item.value.begin();
          ch!=item.value.end();
          ++ch)
      {
        key.push_back(alha_key[static_cast<size_t>(*ch)]);
      }
      dic[key].push_front(item);
      key.clear();
    }//Списки слов, сопоставленных одинаковому ключу не отсортированы

    Pr pr;
    for(std::map<std::string,std::list<Item> >::iterator i=dic.begin();
        i!=dic.end();
        ++i)
    {
      (i->second).sort(pr);
    }//Теперь отсортированы

    //Начинаем читать последовательность ввода
    key.clear();
    std::list<Item>::iterator s,c,w;
    std::cin.ignore();
    while(std::cin.get(buf))
    {
      switch(buf)
      {
      case '1':
        if(!key.empty())
        {
          output(s,w,key,dic);
        }
        buf=std::cin.peek();
        if('*'==buf)
        {
          std::cin.ignore();
          buf=std::cin.peek();
          if('*'==buf)
          {
            std::cin.ignore();
            std::cout<<'?';
          }
          else
            std::cout<<',';
        }
        else
          std::cout<<'.';
        break;

      case ' ':
        if(!key.empty())
        {
          output(s,w,key,dic);
          std::cout<<' ';
        }
        else
          std::cout<<' ';
        break;

      case '*':
        ++w;
        if(w->freq!=c->freq)
        {
          if(s!=c)
          {
            s=c;
          }
          c=w;
        }
        break;

      default:
        key+=buf;
        while(std::cin.get(buf))
        {
          if(is_alpha(buf))
            key+=buf;
          else
          {
            std::cin.putback(buf);
            break;
          }
        }
        s=c=w=dic[key].begin();
      }
    }

    if((!key.empty()) && ('\n'!=key[0]))
      std::cout<<w->value;
  }
  catch(std::bad_alloc e)
  {
    std::cerr<<"Can't allocate of memory: "<<e.what()<<std::endl;
    std::terminate();
  }
  catch(std::out_of_range e)
  {
    std::cerr<<"Index is out of range: "<<e.what()<<std::endl;
    std::terminate();
  }
  catch(...)
  {
    std::terminate();
  }

  return 0;
}
