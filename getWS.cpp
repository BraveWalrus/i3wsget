#include <string>
#include <iostream>
#include <sstream>
using namespace std;


string GetStdoutFromCommand(string cmd);


int main() {
    string cmd = "i3-msg -t get_workspaces";
    string rawOut = GetStdoutFromCommand(cmd);
    bool isReal[5] = {0}, isVisable[5] = {0};

    for(int i=0; i<rawOut.length()-6; i++){
      char window[3];
      for(int j=0; j<3; j++){
        window[j] = rawOut[i+j];
      }
      string windowStr(window);
      if(windowStr=="num"){
        int windInd = rawOut[i+5] - '0';
        isReal[windInd] = 1;
        if(rawOut[i+28]=='t'){
          isVisable[windInd] = 1;
        }
      }
    }
    for(int i=0;i<5;i++){
      cout<<isReal[i]<<" ";
    }
    cout<<endl;

    for(int i=0;i<5;i++){
      cout<<isVisable[i]<<" ";
    }
    cout<<endl;
    return 0;
}


string GetStdoutFromCommand(string cmd) {

  string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");

  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}
