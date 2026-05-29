#include<iostream>
#include<string>
#include<vector>
using namespace std;
class dxs
{
public:
	dxs()
	{
		this->cs = -1;
		this->xs = -1;
	}
	dxs(int a, int b)
	{
		this->cs = a;
		this->xs = b;
	}
	int cs;  // degree
	int xs;  // coefficient
};

vector<dxs> d[2];  // d[0] = first polynomial, d[1] = second

// ========== Parse a single term and store it ==========
void t1(const string& a, int f, int num)
{
	if (a.find('x') == string::npos && a.find('X') == string::npos)
	{
		dxs t(0, stoi(a) * f);
		d[num].push_back(t);
		return;
	}
	else
	{
		int index = a.find('x');
		if (index == -1)
			index = a.find('X');

		string xst, cst;
		if (index == 0)
			xst = "1";
		else
			xst = a.substr(0, index);

		if (index == a.size() - 1)
			cst = "1";
		else
			cst = a.substr(index + 2);

		dxs t(stoi(cst), stoi(xst) * f);
		d[num].push_back(t);
		return;
	}
}

// ========== Parse a polynomial string ==========
void op(string& s, int num)
{
	int count = 0;
	int flag = 0;
	int l = s.size();
	string a;

	for (int i = 0; i < l; i++)
	{
		if (s[0] == '-' && i == 0)
			i = 1;
		flag = 1;

		for (int j = i; j <= l; j++)
		{
			if (s[j] == '+' || s[j] == '-' || s[j] == '\0')
			{
				count++;
				if (i > 0 && s[i - 1] == '-')
					flag = -1;

				for (int k = i; k < j; k++)
					a += s[k];

				t1(a, flag, num);
				a.clear();
				i = j;
				break;
			}
		}
	}
	cout << "共有 " << count << " 项" << endl;
}

// ========== Sort polynomial by degree (ascending) ==========
void sort_poly(vector<dxs>& poly)
{
	int n = poly.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (poly[j].cs > poly[j + 1].cs)
			{
				dxs temp = poly[j];
				poly[j] = poly[j + 1];
				poly[j + 1] = temp;
			}
		}
	}
}

// ========== Merge into big list, then combine like terms ==========
vector<dxs> add_poly()
{
	sort_poly(d[0]);
	sort_poly(d[1]);

	// Merge two sorted vectors into one big list
	vector<dxs> merged;
	int i = 0, j = 0;
	while (i < d[0].size() && j < d[1].size())
	{
		if (d[0][i].cs < d[1][j].cs)
			merged.push_back(d[0][i++]);
		else if (d[0][i].cs > d[1][j].cs)
			merged.push_back(d[1][j++]);
		else
		{
			merged.push_back(d[0][i++]);
			merged.push_back(d[1][j++]);
		}
	}
	while (i < d[0].size()) merged.push_back(d[0][i++]);
	while (j < d[1].size()) merged.push_back(d[1][j++]);

	// Combine like terms in the big list
	vector<dxs> result;
	for (int k = 0; k < merged.size(); k++)
	{
		if (!result.empty() && result.back().cs == merged[k].cs)
			result.back().xs += merged[k].xs;
		else
			result.push_back(merged[k]);
	}

	// Remove terms with zero coefficient
	vector<dxs> final_result;
	for (int k = 0; k < result.size(); k++)
	{
		if (result[k].xs != 0)
			final_result.push_back(result[k]);
	}

	return final_result;
}

// ========== Main ==========
int main()
{
	void op(string&, int);
	string s1, s2;
	int num = 0;
	char c;

	// ----- Input first polynomial -----
	cout << "输入第一个多项式:（形式如ax^n-bx^m+...）" << endl;
	for (int i = 0; i < 100; i++)
	{
		cin.get(c);
		if (c != '\n')
			s1 += c;
		else
			break;
	}
	/*cout << "You entered: " << s1 << endl;*/
	op(s1, num);

	// ----- Input second polynomial -----
	num++;
	cout << "输入第二个多项式:（形式如ax^n-bx^m+...）:" << endl;
	for (int i = 0; i < 100; i++)
	{
		cin.get(c);
		if (c != '\n')
			s2 += c;
		else
			break;
	}
	/*cout << "You entered: " << s2 << endl;*/
	op(s2, num);

	// ========== Add polynomials ==========
	cout << "\n===== Result =====" << endl;
	vector<dxs> result = add_poly();

	cout << "Sum: ";
	if (result.empty())
	{
		cout << "0" << endl;
	}
	else
	{
		for (int i = 0; i < result.size(); i++)
		{
			if (i > 0 && result[i].xs > 0)
				cout << "+";
			if (result[i].cs == 0)
				cout << result[i].xs;
			else if (result[i].xs == 1)
				cout << "x^" << result[i].cs;
			else if (result[i].xs == -1)
				cout << "-x^" << result[i].cs;
			else
				cout << result[i].xs << "x^" << result[i].cs;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
