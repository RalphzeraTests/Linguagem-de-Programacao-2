#ifndef ITEM_HPP
#define ITEM_HPP
#include <iostream>
#include <sstream>
using namespace std;
class Item
{
protected:
    int _valor;
    string _nome;

public:
    Item();
    Item(int v, string n);
    ~Item();

public:
    string str()
    {
        stringstream s;
        s << _nome << ", " << _valor << "PP";
        return s.str();
    }
};

class Arma : public Item
{
private:
    int _atk;

public:
    Arma();
    Arma(int v, string n, int a);
    ~Arma();

public:
    string str()
    {
        stringstream s;
        s << _nome << ", " << _valor << "PP / ATK = " << _atk;
        return s.str();
    }
};
class Armadura : public Item
{
private:
    int _def;

public:
    Armadura();
    Armadura(int v, string n, int d);
    ~Armadura();

public:
    string str()
    {
        stringstream s;
        s << _nome << ", " << _valor << "PP / DEF = " << _def;
        return s.str();
    }
};

#endif