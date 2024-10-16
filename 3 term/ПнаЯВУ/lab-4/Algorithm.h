namespace sss
{
    template <typename Iterator>
    Iterator search(Iterator begin, Iterator end, int num)
    {
        for(int i=0;i<num;i++)
            while(begin!=end)
                begin++;
        return begin;
    }

/*    template <typename Iterator>
    void sort(Iterator begin,Iterator end)
    {
        Iterator iter=begin;
        for(iter;iter!=end;iter++)
        {
            Iterator next=iter;
            next++;
            for(Iterator iter1=iter;next!=end;iter1++)
            {
                if (!comp(*iter1, *next))
                {
                    std::swap(*iter1,*next);
                }
                next++;
            }
        }
    }*/

    template<typename Iterator>
    void for_each(Iterator begin, Iterator end)
    {
        for(auto iter=begin;iter!=end;iter++)
        {
            check_for_each(*iter);
        }
    }

    template<typename Iterator>
    int count(Iterator begin, Iterator end)
    {
        int count=0;
        for(auto iter=begin;iter!=end;iter++)
        {
            count++;
        }
        return count;
    }
}

/*
template <typename T>
bool comp(const T&t1, const T&t2)
{
    return t1<t2;
}*/
