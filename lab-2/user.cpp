/// Header include
#include "user.hpp"

namespace SocialNetworkNS
{
    User::User(const std::string &_name, const std::string &_surname) :
        name(_name), surname(_surname) {}

    const std::string &User::CGetName() const
    {
        return name;
    }

    const std::string &User::CGetSurname() const
    {
        return surname;
    }

    std::string User::ToString() const
    {
        return name + " " + surname;
    }

    bool operator==(const User &lhs, const User &rhs)
    {
        // same if they have same name and surname
        // must use getters since we are outside of object scope
        return ((lhs.CGetName() == rhs.CGetName()) &&
            (lhs.CGetSurname() == rhs.CGetSurname()));
    }
}
