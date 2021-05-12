#ifndef Heap_Hpp
#define Heap_Hpp

#include <vector>

using std::vector;

namespace Common
{
    typedef int (*CompareFunc)(void const*, void const*);
    typedef bool (*EnumFunc)(void const*);

    template <typename T>
    class Heap
    {
    public:
        CompareFunc Compare;

        void EnumObject(EnumFunc EnumCallBack)
        {
            _EnumObjectInternel(EnumCallBack, 1);
        }

        bool PopRoot(T& root)
        {
            if (!IsEmpety())
            {
                root = data[1];

                if (data.size() == 2)
                {
                }
                else
                {
                    std::swap(data[1], data[data.size() - 1]);
                }
                data.erase(data.end() - 1);
                topToBottom(1);
                return true;
            }
            return false;
        }

        bool GetRoot(T &root)
        {
            if (!IsEmpety())
            {
                root = data[1];
                return true;
            }
            return false;
        }

        void Insert(T v)
        {
            if (data.size() == 0)
            {
                data.push_back(v);
            }
            data.push_back(v);
            bottomToTop(data.size() - 1);
        }

        bool FindApproximate(T& v, int &idx, void* pole, CompareFunc compare)
        {
            if (IsEmpety())
            {
                return false;
            }

            int minGap = 2147483647;//MAX_INT
            int minGapObjIdx = 0;

            for (int i = 1; i < data.size(); i++)
            {
                int gap = compare(&data[i], pole);
                if (gap < minGap)
                {
                    minGap = gap;
                    minGapObjIdx = i;
                }
            }

            v = data[minGapObjIdx];
            idx = minGapObjIdx;
            return true;
        }

        bool IsEmpety()
        {
            if (data.size() <= 1)
            {
                return true;
            }
            return false;
        }

        void RemoveAt(int idx)
        {
            if (idx > 0 && idx < data.size())
            {
                vector<T> tmp = data;
                data.clear();
                data.push_back(tmp[0]);
                for (int i = 1; i < tmp.size(); i++)
                {
                    if (i != idx)
                    {
                        Insert(tmp[i]);
                    }
                }
            }
        }

    private:
        vector<T> data;

        void _EnumObjectInternel(EnumFunc EnumCallBack, int idx)
        {
            if (idx < data.size())
            {
                if (!EnumCallBack(data + idx))
                {
                    return;
                }
            }
            else
            {
                return;
            }

            int left = idx * 2;
            int right = left + 1;
            if (left < data.size())
            {
                if (!EnumCallBack(data + left))
                {
                    return;
                }
            }
            if (right < data.size())
            {
                if (!EnumCallBack(data + right))
                {
                    return;
                }
            }

            _EnumObjectInternel(EnumCallBack, left);
            _EnumObjectInternel(EnumCallBack, right);
        }

        void bottomToTop(int idx)
        {
            int parent = idx / 2;
            if (parent >= 1)
            {
                if (Compare(&data[idx], &data[parent]) > 0)
                {
                    std::swap(data[idx], data[parent]);
                    bottomToTop(parent);
                }
            }
        }

        void topToBottom(int idx)
        {
            int left = idx * 2;
            int right = left + 1;

            if (left < data.size() && right < data.size())
            {
                if (Compare(&data[left], &data[right]) > 0)
                {
                    if (Compare(&data[left], &data[idx]) > 0)
                    {
                        std::swap(data[idx], data[left]);
                        topToBottom(left);
                    }
                }
                else
                {
                    if (Compare(&data[right], &data[idx]) > 0)
                    {
                        std::swap(data[idx], data[right]);
                        topToBottom(right);
                    }
                }
            }
            else if (left < data.size())
            {
                if (Compare(&data[left], &data[idx]) > 0)
                {
                    std::swap(data[idx], data[left]);
                    topToBottom(left);
                }
            }
            else if (right < data.size())
            {
                if (Compare(&data[right], &data[idx]) > 0)
                {
                    std::swap(data[idx], data[right]);
                    topToBottom(right);
                }
            }
        }

    };
}

#endif
