#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;
struct RootNode {
	char ch;
	int frequency;
	RootNode* left, * right;
};
RootNode* GetListBegin(char ch, int freq, RootNode* left, RootNode* right) {
	RootNode* node = new RootNode();
	node->ch = ch;
	node->frequency = freq;
	node->left = left;
	node->right = right;
	return node;
}

struct Comparrer {
	bool operator()(RootNode* left, RootNode* right) {
		return left->frequency > right->frequency;
	}
};

void Encode(RootNode* root, string str,
	unordered_map<char, string>& code_by_Haff) {
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		code_by_Haff[root->ch] = str;
	}
	Encode(root->left, str + "0", code_by_Haff);
	Encode(root->right, str + "1", code_by_Haff);
}
void Decode(RootNode* root, int& index, string str) {
	if (root == nullptr) {
		return;
	}
	if (!root->left && !root->right) {
		cout << root->ch;
		return;
	}
	index++;
	if (str[index] == '0')
		Decode(root->left, index, str);
	else
		Decode(root->right, index, str);
}
void CreateHuffmanTree(string text) {
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}
	priority_queue<RootNode*, vector<RootNode*>, Comparrer> pq;
	for (auto pair : freq) {
		pq.push(GetListBegin(pair.first, pair.second, nullptr, nullptr));
	}
	while (pq.size() != 1) {
		RootNode* left = pq.top(); pq.pop();
		RootNode* right = pq.top();	pq.pop();
		int sum = left->frequency + right->frequency;
		pq.push(GetListBegin('\0', sum, left, right));
	}
	RootNode* root = pq.top();
	unordered_map<char, string> code_by_Haff;
	Encode(root, "", code_by_Haff);
	cout << "accordance (char=binary code):" << '\n';
	for (auto pair : code_by_Haff) {
		cout << pair.first << "=" << pair.second << '\n';
	}
	cout << "source string:\n" << text << '\n';
	string str = "";
	for (char ch : text) {
		str += code_by_Haff[ch];
	}
	cout << "crypted string:\n" << str << "\n\n";
	int index = -1;
	while (index < (int)str.size() - 2) {
		Decode(root, index, str);
	}
}
int main()
{
	setlocale(0, "");
	cout << "input text to encrypt:\n";
	string text;
	getline(cin, text);
	map<char, int> chars_rate;
	for (unsigned int i = 0; i < text.size(); i++)
		chars_rate[text[i]]++;
	cout << "chars rate:" << endl;

	for (map<char, int>::iterator it = chars_rate.begin(); it != chars_rate.end(); ++it)
		cout << it->first << "=" << it->second << "  ";
	cout << endl;
	CreateHuffmanTree(text);

	return 0;
}