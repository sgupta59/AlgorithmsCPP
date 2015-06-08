const int maxBuf = 100;
const int maxSymbols = 40;
#include <iostream>
#include "Parse.h"
#include "Scan.h"
#include "Store.h"
#include "Symtab.h"
#include "Tree.h";
using namespace std;
int main ()
{
    // Notice all these local objects.
    // A clear sign that there should be
    // a top level object, say, the Calculator.
    // Back to the drawing board!

    char buf [maxBuf];
    Status status;
    SymbolTable symTab (maxSymbols);
    FunctionTable funTab (symTab, funArr);
    Store store (maxSymbols, symTab);

    do
    {
        cout << "> ";  // prompt
        cin.getline (buf, maxBuf);
        Scanner scanner (buf);
        Parser  parser (scanner, store, funTab, symTab);
        status = parser.Eval ();
    } while (status != stQuit);
}