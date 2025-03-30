#include "Elements.h"


Elements::Elements(int sz, char sym, int effect) : size(sz), symbol(sym), Effect(effect) {}
Elements::~Elements(){};
Elements::Elements (Elements &other){
    size=other.size;
    symbol=other.symbol;
    Effect=other.Effect;
}

int Elements::getHealthEffect() const { return Effect; }



Food::Food(int n) : Elements(1, 'F', n/6) {}
char Food::getSymbol() const   { return symbol; }
Food::~Food(){}
string Food::getName() const  { return "Food"; }
bool Food::isAnimal() const { return false;}



Wood::Wood(int n) : Elements(2, 'I', floor(n / 8.0)) {}
char Wood::getSymbol() const   { return symbol; }
string Wood::getName() const  { return "Wood"; }
bool Wood::isAnimal() const { return false;}
Wood::~Wood(){}




MedicalSupplies::MedicalSupplies(int n) : Elements(1, 'S', floor(n / 4.0)) {}
char MedicalSupplies::getSymbol() const   { return symbol; }
string MedicalSupplies::getName() const  { return "Medical Supplies"; }
bool MedicalSupplies::isAnimal() const { return false;}
MedicalSupplies::~MedicalSupplies(){}




Gold::Gold() : Elements(1, 'G', 0) {} // Gold has no health effect.
char Gold::getSymbol() const { return symbol; }
string Gold::getName() const { return "Gold"; }
bool Gold::isAnimal() const { return false;}
Gold::~Gold(){}




WildAnimal::WildAnimal(int sz, char sym, int effect) : Elements(sz, sym, effect) {}
WildAnimal::~WildAnimal(){}




Wolf::Wolf(int n) : WildAnimal(1, 'W', -n/4) {} // because of the animals' negative effect we directly take negative to count it easier.
char Wolf::getSymbol() const { return symbol; }
string Wolf::getName() const { return "Wolf"; }
bool Wolf::isAnimal() const{ return true;}
Wolf::~Wolf(){}




Bear::Bear(int n) : WildAnimal(3, 'B', -n/2) {} // because of the animals' negative effect we directly take negative to count it easier.
char Bear::getSymbol() const { return symbol; }
string Bear::getName() const { return "Bear"; }
bool Bear::isAnimal() const { return true;}
Bear::~Bear(){}
