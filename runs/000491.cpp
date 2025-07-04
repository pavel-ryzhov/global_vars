#include <stdlib.h>
#include <string.h> //for strlen()

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

/* yat stands for a _ya_ndex _t_est :)
 */
namespace yat {

/* namespace for constants
 */
namespace k {
/* represents null item for char type
 */
const char null_char = '\0';
} //namespace k


/* splittable search key
 *
 * this key can be splitted into items
 * whole key is of std::string type and items is of char type
 *
 * for a future use it is needed to parametrize this class
 * by an item type, but for now -> skip it
 */
class string_key {

private:
    // key value
    std::string  __key_value;

    // key frequency
    int __key_frequency;
    int __key_relevancy;

public:

    /* default ctor
     */
    string_key() :
    __key_frequency(0), __key_relevancy(0) { }

    /* ctor that constructs key
     */
    string_key(const std::string& key) {
        set_value(key);
        __key_frequency = 0;
        __key_relevancy = 0;
    }

    /* ctor that constructs key
     * and sets frequency
     */
    string_key(const std::string& key, int key_freq) {
        set_value(key);
    	__key_frequency = key_freq;
    	__key_relevancy = 0;
    }

    /* sets key usage frequency
     */
    void set_frequency(int key_freq) {
        __key_frequency = key_freq;
    }

    /* key frequency getter
     */
    int get_frequency() const {
        return __key_frequency;
    }

    void set_relevancy(int key_rel) {
        __key_relevancy = key_rel;
    }

    int get_relevancy() const {
    	return __key_relevancy;
    }

    void set_value(const std::string& new_key) {
        __key_value.clear();
        __key_value.resize(0);

        __key_value = new_key;
    }

    /* sets key
     */
    void set(const std::string& new_key, int frequency) {
    	set_value(new_key);
    	set_frequency(frequency);
    	__key_relevancy = 0;
    }

    void set(const string_key& rhs) {
    	__key_value = rhs.get_full_key();
    	__key_frequency = rhs.get_frequency();
    	__key_relevancy = rhs.get_relevancy();
    }

    void extend(char item) {
    	__key_value += item;
    }

    void extend(const std::string& items) {
    	__key_value += items;
    }

    /* returns key[index] item
     *
     * if given index is behind the key's upper boundary
     * then k::null_char is returned
     */
    char at(unsigned int index) const {

        //__key_value.length() decreased due to
        //(__key_value.length() - 1) represents maximum index
        //while __key_value.length() - number of elements
        if( index > (__key_value.length() - 1) )
            return k::null_char;

        return __key_value[index];
    }

    /* key value getter
     */
    std::string get_full_key() const {
    	return __key_value;
    }

    /* cleans key value and frequency
     */
    void clear() {
    	__key_value.clear();
    	__key_frequency = 0;
    }

    bool operator< (const string_key& rhs) const {
    	return (__key_value < rhs.get_full_key());
    }

    bool operator== (const string_key& rhs) const {
    	return (__key_value == rhs.get_full_key());
    }

    bool operator> (const string_key& rhs) const {
    	return (__key_value > rhs.get_full_key());
    }


}; //class string_key

/* sorted collection of a unique keys
 */
typedef std::set<string_key> unique_key_collection_t;

/* Ternary search tree.
 *
 * key_t is used to represent splittable search keys as well
 * as a container for data to be inserted into tree
 *
 * item_t is used to represent items of a key_t
 *
 * key_t and item_t must coexist together well (f.ex. if key_t
 * is a string, then item_t has to be a char), for now the task
 * for the coexistence must be solved manually through template
 * parameters, must to change this in future
 *
 * NOTE: item_t's support of operators <, >, == is must!
 *
 * key_collection_t is used to represent a collection of keys
 */
template<
	typename item_t,
	item_t   null_item,
	typename key_t,
	typename key_collection_t
		>
class search_tree {
private:
	int __relevance;

    struct tree_node {
        item_t  item;
        bool 	is_terminator;
        int     frequency;
        int		relevancy;
        tree_node *lo_kid, *eq_kid, *hi_kid;

        tree_node(item_t new_item):
        	item(new_item), is_terminator(false),
        	frequency(0), relevancy(0),
        	lo_kid(NULL), eq_kid(NULL),	hi_kid(NULL) { }
    };

    typedef tree_node *tree_node_ptr_t;

    /* pointer to a head node (root) of a tree
     */
    tree_node_ptr_t __tree_head;

    /* tree cleanup
     *
     * correctly disposes all tree nodes
     */
    void _cleanup_tree(tree_node_ptr_t& node) {

    	__relevance = 0;

    	if (!node)
    		return;

    	_cleanup_tree(node->lo_kid);
        _cleanup_tree(node->eq_kid);
        _cleanup_tree(node->hi_kid);

        delete node;
    }

    /* inserts a key into a tree
     */
    void _insert_recursive(
            tree_node_ptr_t& node, const key_t& key, unsigned int index) {

        item_t temp_item = key.at(index);

        if ( !node ) {
        	node = new tree_node(temp_item);
        }


        if( null_item == temp_item ) {

            node->frequency = key.get_frequency();
            node->is_terminator = true;

        } else {

            if( temp_item < node->item )
                _insert_recursive(node->lo_kid, key, index);

            if( temp_item == node->item )
                _insert_recursive(node->eq_kid, key, ++index);

            if( temp_item > node->item )
                _insert_recursive(node->hi_kid, key, index);
        }

    }

    /* gets the key subtree
     *
     * walks over the tree using key items
     * returns a pointer to a node that contains the last key item
     */
    tree_node_ptr_t _get_key_subtree_recursive(
            tree_node_ptr_t node, const key_t& key, unsigned int index) {

        item_t temp_item = key.at(index);
        item_t next_item = key.at(index + 1);

        if( !node )
            return NULL;

        if( temp_item < node->item )
        	return _get_key_subtree_recursive(node->lo_kid, key, index);

        if( temp_item == node->item ){
            if( null_item == next_item )
                return node;

            return _get_key_subtree_recursive(node->eq_kid, key, ++index);
        }

        if( temp_item > node->item )
        	return _get_key_subtree_recursive(node->hi_kid, key, index);

        //should not be reached!
        return NULL;
    }


    /* searches for postfixes to a key (prefix_key) in a subtree
     * starting with a node
     *
     * restricted_keys are used to indicate if we already have been
     * used some keys (when user hits key '*' the previous key should
     * be put into restricted_keys to exclude it in next search results)
     *
     * node - subtree head that has been looked for postfixes
     *
     * prefix_key - technical value, used to construct the hole key
     * in order to check if a found key is not in restricted_keys
     *
     * found_key - value of a key (result of a search), it is one for
     * the whole subtree
     *
     * pretender_key - local copy of a key constructed by walking over nodes
     * (it differs from path to path)
     */
    void _search_postfix_recursive(
    		tree_node_ptr_t node,
    		const key_t& prefix_key,
    		key_t& found_key, key_t pretender_key,
    		const key_collection_t& restricted_keys ) {

    	if(!node)
    		return;

    	/* if a node is terminator (*) -> check if a pretender key has more frequency
    	 * then the previous key found, and stop search in this branch (as it is the last node)
    	 *
    	 * (*) a terminator node is a node that linked at the end of each subtree that holds a key,
    	 * it contains information about key attributes (frequency) and has empty item field
    	 */
    	if( node->is_terminator ) {
    		int found_key_freq, pretender_key_freq;
    		int found_key_relv, pretender_key_relv;

    		found_key_freq = found_key.get_frequency();
    		found_key_relv = found_key.get_relevancy();

    		pretender_key_freq = node->frequency;
    		pretender_key_relv = node->relevancy;

    		key_t temp_key;

    		temp_key.extend(prefix_key.get_full_key());
    		temp_key.extend(pretender_key.get_full_key());

    		temp_key.set_frequency(pretender_key_freq);
    		temp_key.set_relevancy(pretender_key_relv);

    		//check if a pretender_key is in restricted_keys
    		//(this means that this key have been already used and
    		// since it must be excluded from further examination)
    		if( 0 != restricted_keys.count(temp_key) )
    			return;

   			if( pretender_key_freq > found_key_freq ) {
   				found_key.set(temp_key);
   			}

   			if ( ( pretender_key_freq == found_key_freq ) &&
   					(pretender_key_relv > found_key.get_relevancy() ) ) {
   		   		found_key.set(temp_key);
   		   	}

   			return;
    	}

    	/* !!! very important !!!
    	 *
    	 * 1) branching in ternary search trees goes at a constant index
    	 * 2) technically it looks like subnoding by lo_kid and hi_kid links
    	 * 2) the fact is that the branched nodes are linked to the higher level node
    	 *
    	 *  f.ex. in the following tree:
    	 *
    	 *    node1(item=a)					|	tree_head         				(index=0)
    	 *      |							|      |
    	 *    node2(item=b)---node3(item=c)	|	 eq_kid---hi_kid(of eq_kid)		(index=1)
    	 *
    	 *  the eq_kid for a node1 (tree_head) will be the node2 (with item 'b')
    	 *  and the node3 (with item 'c') will be the hi_kid of a node2
    	 *
    	 *	such tree structure is a result of insertion of keys 'ab' and 'ac'! (*)
    	 *
    	 *  so the valid paths will be 'ab' and 'ac', not 'abc'!!!
    	 *
    	 * 3) in order not to grab alien item during a subtree keys extraction ('b' in 'abc'
    	 * path above) we must not extend pretender_key with current node item for lo_kid
    	 * & hi_kid nodes
    	 *
    	 * (*) it is indeed so! if you don't believe me then ask Robert Sedgewick for details
    	 * he is telling the truth and I guarantee it :)
    	 */

    	//first should be checked eq_kid subtree because eq_kid always means better coincidence

    	string_key preserved_pretender;

    	//saving pretender key due to it modifies while traversing through node->eq_kid
    	preserved_pretender.set(pretender_key);

    	pretender_key.extend(node->item);
    	_search_postfix_recursive(node->eq_kid, prefix_key, found_key, pretender_key, restricted_keys);

    	//restoring pretender key
    	pretender_key.set(preserved_pretender);

		_search_postfix_recursive(node->lo_kid, prefix_key, found_key, pretender_key, restricted_keys);
    	_search_postfix_recursive(node->hi_kid, prefix_key, found_key, pretender_key, restricted_keys);

    }

    /* updates frequency of a word usage (should be called when a user confirms T9 prompt)
     */
    void _update_frequency_recursive(tree_node_ptr_t node, const key_t& key, int index) {

        item_t temp_item = key.at(index);

        if ( !node )
        	return;

        if( null_item == temp_item ) {

        	if(node->is_terminator) {
        		node->frequency += 1;
        		node->relevancy = _get_relevancy_value();
        	}

        } else {

            if( temp_item < node->item )
                _update_frequency_recursive(node->lo_kid, key, index);

            if( temp_item == node->item )
            	_update_frequency_recursive(node->eq_kid, key, ++index);

            if( temp_item > node->item )
            	_update_frequency_recursive(node->hi_kid, key, index);
        }
    }

    int _get_relevancy_value() {
    	return __relevance++;
    }


public:

    search_tree() : __relevance(0), __tree_head(NULL) { }

    ~search_tree() {
        _cleanup_tree(__tree_head);
     }

    void cleanup() {
        _cleanup_tree(__tree_head);
    }

    void insert(const key_t& key) {
        _insert_recursive(__tree_head, key, 0);
    }

    bool search(const key_t& key, key_t& found_key, const key_collection_t& restricted_keys) {

        if( !__tree_head )
        	return false;

        tree_node_ptr_t key_end_node;

        key_end_node = _get_key_subtree_recursive(__tree_head, key, 0);

        if(!key_end_node)
        	return false;

    	key_t postfix_key;
    	key_t pretender_key("", 0);

    	_search_postfix_recursive(
    			key_end_node->eq_kid,
    			key, postfix_key,
    			pretender_key, restricted_keys);

    	found_key.extend(postfix_key.get_full_key());
    	found_key.set_frequency(postfix_key.get_frequency());
    	found_key.set_relevancy(postfix_key.get_relevancy());

        return true;
    }

    void update_frequency(const key_t& key) {
    	_update_frequency_recursive(__tree_head, key, 0);
    }


}; //search_tree

typedef search_tree<
	char, k::null_char, string_key, unique_key_collection_t > string_search_tree_t;

/* keypad character input analyzer
 */
class keypad {
private:
	int __key_one_index;
	std::map< char, std::string > __collection;

	void _insert(char key, const char* chr_val) {
		std::string str_val(chr_val);
		__collection.insert(std::make_pair(key, chr_val));
	}

public:

	/* ctor
	 */
	keypad() {

		__key_one_index = 0;

		_insert('1', ".,?" );
		_insert('2', "abc" );
		_insert('3', "def" );
		_insert('4', "ghi" );
		_insert('5', "jkl" );
		_insert('6', "mno" );
		_insert('7', "qrs" );
		_insert('8', "tuv" );
		_insert('9', "wxyz");
	}

	/* process keypress events
	 *
	 * returns ".", "," or "?" on key 1 press (sequentially switching)
	 * or a string of possible characters otherwise (f.ex. "abc" on key 2)
	 *
	 * NOTE: this function doesn't handle control characters, such as "*" or " "
	 */
	std::string process_keypress(char key) {
		std::string temp;

		if (0 ==__collection.count(key))
			return temp;

		if( '1'== key ) {
			temp = (__collection.at(key))[__key_one_index % 3];

			++__key_one_index;

			return temp;
		}

		__key_one_index = 0;

		return __collection.at(key);
	}

};

/* t9 system class
 *
 * contains search tree (__dictionary) and keypad character input analyzer
 */
class t9 {
private:
	keypad __keypad;
	string_search_tree_t __dictionary;
	unique_key_collection_t __restricted_keys;

	struct __key_progression {
		unsigned int index;
		std::string keys;

		__key_progression() {
			index = 0;
		}

		char get_curernt_key() {
			if( index > keys.size() )
				return k::null_char;

			return keys[index];
		}

		char get_next_key() {
			if( index > keys.size() )
				return k::null_char;

			return keys[++index];
		}

		char get_key() {
			if( index > keys.size() )
				return k::null_char;

			return keys[index++];
		}

	};

	std::vector< __key_progression > __key_progression_collection;

	typedef std::vector< __key_progression >::const_iterator key_progression_it_k_t;

	bool _check_found_key(const string_key& found_key) {
		std::string found_key_value = found_key.get_full_key();

		if( 0 == found_key_value.size() ) {
			return false;
		}

		int key_max_index = found_key_value.size() - 1;
		int index = 0;
		size_t position;

		std::vector< __key_progression >::const_iterator iter_k;
		iter_k = __key_progression_collection.begin();

		while( iter_k != __key_progression_collection.end() ) {

			if( index > key_max_index )
				return false;

			position = (*iter_k).keys.find( found_key_value[index] );

			if( position == std::string::npos )
				return false;

			++index;
			++iter_k;
		}

		return true;
	}

	bool _search_progression_recursive(
			string_key search_prefix,
			unsigned int progression_depth,
			string_key& found_key			) {

		bool key_found = false;

		if( progression_depth > (__key_progression_collection.size() - 1) )
			return false;

		std::string keys = __key_progression_collection[progression_depth].keys;
		std::string::const_iterator keys_iter_k = keys.begin();

		while( keys_iter_k != keys.end() ) {

			string_key prefix(search_prefix);
			prefix.extend( (*keys_iter_k) );

			string_key pretender_key;

			if( __dictionary.search(
					prefix,
					pretender_key,
					__restricted_keys
					)					) {

				key_found = true;

				int pretender_key_frequency = pretender_key.get_frequency();
				int found_key_frequency = found_key.get_frequency();

				if( pretender_key_frequency > found_key_frequency )
					found_key.set(pretender_key);

				if( (pretender_key_frequency == found_key_frequency) &&
						(pretender_key.get_relevancy() > found_key.get_relevancy() ) )
					found_key.set(pretender_key);

				_search_progression_recursive(
						prefix,	(progression_depth+1), found_key	);
			}

			++keys_iter_k;
		}

		if( !key_found )
			found_key.clear();

		return key_found;
	}

	void _update_result_and_clean(
			std::string& result_str,
			string_key& found_key,
			char punctuation,
			char end_symbol	= k::null_char	){

		if( !( found_key.get_full_key().empty() ) ) {
			result_str += found_key.get_full_key();
			__dictionary.update_frequency(found_key);

			found_key.clear();
		}

		if( !(k::null_char == punctuation) )
			result_str += punctuation;

		if( !(k::null_char == end_symbol) )
			result_str += end_symbol;
	}

	void _clean_intermediate_data() {
		__key_progression_collection.clear();
		__restricted_keys.clear();
	}

public:

	void add_key(const string_key& key) {
		__dictionary.insert(key);
	}

	std::string process_keypress_sequence(const std::string& key_seq) {
		std::string result;
		std::string::const_iterator iter_k;

		char punctuation = k::null_char;

		string_key search_key, found_key, prefix_key;

		iter_k = key_seq.begin();

		while( iter_k != key_seq.end() ) {
			char input_item = (*iter_k);

			//----begin keypress process loop-----

			if( ' ' == input_item ) {

				_update_result_and_clean(
						result, found_key, punctuation, input_item );

				_clean_intermediate_data();

			} else if ( '1' == input_item ) {

				_update_result_and_clean(
						result, found_key, k::null_char);

				punctuation = __keypad.process_keypress(input_item).at(0);

				_clean_intermediate_data();


			} else if ( ('*' == input_item) && ( k::null_char != punctuation ) ) {

				punctuation = __keypad.process_keypress('1').at(0);

			} else {

				if( '*' == input_item ) {

					__restricted_keys.insert(found_key.get_full_key());

					found_key.clear();

				} else {

				__key_progression input_keys;

				input_keys.keys = __keypad.process_keypress(input_item);
				__key_progression_collection.push_back(input_keys);
				}

				if( !_check_found_key(found_key) ) {

					unsigned int progression_depth = 0;
					found_key.clear();

					_search_progression_recursive(
							prefix_key, progression_depth, found_key);
				}

			}

			//----end keypress process loop-----

			++iter_k;
		}

		_update_result_and_clean(
				result, found_key, punctuation);

		_clean_intermediate_data();

		return result;
	}

}; //class t9

} //namespace yat

/* Main function.
 */
int main(int argc, char** argv) {

    //number of rules (0 by default)
    int words_count = 0;
    yat::t9 t9_system;
    yat::string_key word_key;

    std::string word;
    std::string keypress_sequence, keypress;

    //word usage frequency
    int word_usage_frequency;

    //reads the rules count
    std::cin >> words_count;

    //read words with theirs usage frequencies from standard input
    for(int index = 0; index < words_count; ++index) {

        //reset data variables
        word.clear();
        word_usage_frequency = 0;
        word_key.clear();

        std::cin >> word;
        std::cin >> word_usage_frequency;

        word_key.set(word, word_usage_frequency);

        t9_system.add_key(word_key);

    }

	std::cin.ignore(1, ' ');
    std::getline(std::cin, keypress_sequence);

    std::string output;

    output = t9_system.process_keypress_sequence(keypress_sequence);

    std::cout <<  output << std::endl;

    return (EXIT_SUCCESS);
}

