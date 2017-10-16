#include <iostream>
#include <string>
#include <fstream>


using namespace std;

int main(int argc, char *argv[])
{
    /*
     * First argument: input phrase file = argv[1]
     * Second argument: output dictionary file = argv[2]
     * Third argument: output mode - append or rewrite 
     *                      (Default: rewrite)
     * 
    */ 
    if (!(argc==3||argc==4)) {
        cout<<"Argument Error\n";
        cout<<"Expect: ./program input_phrase_file output_dictionary_file\n";
        cout<<"Or\n";
        cout<<"Expect: ./program input_phrase_file output_dictionary_file output_mode\n";
        return -1;
    }
    string dictOneLine;
    ifstream myfile(argv[1]);
    ofstream assignedDict;
    
    if (argc==3)
        assignedDict.open(argv[2], ofstream::out);
    else if (string(argv[3])=="append")
        assignedDict.open(argv[2], ofstream::app | ofstream::out);
    else if (string(argv[3])=="rewrite")
        assignedDict.open(argv[2], ofstream::out);
    else {
        cout<<"Output mode Error\n";
        cout<<"Expect: rewrite or append\n";
        return -1;
    }

    int i=0;
    int found;
    while (getline(myfile, dictOneLine)) {
        if (dictOneLine.find(".gif")==-1 && dictOneLine.length()>=6 && dictOneLine.length()<=21 && dictOneLine!="字詞名") {
            //cout<<dictOneLine<<endl;
            //cout<<dictOneLine.length()<<endl;
            //cin.get();
            assignedDict<<dictOneLine<<endl;
            i++;
        }
    }
    myfile.close();
    assignedDict.close();
    cout<<"i= "<<i<<endl;

    return 0;
}