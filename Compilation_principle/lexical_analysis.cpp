#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include <iomanip>
#include <sstream>
using namespace std;
class LexicalAnalyzer
{
public:
	LexicalAnalyzer();
	~LexicalAnalyzer();
	void GetFileName(ifstream& filename);
	void InputFile(ifstream& filename);
	void AnalyzeToken(vector <char>);
	void print();
	bool IsSymbol(char);
	bool IsWei(string);
	bool IsInclude(string);
	bool IsLessSign(char);
	bool IsLargeSign(char);
	bool IsMain(string);
	bool IsInt(string);
	bool IsFloat(string);
	bool IsChar(string);
	bool IsLeftBrace(string);
	bool IsRightBrace(string);
	bool IsSemicolon(string);
	bool IsPrintf(string);
	bool IsLeftBrackets(string);
	bool IsRightBrackets(string);
	bool IsOperator(char);
	bool IsComma(string);
	bool IsAddOperator(string);
	bool IsReduceOperator(string th);
	bool IsWhiteSpace(char);
	bool IsString(char);
	bool IsNotes(char ch);
	bool IsID(string th);
	bool IsReturn(string th);
	bool IsSolution(string th);
private:
	vector<char> token;
	vector<string> lexical_vector;
	vector<string> finish_token;
};

LexicalAnalyzer::LexicalAnalyzer()
{
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}

int main()
{
	LexicalAnalyzer lexicalanalyzer;
	ifstream myfile;
	lexicalanalyzer.GetFileName(myfile);
	lexicalanalyzer.InputFile(myfile);
	lexicalanalyzer.print();
	cin.get();
	return 0;
}
void LexicalAnalyzer::GetFileName(ifstream& filename)
{
	string file;
	file = "test.cpp";
	filename.open(file);
	if (!filename)
	{
		cout << "文件名有误，请检查目录下是否有名为test.cpp的文件!";
	}
}

void LexicalAnalyzer::InputFile(ifstream& filename)
{
	string currentToken;
	string readLine;
	char lookahead;
	string myNumber = "";
	string myString = "";
	int temp;
	while (getline(filename,readLine))
	{
		for (size_t i = 0; i < readLine.length(); i++)
		{
			temp = i;
			lookahead = readLine[i];
			token.push_back(readLine[i]);
			if (IsWhiteSpace(lookahead))
			{
				token.pop_back();
				vector<char> temp = token;
				AnalyzeToken(temp);
				token.clear();
			}
			//else if(IsNotes(lookahead))
			//{
			//	token.pop_back();
			//	token.clear;
			//	break;
			//}
			else if(IsSymbol(lookahead))
			{
				token.pop_back();
				AnalyzeToken(token);
				token.clear();
				token.push_back(lookahead);
				AnalyzeToken(token);
				token.clear();
			}
			else if (isdigit(lookahead)&&!isalpha(lookahead))
			{
				while (isdigit(readLine[i+1]))
				{
					token.push_back(readLine[i + 1]);
					i++;
				}
				for (size_t i = 0; i < token.size(); i++)
				{
					myNumber += token[i];
				}
				vector<string>::iterator it = find(lexical_vector.begin(), lexical_vector.end(), myNumber);
				if (it != lexical_vector.end())
				{
					lexical_vector.push_back(myNumber);
					finish_token.push_back(myNumber);
				}
				cout << "<number," << myNumber <<">"<< endl;
				myNumber = "";
				token.clear();
			}
			else if(IsString(lookahead))
			{
				token.pop_back();
				while (readLine[i+1]!='"')
				{
					token.push_back(readLine[i + 1]);
					i++;
				}
				for (size_t i = 0; i < token.size(); i++)
				{
					myString += token[i];
				}
				i++;
				cout << "<string," << myString << ">" << endl;
				myString = "";
				token.clear();
			}
			else if (IsOperator(lookahead))
			{
				token.pop_back();
				if (IsOperator(readLine[i+1]))
				{
					token.push_back(lookahead);
					token.push_back(readLine[i + 1]);
					i += 2;
					AnalyzeToken(token);
					token.clear();
				}
				else if (IsOperator(lookahead))
				{
					///*token.pop_back();*/
					//if (lookahead == '<' || '>')
					//{
					//	token.push_back(lookahead);
					//	AnalyzeToken(token);
					//	i++;
					//	token.clear();
					//}
					//else
					//{
						AnalyzeToken(token);
						cout << "<operator," << lookahead << ">" << endl;
						token.clear();
					//}
				}
			}
		}
	}
}

void LexicalAnalyzer::AnalyzeToken(vector<char> token)
{
	string currenttoken;
	int FLAG = 1;
	for (size_t i = 0; i < token.size(); i++)
	{
		if (token[i] != '/t')
		{
			currenttoken += token[i];
		}
	}
	vector<string>::iterator it = find(lexical_vector.begin(), lexical_vector.end(), currenttoken);
	if (it != lexical_vector.end())
	{

	}
	else
	{
		lexical_vector.push_back(currenttoken);
		FLAG = 0;
	}
	if (IsMain(currenttoken))
	{
		cout << "<keywords:main," << currenttoken << ">" << endl;
		if (FLAG==0)
		{
			finish_token.push_back("keyword");
		}
	}
	else if (IsInt(currenttoken))
	{
		cout << "<keywords:int," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("keyword");
		}
	}
	else if (IsPrintf(currenttoken))
	{
		cout << "<keywords:printf," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("keyword");
		}
	}
	else if(IsChar(currenttoken))
	{
		cout << "<keywords:char," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("keyword");
		}
	}
	else if(IsSemicolon(currenttoken))
	{
		cout << "<semicolon," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("semicolon");
		}
	}
	else if(IsLeftBrackets(currenttoken))
	{
		cout << "<leftbrackets," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("leftbrackets");
		}
	}
	else if (IsRightBrackets(currenttoken))
	{
		cout << "<rightbrackets," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("rightbrackets");
		}
	}
	else if (IsLeftBrace(currenttoken))
	{
		cout << "<leftbrace," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("leftbrace");
		}
	}
	else if (IsRightBrace(currenttoken))
	{
		cout << "<rightbrace," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("rightbrace");
		}
	}
	else if(IsComma(currenttoken))
	{
		cout << "<comma," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("comma");
		}
	}
	else if(IsAddOperator(currenttoken))
	{
		cout << "<operator:+," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("addoperator");
		}
	}
	else if (IsReduceOperator(currenttoken))
	{
		cout << "<operator:-," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("reduceoperator");
		}
	}
	else if (IsFloat(currenttoken))
	{
		cout << "<keywords:float," << currenttoken << ">" << endl;
		if (FLAG==0)
		{
			finish_token.push_back("keyword");
		}
	}
	else if(IsID(currenttoken))
	{
		cout << "<words," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back(currenttoken);
		}
	}
	else if (IsWei(currenttoken))
	{
		cout << "<wei," << currenttoken << ">" << endl;
		if (FLAG == 0)
		{
			finish_token.push_back("specialsign");
		}
	}
	else if (IsReturn(currenttoken))
	{
	cout << "<kewords:return," << currenttoken << ">" << endl;
	if (FLAG == 0)
	{
		finish_token.push_back("keyword");
	}
	}
	else if (IsSolution(currenttoken))
	{
		cout << "<words," << currenttoken << ">" << endl;
		if (FLAG==0)
		{
			finish_token.push_back(currenttoken);
		}
	}
}

void LexicalAnalyzer::print()
{
	int count = 0;
	cout << "符号表" << endl;
	vector<string>::iterator tmp = lexical_vector.begin();
	vector<string>::iterator tmp2 = finish_token.begin();
	tmp += 1;
	for (;tmp != lexical_vector.end(); tmp++,tmp2++)
	{
		count++;
		cout << setw(3) << count << " " << setw(10) << *tmp  << setw(15)<<*tmp2<<endl;
	}
}

bool LexicalAnalyzer::IsSymbol(char ch)
{
	if (ch == '#' || ch == '(' || ch == ')' || ch == ',' || ch == '{' || ch == '}' || ch == '+' ||
		ch == '-' || ch == '*' || ch == '/' || ch == '&' || ch == '!' || ch == '|' || ch == ';')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsWei(string th)
{	
	if (th == "#")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsInclude(string currentToken)
{
	if (currentToken =="include")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsLessSign(char ch)
{
	if (ch =='<')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsLargeSign(char ch)
{
	if (ch == '>')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsMain(string currentToken)
{
	if (currentToken == "main")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsInt(string currentToken)
{
	if (currentToken =="int"||currentToken =="\tint")
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool LexicalAnalyzer::IsFloat(string currentToken)
{
	if (currentToken == "float"||currentToken=="\tfloat")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsChar(string currentToken)
{
	if (currentToken == "char")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsLeftBrace(string th)
{
	if (th == "{")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsRightBrace(string th)
{
	if (th == "}")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsSemicolon(string st)
{
	if (st == ";")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsPrintf(string currentToken)
{
	if (currentToken == "printf")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsLeftBrackets(string th)
{
	if (th == "(")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsRightBrackets(string th)
{
	if (th == ")")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsOperator(char ch)
{
	if (ch == '=' || ch == '<' || ch == '>')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsComma(string th)
{
	if (th==",")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsAddOperator(string th)
{
	if (th=="+")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsReduceOperator(string th)
{
	if (th == "-")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsWhiteSpace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsString(char ch)
{
	if (ch == '"') {
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsNotes(char ch)
{
	if (ch=='/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsID(string th)
{
	if (isalpha(th[0]) && th != "if" && th != "function" &&th != "else" && th != "return" && th!= "var" &&th != "while") 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool LexicalAnalyzer::IsReturn(string th)
{
	if (th == "return")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LexicalAnalyzer::IsSolution(string th)
{
	if (th == "'a'")
	{
		return true;
	}
	else
	{
		return false;
	}
}
