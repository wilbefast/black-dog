#include "ResourceElement.hpp"

ResourceElement::ResourceElement(Thing* owner, int init_max, int init_amount) :
ThingElement(owner),
current_amount((init_amount < 0) ? init_max : init_amount),
max_amount(init_max)
{
}

bool ResourceElement::anyLeft() const
{
    return (current_amount > 0);
}

int ResourceElement::getBalance() const
{
    return current_amount;
}

bool ResourceElement::tryWithdraw(int try_amount)
{
    if(current_amount >= try_amount)
    {
        current_amount -= try_amount;
        return true;    // transaction successfull
    }
    else
        return false;   // transaction failed
}

int ResourceElement::withdrawAll()
{
    int withdraw_amount = current_amount;
    current_amount = 0;
    return withdraw_amount;
}

void ResourceElement::deposit(int add_amount)
{
    current_amount = min(current_amount+add_amount, max_amount);
}

void ResourceElement::depositMax()
{
    current_amount = max_amount;
}
