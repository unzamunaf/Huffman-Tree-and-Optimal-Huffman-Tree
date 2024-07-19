#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;

class node //node of huffman
{
public:
    char character;
    string code;
    int frequency;
    node* left;
    node* right;
    node* next;
    node* perv;

    node()
    {
        perv = NULL;
        next = NULL;
        code = "";
        left = NULL;
        right = NULL;
        frequency = 0;
        character = 0;
    }
};

class huffman           //creating huffman class
{
public:
    string s;
    node* start;    // linked list for que optimal huffman
    node* start2;   //head of linked list
    node* stop2;   //  tail of linked list               
    node* stop; // tail of linked list
    node* root; // starting point of tree

    huffman()           //declaring constructors 
    {
        s = "";
        start2 = NULL;
        start = NULL;
        stop = NULL;
        root = NULL;
        stop2 = NULL;

    }

    void calFrequency(string text)  /*calculating the frequency of each character,
                                    that is number of times each character occurs*/
    {
        int i = 0;
        while (i < text.length())
        {

            if (text[i] == '*')
            {
                cout << "invalid String";       //if the given input in the file that is the text is valid or not

                return;
            }

            i++;
        }

        i = 0;
        int fre = 0;
        char c;                                             // making the frequency table
        cout << "\n\u001b[1;31mFREQUENCY TABLE : \n\n";
        while (i < text.length())
        {
            c = text[i];
            int j = 0;
            while (j < text.length() && c != '*' && c != '\n')
            {
                if (c == text[j])
                {
                    text[j] = '*';
                    fre++;
                }

                j++;
            }

            if (c != '*' && c != '\n')
            {

                cout << "\u001b[1;35mcharacter : \u001b[1;34m" << c << "\u001b[1;35m frequency : \u001b[1;34m" << fre << " \n";
                enqueue(c, fre); //enter char in queue 
            }
            fre = 0;
            i++;
        }

    }

    void enqueue2(node* n)      //takes whole node as input 
    {

        if (start == NULL)
        {
            start = n;
            stop = n;
        }
        else
        {
            stop->next = n;
            stop = stop->next;
        }
    }

    void enqueue(char c, int fre)   // entering element in queue
    {
        node* n = new node;     // new node for queue
        n->character = c;
        n->frequency = fre;
        node* n2 = new node;        // new nodw for linked list 
        n2->character = c;
        n2->frequency = fre;
        if (start == NULL)
        {
            start2 = n2;
            stop2 = n2;
            start = n;
            stop = n;

        }
        else
        {
            stop->next = n;

            stop = stop->next;
            stop2->next = n2;

            stop2 = stop2->next;
        }
    }

    node* dequeue()
    {

        if (start == NULL)
        {

        }
        else
        {
            node* temp = start;
            start = start->next;
            return temp;
        }
    }

    void make_tree()            // normal huffman 
    {
        while (start != stop) {     // loop tab tk chalay ga jab tk aik element nahin reh jaata 


            node* temp = dequeue();
            node* temp2 = dequeue();
            node* tempF = new node;
            tempF->left = temp;
            tempF->right = temp2;
            tempF->frequency = tempF->left->frequency + tempF->right->frequency;
            tempF->character = '*';
            enqueue2(tempF);

        }

        node* temp = dequeue();     //assign root variable top of tree
        root = temp;

    }

    void make_tree2()       // optimal huffman 
    {
        while (start != stop)
        {

            node* temp = dequeue();
            node* temp2 = dequeue();
            node* tempF = new node;
            tempF->left = temp;
            tempF->right = temp2;
            tempF->frequency = tempF->left->frequency + tempF->right->frequency;
            tempF->character = '*';
            enqueue2(tempF);

            start = merge_sort(start);
            replace_stop();
            //cout << "\n";
            //show();
        }

        node* temp = dequeue();
        root = temp;

    }

    void coding(node* r, string c) //  (Left, current node, Right)
    {

        if (r == NULL)
        {
            return;
        }
        else
        {
            s = s.append(c);

        }

        /* first recur on left child */
        coding(r->left, "0");
        /* then print the data of node */
        if (r->character != '*' && r != root)
        {
            cout << "\u001b[1;35m\nCharacter : \u001b[1;34m" << r->character << "\u001b[1;35m  Frequency : \u001b[1;34m" << r->frequency << "\u001b[1;35m   code  : \u001b[1;34m" << s;
            node* temp = start2;
            while (temp->next != NULL)  //assign the code value calculated (in linked list) 
            {
                if (temp->character == r->character)
                {
                    temp->code = s;
                }
                temp = temp->next;
            }
            if (temp->character == r->character)
            {
                temp->code = s;
            }
            r->code = s;
            s.pop_back();

        }
        if (r == root)
        {
            s = "";
        }

        /* now recur on right child */
        coding(r->right, "1");

        if (r->character == '*' && s != "") //going to recur right tree
        {
            s.pop_back();
        }
    }

    string encoder(string c)    //input the coded values 
    {
        string coded = "";

        int j = 0;
        int i = 0;
        int len = c.length();

        node* temp = start2;    //head of linked list 
        for (i = 0; i < len; i++)
        {

            while (temp->next != NULL)
            {

                if (temp->character == c[i])
                {
                    coded = coded.append(temp->code);
                }
                temp = temp->next;
            }

            if (temp->character == c[i])
            {
                coded = coded.append(temp->code);
            }

            temp = start2;

        }

        return coded;

    }

    void show()
    {
        node* temp = start;
        while (temp->next != NULL)
        {
            cout << temp->character << "      " << temp->frequency << "\n";
            temp = temp->next;
        }
        cout << temp->character << "      " << temp->frequency;
    }

    void show2()
    {
        node* temp = start2;
        while (temp->next != NULL)
        {
            cout << temp->character << "      " << temp->frequency << "\n";
            temp = temp->next;
        }
        cout << temp->character << "      " << temp->frequency;
    }

    void decoder(string c)
    {
        string ss = "";
        node* temp = root;

        for (int i = 0; i < c.length(); i++)
        {

            if (c[i] == '0')
            {

                temp = temp->left;
            }
            else if (c[i] == '1')
            {

                temp = temp->right;

            }

            if (temp->character != '*')     //destination reached if we get a char 
            {

                ss.push_back(temp->character);
                temp = root;

            }
        }
        cout << "\n\u001b[1;31mDECODED TEXT : ";
        cout << "\n\u001b[1;32m> ";
        cout << ss;

        cout << "\n";

    }

    node* merge(node* a, node* b)
    {
        // base case
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;

        node* c;

        if (a->frequency < b->frequency)
        {
            c = a;
            c->next = merge(a->next, b);
        }
        else
        {
            c = b;
            c->next = merge(a, b->next);
        }

        return c;
    }

    node* mid_point(node* head)
    {

        if (head == NULL || head->next == NULL)
            return head;


        node* fast = head;
        node* slow = head;

        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next;

            if (fast->next == NULL)
                break;

            fast = fast->next;
            slow = slow->next;
        }

        return slow;
    }

    node* merge_sort(node* head)
    {

        if (head == NULL || head->next == NULL)
            return head;


        node* mid = mid_point(head);
        node* a = head;
        node* b = mid->next;

        mid->next = NULL;


        a = merge_sort(a);
        b = merge_sort(b);
        node* c = merge(a, b);

        return c;
    }

    void replace_stop()
    {
        node* temp = start;
        while (temp->next != NULL)
        {

            temp = temp->next;
        }
        stop = temp;
    }



};


int main()
{
    cout << "\u001b[1;32m                         # #### ####" << endl;
    cout << "\u001b[1;32m                      ### \\/#|### |/####" << endl;
    cout << "\u001b[1;32m                    ##\\/#/ \\||/##/_/##/_#" << endl;
    cout << "\u001b[1;32m                     ##\\/#/ \\||/##/_/##/_#" << endl;
    cout << "\u001b[1;32m                    # ##  \\/###|/ \\/ # ###" << endl;
    cout << "\u001b[1;32m                  ##_\\_#\\_\\## | #/###_/_####" << endl;
    cout << "\u001b[1;32m                  ##_\\_#\\_\\## | #/###_/_####" << endl;
    cout << "\u001b[1;32m                 ## #### # \\ #| /  #### ##/##" << endl;
    cout << "\u001b[1;32m                  _#_--###`  |{,###---###-~" << endl;
    cout << "\u001b[1;33m                            \\ }{" << endl;
    cout << "\u001b[1;33m                             }}{" << endl;
    cout << "\u001b[1;33m                             }}{" << endl;
    cout << "\u001b[1;33m                       , -=-~{ .-^- _" << endl;
    cout << "\u001b[1;32m                     HUFFMAN TREE MAKER" << endl << endl << endl;


    cout << "\u001b[1;31m************************\n";
    cout << "\u001b[1;31m*                      *\n";
    cout << "\u001b[1;32m*     HUFFMAN TREE     *\n";
    cout << "\u001b[1;31m*                      *\n";
    cout << "\u001b[1;31m************************\n";

    huffman h;
    string path;
    string txt;
    cout << "\n\nENTER THE PATH OF THE FILE : ";        //accessing the path of the file in which our text is present 
    cout << "\n\u001b[1;32m>";
    cin >> path;


    ifstream myfile(path);          // reading the file 
    cout << "\n\u001b[1;31m_______________________________________________________________________________________________________" << endl;
    cout << "\u001b[1;31m_______________________________________________________________________________________________________" << endl;
    cout << "\n\n\u001b[1;31mTEXT :\n";
    cout << "\u001b[1;32m";
    if (myfile.is_open())
    {
        while (getline(myfile, txt))            //reading the file 
        {
            cout << txt << '\n';

        }
        myfile.close();
    }
    else
    {
        cout << "\nUnable to open file : ";         // if file is not found 
        return 0;
    }

    cout << "\n\u001b[1;31m_______________________________________________________________________________________________________" << endl;
    cout << "\u001b[1;31m_______________________________________________________________________________________________________\n" << endl;

    cout << "\u001b[1;34m             MENU" << endl;
    cout << "\u001b[1;31m*****************************" << endl;
    cout << "\u001b[1;31m*                           *" << endl;
    cout << "\u001b[1;31m*"; cout << "\u001b[1;34m>optimal huffman --> 1"; cout << "\u001b[1;31m     *" << endl;
    cout << "\u001b[1;31m*                           *" << endl;
    cout << "\u001b[1;31m*"; cout << "\u001b[1;34m>normal huffman  --> 2"; cout << "\u001b[1;31m     *" << endl;
    cout << "\u001b[1;31m*                           *" << endl;
    cout << "\u001b[1;31m*****************************" << endl << endl;
    char c;
    cout << "\u001b[1;32m> ";
    cout << "\u001b[1;32m";
    cin >> c;

    if (c == '1')
    {

        string c = "";
        string code;
        h.calFrequency(txt);
        h.start = h.merge_sort(h.start);
        h.replace_stop();
        // h.replace_start();
         //h.show();

        h.make_tree2();
        // h.show2();
        cout << "\n\u001b[1;31mHUFFMAN CODES : \n";
        h.coding(h.root, c);
        code = h.encoder(txt);
        float bit = code.length();
        cout << "\n\n\u001b[1;31mCODED TEXT : ";
        cout << "\n\u001b[1;32m> ";
        cout << code << "\n";
        h.decoder(code);

        float or_len = txt.length() * 8;
        float txt_len = txt.length();
        float abr = bit / txt_len;
        cout << "\n\n";
        cout << "\u001b[1;35m______________________________________\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mHUFFMAN BITS OF CODE             : \u001b[1;34m" << bit << "\u001b[1;35m      " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mLENGTH OF TEXT                   : \u001b[1;34m" << txt_len << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mORIGINAL BITS OF CODE            : \u001b[1;34m" << or_len << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mABR                              : \u001b[1;34m" << abr << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mCOMPRESSION RATION               : \u001b[1;34m" << 8 / abr << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|______________________________________\n";

    }
    else if (c == '2')
    {
        string c = "";
        string code;
        h.calFrequency(txt);

        h.make_tree();
        cout << "\n\n\u001b[1;31mHUFFMAN CODES : \n";
        h.coding(h.root, c);
        code = h.encoder(txt);
        float bit = code.length();
        cout << "\n\n\u001b[1;31mCODED TEXT : ";
        cout << "\n\u001b[1;32m> ";
        cout << code;
        h.decoder(code);

        float or_len = txt.length() * 8;
        float txt_len = txt.length();
        float abr = bit / txt_len;
        cout << "\n\n";
        cout << "\u001b[1;35m______________________________________\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mHUFFMAN BITS OF CODE             : \u001b[1;34m" << bit << "\u001b[1;35m      " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mLENGTH OF TEXT                   : \u001b[1;34m" << txt_len << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mORIGINAL BITS OF CODE            : \u001b[1;34m" << or_len << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mABR                              : \u001b[1;34m" << abr << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|" << "\n|\u001b[1;31mCOMPRESSION RATION               : \u001b[1;34m" << 8 / abr << "\u001b[1;35m     " << "\n";
        cout << "\u001b[1;35m|______________________________________\n";

    }

    return 0;
}

