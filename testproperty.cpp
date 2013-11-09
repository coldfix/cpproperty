#include <iostream>
#include "property.h"
#include <vector>


class test
{
    int _theint;
    double _thedbl;
    std::vector<double> _thevec;
public:

    void setint(const int& i)
    {
        _theint = i * 3;
    }

    const int& getint() const
    {
        return _theint;
    }

    void setdbl(const double& d)
    {
        _thedbl = d + 2;
    }

    const double& getdbl() const
    {
        return _thedbl;
    }

    void setvec(const std::vector<double>& d)
    {
        _thevec = d;
    }

    const std::vector<double>& getvec() const
    {
        return _thevec;
    }

    test()
        : _int(this, &test::getint, &test::setint)
        , _dbl(this, &test::getdbl, &test::setdbl)
        , _vec(this, &test::getvec, &test::setvec)
        , _int2(this)
    {
    }

    property<int> _int;
    property<double> _dbl;
    property<std::vector<double>> _vec;

    std_property<int, test, &test::getint, &test::setint> _int2;
};


int main()
{
    using namespace std;

    test t;
    t._int = 3;
    t._vec = vector<double>{5, 3.3, 2.6};

    cout << *t._int << endl;

    cout << t._vec->size() << ':';
    for (auto v : *t._vec)
        cout << ' ' << v;
    cout << endl;

    cout << *t._int2 << endl;
    t._int2 = 5;
    cout << *t._int2 << endl;

    return 0;
}

