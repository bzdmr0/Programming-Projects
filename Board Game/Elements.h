/** Arda Menşur – 2585214 , Muhammet Sait Bozdemir – 2584738
We read and accept the submission rules and the extra rules specified in each question. This is our own work that is done by us only **/
#ifndef INC_242ASSIGNMENT3_ELEMENTS_H
#define INC_242ASSIGNMENT3_ELEMENTS_H

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
/** We created this class together **/
class Elements {
protected:
    int size;
    char symbol;
    int Effect;
public:
    Elements(int sz, char sym, int effect) ;
    virtual ~Elements();
    Elements (Elements &other);
    virtual string getName() const =0;
    virtual char getSymbol() const =0;
    virtual bool isAnimal() const =0;
    int getHealthEffect() const ;

};

class Food : public Elements {
public:
    Food(int n);
    char getSymbol() const  override;
    ~Food();
    string getName() const override;
    bool isAnimal() const override;
};


class Wood : public Elements {
public:
    Wood(int n);
    char getSymbol() const  override;
    string getName() const override;
    bool isAnimal() const override;
    ~Wood();
};


class MedicalSupplies : public Elements {
public:
    MedicalSupplies(int n);
    char getSymbol() const  override ;
    string getName() const override ;
    bool isAnimal() const override;
    ~MedicalSupplies();
};


class Gold : public Elements {
public:
    Gold();
    char getSymbol() const  override ;
    string getName() const override ;
    bool isAnimal() const override;
    ~Gold();
};


class WildAnimal : public Elements {
protected:
    WildAnimal(int sz, char sym, int effect);
    virtual bool isAnimal() const override =0;
    ~WildAnimal();
};


class Wolf : public WildAnimal {
public:
    Wolf(int n);
    char getSymbol() const  override;
    string getName() const override;
    bool isAnimal() const override;
    ~Wolf();
};


class Bear : public WildAnimal {
public:
    Bear(int n);
    char getSymbol() const  override;
    string getName() const override;
    bool isAnimal() const override;
    ~Bear();
};

#endif
