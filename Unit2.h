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

// comparator for working in mappings
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

// grammar class
class Grammar{
        public:
                charset N; // set of nonterminals
                charset T; // set of terminals
                rulemap P; // lots of rules
                char S; // initial character
 int IsRegular(); //grammar check function for regularity
 void InGrammar(char *fname); //grammar input function from a file
 string AsString(); //function grammar output to a string
 void OutGrammar(char *fname); // output function grammars to file
};

typedef map<char, map<char, charset> > ftable;

// finite state machine class
class FAutomat{
 public:
        Grammar *G; // related grammar
        charset Q; // multiple states
        charset T; // multiple input characters
        ftable F; // rules table
        char H; // initial state
        charset Z; // set of finite states
        int MustPaint; // graph rendering flag
        FAutomat(){
                MustPaint = 0;
        }
        void SetGrammar(Grammar *NG); // function linking with grammar
        void CreateAutomat(); // function creating an automaton from grammar
        void PaintAutomat(TCanvas * Canvas, long w, long h); // graph rendering function
        void OutToTable(TStringGrid * Grid); //the function for displaying the rule table in StringGrid
        void CreateDeterm(); // DKA conversion function
};
