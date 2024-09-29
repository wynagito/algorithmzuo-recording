// 插入、删除和获取随机元素O(1)时间的结构
// 测试链接 : https://leetcode.cn/problems/insert-delete-getrandom-o1/

#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedSet
{
public:
    unordered_map<int, int> hh; // 元素的值 : 对应在vc中的下标
    vector<int> vc;
    RandomizedSet()
    {
        hh.clear();
        vc.clear();
    }

    bool insert(int val)
    {
        auto index = hh.find(val);
        if (index == hh.end())
        {
            hh[val] = vc.size();
            vc.push_back(val);
            return true;
        }
        return false;
    }

    bool remove(int val)
    {
        auto index = hh.find(val);
        if (index != hh.end())
        {
            vc[index->second] = vc[vc.size() - 1];
            hh[vc[vc.size() - 1]] = index->second;
            vc.pop_back();
            hh.erase(index);
            return true;
        }
        return false;
    }

    int getRandom()
    {
        return vc[rand() % vc.size()];
    }
};