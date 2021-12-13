#include "header.h"
int main()
{
    database* newDatabase = new database();
    bool flag = true;
    std::cout<<"\n---- WELCOME TO JOBSPOT! ----\n";
    int n;
    std::cout<<"\n Enter your choice: \n";
    std::cout<<"1. Login or Create Your Account\n";
    std::cout<<"2. Exit\n";
    std::cin>>n;
    while(flag)
    {
        switch(n)
        {
            case 1:
            {
                std::cout<<"A) Login into existing account \nB) Create new account\n";
                std::cout<<"Enter your choice(A/B): ";
                char choice;
                std::cin>>choice;
                switch(choice)
                {
                    case 'A':
                    {
                        std::string un,pw;
                        std::cout<<"Enter username: ";
                        std::cin>>un;
                        std::cout<<"Enter password: ";
                        std::cin>>pw;
                        user* newUser = NULL;
                        int k;
                        bool loginFlag = loginVerification(*newDatabase,un,pw,k);
                        if(loginFlag)
                        {
                            newUser = newDatabase->findUser(k);
                            std::cout<<"\nLogin Succesful!\n\n";
                            std::cout<<"I want to ... \n\n";
                            std::cout<<"a. Print account details \n";
                            std::cout<<"b. Add Connections \n";
                            std::cout<<"c. View my connections and network \n";
                            std::cout<<"d. List user groups based on skill \n";
                            std::cout<<"e. View shortest path to another user \n";
                            std::cout<<"f. Find user \n";
                            std::cout<<"g. Delete my account \n";
                            std::cout<<"Press 'x' to logout \n";
                            char ch;
                            std::cin>>ch;
                            bool flag2 = true;
                            while(flag2)
                            {
                                switch(ch)
                                {
                                    case 'a':
                                    {
                                        newUser = newDatabase->findUser(k);
                                        newUser->printAccountDetails();
                                        break;
                                    }
                                    case 'b':
                                    {
                                        newUser->addConnections(*newDatabase);
                                        break;
                                    }
                                    case 'c':
                                    {
                                        newUser->printNetworkForUser(*newDatabase);
                                        break;
                                    }
                                    case 'd':
                                    {
                                        newDatabase->printUserGroupBySkill();
                                        break;
                                    }
                                    case 'e':
                                    {
                                        std::string searchQuery;
                                        std::cout<<"Enter username of another user: ";
                                        std::cin>>searchQuery;
                                        std:: string un = newUser->getUsername();
                                        newDatabase->printShortestPathBetweenTwoUsers(un,searchQuery);
                                        break;
                                    }
                                    case 'f':
                                    {
                                        std::cout<<"Enter user name of another user: ";
                                        std::string searchQuery;
                                        std::cin>>searchQuery;
                                        int i;
                                        if(newDatabase->findConnectionIndex(searchQuery,i))
                                        {
                                            std::cout<<"\nSearch results for '"<<searchQuery<<"'...\n";
                                            user* searchResult = newDatabase->findUser(i);
                                            searchResult->printAccountDetails();
                                        }
                                        else
                                        {
                                            std::cout<<"User not found.\n"<<std::endl;
                                        }
                                        break;
                                    }
                                    case 'g':
                                    {
                                        newUser->deleteAccount(*newDatabase);
                                        flag2 = false;
                                        break;
                                    }
                                    case 'x':
                                    {
                                        flag2 = false;
                                        break;
                                    }
                                    default:
                                    {
                                        std::cout<<"Please enter valid choice.\n";
                                    }
                                }
                                if(flag2)
                                {
                                    std::cout<<"a. Print account details \n";
                                    std::cout<<"b. Add Connections \n";
                                    std::cout<<"c. View my network \n";
                                    std::cout<<"d. List user groups based on skill \n";
                                    std::cout<<"e. View shortest path to a another user \n";
                                    std::cout<<"f. Find user \n";
                                    std::cout<<"g. Delete my account \n";
                                    std::cout<<"Press 'x' to logout \n"; 
                                    std::cin>>ch;
                                }
                            }
                        }
                        else
                        {
                            std::cout<<"Username or Password incorrect.\n";
                        }
                        break;
                    }
                    case 'B':
                    {
                        user* newUser = new user();
                        newUser->createAccount(*newDatabase);
                        std::cout<<"\nAccount created succesfully!\n";
                        break;
                    }
                    default:
                    {
                        std::cout<<"Please enter valid choice.\n";
                    }
                }
                break;
            }
            case 2:
            {
                std::cout<<"\nThanks for using JOBSPOT!\n";
                flag = false;
                break;
            }
            default:
            {
                std::cout<<"\nPlease enter a valid choice.\n";
            }
        }
        if(flag)
        {
            std::cout<<"Enter next choice: \n";
            std::cout<<"1. Login or Create Your Account\n";
            std::cout<<"2. Exit\n";
            std::cin>>n;
        }
    }
    return 0;
}