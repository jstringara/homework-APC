/// Header include
#include "social_network.hpp"
#include "user.hpp"

/// STD include
#include <iostream>
#include <algorithm>

namespace SocialNetworkNS
{
    size_t SocialNetwork::CUserIndex(
        const std::string &name, const std::string &surname) const
    {
        size_t i;

        User u(name, surname);

        bool found = false;

        for (i = 0; i < users.size() && !found; ++i)
            if (users[i] == u)
                found = true;

        if (found)
            return --i;
        else
            return users.size();
    }

    void SocialNetwork::AddUser(
        const std::string &name, const std::string &surname)
    {
        // check for existence, if max then proceed
        if (CUserIndex(name, surname) == users.size())
        {
            // add to the list of users
            users.push_back(User(name, surname));
            // add an empty vector as the list of friends
            friends.push_back(std::vector<size_t>{});
        } else
            std::cout << "User already present!" << std::endl;
    }

    const std::vector<User> SocialNetwork::CGetUsers() const
    {
        return users;
    }

    const std::vector<User> SocialNetwork::CGetFriends(const User &user) const
    {
        // call the same method but passing directly the name and surname
        return CGetFriends(user.CGetName(), user.CGetSurname());
    }

    const std::vector<User> SocialNetwork::CGetFriends(
        const std::string &name, const std::string &surname) const
    {
        std::vector<User> ret{};

        // get the user index
        const size_t userIndex = CUserIndex(name, surname);

        // if it does not exist, return empty vector
        if (userIndex == users.size()){
            std::cout << "User is not present in network!" << std::endl;
            return ret; // how to throw an actual error???
        }

        // loop over the friends (should be size_t but use auto)
        // use range for -> if empty -> no problem
        for (size_t friendIndex: friends[userIndex])
        {
            ret.push_back(users[friendIndex]);
        }

        return ret;
    }

    void SocialNetwork::AddFriendship(
        const std::string &first_name,
        const std::string &first_surname,
        const std::string &second_name,
        const std::string &second_surname)
    {

        // get the user indexes
        const size_t firstIndex = CUserIndex(first_name, first_surname);
        const size_t secondIndex = CUserIndex(second_name, second_surname);

        // if either does not exist stop
        if ((firstIndex == users.size()) || (secondIndex == users.size())){
            std::cout << "One of the users does not exist!" << std::endl;
            return;
        }

        // add second to first's list of friends
        // make sure not already present
        if (std::find(
            friends[firstIndex].begin(),
            friends[firstIndex].end(),
            secondIndex) == friends[firstIndex].end())
            friends[firstIndex].push_back(secondIndex); // add to the list
        else {
            std::cout << "Friendship already present:" << users[firstIndex].ToString() << " and " <<
                users[secondIndex].ToString() << " are already friends!" << std::endl;
        }
        // add first to second's list of friends
        if (std::find(
        friends[secondIndex].begin(),
        friends[secondIndex].end(),
        firstIndex) == friends[secondIndex].end())
            friends[secondIndex].push_back(firstIndex);
    }
}
