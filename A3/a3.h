#include <string>
using namespace std;

class Trie{
private:
//this struct represents a node in the trie and contains an array of pointers to children nodes and a boolean to indicate if the node is the end of a word
	struct Node{
		Node* children[26];
		bool isWord;
	};
	Node* root;
public:
	Trie(const std::string wordList[],int sz);
	void addWord(const std::string& newWord);
	bool lookup(const std::string& word) const;
	int beginsWith(const std::string& prefix, std::string resultList[]) const;
	~Trie();	
};
