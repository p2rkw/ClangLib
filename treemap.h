#ifndef TREEMAP_H
#define TREEMAP_H

#include <vector>

struct TreeNode;
class wxString;
template<typename _Tp> class TreeMap;

template<>
class TreeMap<int>
{
    public:
        TreeMap();
        ~TreeMap();
        int Insert(const wxString& key, int value); // returns value
        void Shrink();
        std::vector<int> GetIdSet(const wxString& key) const;
        int GetValue(int id) const; // returns id
    private:
        TreeNode* m_Root;
};

template<typename _Tp>
class TreeMap
{
    public:
        // returns the id of the value inserted
        int Insert(const wxString& key, const _Tp& value)
        {
            m_Data.push_back(value);
            return m_Tree.Insert(key, m_Data.size() - 1);
        }

        void Shrink()
        {
            m_Tree.Shrink();
#if __cplusplus >= 201103L
            m_Data.shrink_to_fit();
#else
            std::vector<_Tp>(m_Data).swap(m_Data);
#endif
        }

        std::vector<int> GetIdSet(const wxString& key) const
        {
            return m_Tree.GetIdSet(key);
        }

        _Tp& GetValue(int id)
        {
            return m_Data[id];
        }

    private:
        TreeMap<int> m_Tree;
        std::vector<_Tp> m_Data;
};

#endif // TREEMAP_H
