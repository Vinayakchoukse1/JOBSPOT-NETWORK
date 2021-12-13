/*
    NAME: VINAYAK CHOUKSE
    ENROLLMENT NUMBER: BT19CSE120
    E-MAIL: priyanka.borwanker@gmail.com
    DSPD SUMMER PROJECT - IMPLEMENTATION OF UNWEIGHTED AND UNDIRECTED GRAPHS USING ADJACENCY LIST
*/
#include <bits/stdc++.h>
using namespace std;

/*---NODE STRUCTURE---*/

struct node
{
    int data;
    node *next;
};

/*---NODE FUNCTIONS---*/

node *create_node(int n)
{
    node *new_node = new node();
    new_node->data = n;
    new_node->next = NULL;
    return new_node;
}

/*---PRINT LIST---*/

void print_list(node *head)
{
    node *ptr = head;
    while (ptr)
    {
        cout << ptr->data << " -->";
        ptr = ptr->next;
    }
    cout << endl;
}

/*---ADD NODE---*/

void add_node_LL(node *head, int val)
{
    if (head == NULL)
    {
        head = create_node(val);
    }
    else
    {
        node *ptr = head;
        while (ptr->data > val && ptr->next)
        {
            ptr = ptr->next;
        }
        node *temp = ptr->next;
        ptr->next = create_node(val);
        ptr = ptr->next;
        ptr->next = temp;
    }
}

/*---DELETE NODE---*/

void delete_node_LL(node **head, int key)
{
    node *temp;
    if ((*head)->data == key)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    else
    {
        node *current = *head;
        while (current->next != NULL)
        {
            if (current->next->data == key)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                break;
            }
            else
            {
                current = current->next;
            }
        }
    }
}

/*---GRAPH FUNCTIONS---*/

int minimum_nodes_in_path(vector<node *> &graph, unordered_set<node *> &st, int n1, int n2)
{
    bool flag1 = false, flag2 = false;
    int ans = -1;
    for (int k = 0; k < graph.size(); k++)
    {
        if (graph[k]->data == n1)
        {
            flag1 = true;
        }
        if (graph[k]->data == n2)
        {
            flag2 = true;
        }
    }
    if (flag1 && flag2)
    {
        if (n1 == n2)
        {
            ans = 0;
        }
        int k;
        for (k = 0; k < graph.size() && graph[k]->data != n1; k++)
        {
        }
        bool flag3 = false;
        node *ptr = graph[k];
        while (ptr)
        {
            if (ptr->data == n2)
            {
                flag3 = true;
            }
            ptr = ptr->next;
        }
        if (flag3)
        {
            ans = 1;
        }
        else
        {
            node *ptr = graph[k]->next;
            vector<node *> list_nodes_to_explore_next;
            //cout<<"yes in else "<<n1<<" "<<n2<<endl;
            while (ptr)
            {
                if (st.find(ptr) == st.end())
                {
                    list_nodes_to_explore_next.push_back(ptr);
                    st.insert(ptr);
                }
                ptr = ptr->next;
            }
            for (int i = 0; i < list_nodes_to_explore_next.size(); i++)
            {
                int h = minimum_nodes_in_path(graph, st, list_nodes_to_explore_next[i]->data, n2);
                //cout<<n1<<" "<<n2<<" "<<list_nodes_to_explore_next[i]->data<<endl;
                if (h != -1)
                {
                    if (ans == -1)
                    {
                        ans = 1 + h;
                    }
                    else
                    {
                        if (ans > 1 + h)
                        {
                            ans = 1 + h;
                        }
                    }
                }
            }
        }
    }
    return ans;
}

/*--------------------------------------CREATE GRAPH---------------------------------------------------------*/

vector<node *> create_graph()
{
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    vector<node *> new_graph;
    int i = 0;
    while (n--)
    {
        node *new_node = create_node(i);
        new_graph.push_back(new_node);
    }
    return new_graph;
}
vector<node *> create_graph(int n)
{
    vector<node *> new_graph;
    int i = 0;
    while (n--)
    {
        node *new_node = create_node(i);
        i++;
        new_graph.push_back(new_node);
    }
    return new_graph;
}
vector<node *> create_graph(vector<int> nodes)
{
    vector<node *> new_graph;
    for (int i = 0; i < nodes.size(); i++)
    {
        node *new_node = create_node(i);
        new_graph.push_back(new_node);
    }
    return new_graph;
}
/*---ADD & DELETE NODE---*/
void add_node(vector<node *> &graph, int n)
{
    node *new_node = create_node(n);
    graph.push_back(new_node);
}
void delete_node(vector<node *> &graph, int n)
{
    vector<node *>::iterator itr;
    for (itr = graph.begin(); itr != graph.end(); itr++)
    {
        //cout<<(*itr)->data<<endl;
        if ((*itr)->data == n)
        {
            graph.erase(itr);
        }
    }
    for (itr = graph.begin(); itr != graph.end(); itr++)
    {
        delete_node_LL(&(*itr), n);
    }
}
/*--ADD & DELETE EDGE--*/
void add_edge(vector<node *> &graph, int i, int j)
{
    //Searching if both nodes are present
    bool flag1 = false, flag2 = false;
    for (int k = 0; k < graph.size(); k++)
    {
        if (graph[k]->data == i)
        {
            flag1 = true;
        }
        if (graph[k]->data == j)
        {
            flag2 = true;
        }
    }
    if (flag1 && flag2 && i != j)
    {
        add_node_LL(graph[i], j);
        add_node_LL(graph[j], i);
    }
}
void delete_edge(vector<node *> &graph, int i, int j)
{
    bool flag1 = false, flag2 = false;
    for (int k = 0; k < graph.size(); k++)
    {
        if (graph[k]->data == i)
        {
            flag1 = true;
        }
        if (graph[k]->data == j)
        {
            flag2 = true;
        }
    }
    if (flag1 && flag2 && i != j)
    {
        delete_node_LL(&graph[i], j);
        delete_node_LL(&graph[j], i);
    }
}
/*---PRINT FUNCTION---*/
void print_graph(vector<node *> &graph)
{
    cout << graph.size() << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        print_list(graph[i]);
    }
}
void print_dfs(vector<node *> &graph, unordered_map<int, bool> &visited, int key)
{
    //Checking if node is present and unvisited
    bool flag1 = false;
    int i;
    for (i = 0; i < graph.size() && !flag1; i++)
    {
        if (graph[i]->data == key)
        {
            //cout<<"Node is present and unvistied"<<graph[i]->data<<endl;
            flag1 = true;
            break;
        }
    }
    if (flag1 && !visited[graph[i]->data])
    {
        node *ptr = graph[i];
        cout << graph[i]->data << "--> ";
        visited[graph[i]->data] = true;
        //cout<<"First node is"<<ptr->data<<endl;
        while (ptr)
        {
            if (!visited[ptr->data])
            {
                print_dfs(graph, visited, ptr->data);
            }
            ptr = ptr->next;
        }
    }
}
void print_bfs(vector<node *> &graph, unordered_map<int, bool> &visited, int key)
{
    //Checking if node is present and unvisited
    //cout<<"In BFS of "<<key<<endl;
    bool flag1 = false;
    int i;
    for (i = 0; i < graph.size() && !flag1; i++)
    {
        if (graph[i]->data == key)
        {
            //cout<<"Node is present and unvistied"<<graph[i]->data<<endl;
            flag1 = true;
            break;
        }
    }
    if (flag1)
    {
        //cout<<"First node is"<<ptr->data<<endl;
        node *ptr = graph[i];
        vector<node *> v;
        while (ptr)
        {
            if (!visited[ptr->data])
            {
                cout << ptr->data << "--> ";
                visited[ptr->data] = true;
                v.push_back(ptr);
            }
            ptr = ptr->next;
        }
        for (int i = 0; i < v.size(); i++)
        {
            //cout<<"Next exploring "<<v[i]->data<<endl;
            print_bfs(graph, visited, v[i]->data);
        }
    }
}
void print_shortest_path1(vector<node *> &graph, int n1, int n2)
{
    bool flag1 = false, flag2 = false;
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i]->data == n1)
        {
            flag1 = true;
        }
        if (graph[i]->data == n2)
        {
            flag2 = true;
        }
    }
    if (flag1 && flag2)
    {
        unordered_set<node *> st;
        int mn = minimum_nodes_in_path(graph, st, n1, n2);
        if (mn != -1)
        {
            if (mn == 0)
            {
                cout << n1 << " -->" << n2 << endl;
            }
            else
            {
                int k;
                for (k = 0; k < graph.size() && graph[k]->data != n1; k++)
                {
                }
                node *ptr = graph[k]->next;
                cout << n1 << " -->";
                int l = mn, index_l;
                while (ptr)
                {
                    st.clear();
                    int ms = minimum_nodes_in_path(graph, st, ptr->data, n2);
                    if (ms != -1 && ms < l)
                    {
                        l = ms;
                        index_l = ptr->data;
                    }

                    ptr = ptr->next;
                }
                print_shortest_path1(graph, index_l, n2);
            }
        }
        else
        {
            cout << "Path does not exist :(" << endl;
        }
    }
}
bool check_loop(vector<node *> &graph)
{
    bool flag = false;
    for (int i = 0; i < graph.size(); i++)
    {
    }
    return flag;
}
int main()
{
    vector<node *> new_graph = create_graph(8);
    add_edge(new_graph, 1, 2);
    add_edge(new_graph, 1, 5);
    add_edge(new_graph, 0, 3);
    add_edge(new_graph, 3, 4);
    add_edge(new_graph, 4, 6);
    add_edge(new_graph, 0, 1);
    add_edge(new_graph, 4, 5);
    print_graph(new_graph);
    int n = 8;
    unordered_map<int, bool> v;
    for (int i = 0; i < n; i++)
    {
        v[i] = false;
    }
    unordered_set<node *> st;
    cout << "Printing shortes path : " << minimum_nodes_in_path(new_graph, st, 4, 2) << endl;
    print_shortest_path1(new_graph, 4, 4);
    return 0;
}