#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

char keywords[32][15] = {
"auto","break","case","char","const","continue","default","do","double",
"else","enum","extern","float","for","goto","if","int","long","register",
"return","short","signed","sizeof","static","struct","switch","typedef",
"union","unsigned","void","volatile","while"
};

char operators[] = "+-*/%=!<>|&";
char punctuations[] = "();{},[]";

char symbolTable[100][30];
int symCount = 0;

int isKeyword(char word[]) {
    for(int i=0;i<32;i++)
        if(strcmp(word,keywords[i])==0) return 1;
    return 0;
}

int isOperator(char c) {
    for(int i=0;i<strlen(operators);i++)
        if(c==operators[i]) return 1;
    return 0;
}

int isPunctuation(char c) {
    for(int i=0;i<strlen(punctuations);i++)
        if(c==punctuations[i]) return 1;
    return 0;
}

int isIdentifier(char word[]) {
    if(!(isalpha(word[0]) || word[0]=='_')) return 0;
    for(int i=1;i<strlen(word);i++)
        if(!(isalnum(word[i]) || word[i]=='_')) return 0;
    return 1;
}

int isNumber(char word[]) {
    for(int i=0;i<strlen(word);i++)
        if(!isdigit(word[i])) return 0;
    return 1;
}

int inSymbolTable(char word[]) {
    for(int i=0;i<symCount;i++)
        if(strcmp(symbolTable[i],word)==0) return 1;
    return 0;
}

void addSymbol(char word[]) {
    if(!inSymbolTable(word))
        strcpy(symbolTable[symCount++],word);
}

int main() {
    ifstream file("input.c");
    if(!file) {
        cout<<"File not found\n";
        return 0;
    }

    char ch, word[50];
    int i=0, lineNo=1;
    int inComment=0;

    cout<<"TOKENS\n";

    while(file.get(ch)) {

        if(ch=='\n') lineNo++;

        // Handle comments
        if(!inComment && ch=='/') {
            char next = file.peek();
            if(next=='/') {
                while(file.get(ch) && ch!='\n');
                lineNo++;
                continue;
            }
            else if(next=='*') {
                file.get(ch);
                inComment=1;
                continue;
            }
        }

        if(inComment) {
            if(ch=='*' && file.peek()=='/') {
                file.get(ch);
                inComment=0;
            }
            continue;
        }

        if(isalpha(ch) || ch=='_') {
            word[i++]=ch;
            while(file.peek()!=EOF && (isalnum(file.peek()) || file.peek()=='_'))
                file.get(word[i++]);
            word[i]='\0';
            i=0;

            if(isKeyword(word))
                cout<<"Keyword: "<<word<<endl;
            else if(isIdentifier(word)) {
                cout<<"Identifier: "<<word<<endl;
                addSymbol(word);
            }
            else
                cout<<"LEXICAL ERROR Line "<<lineNo<<" : "<<word<<endl;
        }

        else if(isdigit(ch)) {
            word[i++]=ch;
            while(file.peek()!=EOF && isalnum(file.peek()))
                file.get(word[i++]);
            word[i]='\0';
            i=0;

            if(isNumber(word))
                cout<<"Constant: "<<word<<endl;
            else
                cout<<"LEXICAL ERROR Line "<<lineNo<<" : "<<word<<" invalid lexeme\n";
        }

        else if(ch=='\'') {
            word[0]='\'';
            i=1;
            while(file.get(ch) && ch!='\'')
                word[i++]=ch;
            word[i++]='\'';
            word[i]='\0';
            i=0;
            cout<<"Constant: "<<word<<endl;
        }

        else if(ch=='"') {
            word[0]='"';
            i=1;
            while(file.get(ch) && ch!='"')
                word[i++]=ch;
            word[i++]='"';
            word[i]='\0';
            i=0;
            cout<<"Constant: "<<word<<endl;
        }

        else if(isOperator(ch))
            cout<<"Operator: "<<ch<<endl;

        else if(isPunctuation(ch))
            cout<<"Punctuation: "<<ch<<endl;

        else if(!isspace(ch))
            cout<<"LEXICAL ERROR Line "<<lineNo<<" : "<<ch<<endl;
    }

    cout<<"\nSYMBOL TABLE\n";
    for(int j=0;j<symCount;j++)
        cout<<j+1<<" -> "<<symbolTable[j]<<endl;

    return 0;
}
