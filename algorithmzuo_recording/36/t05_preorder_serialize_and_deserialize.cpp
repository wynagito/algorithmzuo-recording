// 二叉树先序序列化和反序列化
// 测试链接 : https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/

#include <string>
#include <list>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 先序序列化和反序列化
class Codec1
{
public:
    // 二叉树可以通过先序、后序或者按层遍历的方式序列化和反序列化
    // 但是，二叉树无法通过中序遍历的方式实现序列化和反序列化
    // 因为不同的两棵树，可能得到同样的中序序列，即便补了空位置也可能一样。
    // 比如如下两棵树
    //         2
    //        / \
    //       1  null
    //      / \
    //   null  null
    //       和
    //        1
    //       / \
    //     null  2
    //          / \
    //        null null
    // 补足空位置的中序遍历结果都是{ null, 1, null, 2, null}
    // null = #
    void rserialize(TreeNode *root, string &str)
    {
        if (root == nullptr)
        {
            str += "#,";
        }
        else
        {
            str += to_string(root->val) + ",";
            rserialize(root->left, str);
            rserialize(root->right, str);
        }
    }

    string serialize(TreeNode *root)
    {
        string ret;
        rserialize(root, ret);
        return ret;
    }

    TreeNode *rdeserialize(list<string> &dataArray)
    {
        if (dataArray.front() == "#")
        {
            dataArray.erase(dataArray.begin());
            return nullptr;
        }

        TreeNode *root = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        root->left = rdeserialize(dataArray);
        root->right = rdeserialize(dataArray);
        return root;
    }

    TreeNode *deserialize(string data)
    {
        list<string> dataArray;
        string str;
        for (auto &ch : data)
        {
            if (ch == ',')
            {
                dataArray.push_back(str);
                str.clear();
            }
            else
            {
                str.push_back(ch);
            }
        }
        if (!str.empty())
        {
            dataArray.push_back(str);
            str.clear();
        }
        return rdeserialize(dataArray);
    }
};

// 按层序列化和反序列化
class Codec2
{
public:
    static const int MAXN = 10001;
    TreeNode *qu[MAXN];
    int l, r;

    string serialize(TreeNode *root)
    {
        string builder = "";
        if (root != nullptr)
        {
            builder += to_string(root->val) + ",";
            l = 0;
            r = 0;
            qu[r++] = root;
            while (l < r)
            {
                root = qu[l++];
                if (root->left != nullptr)
                {
                    builder += to_string(root->left->val) + ",";
                    qu[r++] = root->left;
                }
                else
                {
                    builder += "#,";
                }
                if (root->right != nullptr)
                {
                    builder += to_string(root->right->val) + ",";
                    qu[r++] = root->right;
                }
                else
                {
                    builder += "#,";
                }
            }
        }
        return builder;
    }

    TreeNode *deserialize(string data)
    {
        if (data.empty())
        {
            return nullptr;
        }
        vector<string> nodes;
        string str;
        for (auto &ch : data)
        {
            if (ch == ',')
            {
                nodes.push_back(str);
                str.clear();
            }
            else
            {
                str.push_back(ch);
            }
        }
        if (!str.empty())
        {
            nodes.push_back(str);
            str.clear();
        }
        int index = 0;
        TreeNode *root = generate(nodes[index++]);
        l = 0;
        r = 0;
        qu[r++] = root;
        while (l < r)
        {
            TreeNode *cur = qu[l++];
            cur->left = generate(nodes[index++]);
            cur->right = generate(nodes[index++]);
            if (cur->left != nullptr)
            {
                qu[r++] = cur->left;
            }
            if (cur->right != nullptr)
            {
                qu[r++] = cur->right;
            }
        }
        return root;
    }

    TreeNode *generate(string val)
    {
        return val == "#" ? nullptr : new TreeNode(stoi(val));
    }
};