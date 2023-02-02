#include <fstream.h>
#include <math.h>
#include <sysutils.hpp>
#include <graphics.hpp>
#include <grids.hpp>
#include <map>
#include <set>
#include <string>
#include <list>
#include <vector>
using std::string;
using std::map;
using std::multimap;
using std::set;
using std::pair;

struct rulecmp{
        bool operator()(const char c1, const char c2){
                return (c1 < c2);
        }
};

typedef string rule_r;
typedef char rule_l;
typedef pair<rule_l, rule_r> rule;
typedef multimap<rule_l, rule_r, rulecmp> rulemap;
typedef set<char> charset;

class Grammar{
        public:
                charset N;
                charset T;
                rulemap P;
                char S;
 int IsRegular();
 void InGrammar(char *fname);
 string AsString();
 void OutGrammar(char *fname);
};

typedef map<char, map<char, charset> > ftable;

class FAutomat{
 public:
        Grammar *G;
        charset Q;
        charset T;
        ftable F;
        char H;
        charset Z;
        int MustPaint;
        FAutomat(){
                MustPaint = 0;
        }
        void SetGrammar(Grammar *NG);
        void CreateAutomat();
        void PaintAutomat(TCanvas * Canvas, long w, long h);
        void OutToTable(TStringGrid * Grid);
        void CreateDeterm();
};
