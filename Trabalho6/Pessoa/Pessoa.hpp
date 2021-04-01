#ifndef PESSOA_HPP
#define PESSOA_HPP
#include "../SerVivo/SerVivo.hpp"
#include <vector>
#include "../Item/GenericItem.hpp"

class Pessoa : public SerVivo
{
protected:
    string _nome;
    vector<GenericItem *> _mochila;
    size_t _dinheiro;
    size_t _pontos;
    size_t _nivel;
    size_t _xp;

public:
    Pessoa();
    Pessoa(string nome, size_t dinheiro);
    ~Pessoa();

public:
    size_t getPontos() { return _pontos; };
    void depositar(size_t q) { _dinheiro += q; };
    bool gastar(size_t q)
    {
        if (q > _dinheiro)
            return false;
        _dinheiro -= q;
        return true;
    };
    bool upar(string atr, size_t qnt);
    void push_bag(GenericItem *i)
    {
        _mochila.push_back(i);
    };
    string getNome() { return _nome; }
    string str();
    string bagToStr();
    size_t getDinheiro() { return _dinheiro; };
    GenericItem *pop_bag(size_t i)
    {
        if (i >= _mochila.size())
            return nullptr;
        GenericItem *it = _mochila.at(i);
        _mochila.erase(_mochila.begin() + i);
        return it;
    }
    bool equipar(size_t n)
    {
        cout << "equipando" << endl;
        if (n < 0 || n >= _mochila.size())
            return false;
        GenericItem *i = pop_bag(n);
        cout << i->getTipo() << endl;
        if (i->getTipo() == t_Item)
        {
            push_bag(i);
            return false;
        }

        if (i->getTipo() == t_Consumivel)
        {
            Consumivel *it = (Consumivel *)i->getPointer();
            if (it->getAcao() == "HP")
            {
                if (!_hp.isMax())
                {
                    _hp + it->getAtr();
                    delete i;
                }
                else
                    push_bag(i);
            }
        }
        if (i->getTipo() == t_Arma)
        {
            GenericItem *rem = new GenericItem(_armaEquipada);
            if (_armaEquipada->getValue() != 0)
                push_bag(rem);
            else
                delete _armaEquipada;
            _armaEquipada = (Arma *)i->getPointer();
        }
        if (i->getTipo() == t_Armadura)
        {
            GenericItem *rem = new GenericItem(_armaduraEquipada);
            if (_armaduraEquipada->getValue() != 0)
                push_bag(rem);
            else
                delete _armaduraEquipada;
            _armaduraEquipada = (Armadura *)i->getPointer();
        }
        return true;
    }
};

#endif