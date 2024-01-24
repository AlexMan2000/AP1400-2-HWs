#ifndef INGREDIENT_H
#define INGREDIENT_H

class Ingredient
{
public:
    double get_price_unit() {
        return this -> price_unit;
    }
    size_t get_units() {
        return this -> units;
    }

    // Make it virtual to enable polymorphism
    virtual std::string get_name() = 0;

    double price() {
        return this -> price_unit * this -> units;
    }
    

protected:
    Ingredient(double price_unit, size_t units);

    double price_unit;
    size_t units;
    std::string name;
};


#endif // INGREDIENT_H

