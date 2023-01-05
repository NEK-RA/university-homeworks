#include "arguments.h"

void printVectorStr(vector<string> args, string msg){
  cout << endl << msg << endl;
  for(string arg : args){
    cout << arg << endl;
  }
}

int findArgument(vector<string> args, string target);

vector<pair<actions,string>> parseArguments(int argc, char **argv){
  if(argc == 1){
    return {{showHelp,""}};
  }else{
    vector<string> args = {};
    vector<pair<actions,string>> tasks = {};
    for(int i=1; i < argc; i++){
      args.push_back(argv[i]);
    }
    printVectorStr(args,"Arguments: ");

    if(findArgument(args,"--help")!=-1){
      return {{showHelp,""}};
    }

    if(findArgument(args,"--version")!=-1){
      return {{showVersion,""}};
    }
    if(findArgument(args,"--list")!=-1){
      return {{listDesktops,""}};
    }

    if(findArgument(args,"--vnc")!=-1){
      tasks.push_back({installVnc,""});
    }

    int addDE = findArgument(args,"--add");
    int removeDE = findArgument(args,"--remove");
    int switchDE = findArgument(args,"--switch");
    string id = "";

    if(addDE != -1){
      if(addDE+1 >= 0 && addDE+1 <= args.size()){
        id = args[addDE+1];
      }
      tasks.push_back({addDesktop,id});
    }else if(removeDE!=-1){
      if(removeDE+1 >= 0 && removeDE+1 <= args.size()){
        id = args[removeDE+1];
      }
      tasks.push_back({removeDesktop,id});
    }else if(switchDE!=-1){
      if(switchDE+1 >= 0 && switchDE+1 <= args.size()){
        id = args[switchDE+1];
      }
      tasks.push_back({switchDesktop,id});
    }
    return tasks;
  }
}

int findArgument(vector<string> args, string target){
  int result = -1;
  for(int i=0;i<args.size();i++){
    if(args[i] == target){
      result = i;
      break;
    }
  }
  return result;
}
