#include<bits/stdc++.h>

typedef struct date
{
    int dd; 
    int mm;
    int yy;
}date;

typedef struct experience
{
    int startYear;
    int endYear;
    std::string title;
    std::string employer;
}experience;
class database;
class user
{
    friend class database;
    friend bool loginVerification(database& centralDatabase, std::string un,std::string pw,int &k);
    private:
        std::string userName;
        std::string name;
        std::string email;
        std::string password;
        date birthDate;
        std::vector<user*> connections;
        std::vector<experience*> workExperience;
        std::unordered_set<std::string> skills;  
        void printNetworkForUserHelper(std::unordered_set<std::string>&visited,database& centralDatabase);
    public:
        std::string getUsername();
        void createAccount(database &centralDatabase);
        void addConnections(database &centralDatabase);
        void printAccountDetails();
        void printConnections();
        void printNetworkForUser(database &centralDatabase);
        void deleteAccount(database &centralDatabase);
};

class database
{
    friend class user;
    friend bool loginVerification(database& centralDatabase, std::string un,std::string pw,int& k);
    private:
        std::vector<user*> userDatabase;
        std::unordered_map<std::string,std::vector<user*>> skillGroup;
        int lengthOfShortestPath(std::string un1,std::string un2,std::unordered_set<std::string>&visited,std::vector<std::string> &path);
    public:
        bool findConnectionIndex(std::string un, int &k);
        user* findUser(int k);
        void printShortestPathBetweenTwoUsers(std::string un1,std::string un2);
        void printCompleteNetwork();
        void pathBetweenTwoUsers();
        void printConnectionBetweenTwoUsers();
        void printUserGroupBySkill();
};