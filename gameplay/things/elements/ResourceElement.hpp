#ifndef RESOURCEELEMENT_HPP_INCLUDED
#define RESOURCEELEMENT_HPP_INCLUDED

#include "ThingElement.hpp"

class ResourceElement : public ThingElement
{
    /// ATTRIBUTES
    private:
    int current_amount;
    int max_amount;

    /// METHODS
    public:
    ResourceElement(Thing* owner, int init_max, int init_amount = -1);
    bool anyLeft() const;
    int getBalance() const;
    bool tryWithdraw(int try_amount = 1);
    int withdrawAll();
    void deposit(int add_amount = 1);
    void depositMax();
};

#endif // RESOURCEELEMENT_HPP_INCLUDED
