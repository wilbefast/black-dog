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
    bool isFull() const;
    int getBalance() const;
    bool tryWithdraw(int try_amount = 1);
    int withdrawAll();
    void deposit(int add_amount = 1);
    void depositMax();
};

#endif // RESOURCEELEMENT_HPP_INCLUDED
