#include "Unit2.h"

int Grammar::IsRegular(){
 if (N.empty() || P.empty())
        return 0;
        for(rulemap::iterator i = P.begin(); i != P.end();i++){
                if (!N.count(i->first))
                        return 0;
                switch(i->second.length()){
                        case 1:{
                                if (!T.count(i->second[0]))
                                return 0;
                                break;
                        }
                        case 2:{
                                if (!T.count(i->second[0]) || !N.count(i->second[1]))
                                        return 0;
                                break;
                        }
                        default:
                                return 0;
                        }
                }
        return 1;
}


void Grammar::InGrammar(char *fname){
 long n, i;
 rule r;
 char c;
ifstream fi(fname);
 N.clear();
 T.clear();
 P.clear();

 fi >> n;
 for (i = 0; i < n; i++){
        fi >> c;
        N.insert(c);
 }

 fi >> n;
 for (i = 0; i < n; i++){
        fi >> c;
        T.insert(c);
 }

 fi >> n;
 for (i = 0; i < n; i++){
        fi >> r.first >> r.second;
        P.insert(r);
 }

 fi >> S;
}

string Grammar::AsString(){
 string res = "";
 charset::iterator i;
 res += "Nonterminals (";
 res += IntToStr(N.size()).c_str();
 res += ") : ";
 for (i = N.begin(); i != N.end(); i++){
        res += *i;
        res += " ";
 }
 res += "\nTerminals (";
 res += IntToStr(T.size()).c_str();
 res += ") : ";
 for (i = T.begin(); i != T.end(); i++){
        res += *i;
        res += " ";
 }
 res += "\nRules (";
 res += IntToStr(P.size()).c_str();
 res += ")\n";
 for (rulemap::iterator j = P.begin(); j != P.end();j++){
        res += "\t";
        res += j->first;
        res += " -> " + j->second + "\n";
 }
 res += "Starting symbol: ";
 res += S;
 res += "\n";
 return res;
}
void Grammar::OutGrammar(char *fname){ ofstream fo(fname);
 charset::iterator i;
 fo << N.size() << "\n";
 for (i = N.begin(); i != N.end(); i++)
        fo << *i;
        fo << "\n" << T.size() << "\n";
 for (i = T.begin(); i != T.end(); i++)
        fo << *i;
        fo << "\n" << P.size() << "\n";
 for (rulemap::iterator j = P.begin(); j != P.end();j++)
        fo << j->first << " " << j->second << "\n";
        fo << "\n" << S;
}
void FAutomat::SetGrammar(Grammar *NG){ G = NG;
}
void FAutomat::CreateAutomat(){ rulemap::iterator i, j;
 rule r;
 char c, t;
 int k;

 for(c = 'A'; G->N.count(c); c++);

 for(i = G->P.begin(); i != G->P.end(); i++)
        if (i->second.length() == 1 && G->T.count(i->second[0])){
                for(j = G->P.lower_bound(i->first), k = G->P.count(i->first); k; j++, k--)
                        if (j->second.length() == 2 && j->second[0] == i->second[0] && G->N.count(j->second[1]))
                                break;
                        if (!k){
                                r.first = i->first;
                                r.second = i->second + c;
                                G->P.insert(r);
                                G->N.insert(c);
                        }
        }

 H = G->S;

 Q = G->N;
 }

 