#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>

struct team
{
    int points;
    std::string name;
    std::vector<std::string> members;

    team();

    team(std::string n)
    {
        name = n;
        points = 0;
    }

    void addTeamMember(std::string member)
    {
        members.push_back(member);
    }

    void increasePoints(int p)
    {
        points += p;
    }

    std::string printMembers() {
        std::string s = "";
        for (std::string m : members) {
            s += " " + m;
        }
        return s;
    }
};

#endif
