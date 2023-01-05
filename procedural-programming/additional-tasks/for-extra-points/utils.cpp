#include "utils.h"

string taskName(actions act){
  switch(act){
    case showHelp:
      return "Show Help";
    case showVersion:
      return "Show version";
    case listDesktops:
      return "List available desktops";
    case installVnc:
      return "Install vnc server";
    case addDesktop:
      return "Add desktop";
    case removeDesktop:
      return "Remove desktop";
    case switchDesktop:
      return "Switch to another desktop";
  }
  return "";
}

int searchVectorStr(vector<string> data, string query){
  for(int i=0; i<data.size(); i++){
    if(data[i]==query){
      return i;
    }
  }
  return -1;
}

void noProcessing(string line){}

void printLine(string line){
  cout << line << endl;
}

//https://manpages.org/popen
ExecResult exec(string command, void processLine(string)){
  char buffer[8192];
  string output = "";
  ExecResult result;
  string fullcmd ="sh -c \"" + command + " 2>&1\"";
  chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
  // Open pipe to file
  FILE* pipe = popen(fullcmd.c_str(), "r");
  if (!pipe) {
    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    result.exitCode = 1;
    result.outerr = "popen failed!";
    result.time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    return result;
  }

  // read till end of process:
  while (!feof(pipe)) {

    // use buffer to read and add to result
    if (fgets(buffer, 8192, pipe) != NULL){
      processLine(buffer);
      output += buffer;
    }
   }
  int exitcode = pclose(pipe);
  chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
  result.exitCode = exitcode;
  result.outerr = output;
  result.time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  return result;
}

string strReplace(string original, string placeholder, string content){
  int holderStart = original.find(pkgPlaceholder);
  if(holderStart != -1){
    string result = "";
    int holderEnd = holderStart+placeholder.size();
    result = original.substr(0,holderStart);
    result += content;
    result += original.substr(holderEnd);
    return result;
  }else{
    return original;
  }
}

ExecResult packageManagement(bool install, string installCommand, string removeCommand, string packages, bool detailed){
  string finalCommand = "";
  if(install){
    finalCommand = strReplace(installCommand,pkgPlaceholder,packages);
  }else{
    finalCommand = strReplace(removeCommand,pkgPlaceholder,packages);
  }
  cout << "Executing: " << finalCommand << endl;
  ExecResult result;
  if(detailed){
    result = exec(finalCommand,printLine);
  }else{
    result = exec(finalCommand,noProcessing);
  }
  return result;
}