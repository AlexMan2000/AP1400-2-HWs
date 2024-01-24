#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H



class Cinnamon
{
public:
    Cinnamon(size_t units) : Ingredient{5, units}
    {
        this->name = "Cinnamon";
    }

    virtual std::string get_name() {return this->name;}
};




#endif // SUB_INGREDIENTS_H