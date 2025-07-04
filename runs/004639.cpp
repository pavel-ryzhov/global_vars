#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cstdio>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::queue;
using std::pair;

// ----------------------------------------------------------------------
// TrieLib

#include <iostream>

namespace ToolBox
{
  //fwd declaration
  template <typename T>
    class TrieFactory;
  template <typename T>
    class TrieNode;

  /**
   * Implement a trie in memory with the smallest structure as possible
   * (use few RAM as possible)
   */
  template <typename T>
    class Trie
    {
    public:
      /// constuctor, empty is the value returned when no match in found
      /// in trie
      Trie(const T &empty);
      ~Trie();

    private:
      /// avoid default constructor
      Trie();
      /// avoid copy constructor
      Trie(const Trie &e);
      /// avoid affectation operator
      Trie& operator=(const Trie &e);
    
    public:
      /// add an entry in the Trie, if entry already exist an exception
      /// is throw
      void addEntry(const char *str, unsigned strLen, const T &value);
      /// associates a value to a string, if string is already in Trie,
      /// value is overwriten
      void setEntry(const char *str, unsigned strLen, const T &value);
      /// get an entry in the Trie
      const T& getEntry(const char *str, unsigned strLen) const;
      /// check an entry in the Trie
      bool checkEntry(const char *str, unsigned strLen) const;
      /// get initial TrieNode
      const TrieNode<T>* getInitialNode() const;
      /// display content of trie in output stream
      void display(std::ostream &os);
      /// clear the content of trie
      void clear();

    protected:
      TrieNode<T>* _addEntry(const char *str, unsigned strLen);

    private:
      /// value returned when no match is found in trie
      T			_empty;
      /// factory
      TrieFactory<T>	*_factory;
      /// first node of trie
      TrieNode<T>		*_initialNode;
    };
}


#include <vector>
#include <algorithm>
#include <assert.h>


#include <list>

namespace ToolBox
{
  // fwd declaration
  template <typename T>
  class TrieNode;

  /**
   * The goal of this class is to allocate Trie node by paquet of X
   * element in order to reduce heap-admin size
   */
  template <typename T>
  class TrieFactory
    {
    public:
      TrieFactory(unsigned paquetSize);
      ~TrieFactory();

    private:
      /// avoid default constructor
      TrieFactory();
      /// avoid copy constructor
      TrieFactory(const TrieFactory &e);
      /// avoid affectation operator
      TrieFactory& operator=(const TrieFactory &e);

    public:
      TrieNode<T>* getNewNode(const T &value);
      void clear();

    private:
      unsigned			_paquetSize;
      std::list<TrieNode<T>*>	_allocatedNodes;
      TrieNode<T>		*_lastNodes;
      unsigned			_nbUsedInLastNodes;
    };
}


namespace ToolBox
{
  /**
   * @brief this class represent the node of a trie, it contains a
   * link to a sub node and a link to a brother (node which have the
   * same father)
   */
  template <typename T>
  class TrieNode
  {
  public:
    TrieNode();
    ~TrieNode();

  private:
    /// avoid copy constructor
    TrieNode(const TrieNode &e);
    /// avoid affectation operator
    TrieNode& operator=(const TrieNode &e);

  public:
    /// set value associed to node
    void setValue(const T &val);
    /// get value associed to node
    const T& getValue() const;

    /// get brother (return 0x0 this node has no brother)
    const TrieNode<T>* getBrother() const;
    TrieNode<T>* getBrother();
    /// get brother label
    unsigned char getBrotherLabel() const;

    // get first sub Node
    const TrieNode<T>* getSubNode() const;
    TrieNode<T>* getSubNode();
    unsigned char getSubNodeLabel() const;

    /// get parent (return 0x0 this node has no parent)
    const TrieNode<T>* getParent() const;
    TrieNode<T>* getParent();
    /// get brother label
    unsigned char getParentLabel() const;

    // Looking for a sub node
    const TrieNode<T>* getSubNodeByLabel(unsigned char chr) const;
    TrieNode<T>* getSubNodeByLabel(unsigned char chr);

    // add an edge
    void addSubNode(unsigned char chr, TrieNode<T> *node);

    /// display content of node in output stream
    void display(std::ostream &os, unsigned offset, unsigned char label) const;

    /// clear content of TrieNode
    void clear();

  protected:
    template <typename Node>
    Node _sequentialSearch(Node first, unsigned char label,
			   unsigned char val) const;
    /// set brother (used by sort)
    void _setBrother(TrieNode<T> *brother, unsigned char brotherLabel);
    /// add a new brother
    void _addBrother(unsigned char chr, TrieNode<T> *brother);
    /**
     * @ brief get brother that has the label chr (return 0x0 if brother is
     * not found)
     */
    const TrieNode<T>* _getBrother(unsigned char chr) const;
    /**
     * @ brief get brother that has the label chr (return 0x0 if brother is
     * not found)
     */
    TrieNode<T>* _getBrother(unsigned char chr);

  private:
    /// pointer to brother (node with same father as this one)
    TrieNode<T>		*_brother;
    /// character to go to brother (node with same father as this one)
    unsigned char	_brotherLabel;
    /// pointer to first sub node
    TrieNode<T>		*_firstSubNode;
    /// character to go to first subnode
    unsigned char	_firstSubNodeLabel;
    /// pointer to parent 
    TrieNode<T>		*_parent;
    /// character to go to parent
    unsigned char	_parentLabel;

    /// value associed to this node
    T			_value;
  };
}

template <typename T>
ToolBox::TrieNode<T>::TrieNode() :
  _brother(0), _brotherLabel(0), _firstSubNode(0), _firstSubNodeLabel(0)
  /// we can not set _value here because type is unknown. assert that
  /// the value is set later with setValue()
{
}

template <typename T>
ToolBox::TrieNode<T>::~TrieNode()
{
  // do not delete _brother and _firstSubNode because they are
  // allocated by factory (TrieFactory) and factory will delete them
}

template <typename T>
void ToolBox::TrieNode<T>::setValue(const T &val)
{
  _value = val;
}

template <typename T>
const T& ToolBox::TrieNode<T>::getValue() const
{
  return _value;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getBrother() const
{
  return _brother;
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getBrother()
{
  return _brother;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::_getBrother(unsigned char chr) const
{
  const TrieNode<T> *brother = _brother;
  return _sequentialSearch(brother, _brotherLabel, chr);
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::_getBrother(unsigned char chr)
{
  return _sequentialSearch(_brother, _brotherLabel, chr);
}

template <typename T>
void ToolBox::TrieNode<T>::_addBrother(unsigned char chr, TrieNode<T> *brother)
{
  if (!_brother || _brotherLabel > chr)
    {
      brother->_setBrother(_brother, _brotherLabel);
      _brother = brother;
      _brotherLabel = chr;
    }
  else
    _brother->_addBrother(chr, brother);
}

template <typename T>
unsigned char ToolBox::TrieNode<T>::getBrotherLabel() const
{
  return _brotherLabel;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getSubNode() const
{
  return _firstSubNode;
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getSubNode()
{
  return _firstSubNode;
}

template <typename T>
unsigned char ToolBox::TrieNode<T>::getSubNodeLabel() const
{
  return _firstSubNodeLabel;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getParent() const
{
  return _parent;
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getParent()
{
  return _parent;
}

template <typename T>
unsigned char ToolBox::TrieNode<T>::getParentLabel() const
{
  return _parentLabel;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getSubNodeByLabel(unsigned char chr) const
{
  const TrieNode<T> *first = _firstSubNode;
  return _sequentialSearch(first, _firstSubNodeLabel, chr);
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieNode<T>::getSubNodeByLabel(unsigned char chr)
{
  return _sequentialSearch(_firstSubNode, _firstSubNodeLabel, chr);
}

template <typename T>
void ToolBox::TrieNode<T>::addSubNode(unsigned char chr, TrieNode<T> *node)
{
  if (!_firstSubNode || _firstSubNodeLabel > chr)
    {
      node->_setBrother(_firstSubNode, _firstSubNodeLabel);
      _firstSubNode = node;
      _firstSubNodeLabel = chr;
    }
  else
    _firstSubNode->_addBrother(chr, node);
}

template <typename T>
template <typename Node>
inline Node ToolBox::TrieNode<T>::_sequentialSearch(Node first, unsigned char label, unsigned char val) const
{
  if (first && label <= val)
    {
      if (label == val)
	return first;
      return first->_getBrother(val);
    }
  return 0x0;
}

template <typename T>
void ToolBox::TrieNode<T>::_setBrother(TrieNode<T> *brother, unsigned char brotherLabel)
{
  _brother = brother;
  _brotherLabel = brotherLabel;
}

template <typename T>
void ToolBox::TrieNode<T>::display(std::ostream &os, unsigned offset, unsigned char label) const
{
  unsigned int i;
  for (i = 0; i < offset; ++i)
    os << " ";
  if (label)
    os << "label[" << label << "] ";
  os << "value[" << _value << "]" << std::endl;
  if (_firstSubNode)
    _firstSubNode->display(os, offset + 2, _firstSubNodeLabel);
  if (_brother)
    _brother->display(os, offset, _brotherLabel);
}

template <typename T>
void ToolBox::TrieNode<T>::clear()
{
  _brother = 0x0;
  _brotherLabel = 0;
  _firstSubNode = 0x0;
  _firstSubNodeLabel = 0;
}

template <typename T>
ToolBox::TrieFactory<T>::TrieFactory(unsigned paquetSize) :
  _paquetSize(paquetSize), _lastNodes(0x0), _nbUsedInLastNodes(0)
{
  _lastNodes = new TrieNode<T>[paquetSize];
}

template <typename T>
ToolBox::TrieFactory<T>::~TrieFactory()
{
  typename std::list<TrieNode<T>*>::const_iterator it;

  for (it = _allocatedNodes.begin(); it != _allocatedNodes.end(); ++it)
    delete[] *it;
  if (_lastNodes)
    delete[] _lastNodes;
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::TrieFactory<T>::getNewNode(const T &value)
{
  if (_nbUsedInLastNodes == _paquetSize)
    {
      _allocatedNodes.push_back(_lastNodes);
      _nbUsedInLastNodes = 0;
      _lastNodes = new TrieNode<T>[_paquetSize];
    }
  TrieNode<T> *res = &_lastNodes[_nbUsedInLastNodes];
  ++_nbUsedInLastNodes;
  res->setValue(value);
  res->clear();
  return res;
}

template <typename T>
void ToolBox::TrieFactory<T>::clear()
{
  typename std::list<TrieNode<T>*>::const_iterator it;
  for (it = _allocatedNodes.begin(); it != _allocatedNodes.end(); ++it)
    delete[] *it;
  _allocatedNodes.clear();
  _nbUsedInLastNodes = 0;
}


#include <iostream>
#include <exception>
#include <string>
#include <list>

/**
 * \file
 * \brief Exception API: provide common exception class
 *
 * <h2>Common exceptions functionalities, tracing for debug...</h2>
 *
 * <p>This API is used to create exception object in the same way
 * everywhere in projects. It provides tracing support and macro to
 * include file position in trace</p>
 */

namespace ToolBox
{
  /**
   * macro used to add file position (filename and line to the
   * exception), it uses preprocessor functions.
   */
#define HERE	__FILE__, __LINE__


  /**
   * macro used to define header of an Exception class
   * @param Name the name of class
   * @param From the name of superclass
   */
#define ExceptionHeader(Name, From)		\
  class  Name : public From			\
  {						\
  public:					\
    Name(const std::string &what,		\
         const std::string &file, int line)	\
          throw();				\
    Name(const Exception &e,			\
	 const std::string &file, int line)	\
	  throw();				\
    virtual ~Name() throw();			\
						\
  private:					\
    Name& operator=(const Name &e);		\
    Name();					\
  }

  /**
   * macro used to define the implementation of an Exception
   * class. The implementation call the superclass constructor.
   * @param Name the name of class
   * @param From the name of superclass
   */
#define ExceptionCore(Name, From)		\
  Name::Name(const std::string &vwhat,		\
         const std::string &file, int line) 	\
    throw() : From(vwhat, file, line)  {}	\
  Name::Name(const Exception &e,		\
         const std::string &file, int line) 	\
    throw() : From(e, file, line)  {}		\
  Name::~Name() throw() {}

  /// store stack of exception
  class StackTrace
  {
  public:
    /// constructor
    StackTrace(const std::string &error, const std::string &file, unsigned line);
    /// destructor
    ~StackTrace();

  private:
    /// avoid default constructor
    StackTrace();

  public:
    /**
     * @brief get the error message of exception
     */
    const std::string& getError() const;
    /**
     * @brief get the filename where exception has been launched
     */
    const std::string& getFile() const;
    /**
     * @brief get the line of the file where exception has been
     * launched
     */
    const int getLine() const;

  protected:
    /// @brief the error message of exception
    std::string	_error;
    /// @brief the filename where exception has been launched
    std::string	_file;
    /// @brief the line of file where exception has been launched
    int		_line;
  };

  /**
   * @brief Generic definition of an exception. This is the
   * superclass of all kind of exception, it contains all
   * implementation.
   * @author Julien Lemoine <speedblue@happycoders.org>
   */
  class Exception : public std::exception
  {
  public:
    /**
     * @brief constructor of exception and add a exception on the stack
     * @param what the description of the error
     * @param file and line are filled using the {@link HERE} macro.
     */
    Exception(const std::string &what,
	      const std::string &file, int line) throw();
    /**
     * @brief constructor of exception from a previous one. This
     * constructor add a trace of current filename and position in the
     * output of exception. This method is usefull for debug purpose.
     * @param e represent the previous exception
     * @param file and line are filled using the {@link HERE} macro.
     */
    Exception(const Exception& e, const std::string &file, 
	      int line) throw();
    /// destructor
    virtual ~Exception() throw();

  public:
    /**
     * @brief compatibility method to be compatible with
     * std::exception. It gives the same result as {@link getError}
     * with char* instead of std::string.
     */
    const char* what() const throw();
    /**
     * @brief get the error message of exception
     */
    const std::string& getError() const;
    /**
     * @brief get the filename where exception has been launched
     */
    const std::string& getFile() const;
    /**
     * @brief get the line of the file where exception has been
     * launched
     */
    const int getLine() const;
    /**
     * @brief display the complet trace of exception.
     */
    void print(std::ostream& stream) const;

  private:
    /// @brief avoid default constructor
    Exception();
    /// @brief avoid affectation operator
    Exception& operator=(const Exception&);

  protected:
    /// @brief stack trace
    std::list<StackTrace>	_trace;
  };

  /**
   * @brief display the complet trace of exception in a
   * std::ostream. This method calls {@link ToolBox::Exception::display}.
   */
  std::ostream& operator<<(std::ostream& stream, const Exception& e);

  // all subclass headers of superclass Exception
  ExceptionHeader(EmptyException, Exception);
  ExceptionHeader(ExecException, Exception);
  ExceptionHeader(MemoryError, Exception);
  ExceptionHeader(CancelAlgorithm, Exception);
  ExceptionHeader(StrtolError, Exception);
  ExceptionHeader(ThreadError, Exception);
  ExceptionHeader(ParseError, Exception);
  ExceptionHeader(Sentinel, Exception);
  ExceptionHeader(NullPointer, Exception);
  ExceptionHeader(InputException, Exception);
  ExceptionHeader(FileException, InputException);
  ExceptionHeader(EOFException, FileException);
  ExceptionHeader(MD5Exception, InputException);
  ExceptionHeader(XmlException, InputException);
  ExceptionHeader(DbException, InputException);
  ExceptionHeader(LibraryException, Exception);
  ExceptionHeader(ColumnException, Exception);
  ExceptionHeader(InvalidIndex, Exception);
  ExceptionHeader(InvalidMatrix, Exception);
  ExceptionHeader(NetException, Exception);
  ExceptionHeader(HostnameError, NetException);
  ExceptionHeader(Ipv6SupportError, NetException);
  ExceptionHeader(InetptonError, NetException);
  ExceptionHeader(InetntopError, NetException);
  ExceptionHeader(ConnectionClosed, NetException);
  ExceptionHeader(NoConnection, NetException);
  ExceptionHeader(Timeout, NetException);
  ExceptionHeader(BindError, NetException);
  ExceptionHeader(SocketError, NetException);
  ExceptionHeader(ListenError, NetException);
  ExceptionHeader(SetsockoptError, NetException);
  ExceptionHeader(CloseError, NetException);
  ExceptionHeader(SelectError, NetException);
  ExceptionHeader(ConnectError, NetException);
  ExceptionHeader(AcceptError, NetException);
  ExceptionHeader(GetpeernameError, NetException);
  ExceptionHeader(UnicodeError, Exception);
  ExceptionHeader(TokenizerError, Exception);
  ExceptionHeader(CompilerError, Exception);
  ExceptionHeader(PoolError, Exception);
}

namespace ToolBox
{
  StackTrace::StackTrace(const std::string &error, const std::string &file, unsigned line) :
    _error(error), _file(file), _line(line)
  {
  }

  StackTrace::~StackTrace()
  {
  }

  const std::string& StackTrace::getError() const
  {
    return _error;
  }

  const std::string& StackTrace::getFile() const
  {
    return _file;
  }

  const int StackTrace::getLine() const
  {
    return _line;
  }

  Exception::Exception(const Exception& e, 
		       const std::string &file, int line) throw()
  {
    _trace = e._trace;
    _trace.push_back(StackTrace("", file, line));
  }

  Exception::Exception(const std::string& err, 
		       const std::string &file, int line) throw()
  {
    _trace.push_back(StackTrace(err, file, line));
  }

  Exception::~Exception() throw()
  {
  }

  const char* Exception::what() const throw()
  {
    assert(!_trace.empty());
    return _trace.front().getError().c_str();
  }

  const std::string& Exception::getError() const
  {
    assert(!_trace.empty());
    return _trace.front().getError();
  }

  const std::string& Exception::getFile() const
  {
    assert(!_trace.empty());
    return _trace.front().getFile();
  }

  const int Exception::getLine() const
  {
    assert(!_trace.empty());
    return _trace.front().getLine();
  }

  void Exception::print(std::ostream& stream) const
  {
    bool first = true;
    stream << "Exception : " << std::endl;
    for (std::list<StackTrace>::const_iterator it = _trace.begin();
	 it != _trace.end(); ++it)
      {
	if (it->getError().size())
	  stream << "Error[" << it->getError() << "] ";
	stream << (first ? "throwed at [" : "catched at [") 
	       << it->getFile() << ":" << it->getLine() << "]" << std::endl;
	first = false;
      }
  }

  std::ostream& operator<<(std::ostream& stream, const Exception& e)
  {
    e.print(stream);
    return (stream);
  }

  // all subclass implementation of superclass Exception
  ExceptionCore(EmptyException, Exception)
  ExceptionCore(ExecException, Exception)
  ExceptionCore(MemoryError, Exception)
  ExceptionCore(CancelAlgorithm, Exception)
  ExceptionCore(StrtolError, Exception)
  ExceptionCore(ThreadError, Exception)
  ExceptionCore(ParseError, Exception)
  ExceptionCore(Sentinel, Exception)
  ExceptionCore(NullPointer, Exception)
  ExceptionCore(InputException, Exception)
  ExceptionCore(FileException, InputException)
  ExceptionCore(EOFException, FileException)
  ExceptionCore(MD5Exception, InputException)
  ExceptionCore(XmlException, InputException)
  ExceptionCore(DbException, InputException)
  ExceptionCore(LibraryException, Exception)
  ExceptionCore(ColumnException, Exception)
  ExceptionCore(InvalidIndex, Exception)
  ExceptionCore(InvalidMatrix, Exception)
  ExceptionCore(NetException, Exception)
  ExceptionCore(HostnameError, NetException)
  ExceptionCore(Ipv6SupportError, NetException)
  ExceptionCore(InetptonError, NetException)
  ExceptionCore(InetntopError, NetException)
  ExceptionCore(ConnectionClosed, NetException)
  ExceptionCore(NoConnection, NetException)
  ExceptionCore(Timeout, NetException)
  ExceptionCore(BindError, NetException)
  ExceptionCore(SocketError, NetException)
  ExceptionCore(ListenError, NetException)
  ExceptionCore(SetsockoptError, NetException)
  ExceptionCore(CloseError, NetException)
  ExceptionCore(SelectError, NetException)
  ExceptionCore(ConnectError, NetException)
  ExceptionCore(AcceptError, NetException)
  ExceptionCore(GetpeernameError, NetException)
  ExceptionCore(UnicodeError, Exception)
  ExceptionCore(TokenizerError, Exception)
  ExceptionCore(CompilerError, Exception)
  ExceptionCore(PoolError, Exception)
}

template <typename T>
ToolBox::Trie<T>::Trie(const T &empty) :
  _empty(empty), _factory(0x0), _initialNode(0x0)
{
  // initialize nodes by paquets of 10000
  _factory = new TrieFactory<T>(10000);
  _initialNode = _factory->getNewNode(_empty);
}

template <typename T>
ToolBox::Trie<T>::~Trie()
{
  if (_factory)
    delete _factory;
}

template <typename T>
void ToolBox::Trie<T>::setEntry(const char *str, unsigned strLen, const T &value)
{
  TrieNode<T>	*node = _addEntry(str, strLen);
  node->setValue(value);
}

template <typename T>
ToolBox::TrieNode<T>* ToolBox::Trie<T>::_addEntry(const char *str, unsigned strLen)
{
  unsigned	pos = 0;
  bool		found = true;
  TrieNode<T>	*node = _initialNode, *previous = 0x0;

  // Look for the part of the word which is in Trie
  while (found && pos < strLen)
    {
      found = false;
      previous = node;
      node = node->getSubNodeByLabel(str[pos]);
      if (node)
	    {
	      found = true;
	      ++pos;
	    }
    }

  // Add part of the word which is not in Trie
  if (!node || pos != strLen)
  {
    node = previous;
    for (unsigned i = pos; i < strLen; ++i)
    {
      TrieNode<T> *newNode = _factory->getNewNode(_empty);
      node->addSubNode(str[pos], newNode);
      node = newNode;
      ++pos;
    }
  }
  assert(node != 0x0);
  return node;
}

template <typename T>
void ToolBox::Trie<T>::addEntry(const char *str, unsigned strLen, const T &value)
{
  TrieNode<T>	*node = _addEntry(str, strLen);

  // Set the value on the last node
  if (node && node->getValue() != _empty)
    throw ToolBox::Exception("The word is already in automaton", HERE);
  node->setValue(value);
}

template <typename T>
const T& ToolBox::Trie<T>::getEntry(const char *str, unsigned strLen) const
{
  unsigned		pos = 0;
  bool			found = true;
  const TrieNode<T>	*node = _initialNode;
	
  while (found && pos < strLen)
    {
      found = false;
      node = node->getSubNodeByLabel(str[pos]);
      if (node)
	{
	  found = true;
	  ++pos;
	}
    }
  if (node && pos == strLen) // The word is complet in the automaton
    return node->getValue();
  return _empty;
}

template <typename T>
const ToolBox::TrieNode<T>* ToolBox::Trie<T>::getInitialNode() const
{
  return _initialNode;
}

template <typename T>
void ToolBox::Trie<T>::clear()
{
  _factory->clear();
  _initialNode = _factory->getNewNode(_empty);
}

template <typename T>
void ToolBox::Trie<T>::display(std::ostream &os)
{
  if (_initialNode)
    _initialNode->display(os, 0, 0);
}

// ----------------------------------------------------------------------
// Aux

using ToolBox::Trie;
using ToolBox::TrieNode;

struct PriorityFrequency {
  PriorityFrequency() {};
  PriorityFrequency(int _frequency, int _priority, const string& _word) 
    : frequency(_frequency), priority(_priority), word(_word) {}
  int frequency;
  int priority;
  string word;
  bool operator== (const PriorityFrequency& other) const {
    return frequency == other.frequency && priority == other.priority && word == other.word;
  }
  bool operator!= (const PriorityFrequency& other) const {
    return frequency != other.frequency || priority != other.priority || word != other.word;
  }
  static PriorityFrequency Empty() {
    return PriorityFrequency(-1, -1, string());
  }
};



typedef vector<pair<string, int> > Vocabulary;

// ----------------------------------------------------------------------
// Trie traverser class

class TrieTraverser {
public:
  TrieTraverser(const Trie<PriorityFrequency>* trie, const TrieNode<PriorityFrequency>* trie_node, 
                const string& matched_string);
  inline bool HasMatchedSuccessfully() const;
  inline bool CanMatch(char symbol) const;
  inline TrieTraverser Match(char symbol);
  inline string GetMatchedString() const;
  inline PriorityFrequency GetNodeValue() const;
private:
  const Trie<PriorityFrequency>* trie_;
  const TrieNode<PriorityFrequency>* trie_node_;
  string matched_string_;
};

TrieTraverser::TrieTraverser(const Trie<PriorityFrequency>* trie, 
                             const TrieNode<PriorityFrequency>* trie_node, 
                             const string& matched_string) :
  trie_(trie), trie_node_(trie_node), matched_string_(matched_string) {
}

bool TrieTraverser::HasMatchedSuccessfully() const {
  return trie_node_->getValue() != PriorityFrequency::Empty();
}

bool TrieTraverser::CanMatch(char symbol) const {
  return trie_node_->getSubNodeByLabel(symbol) != 0x0;
}

TrieTraverser TrieTraverser::Match(char symbol) {
  matched_string_.push_back(symbol);
  return TrieTraverser(trie_, trie_node_->getSubNodeByLabel(symbol), matched_string_);
}

string TrieTraverser::GetMatchedString() const {
  return matched_string_;
}

PriorityFrequency TrieTraverser::GetNodeValue() const {
  return trie_node_->getValue();
}
//const State* TrieTraverser::GetState() const {
//  return state_;
//}



// ----------------------------------------------------------------------
// Text message builder class

struct MessageObject {
  MessageObject() : change_count(0) {}
  string code;
  int change_count;
};


struct WordHypothesis {
  WordHypothesis(const string& _word, int _frequency, int _priority, int _terminal_state_index) 
    : word(_word), frequency(_frequency), priority(_priority), 
      terminal_state_index(_terminal_state_index) {}
  string word;
  int frequency;
  int priority;
  int terminal_state_index;
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

typedef set<WordHypothesis, WordHypothesisComparator> HypothesisSet;

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
  string GetWord(const MessageObject& message_object, double& match_wait, double& hypothesis_wait);
  HypothesisSet GetMatchedWords(const string& code);
  Trie<PriorityFrequency> trie_;
  vector<MessageObject> message_objects_;
  int priority_timer_;
  vector<string> letters_;
};

TextMessageBuilder::TextMessageBuilder() : trie_(PriorityFrequency::Empty()) {
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
  //clock_t start, finish;
  //
  //start = clock();

  priority_timer_ = 0;

  trie_.clear();
  for (Vocabulary::const_iterator word_it = vocabulary.begin(); 
    word_it != vocabulary.end(); ++word_it) {
    trie_.addEntry(word_it->first.c_str(), word_it->first.length(), 
                   PriorityFrequency(word_it->second, 0, word_it->first));
  }

  //finish = clock();
  //cout << "Set vocabulary in " << static_cast<double>(finish - start) << " ms" << endl;
}

string TextMessageBuilder::ConvertToText(const string &message) {
  ParseMessageCode(message);
  
  double match_wait = 0, hypothesis_wait = 0;
  string message_text;
  for (vector<MessageObject>::iterator message_object_it = message_objects_.begin();
       message_object_it != message_objects_.end(); ++message_object_it) {
    if (IsPunctuationSymbol(*message_object_it)) {
      message_text.append(GetPunctuationSymbol(*message_object_it));
    } else if (IsSpace(*message_object_it)) {
      message_text.append(GetSpace(*message_object_it));
    } else {
      message_text.append(GetWord(*message_object_it, match_wait, hypothesis_wait));    
    }
  }
  //cout << "Match in " << match_wait << " ms, " 
  //  << "hypothesis in " << hypothesis_wait << " ms, " << endl;
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

string TextMessageBuilder::GetWord(const MessageObject &message_object, double& match_wait, double& hypothesis_wait) {
  //clock_t start;

  //start = clock();
  HypothesisSet hypotheses = GetMatchedWords(message_object.code);
  //match_wait += static_cast<double>(clock() - start);

  //start = clock();
  HypothesisSet::iterator answer_hypothesis_it = hypotheses.begin();
  for (int change_index = 0; change_index < message_object.change_count; ++change_index) {
    ++answer_hypothesis_it;
  }
  
  ++priority_timer_;
  trie_.setEntry(answer_hypothesis_it->word.c_str(), answer_hypothesis_it->word.length(),
    PriorityFrequency(answer_hypothesis_it->frequency + 1, priority_timer_, answer_hypothesis_it->word));
  //hypothesis_wait += static_cast<double>(clock() - start);


  return answer_hypothesis_it->word;
}

HypothesisSet TextMessageBuilder::GetMatchedWords(const string &code) {
  queue<const TrieNode<PriorityFrequency>* > old_states, new_states;

  old_states.push(trie_.getInitialNode());
  string::const_iterator code_it = code.begin();
  while (code_it != code.end()) {
    int code_number = *code_it - kZeroChar;
    
    while (!old_states.empty()) {
      const TrieNode<PriorityFrequency>* front_node = old_states.front();
      old_states.pop();

      for (string::iterator letter_it = letters_[code_number].begin();
           letter_it != letters_[code_number].end(); ++letter_it) {
             const TrieNode<PriorityFrequency>* sub_node = front_node->getSubNodeByLabel(*letter_it);
        if (sub_node) {
          new_states.push(sub_node);
        }
      }
    }

    std::swap(old_states, new_states);
    ++code_it;
  }

  HypothesisSet hypotheses;
  while (!old_states.empty()) {
    const TrieNode<PriorityFrequency>* front_node = old_states.front();
    old_states.pop();
    PriorityFrequency front_value = front_node->getValue();
    if (front_value != PriorityFrequency::Empty()) {
      hypotheses.insert(
        WordHypothesis(front_value.word, front_value.frequency, front_value.priority, 0));
    }
  }

  return hypotheses;
}

//HypothesisSet TextMessageBuilder::GetMatchedWords(const string &code) {
//  queue<TrieTraverser> old_states, new_states;
//
//  old_states.push(TrieTraverser(&trie_, trie_.getInitialNode(), string()));
//  string::const_iterator code_it = code.begin();
//  while (code_it != code.end()) {
//    int code_number = *code_it - kZeroChar;
//    
//    while (!old_states.empty()) {
//      TrieTraverser front_traverser = old_states.front();
//      old_states.pop();
//
//      for (string::iterator letter_it = letters_[code_number].begin();
//           letter_it != letters_[code_number].end(); ++letter_it) {
//        if (front_traverser.CanMatch(*letter_it)) {
//          new_states.push(front_traverser.Match(*letter_it));
//        }
//      }
//    }
//
//    std::swap(old_states, new_states);
//    ++code_it;
//  }
//
//  HypothesisSet hypotheses;
//  while (!old_states.empty()) {
//    TrieTraverser front_traverser = old_states.front();
//    old_states.pop();
//    if (front_traverser.HasMatchedSuccessfully()) {
//      PriorityFrequency node_value = front_traverser.GetNodeValue();
//      hypotheses.insert(
//        WordHypothesis(front_traverser.GetMatchedString(), node_value.frequency,
//                       node_value.priority, 0));
//    }
//  }
//
//  return hypotheses;
//}

//HypothesisSet TextMessageBuilder::GetMatchedWords(const string &code) {
//  queue<TrieTraverser> old_states, new_states;
//
//  old_states.push(TrieTraverser(&trie_, trie_.getInitialNode(), string()));
//  string::const_iterator code_it = code.begin();
//  while (code_it != code.end()) {
//    int code_number = *code_it - kZeroChar;
//    
//    while (!old_states.empty()) {
//      TrieTraverser front_traverser = old_states.front();
//      old_states.pop();
//
//      for (string::iterator letter_it = letters_[code_number].begin();
//           letter_it != letters_[code_number].end(); ++letter_it) {
//        if (front_traverser.CanMatch(*letter_it)) {
//          new_states.push(front_traverser.Match(*letter_it));
//        }
//      }
//    }
//
//    std::swap(old_states, new_states);
//    ++code_it;
//  }
//
//  HypothesisSet hypotheses;
//  while (!old_states.empty()) {
//    TrieTraverser front_traverser = old_states.front();
//    old_states.pop();
//    if (front_traverser.HasMatchedSuccessfully()) {
//      PriorityFrequency node_value = front_traverser.GetNodeValue();
//      hypotheses.insert(
//        WordHypothesis(front_traverser.GetMatchedString(), node_value.frequency,
//                       node_value.priority, 0));
//    }
//  }
//
//  return hypotheses;
//}

//HypothesisSet TextMessageBuilder::GetMatchedWords(const string &code) {
//  queue<string> old_states, new_states;
//
//  old_states.push(string());
//  string::const_iterator code_it = code.begin();
//  while (code_it != code.end()) {
//    int code_number = *code_it - kZeroChar;
//    
//    while (!old_states.empty()) {
//      string front_string = old_states.front();
//      old_states.pop();
//
//      for (string::iterator letter_it = letters_[code_number].begin();
//           letter_it != letters_[code_number].end(); ++letter_it) {
//        string new_string = front_string + *letter_it;
//        if (trie_.checkEntry(new_string.c_str(), new_string.length())) {
//          new_states.push(new_string);
//        }
//      }
//    }
//
//    std::swap(old_states, new_states);
//    ++code_it;
//  }
//
//  HypothesisSet hypotheses;
//  while (!old_states.empty()) {
//    string front_string = old_states.front();
//    old_states.pop();
//    PriorityFrequency front_entry = trie_.getEntry(front_string.c_str(), front_string.length());
//    if (front_entry != PriorityFrequency::Empty()) {
//      hypotheses.insert(
//        WordHypothesis(front_string, front_entry.frequency,
//                       front_entry.priority, 0));
//    }
//  }
//
//  return hypotheses;
//}

// ----------------------------------------------------------------------
// Input/Output

void Input(Vocabulary* vocabulary, string* message) {
  int vocabulary_size;
  scanf("%d", &vocabulary_size);
  vocabulary->resize(vocabulary_size);

  const int kMaxWordSize = 20;
  for (int word_index = 0; word_index < vocabulary_size; ++word_index) {
    char word[kMaxWordSize + 1];
    int frequency;
    scanf("%s %d", word, &frequency);
    vocabulary->at(word_index) = std::make_pair(string(word), frequency);
  }

  cin >> std::ws;
  std::getline(cin, *message);
}

//void TestInput1(Vocabulary* vocabulary, string* message) {
//  vocabulary->insert(std::make_pair("ad", 2));
//  vocabulary->insert(std::make_pair("be", 1));
//  vocabulary->insert(std::make_pair("not", 10));
//  vocabulary->insert(std::make_pair("or", 5));
//  vocabulary->insert(std::make_pair("to", 50));
//
//  *message = "86 23* 67 668 86 231**";
//}
//
//void TestInput2(Vocabulary* vocabulary, string* message) {
//  vocabulary->insert(std::make_pair("act", 1));
//  vocabulary->insert(std::make_pair("bat", 1));
//  vocabulary->insert(std::make_pair("cat", 1));
//
//  *message = "228* 228** 228** 228**1";
//}
//
//Vocabulary CreateVocabulary(const string& message) {
//  for (char first_letter = 'a'; first_letter <= 'z'; ++first_letter) {
//    for (char second_letter = 'a'; second_letter <= 'z'; ++second_letter) {
//      for (char third_letter = 'a'; third_letter <= 'z'; ++third_letter) {
//        string word;
//        word.push_back(first_letter);
//        word.push_back(second_letter);
//        word.push_back(third_letter);
//        int frequency = rand();
//        vocabulary->insert(std::make_pair(word, 0));
//      }
//    }
//  }
//
//  for (char first_letter = 'a'; first_letter <= 'z'; ++first_letter) {
//    for (char second_letter = 'a'; second_letter <= 'z'; ++second_letter) {
//      for (char third_letter = 'a'; third_letter <= 'z'; ++third_letter) {
//        for (char fourth_letter = 'a'; fourth_letter <= 'b'; ++fourth_letter) {
//          string word;
//          word.push_back(first_letter);
//          word.push_back(second_letter);
//          word.push_back(third_letter);
//          word.push_back(fourth_letter);
//          int frequency = rand();
//          vocabulary->insert(std::make_pair(word, 0));
//        }
//      }
//    }
//  }
//}
//
//string CreateMessage() {
//  const int kMaxWordCount = 20000;
//  srand(25);
//  std::ostringstream oss;
//  
//  for (int word_index = 0; word_index < kMaxWordCount; ++word_index)
//  {
//    int oracle = rand() % 4;
//    if (oracle == 0) {
//      oss << 1;
//    } else {
//      oss << rand() % 8 + 2;
//      oss << rand() % 8 + 2;
//      oss << rand() % 8 + 2;
//    }
//    int change_count = rand() % ((oracle == 0) ? 3 : 2);
//    for (int change_index = 0; change_index < change_count; ++change_index) {
//      oss << '*';
//    }
//    int space_count = rand() % 5 + 1;
//    for (int space_index = 0; space_index < space_count; ++space_index) {
//      oss << ' ';
//    }
//  }
//
//  return oss.str();
//}

//vector<MessageObject> CreateMessage() {
//  const int kMessageObjectCount = 11500;
//  //const int kMessageObjectCount = 1000;
//  vector<MessageObject> message_objects;
//  bool was_word = false;
//  for (int object_index = 0; object_index < kMessageObjectCount; ++object_index) {
//    int oracle = rand() % 7;
//    if (oracle > 1 && !was_word) {
//      // word
//      was_word = true;
//      std::ostringstream oss;
//      int word_length = rand() % 5 + 16;
//      for (int letter_index = 0; letter_index < word_length; ++letter_index) {
//        int letter = rand() % 8 + 2;
//        oss << letter;
//      }
//      int change_count = rand() % 20;
//      MessageObject word_object;
//      word_object.code = oss.str();
//      word_object.change_count = change_count;
//      message_objects.push_back(word_object);
//    } else if (oracle == 1) {
//      // punctuation
//      was_word = false;
//      MessageObject punctuation_object;
//      punctuation_object.code.push_back('1');
//      punctuation_object.change_count = rand() % 3;
//      message_objects.push_back(punctuation_object);
//      
//    } else {
//      // space
//      was_word = false;
//      MessageObject space_object;
//      int space_count = rand() % 3 + 1;
//      for (int space_index = 0; space_index < space_count; ++space_index) {
//        space_object.code.push_back(' ');
//      }
//      message_objects.push_back(space_object);
//      
//    }
//  }
//  return message_objects;
//}
//
//string CreateMessageString(const vector<MessageObject>& message) {
//  std::ostringstream oss;
//  for (vector<MessageObject>::const_iterator object_it = message.begin();
//       object_it != message.end(); ++object_it) {
//    oss << object_it->code;  
//    for (int change_index = 0; change_index < object_it->change_count; ++change_index) {
//      oss << '*';
//    }
//  }
//  return oss.str();
//}
//
//typedef map<string, int> VocabularyMap;
//
//VocabularyMap CreateVocabulary(const vector<MessageObject>& message_objects) {
//  vector<string> letters;
//  letters.resize(10);
//  letters[2] = "abc";
//  letters[3] = "def";
//  letters[4] = "ghi";
//  letters[5] = "jkl";
//  letters[6] = "mno";
//  letters[7] = "pqrs";
//  letters[8] = "tuv";
//  letters[9] = "wxyz";
//  
//  VocabularyMap vocabulary;
//
//  for (vector<MessageObject>::const_iterator object_it = message_objects.begin();
//       object_it != message_objects.end(); ++object_it) {
//    if (object_it->code[0] == ' ' || object_it->code[0] == '1') {
//      continue;
//    }
//
//    for (int change_index = 0; change_index < object_it->change_count + 1; ++change_index) {
//
//      string word;
//      do 
//      {
//        word.clear();
//        for (unsigned int letter_index = 0; letter_index < object_it->code.size(); ++letter_index) {
//          word.push_back(letters[object_it->code[letter_index] - '0'][rand() % 3]);
//
//        }
//      } while (vocabulary.find(word) != vocabulary.end());
//
//      vocabulary.insert(std::make_pair(word, rand() % 1000 + 1));
//    }
//  }
//
//  return vocabulary;
//}
//
//void BigRandomInput(Vocabulary* vocabulary, string* message) {
//  vector<MessageObject> message_objects = CreateMessage();
//  *message = CreateMessageString(message_objects);
//  VocabularyMap vocabulary_map = CreateVocabulary(message_objects);
//  vocabulary->resize(vocabulary_map.size());
//  int word_index = 0;
//  for (VocabularyMap::iterator word_it = vocabulary_map.begin(); 
//       word_it != vocabulary_map.end(); ++word_it) {
//    vocabulary->at(word_index) = std::make_pair(word_it->first, word_it->second);
//    ++word_index;
//  }
//}

// ----------------------------------------------------------------------
// main

int main() {
  Vocabulary vocabulary;
  string message;
  //BigRandomInput(&vocabulary, &message);
  Input(&vocabulary, &message);
  //TestInput2(&vocabulary, &message);
  TextMessageBuilder text_message_builder;
  
  text_message_builder.SetVocabulary(vocabulary);
  cout << text_message_builder.ConvertToText(message) << endl;
  //text_message_builder.ConvertToText(message);

  return 0;
}
