#include "header.h"
//Methods of "user" class
void user::createAccount(database& centralDatabase)
{
    int n;
    std::cout<<"Pick a user name : "; 
    std::cin>>userName;
    std::cout<<"Set a password : ";
    std::cin>>password;
    std::cout<<"Enter your name : ";
    std::cin>>name;
    std::cout<<"Enter e-mail : ";
    std::cin>>email;
    std::cout<<"Enter your birthdate:(dd mm yy): ";
    std::cin>>birthDate.dd>>birthDate.mm>>birthDate.yy;
    std::cout<<"Enter number of work experiences to add: ";
    std::cin>>n;
    while(n--)
    {
        experience* e = new experience();
        std::cout<<"Enter start year: ";
        std::cin>>e->startYear;
        std::cout<<"Enter end year: ";
        std::cin>>e->endYear;
        std::cout<<"Enter  title: ";
        std::cin>>e->title;
        std::cout<<"Enter employer: ";
        std::cin>>e->employer;
    }
    std::cout<<"Enter number of skills to add: ";
    std::cin>>n;
    while(n--)
    {
        std::cout<<"Enter skill: ";
        std::string sk;
        std::cin>>sk;
        skills.insert(sk);
        if(centralDatabase.skillGroup.find(sk)!=centralDatabase.skillGroup.end())
        {
            centralDatabase.skillGroup[sk].push_back(this);
        }
        else
        {
            std::vector<user*> v;
            v.push_back(this);
            centralDatabase.skillGroup[sk] = v;   
        }
    }
    centralDatabase.userDatabase.push_back(this);
}
std::string user::getUsername()
{
    return userName;
}
void user::addConnections(database& centralDatabase)
{
    int k=-1;
    bool flag = loginVerification(centralDatabase,userName,password,k);
    if(flag)
    {
        std::string unConnection;
        std::cout<<"Enter user name of your connection: ";
        std::cin>>unConnection;
        int index1,index2;
        if(centralDatabase.findConnectionIndex(userName,index1)&&centralDatabase.findConnectionIndex(unConnection,index2))
        {
            std::cout<<"Index1 and index2 is "<<index1<<" "<<index2<<"\n";
            bool flag2 = true;
            for(int i = 0;i<centralDatabase.userDatabase[index1]->connections.size();i++)
            {
                if(centralDatabase.userDatabase[index1]->connections[i]->userName==unConnection)
                {
                    flag2 = false;
                }
            }
            if(flag2 && index1!=index2)
            {
                centralDatabase.userDatabase[index1]->connections.push_back(centralDatabase.userDatabase[index2]);  
                centralDatabase.userDatabase[index2]->connections.push_back(centralDatabase.userDatabase[index1]);  
            }    
        }   
        else
        {
            std::cout<<"User not found:(\n";
        }
    }
    else
    {
        std::cout<<"Username or Password is incorrect.\n";
    }
}
void user::deleteAccount(database& centralDatabase)
{
    std::string un,pw;
    std::cout<<"Enter your user name: ";
    std::cin>>un;
    std::cout<<"Enter your password: ";
    std::cin>>pw;
    int k = -1;
    bool flag = loginVerification(centralDatabase,un,pw,k);
    if(flag)
    {
        int index;
        centralDatabase.findConnectionIndex(un,index);
        centralDatabase.userDatabase.erase(centralDatabase.userDatabase.begin()+index);
        std::cout<<"Account deleted.\n";
    }
    else
    {
        std::cout<<"Username or Password is incorrect.\n";
    }
}
void user::printConnections()
{
    std::cout<<"\nConnections: ";
    for(int i = 0;i<connections.size();i++)
    {
        std::cout<<connections[i]->userName<<", ";
    }
    std::cout<<"\n";
}
void user::printAccountDetails()
{
    std::cout<<"\n--- USER ACCOUNT DETAILS ---\n\n";
    std::cout<<"User Name: "<<userName<<"\n";
    std::cout<<"Name: "<<name<<"\n";
    std::cout<<"Birth date: "<<birthDate.dd<<"/"<<birthDate.mm<<"/"<<birthDate.yy<<"\n";
    std::cout<<"Skills: ";
    for(auto itr = skills.begin(); itr != skills.end(); itr++)
    {
        std::cout<<*itr<<" ";
    }
    printConnections();
}
user* database::findUser(int k)
{
    user* newUser = userDatabase[k];
    return newUser;
}
void user::printNetworkForUserHelper(std::unordered_set<std::string>&visited,database& centralDatabase)
{
    if(visited.find(userName)==visited.end())
    {
        int k;
        if(centralDatabase.findConnectionIndex(userName,k))
        {
            std::cout<<userName<<" --> ";
            visited.insert(userName);
            for(int i = 0;i<centralDatabase.userDatabase[k]->connections.size();i++)
            {
                if(visited.find(centralDatabase.userDatabase[k]->connections[i]->userName)==visited.end())
                {
                    centralDatabase.userDatabase[k]->connections[i]->printNetworkForUserHelper(visited,centralDatabase);   
                }
            }
        }
    }
}
void user::printNetworkForUser(database& centralDatabase)//Do BFS starting from a particular user
{
    std::cout<<"\nYOUR NETWORK : \n";
    std::unordered_set<std::string>visited;
    printNetworkForUserHelper(visited,centralDatabase);
    std::cout<<"\n";
}


//Methods related to "database" class
bool database::findConnectionIndex(std::string un, int &k)
{
    bool flag = false;
    for(int i = 0;i<userDatabase.size() && !flag;i++)
    {
        if(userDatabase[i]->userName == un)
        {
            flag = true;
            k = i;
        }
    }
    return flag;
}   
void database::printCompleteNetwork()
{
    std::cout<<"----- NETWORK -----"<<"\n";
    for(int i = 0;i<userDatabase.size();i++)
    {
        std::cout<<"\n--- USER NO."<<i+1<<" ---\n";
        userDatabase[i]->printAccountDetails();
    }
}
void database::printUserGroupBySkill()
{
    std::cout<<"Search for a skill e.g. 'Coding' ... ";
    std::string sk;
    std::cin>>sk;
    for(auto i:skillGroup)
    {
        if(i.first == sk)
        {
            std::cout<<"Skill [ "<<i.first<<" ]: Skill Group: [ ";
            for(int j = 0;j<i.second.size();j++)
            {
                std::cout<<i.second[j]->userName<<" ";
            }
            std::cout<<" ]\n";
        }
    }  
}
int database::lengthOfShortestPath(std::string un1,std::string un2,std::unordered_set<std::string>&visited,std::vector<std::string>&path)
{
    int ans = -1;
    int n1,n2;
    if(findConnectionIndex(un1,n1)&&findConnectionIndex(un2,n2))
    {
        visited.insert(un1);
        if(n1==n2)
        {
            ans = 0;
        }
        else
        {
            for(int i = 0;i<userDatabase[n1]->connections.size() && ans==-1;i++)
            {
                if(userDatabase[n1]->connections[i]->userName == un2)
                {
                    ans = 1;
                }
                path.push_back(un2);
            }
            if(ans == -1)
            {
                bool flag1 = false;
                for(int i = 0;i<userDatabase[n1]->connections.size() && !flag1;i++)
                {
                    if(visited.find(userDatabase[n1]->connections[i]->userName)==visited.end())
                    {
                        flag1 = true;
                    }
                }
                if(flag1)
                {
                    int dist,ip=-1;
                    for(int i = 0;i<userDatabase[n1]->connections.size() && !flag1;i++)
                    {
                        if(visited.find(userDatabase[n1]->connections[i]->userName)==visited.end())
                        {
                            dist = lengthOfShortestPath(userDatabase[n1]->connections[i]->userName,un2,visited,path);
                            if(dist!=-1 && dist>ans)
                            {
                                ans = 1 + dist;
                                ip = i;
                            }
                        }
                    }
                    if(ip!=-1)
                    {
                        path.push_back(userDatabase[ip]->userName);
                    }
                }
            }
        }
    }
    return ans;
}
void database::printShortestPathBetweenTwoUsers(std::string un1,std::string un2)
{
    std::unordered_set<std::string>visited;
    std::vector<std::string>path;
    path.push_back(un1);
    int dist = lengthOfShortestPath(un1,un2,visited,path);
    if(dist!=-1)
    {
        std::cout<<"Length of shortest path is :"<<dist;
        std::cout<<"\nSHORTEST PATH: ";
        for(int i = 0;i<path.size();i++)
        {
            std::cout<<path[i]<<" -->";
        }
        std::cout<<"\n";
    }
    else
    {
        std::cout<<"No path found. \n";
    }
}


//Methods unrelated to any class
bool loginVerification(database& centralDatabase,std::string un,std::string pw,int &k)
{
    bool flag = false;
    for(int i = 0;i<centralDatabase.userDatabase.size();i++)
    {
        if(centralDatabase.userDatabase[i]->userName == un && centralDatabase.userDatabase[i]->password == pw)
        {
            flag = true;
            k = i;
        }   
    }
    return flag;
}