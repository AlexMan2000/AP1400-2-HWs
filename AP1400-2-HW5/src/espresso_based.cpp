#include "espresso_based.h"

// Default constructor
EspressoBased::EspressoBased() {
}


// Copy Constructor
EspressoBased::EspressoBased(const EspressoBased& esp) {
    // Valid, get_ingredients return a lvalue, which can be put in lvalue
    this -> ingredients = esp.get_ingredients;
    this -> name = esp.get_name();
}


// Destructor
EspressoBased::~EspressoBased() {
    for (const auto& i: ingredients) {
        delete i;
    }
    ingredients.clear();
}


// Copy Assignment
void EspressoBased::operator= (const EspressoBased& esp) {
    if (this != &other) {
        for (const auto& i: ingredients) {
            delete i;
        }
        ingredients.clear();
        ingredients = esp.ingredients;
        name = esp.get_name();

    }
}


// Member functions
void EspressoBased::brew() {
    
}

std::string EspressoBased::get_name() {
    return this -> name;
}


double EspressoBased::price() {
    double result;
    for (auto& i: ingredients) {
        result += i.price();
    }
    return result;
}   

std::vector<Ingredients*>& EspressoBased::get_ingredients() {
    return this -> ingredients;
}
