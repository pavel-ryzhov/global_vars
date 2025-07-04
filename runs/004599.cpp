#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::queue;

const char kFirstCharacter = 'a';
const int kNonexistent = -1;

typedef map<string, int> Vocabulary;

// ----------------------------------------------------------------------
// State class

class State {
public:
  State(int alphabet_size, int parent, char parent_character) : 
      transitions_(alphabet_size, kNonexistent), 
      parent_(parent), parent_character_(parent_character),
      is_terminal_(false) {}
  bool IsTerminal() const {
    return is_terminal_;
  }
  void MakeTerminal() {
    is_terminal_ = true;
  }
  int GetTransition(char character) const {
    return transitions_[character - kFirstCharacter];
  }
  void SetTransition(char character, int destination) {
    transitions_[character - kFirstCharacter] = destination;
  }
  int GetParent() const {
    return parent_;
  }
  char GetParentCharacter() const {
    return parent_character_;
  }
  
private:
  vector<int> transitions_;
  int parent_;
  char parent_character_;
  bool is_terminal_;
};

// ----------------------------------------------------------------------
// Trie class

// This is a trie.
// All states in trie are numerated in order of their addition.
class Trie {
public:
  Trie(int alphabet_size);
  // Add strings to create to trie
  void AddStrings(const Vocabulary& vocabulary);
  // Reads string from root to specified state
  string ReadString(const State* state);
  void Clear();
  int GetStatesCount() const;
  const State* GetState(int index) const;
  static const int kRoot = 0;
private:
  // Adds new string when building the trie.
  void AddString(const string& new_string);
  // Adds new state when building a trie.
  // Returns index of new state.
  int AddState(int parent_state, char transition_character);
  int alphabet_size_;
  vector<State> states_;
};


Trie::Trie(int alphabet_size) 
                         : alphabet_size_(alphabet_size),
                           // add root state to trie
                           states_(1, State(alphabet_size, kNonexistent, kNonexistent)) {
}

void Trie::AddStrings(const Vocabulary& vocabulary) {
  for (Vocabulary::const_iterator word_it = vocabulary.begin(); 
       word_it != vocabulary.end(); ++word_it) {
    AddString(word_it->first);
  }
}

void Trie::AddString(const string &new_string) {
  int current_state = kRoot;
  string::const_iterator string_pointer = new_string.begin();
  
  while (states_[current_state].GetTransition(*string_pointer) != kNonexistent) {
    current_state = states_[current_state].GetTransition(*string_pointer);
    ++string_pointer;
    if (string_pointer == new_string.end()) {
      break;
    }
  }
  
  while (string_pointer != new_string.end()) {
    current_state = AddState(current_state, *string_pointer);
    ++string_pointer;
  }

  states_[current_state].MakeTerminal();
}

int Trie::AddState(int parent_state, char transition_character) {
  states_.push_back(State(alphabet_size_, parent_state, transition_character));
  int new_state = static_cast<int>(states_.size()) - 1;
  states_[parent_state].SetTransition(transition_character, new_state);
  return new_state;
}

string Trie::ReadString(const State* state) {
  string result;
  const State* current_state = state;
  while (current_state->GetParent() != kNonexistent) {
    result.push_back(current_state->GetParentCharacter());
    current_state = GetState(current_state->GetParent());
  }
  std::reverse(result.begin(), result.end());
  return result;
}

void Trie::Clear() {
  states_.clear();
  states_.push_back(State(alphabet_size_, kNonexistent, kNonexistent));
}

int Trie::GetStatesCount() const {
  return states_.size();
}

const State* Trie::GetState(int index) const {
  return &states_[index];
}




// ----------------------------------------------------------------------
// Trie traverser class

class TrieTraverser {
public:
  TrieTraverser(const Trie* trie, const State* state);  
  bool HasMatchedWord() const;
  bool CanMatch(char symbol) const;
  TrieTraverser Match(char symbol) const;
  const State* GetState() const;
private:
  const Trie* trie_;
  const State* state_;
};

TrieTraverser::TrieTraverser(const Trie* trie, const State* state) :
  trie_(trie), state_(state) {
}

bool TrieTraverser::HasMatchedWord() const {
  return state_->IsTerminal();
}
  
bool TrieTraverser::CanMatch(char symbol) const {
  return state_->GetTransition(symbol) != kNonexistent;
}

TrieTraverser TrieTraverser::Match(char symbol) const {
  return TrieTraverser(trie_, trie_->GetState(state_->GetTransition(symbol)));
}

const State* TrieTraverser::GetState() const {
  return state_;
}

// ----------------------------------------------------------------------
// Text message builder class

struct MessageObject {
  MessageObject() : change_count(0) {}
  string code;
  int change_count;
};

struct PriorityFrequency {
  PriorityFrequency() {};
  PriorityFrequency(int _frequency, int _priority) 
    : frequency(_frequency), priority(_priority) {}
  int frequency;
  int priority;
};

struct WordHypothesis {
  WordHypothesis(const string& _word, int _frequency, int _priority) 
    : word(_word), frequency(_frequency), priority(_priority) {}
  string word;
  int frequency;
  int priority;
};

class WordHypothesisComparator {
public:
  bool operator ()(const WordHypothesis& first, const WordHypothesis& second) {
    if (first.frequency != second.frequency) {
      return first.frequency > second.frequency;
    } else if (first.priority != second.priority) {
      return first.priority > second.priority;
    } else {
      return first.word < second.word;
    }
  }
};

typedef map<string, PriorityFrequency> PriorityVocabulary;

class TextMessageBuilder {
public:
  TextMessageBuilder();
  void SetVocabulary(const Vocabulary& vocabulary);
  string ConvertToText(const string& message);
private:
  static const int kAlphabetSize = 26;
  static const char kSpaceCode = ' ';
  static const char kPunctuationCode = '1';
  static const char kChangeCode = '*';
  static const char kDotChar = '.';
  static const char kCommaChar = ',';
  static const char kQuestionChar = '?';
  static const char kZeroChar = '0';
  void InitializeLetters();
  void ParseMessageCode(const string& message);
  int ReadPunctuationSymbol(const string& message, int start_index);
  int ReadSpace(const string& message, int start_index);
  int ReadWord(const string& message, int start_index);
  bool IsPunctuationSymbol(const MessageObject& message_object);
  bool IsSpace(const MessageObject& message_object);
  string GetPunctuationSymbol(const MessageObject& message_object);
  string GetSpace(const MessageObject& message_object);
  string GetWord(const MessageObject& message_object);
  vector<string> GetMatchedWords(const string& code);
  PriorityVocabulary priority_vocabulary;
  Trie trie_;
  vector<MessageObject> message_objects_;
  int priority_timer_;
  vector<string> letters_;
};

TextMessageBuilder::TextMessageBuilder() : trie_(kAlphabetSize) {
  InitializeLetters();
}

void TextMessageBuilder::InitializeLetters() {
  letters_.resize(10);
  letters_[2] = "abc";
  letters_[3] = "def";
  letters_[4] = "ghi";
  letters_[5] = "jkl";
  letters_[6] = "mno";
  letters_[7] = "pqrs";
  letters_[8] = "tuv";
  letters_[9] = "wxyz";
}

void TextMessageBuilder::SetVocabulary(const Vocabulary& vocabulary) {
  priority_vocabulary.clear();
  priority_timer_ = 0;
  for (Vocabulary::const_iterator word_it = vocabulary.begin(); 
       word_it != vocabulary.end(); ++word_it) {
    priority_vocabulary.insert(
      std::make_pair(word_it->first, PriorityFrequency(word_it->second, 0)));
  }

  trie_.Clear();
  trie_.AddStrings(vocabulary);
}

string TextMessageBuilder::ConvertToText(const string &message) {
  ParseMessageCode(message);
  
  string message_text;
  for (vector<MessageObject>::iterator message_object_it = message_objects_.begin();
       message_object_it != message_objects_.end(); ++message_object_it) {
    if (IsPunctuationSymbol(*message_object_it)) {
      message_text.append(GetPunctuationSymbol(*message_object_it));    
    } else if (IsSpace(*message_object_it)) {
      message_text.append(GetSpace(*message_object_it));
    } else {
      message_text.append(GetWord(*message_object_it));    
    }
  }
  return message_text;
}

void TextMessageBuilder::ParseMessageCode(const string& message) {
  message_objects_.clear();
  int message_index = 0;
  while (message_index < static_cast<int>(message.size())) {
    if (message[message_index] == kSpaceCode) {
      message_index = ReadSpace(message, message_index);
    } else if (message[message_index] == kPunctuationCode) {
      message_index = ReadPunctuationSymbol(message, message_index);
    } else {
      message_index = ReadWord(message, message_index);
    }
  }
}

int TextMessageBuilder::ReadPunctuationSymbol(const string& message, int start_index) {
  MessageObject punctuation_object;
  int message_index = start_index;
  punctuation_object.code.push_back(message[message_index]);
  ++message_index;
  while (message_index < static_cast<int>(message.size()) && 
         message[message_index] == kChangeCode) {
    ++punctuation_object.change_count;
    ++message_index;
  }
  message_objects_.push_back(punctuation_object);
  return message_index;
}

int TextMessageBuilder::ReadSpace(const string& message, int start_index) {
  MessageObject space_object;
  int message_index = start_index;
  while (message_index < static_cast<int>(message.size()) && 
         message[message_index] == kSpaceCode) {
    space_object.code.push_back(message[message_index]);
    ++message_index;
  }
  message_objects_.push_back(space_object);
  return message_index;
}

int TextMessageBuilder::ReadWord(const string& message, int start_index) {
  MessageObject word_object;
  int message_index = start_index;
  while (message_index < static_cast<int>(message.size()) && 
         message[message_index] != kSpaceCode && message[message_index] != kPunctuationCode) {
    if (message[message_index] == kChangeCode) {
      ++word_object.change_count;
    } else {
      word_object.code.push_back(message[message_index]);
    }
    ++message_index;
  }
  message_objects_.push_back(word_object);
  return message_index;
}

bool TextMessageBuilder::IsPunctuationSymbol(const MessageObject& message_object) {
  return message_object.code[0] == kPunctuationCode;
}

bool TextMessageBuilder::IsSpace(const MessageObject& message_object) {
  return message_object.code[0] == kSpaceCode;
}

string TextMessageBuilder::GetPunctuationSymbol(const MessageObject &message_object) {
  string punctuation_symbol;
  if (message_object.change_count == 0) {
    punctuation_symbol.push_back(kDotChar);
  } else if (message_object.change_count == 1) {
    punctuation_symbol.push_back(kCommaChar);
  } else {
    punctuation_symbol.push_back(kQuestionChar);
  }
  return punctuation_symbol;
}

string TextMessageBuilder::GetSpace(const MessageObject &message_object) {
  return message_object.code;
}

string TextMessageBuilder::GetWord(const MessageObject &message_object) {
  vector<string> matched_words = GetMatchedWords(message_object.code);

  typedef set<WordHypothesis, WordHypothesisComparator> HypothesisSet;
  HypothesisSet hypotheses;
  for (vector<string>::iterator matched_word_it = matched_words.begin();
       matched_word_it != matched_words.end(); ++matched_word_it) {
    hypotheses.insert(
      WordHypothesis(*matched_word_it, 
                     priority_vocabulary[*matched_word_it].frequency, 
                     priority_vocabulary[*matched_word_it].priority));
  }

  HypothesisSet::iterator answer_hypothesis_it = hypotheses.begin();
  for (int change_index = 0; change_index < message_object.change_count; ++change_index) {
    ++answer_hypothesis_it;
  }

  ++priority_timer_;
  priority_vocabulary[answer_hypothesis_it->word] = 
    PriorityFrequency(answer_hypothesis_it->frequency + 1, priority_timer_);

  return answer_hypothesis_it->word;
}

vector<string> TextMessageBuilder::GetMatchedWords(const string &code) {
  queue<TrieTraverser> old_states, new_states;

  old_states.push(TrieTraverser(&trie_, trie_.GetState(Trie::kRoot)));
  string::const_iterator code_it = code.begin();
  while (code_it != code.end()) {
    
    while (!old_states.empty()) {
      TrieTraverser front_traverser = old_states.front();
      old_states.pop();

      for (string::iterator letter_it = letters_[*code_it - kZeroChar].begin(); 
           letter_it != letters_[*code_it - kZeroChar].end(); ++letter_it) {
        if (front_traverser.CanMatch(*letter_it)) {
          new_states.push(front_traverser.Match(*letter_it));
        }
      }
    }

    std::swap(old_states, new_states);
    ++code_it;
  }

  vector<string> matched_words;
  while (!old_states.empty()) {
    TrieTraverser front_traverser = old_states.front();
    old_states.pop();
    if (front_traverser.HasMatchedWord()) {
      matched_words.push_back(trie_.ReadString(front_traverser.GetState()));
    }
  }

  return matched_words;
}

// ----------------------------------------------------------------------
// Input/Output

void Input(Vocabulary* vocabulary, string* message) {
  int vocabulary_size;
  scanf("%d", &vocabulary_size);

  const int kMaxWordSize = 20;
  for (int word_index = 0; word_index < vocabulary_size; ++word_index) {
    char word[kMaxWordSize + 1];
    int frequency;
    scanf("%s %d", word, &frequency);
    vocabulary->insert(std::make_pair(string(word), frequency));
  }

  cin >> std::ws;
  std::getline(cin, *message);
}

void TestInput1(Vocabulary* vocabulary, string* message) {
  vocabulary->insert(std::make_pair("ad", 2));
  vocabulary->insert(std::make_pair("be", 1));
  vocabulary->insert(std::make_pair("not", 10));
  vocabulary->insert(std::make_pair("or", 5));
  vocabulary->insert(std::make_pair("to", 50));

  *message = "86 23* 67 668 86 231**";
}

void TestInput2(Vocabulary* vocabulary, string* message) {
  vocabulary->insert(std::make_pair("act", 1));
  vocabulary->insert(std::make_pair("bat", 1));
  vocabulary->insert(std::make_pair("cat", 1));

  *message = "228* 228** 228** 228**1";
}

// ----------------------------------------------------------------------
// main

int main() {
  Vocabulary vocabulary;
  string message;
  Input(&vocabulary, &message);
  //TestInput2(&vocabulary, &message);
  TextMessageBuilder text_message_builder;
  
  text_message_builder.SetVocabulary(vocabulary);
  cout << text_message_builder.ConvertToText(message) << endl;

  return 0;
}
