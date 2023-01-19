#include "LinkedList.h"
#include <string>
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

class CustomData
{
public:
    int f1;
    char f2;
};

string writeData(CustomData d)
{
    string out;

    out.append("Id: ");
    out.append(to_string(d.f1));

    out.append(" Character: ");
    out.append(to_string(d.f2));

    return out;
}

int compareFun(CustomData d1, CustomData d2)
{
    return d1.f1 - d2.f1;
}

CustomData createRandomCustomData() {
    CustomData d;

    d.f1 = 0 + rand() % ((100000 + 1) - 0);
    d.f2 = 97 + rand() % ((122 + 1) - 97);

    return d;
}

int main()
{

    srand(time(NULL));

    LinkedList<CustomData>* list = new LinkedList<CustomData>();

    list->data_cmp = &compareFun;
    list->single_node_to_string = &writeData;

    const int MAX_ORDER = 6;

    for (int o = 1; o <= MAX_ORDER; o++)
    {
        std::cout << "Rzad wielkosci: " << o << std::endl;

        const int n = pow(10, o);

        clock_t t1 = clock();

        for (int i = 0; i < n; i++)
            list->addAtEnd(createRandomCustomData());

        clock_t t2 = clock();

        double time = (t2 - t1) / (double) CLOCKS_PER_SEC * 1000;

        cout << "Czas dodania : " << time << endl;

        const int m = pow (10, 4);

        t1 = clock();

        for (int i = 0; i < m; i++)
            list->removeDataWithCompare(createRandomCustomData());

        t2 = clock();

        time = (t2 - t1) / (double)CLOCKS_PER_SEC * 1000;
        cout << "Czas prob szukania i usuniecia : " << time << endl;

        cout << endl;

    }

    list->clear();
    delete list;
    list = nullptr;

    return 0;
}
