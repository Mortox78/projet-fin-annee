#ifndef _GRAPH_
#define _GRAPH_

#include <vector>
#include <iostream>

namespace Core
{
    namespace DataStructure
    {
        template <typename A, typename B>
        class Graph
        {
        public:

            A* object {nullptr};
            std::vector<B*> list;

            void Add(A* newObject)
            {
                //B n = new B();
                list.push_back(new B());
                list[list.size() - 1]->object = newObject;
                //list.push_back(n);
            };

            void Add(const B *newObjList)
            {
                list.push_back((B*)newObjList);
            }
        };
    }
}

#endif