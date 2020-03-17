#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(): left(nullptr), right(nullptr) {}
    TreeNode(int n): val(n), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    TreeNode *creat_tree() {
        int n = 0;
        cout << "input n (Q: -1): ";
        cin >> n;
        if (n == -1) return nullptr;
        TreeNode *tree = new TreeNode(n);
        tree->left = creat_tree();
        tree->right = creat_tree();
        return tree;
    }

    vector<int> pre_order(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) return res;
        TreeNode *tmp = root;
        stack<TreeNode *> s;
        while (tmp || !s.empty()) {
            while (tmp) {
                res.emplace_back(tmp->val);
                s.emplace(tmp);
                tmp = tmp->left;
            }
            tmp = s.top();
            s.pop();
            tmp = tmp->right;
        }
        return res;
    }

    vector<int> in_order(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) return res;
        TreeNode *tmp = root;
        stack<TreeNode *> s;
        while (tmp || !s.empty()) {
            while (tmp) {
                s.emplace(tmp);
                tmp = tmp->left;
            }
            tmp = s.top();
            s.pop();
            res.emplace_back(tmp->val);
            tmp = tmp->right;
        }
        return res;
    }

    vector<int> post_order(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) return res;
        TreeNode *tmp = root;
        TreeNode *visited = nullptr;
        stack<TreeNode *> s;
        while (tmp || !s.empty()) {
            while (tmp) {
                s.emplace(tmp);
                tmp = tmp->left;
            }
            tmp = s.top();
            if (tmp->right != nullptr && tmp->right != visited) {
                tmp = tmp->right;
            } else {
                s.pop();
                res.emplace_back(tmp->val);
                visited = tmp;
                tmp = nullptr;
            }
        }
        return res;
    }

    vector<int> comm_pre_order(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) return res;
        stack<pair<TreeNode *, bool>> s;
        s.emplace(make_pair(root, false));
        while (!s.empty()) {
            auto item = s.top();
            s.pop();
            if (item.first == nullptr)
                continue;
            if (item.second) {      // if visited
                res.emplace_back(item.first->val);
            } else {                // change push order to pre->in->post
                s.emplace(make_pair(item.first->right, false));
                s.emplace(make_pair(item.first->left, false));
                s.emplace(make_pair(item.first, true));
            }
        }
        return res;
    }
};

int main() {
    Tree tree;
    TreeNode *t = tree.creat_tree();
    vector<int> res = tree.comm_pre_order(t);
    for (auto n: res)
        cout << n << " ";

    return 0;
}
