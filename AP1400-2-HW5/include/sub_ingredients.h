#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H


// Important: Use macro to simplify the class declarations
#define TO_STRING(x) #x

// Define the macro
#define DEFCLASS(className, priceUnit) \
class className: public Ingredient \
{ \
public: \
    className(size_t units) : Ingredient(priceUnit, units) \
    { \
        this->name = TO_STRING(className); \
    } \
    virtual std::string get_name() {return this->name;} \
};

// Avoid repetitions on the code, declare the class
DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);



#endif // SUB_INGREDIENTS_H