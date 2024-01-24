#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <string>
#include <vector>

class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    std::vector<Ingredient*>& get_ingredients();

    /* Reason why we put the destructor here is that we
       want to support the following:
        EspressoBased* esp = new EspressoBased();
        delete esp;
     */
    ~EspressoBased();

protected:
    /* If we put here, the client cannot explicit call 
        destructor through delete keyword.
    */
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients;
    std::string name;

};


#endif // ESPRESSO_BASED_H