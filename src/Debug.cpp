#include <Debug.hpp>

ListNode::ListNode() : val(0), next(nullptr) {}
ListNode::ListNode(int x) : val(x), next(nullptr) {}
ListNode::ListNode(int x, ListNode *next) : val(x), next(next) {}

TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr) {}
TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
TreeNode::TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

// Print a Linked List
void dlog(ListNode* head){
	if (!head){
		std::cout << "Empty" << std::endl;
		return;
	}
	ListNode* curr = head;
	while (curr->next){
		std::cout << curr->val << " - ";
		curr = curr->next;
	}
	std::cout << curr->val << "\n";
}


// recursive function that fills binary tree row by row left to right
void fill(TreeNode* node, std::vector<std::string> v, int i){
	if (v[i] == "null"){
		node = nullptr;
		return;
	}

	node->val = std::stoi(v[i]); // assign value

	if (2*i+1 < v.size()){
		node->left = new TreeNode();
		fill(node->left, v, 2*i+1);
	}
	if (2*i+2 < v.size()){
		node->right = new TreeNode();
		fill(node->right, v, 2*i+2);
	}
}

// initialize and fill a binary tree (row by row) from a given vector
TreeNode* createBinaryTree(std::string vstr){
	if (vstr == "") return nullptr;
	std::vector<std::string> v;
	std::stringstream ss(vstr);
	std::string numstr;
	while (getline(ss,numstr,',')){
		v.push_back(numstr);
	}
	dlog(v);

	TreeNode* head = new TreeNode(stoi(v[0]));
	fill(head, v, 0);
	return head;

}
