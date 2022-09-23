#include <bits/stdc++.h>
#include <algorithm>
using std::cin;
using std::cout;
using std::distance;
using std::endl;
using std::find;
using std::make_pair;
using std::pair;
using std::toupper;
using std::vector;

bool Comp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second;
}

class Poly
{
public:
    static const int max_Degree = 10;
    vector<int> coeff;
    vector<int> degree;
    vector<pair<int, int>> pairs;
    Poly(vector<int> coeff_enter, vector<int> degree_enter)
    {
        coeff = coeff_enter;
        degree = degree_enter;
        for (int i = 0; i < degree.size(); i++)
        {
            pairs.push_back(make_pair(coeff[i], degree[i]));
        }
        sort(pairs.begin(), pairs.end(), Comp);
        coeff.clear();
        degree.clear();
        std::transform(pairs.begin(),
                       pairs.end(),
                       std::back_inserter(coeff), // write to the same location
                       [](const std::pair<double, int> &p)
                       { return p.first; });
        std::transform(pairs.begin(),
                       pairs.end(),
                       std::back_inserter(degree), // write to the same location
                       [](const std::pair<double, int> &p)
                       { return p.second; });
        Format();
    }

    void Show()
    {

        printf("Poly is:\n");
        printf("%dx^%d", coeff[degree.size() - 1], degree[degree.size() - 1]);
        for (int i = degree.size() - 2; i >= 0; i--)
        {
            if (coeff[i] > 0)
            {
                if (degree[i] > 0)
                {
                    printf(" + %dx^%d", coeff[i], degree[i]);
                }
                else
                {
                    printf(" + %d", coeff[i]);
                }
            }
            else if (coeff[i] < 0)
            {
                if (degree[i] > 0)
                {
                    printf(" - %dx^%d", abs(coeff[i]), degree[i]);
                }
                else
                {
                    printf(" - %d", abs(coeff[i]));
                }
            }
        }
    }
    void Add(vector<int> new_coeff, vector<int> new_degree)
    {
        for (int i = 0; i < new_degree.size(); i++)
        {
            auto iter = find(degree.begin(), degree.end(), new_degree[i]);
            if (iter != degree.end())
            {
                int pos = distance(degree.begin(), iter);
                coeff[pos] += new_coeff[i];
            }
            else
            {
                Insert(new_degree[i], new_coeff[i]);
            }
        }
    }
    void Insert(int new_degree, int new_coeff)
    {
        degree.push_back(new_degree);
        sort(degree.begin(), degree.end());
        auto iter = find(degree.begin(), degree.end(), new_degree);
        int dis = distance(degree.begin(), iter);
        coeff.insert(coeff.begin() + dis, new_coeff);
    }
    void Remove(vector<int> del_degree)
    {
        for (int i = 0; i < del_degree.size(); i++)
        {
            auto iter = find(degree.begin(), degree.end(), del_degree[i]);
            if (iter != degree.end())
            {
                int dis = distance(degree.begin(), iter);
                degree.erase(iter);
                coeff.erase(coeff.begin() + dis);
            }
        }
    }
    void Calculate(float x)
    {
        float sum = 0;
        printf("The value of\n");
        printf("%d . %.2f^%d", coeff[degree.size() - 1], x, degree[degree.size() - 1]);
        for (int i = degree.size() - 2; i >= 0; i--)
        {
            sum += coeff[i] * pow(x, degree[i]);
            for (int i = degree.size() - 2; i >= 0; i--)
            {
                if (coeff[i] > 0)
                {
                    if (degree[i] > 0)
                    {
                        printf(" + %d . %.2f^%d", coeff[i], x, degree[i]);
                    }
                    else
                    {
                        printf(" + %d", coeff[i]);
                    }
                }
                else if (coeff[i] < 0)
                {
                    if (degree[i] > 0)
                    {
                        printf(" - %d . %.2f^%d", abs(coeff[i]), x, degree[i]);
                    }
                    else
                    {
                        printf(" - %d", abs(coeff[i]));
                    }
                }
            }
        }
        sum += coeff[0] * pow(x, degree[0]);
        printf(" is: %.2f", sum);
    }
    void Format()
    {
        for (int i = 0; i < degree.size() - 1; i++)
        {
            while ((degree[i] == degree[i + 1]) && (i < degree.size() - 1))
            {
                coeff[i] += coeff[i + 1];
                degree.erase(degree.begin() + i + 1);
                coeff.erase(coeff.begin() + i + 1);
            }
        }
    }
};

int main()
{
    int max_terms;
    cout << "Enter the number of terms in polynomial: ";
    cin >> max_terms;
    vector<int> x_arr;
    vector<int> y_arr;
    for (int i = 0; i < max_terms; i++)
    {
        int x;
        printf("Enter the coefficient of the %d term: ", i + 1);
        cin >> x;
        x_arr.push_back(x);
        int y;
        printf("Enter the degree of the %d term: ", i + 1);
        cin >> y;
        y_arr.push_back(y);
    }
    Poly Equation(x_arr, y_arr);
    int repeat = 1;
    while (repeat)
    {
        char c;
        cout << "What do you want to do Show(S/s), Add(A/a), Remove(R/r), Calculate(C/c), Exit(E/e): ";
        cin >> c;
        c = toupper(c);
        switch (c)
        {
        case 'S':
            Equation.Show();
            cout << endl;
            break;
        case 'A':
        {
            cout << "How many term do you want to add: ";
            int num;
            cin >> num;
            vector<int> add_coeff;
            vector<int> add_degree;
            for (int i = 0; i < num; i++)
            {
                int x;
                printf("Enter the coefficient of the %d term to remove: ", i + 1);
                cin >> x;
                add_coeff.push_back(x);
                int y;
                printf("Enter the degree of the %d term: ", i + 1);
                cin >> y;
                add_degree.push_back(y);
            }
            Equation.Add(add_coeff, add_degree);
            cout << endl;
            break;
        }
        case 'R':
        {
            cout << "How many term do you want to add: ";
            int num;
            cin >> num;
            vector<int> rm_coeff;
            vector<int> rm_degree;
            for (int i = 0; i < num; i++)
            {
                int x;
                printf("Enter the coefficient of the %d term to remove: ", i + 1);
                cin >> x;
                rm_coeff.push_back(x);
                int y;
                printf("Enter the degree of the %d term: ", i + 1);
                cin >> y;
                rm_degree.push_back(y);
            }
            Equation.Add(rm_coeff, rm_degree);
            cout << endl;
            break;
        }
        case 'C':
        {
            cout << "Enter the value of x to evaluate: ";
            float x;
            cin >> x;
            Equation.Calculate(x);
            cout << endl;
            break;
        }
        case 'E':
        {
            repeat = 0;
            break;
        }
        default:
            cout << "Value is not accepted, please try again.";
            cout << endl;
            break;
        }
    }
}