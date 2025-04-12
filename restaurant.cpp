#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
// class 料亭_五条悟;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1) {}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}
	void remove_KOKUSEN()
	{
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		if (number <= 0 || number > MAXSIZE)
			return;
		areaTable[number].print();
	}

private:
	class Tree_BST
	{
		class Node;

	private:
		Node *root;
		queue<int> queueTime;

	public:
		Tree_BST() : root(nullptr) {}
		~Tree_BST()
		{
			while (!queueTime.empty())
			{
				int temp = queueTime.front();
				queueTime.pop();
				root = deleteNode_Recur(root, temp);
			}
		}
		int size()
		{
			return queueTime.size();
		}
		Node *insertNode_Recur(Node *node, int result)
		{
			if (node == nullptr)
			{
				queueTime.push(result);
				return new Node(result);
			}

			if (result < node->result)
				node->left = insertNode_Recur(node->left, result);
			else
				node->right = insertNode_Recur(node->right, result);

			return node;
		}
		void insert(int result) { root = insertNode_Recur(root, result); }
		Node *minFinder(Node *node)
		{
			if (node == nullptr)
				return nullptr;

			while (node->left != nullptr)
				node = node->left;

			return node;
		}
		Node *deleteNode_Recur(Node *node, int val)
		{
			if (node == nullptr)
				return nullptr;

			if (val < node->result)
				node->left = deleteNode_Recur(node->left, val);
			else if (val > node->result)
				node->right = deleteNode_Recur(node->right, val);
			else
			{
				if (node->left == nullptr && node->right == nullptr)
				{
					delete node;
					node = nullptr;
				}
				else if (node->left == nullptr)
				{
					Node *temp = node;
					node = node->right;
					delete temp;
				}
				else if (node->right == nullptr)
				{
					Node *temp = node;
					node = node->left;
					delete temp;
				}
				else
				{
					Node *temp = minFinder(node->right);
					node->result = temp->result;
					node->right = deleteNode_Recur(node->right, temp->result);
				}
			}

			return node;
		}
		int countNode_Recur(Node *node)
		{
			return node != nullptr ? (1 + countNode_Recur(node->left) + countNode_Recur(node->right)) : 0;
		}
		unsigned long long binomialCoefficient(int x, int n)
		{
			vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(x + 1, 0));

			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= x && j <= i; j++)
					(j == 0 || j == i) ? dp[i][j] = 1 : (dp[i][j] = (dp[i - 1][j - 1] % MAXSIZE + dp[i - 1][j] % MAXSIZE));

			return dp[n][x] % MAXSIZE;
		}
		unsigned long long DFS(Node *node)
		{
			if (node == nullptr)
				return 1;

			int leftCount = countNode_Recur(node->left);
			int rightCount = countNode_Recur(node->right);

			return (binomialCoefficient(leftCount, leftCount + rightCount) * DFS(node->left) * DFS(node->right)) % MAXSIZE;
		}
		void remove()
		{
			if (queueTime.empty())
				return;

			unsigned long long number = DFS(root) % MAXSIZE;

			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();
				queueTime.pop();
				root = deleteNode_Recur(root, temp);
				number--;
			}
		}
		void print_recursive(Node *node)
		{
			if (node != NULL)
			{
				print_recursive(node->left);
				cout << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print() { print_recursive(root); }

	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class Tree_BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable;
	list<Node *> the_time_stone;

private:
	int getPos(Node *element)
	{
		int index = 0;
		list<Node *>::iterator it = the_time_stone.begin();

		while (*it != element && it != the_time_stone.end())
		{
			index++;
			++it;
		}

		return index;
	}
	void ReHeap_down(int index)
	{
		int child_left = 2 * index + 1;
		int child_right = 2 * index + 2;
		int largest = index;

		if (child_left < int(areaTable.size()) && areaTable[child_left]->size() < areaTable[largest]->size())
			largest = child_left;
		else if (child_left < int(areaTable.size()) && areaTable[child_left]->size() == areaTable[largest]->size())
			if (getPos(areaTable[child_left]) > getPos(areaTable[largest]))
				largest = child_left;

		if (child_right < int(areaTable.size()) && areaTable[child_right]->size() < areaTable[largest]->size())
			largest = child_right;
		else if (child_right < int(areaTable.size()) && areaTable[child_right]->size() == areaTable[largest]->size())
			if (getPos(areaTable[child_right]) > getPos(areaTable[largest]))
				largest = child_right;

		if (largest != index)
		{
			swap(areaTable[index], areaTable[largest]);
			ReHeap_down(largest);
		}
	}
	void ReHeap_up(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (areaTable[index]->size() < areaTable[parent]->size())
			{
				swap(areaTable[index], areaTable[parent]);
				index = parent;
			}
			else
				break;
		}
	}
	void moveTop(Node *node)
	{
		list<Node *>::iterator it = the_time_stone.begin();

		while (it != the_time_stone.end() && *it != node)
			++it;

		it != the_time_stone.end() ? the_time_stone.splice(the_time_stone.begin(), the_time_stone, it) : the_time_stone.push_front(node);
	}
	void removeNode(Node *node) { the_time_stone.remove(node); }

public:
	RESTAURANT_Sukuna() {}
	~RESTAURANT_Sukuna()
	{
		for (int i = 0; i < int(areaTable.size()); i++)
			delete areaTable[i];
	}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;

		for (int i = 0; i < int(areaTable.size()); i++)
			if (areaTable[i]->ID == ID)
				index = i;

		//*bước 2: xem thử có khu này trong heap chưa để thêm vô
		if (index == -1)
		{
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}
	void remove_KEITEIKEN(int number)
	{
		if (areaTable.size() <= 0)
			return;
		vector<Node *> areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node *> listDelete;
		for (int i = 0; areaTable.size() && i < number; i++)
		{
			Node *nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[areaTable.size() - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);
			listDelete.push(nodeDelete);
		}
		areaTable = areaTableNew;
		while (listDelete.size())
		{
			Node *nodeDelete = listDelete.front();
			listDelete.pop();
			nodeDelete->remove(number);
			int index = 0;
			while (areaTable[index] != nodeDelete)
				index++;
			if (nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[areaTable.size() - 1]);
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];
				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
	}
	void print_pre_order(int index, int number)
	{
		int areaSize = this->areaTable.size();
		if (index >= areaSize || number <= 0)
			return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number) { print_pre_order(0, number); }

private:
	class Node
	{
	private:
		int ID;
		list<int> head;
		friend class RESTAURANT_Sukuna;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result) { head.push_front(result); }
		void remove(int number)
		{
			while (number != 0 && !head.empty())
			{
				cout << head.back() << "-" << ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
				cout << ID << "-" << *it << "\n";
		}
	};
};

class HuffTree_AVL
{
	class Node;

private:
	Node *root = nullptr;

public:
	~HuffTree_AVL() { clear(root); }
	void clear(Node *node)
	{
		if (node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
	static bool op(pair<char, int> a, pair<char, int> b)
	{
		if (a.second > b.second)
			return true;
		else if (a.second == b.second)
		{
			if (isupper(a.first) && islower(b.first))
				return true;
			else if (islower(a.first) && isupper(b.first))
				return false;
			else
				return a.first > b.first;
		}
		else
			return false;
	}
	void sortDesc(vector<pair<char, int>> &vec) { sort(vec.begin(), vec.end(), op); }
	char CaesarEncoding(char c, int fre)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 'a' + fre) % 26 + 'a';
		else if (c >= 'A' && c <= 'Z')
			return (c - 'A' + fre) % 26 + 'A';
		else
			return c;
	}
	vector<pair<char, int>> combinePairs(vector<pair<char, int>> &vec)
	{
		map<char, int> finalFrequencyOfEachChar;
		vector<pair<char, int>> combinedVector;
		for (pair<char, int> p : vec)
			finalFrequencyOfEachChar[p.first] += p.second;
		for (map<char, int>::iterator p = finalFrequencyOfEachChar.begin(); p != finalFrequencyOfEachChar.end(); p++)
			combinedVector.push_back(*p);
		return combinedVector;
	}
	vector<pair<char, int>> EncodedVector(vector<pair<char, int>> &vec)
	{
		vector<pair<char, int>> encodedVector;
		for (pair<char, int> p : vec)
		{
			char encoded_char = CaesarEncoding(p.first, p.second);
			encodedVector.push_back({encoded_char, p.second});
		}
		return encodedVector;
	}
	string newString(vector<pair<char, int>> &vec, string &name)
	{
		string newstr = "";
		for (char c : name)
		{
			char temp;
			if (c >= 'a' && c <= 'z')
			{
				for (pair<char, int> it : vec)
				{
					if (it.first == c)
					{
						temp = (c - 'a' + it.second) % 26 + 'a';
						newstr += temp;
					}
				}
			}
			else if (c >= 'A' && c <= 'Z')
			{
				for (pair<char, int> it : vec)
				{
					if (it.first == c)
					{
						temp = (c - 'A' + it.second) % 26 + 'A';
						newstr += temp;
					}
				}
			}
		}
		return newstr;
	}
	vector<pair<char, int>> string_Processing(string &name)
	{
		map<char, int> frequencyOfEachChar;
		vector<pair<char, int>> frequencyVector;
		for (char c : name)
			frequencyOfEachChar[c]++;
		for (map<char, int>::iterator p = frequencyOfEachChar.begin(); p != frequencyOfEachChar.end(); p++)
			frequencyVector.push_back(*p);
		name = newString(frequencyVector, name);
		if (frequencyVector.size() < 3)
			return {};
		vector<pair<char, int>> caesarEncodedVector = EncodedVector(frequencyVector);
		vector<pair<char, int>> finalVector = combinePairs(caesarEncodedVector);
		sortDesc(finalVector);
		return finalVector;
	}
	int getHeight(Node *node)
	{
		if (node == nullptr)
			return 0;
		return 1 + max(getHeight(node->left), getHeight(node->right));
	}
	Node *rightRotate(Node *node)
	{
		Node *newRoot = node->left;
		Node *temp = newRoot->right;
		node->left = temp;
		newRoot->right = node;
		return newRoot;
	}
	Node *leftRotate(Node *node)
	{
		Node *newRoot = node->right;
		Node *temp = newRoot->left;
		node->right = temp;
		newRoot->left = node;
		return newRoot;
	}
	int getBalance(Node *node)
	{
		if (node == nullptr)
			return 0;
		return getHeight(node->left) - getHeight(node->right);
	}
	Node *balanceNode(Node *node, int &count)
	{
		int balance = getBalance(node);
		if (balance > 1 && getBalance(node->left) >= 0)
		{
			count++;
			return rightRotate(node);
		}
		if (balance > 1 && getBalance(node->left) < 0)
		{
			node->left = leftRotate(node->left);
			count++;

			if (count >= 3)
				return node;

			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node->right) <= 0)
		{
			count++;
			return leftRotate(node);
		}
		if (balance < -1 && getBalance(node->right) > 0)
		{
			node->right = rightRotate(node->right);
			count++;
			if (count >= 3)
				return node;
			return leftRotate(node);
		}
		return node;
	}
	Node *balanceTree(Node *node, int count = 0)
	{
		if (node == nullptr || count == 1)
			return node;
		node = balanceNode(node, count);
		node->left = balanceTree(node->left, count);
		node->right = balanceTree(node->right, count);
		return node;
	}
	Node *buildHuff(vector<pair<char, int>> freq)
	{
		vector<Node *> build;

		for (auto p : freq)
		{
			Node *node = new Node(p.second, p.first, nullptr, nullptr);
			build.push_back(node);
		}

		while (build.size() > 1)
		{
			int pos = 0;
			Node *min1 = build.back();
			build.pop_back();
			Node *min2 = build.back();
			build.pop_back();
			Node *temp_node = new Node(min1->weight + min2->weight);
			temp_node->left = min1;
			temp_node->right = min2;
			for (int i = 0; i < 3; i++)
				temp_node = balanceTree(temp_node);
			while (pos < int(build.size()) && build[pos]->weight > temp_node->weight)
				pos++;
			build.insert(build.begin() + pos, temp_node);
		}
		return build[0];
	}
	int binaryToDecimal(string binary)
	{
		int decimal = 0;
		int base = 1;

		for (int i = binary.size() - 1; i >= 0; --i)
		{
			if (binary[i] == '1')
				decimal += base;

			base *= 2;
		}

		return decimal;
	}
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		if (node == nullptr)
			return;
		if (node->isChar())
			encoding[node->c] = s;
		else
		{
			encodingHuffman_rec(encoding, node->left, s + "0");
			encodingHuffman_rec(encoding, node->right, s + "1");
		}
	}
	int encodingHuffman(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr)
			return 0;
		vector<string> encoding(256, "");
		string binary = "";
		encodingHuffman_rec(encoding, root);
		for (int i = 0; i < int(nameCaesar.length()); i++)
			binary += encoding[nameCaesar[i]];
		reverse(binary.begin(), binary.end());
		string bin = binary.substr(0, 10);
		int result = binaryToDecimal(bin);

		return result;
	}
	int encode(string name)
	{
		vector<pair<char, int>> freq = this->string_Processing(name);
		if (freq.size() == 0)
			return -1;
		this->clear(root);
		root = this->buildHuff(freq);
		if (root->left == nullptr && root->right == nullptr)
			return 0;
		int result = this->encodingHuffman(root, name);
		return result;
	}

	void print_recursive(Node *node)
	{
		if (node == nullptr)
			return;
		print_recursive(node->left);
		if (node->c == '\0')
			cout << node->weight << "\n";
		else
			cout << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND() { print_recursive(root); }

private:
	class Node
	{
	public:
		int weight;
		char c;
		Node *left;
		Node *right;
		friend class HuffTree_AVL;

	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), left(left), right(right) {}
		bool isChar() const { return c != '\0'; }
	};
};

class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;

public:
	void LAPSE(string name)
	{
		int result = New_customers_arrive.encode(name);
		if (result == -1)
			return;

		if (result % 2 == 1)
			hash.insertAreaTable(result);
		else
			heap.insertAreaTable(result);
	}
	void KOKUSEN() { hash.remove_KOKUSEN(); }
	void LIMITLESS(int num) { hash.print_LIMITLESS(num); }
	void KEITEIKEN(int num) { heap.remove_KEITEIKEN(num); }
	void CLEAVE(int num) { heap.print_LIMITLESS(num); }
	void HAND() { New_customers_arrive.print_HAND(); }
};

void simulate(string filename)
{
	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str;
	ss >> MAXSIZE;

	JJK_RESTAURANT_OPERATIONS *junjutsu_kaisen = new JJK_RESTAURANT_OPERATIONS();
	while (ss >> str)
	{
		if (str == "LAPSE")
		{
			ss >> name;
			junjutsu_kaisen->LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			junjutsu_kaisen->KOKUSEN();
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num;
			junjutsu_kaisen->KEITEIKEN(num);
		}
		else if (str == "HAND")
		{
			junjutsu_kaisen->HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num;
			junjutsu_kaisen->LIMITLESS(num);
		}
		else if (str == "CLEAVE")
		{
			ss >> num;
			junjutsu_kaisen->CLEAVE(num);
		}
	}
	delete junjutsu_kaisen;
}
