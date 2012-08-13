/*
Black Dog: a game for Android and Desktop platforms using SDL and OpenGLES.
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ResourceElement.hpp"

ResourceElement::ResourceElement(Thing* owner, unsigned int init_max,
                                                int init_amount) :
ThingElement(owner),
current_amount((init_amount < 0) ? init_max : (unsigned int)init_amount),
max_amount(init_max)
{
}

bool ResourceElement::anyLeft() const
{
    return (current_amount > 0);
}

bool ResourceElement::isFull() const
{
  return (current_amount == max_amount);
}

unsigned int ResourceElement::getBalance() const
{
    return current_amount;
}

unsigned int ResourceElement::tryWithdraw(unsigned int try_amount)
{
    if(current_amount >= try_amount)
    {
      current_amount -= try_amount;
      return try_amount;    // transaction successfull
    }
    else
    {
      return withdrawAll();   // transaction failed
    }
}

unsigned int ResourceElement::withdrawAll()
{
    int withdraw_amount = current_amount;
    current_amount = 0;
    return withdraw_amount;
}

void ResourceElement::deposit(unsigned int add_amount)
{
    current_amount = min(current_amount+add_amount, max_amount);
}

void ResourceElement::depositMax()
{
    current_amount = max_amount;
}
