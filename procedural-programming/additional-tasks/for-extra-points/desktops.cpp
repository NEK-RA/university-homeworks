#include "desktops.h"
#include <filesystem>
#include <fstream>

void printAvailableDesktops(vector<string> installed){
  cout << endl << "Desktops which are available:" << endl;
  vector<string> available =  getAvailableNames(installed);
  for(string dename : available){
    cout << "> " << dename << endl;
  }
  cout << endl;
}

vector<string> getAvailableNames(vector<string> installed){
  vector<string> names = {};
  string line = "";
  for(DE desktop : AVAILABLE_DESKTOPS){
    line = desktop.name;
    if(searchVectorStr(installed, desktop.executable) != -1){
      line += " (installed, ready for switching)";
    }
    names.push_back(line);
  }
  return names;
}

string desktopNameById(int id){
  if(id >= 0 && id <= (AVAILABLE_DESKTOPS.size()-1)){
    return AVAILABLE_DESKTOPS[id].name;
  }else{
    return "UNKNOWN";
  }
}

int desktopIdByName(string name){
  int id = -1;
  for(int i = 0; i < AVAILABLE_DESKTOPS.size(); i++){
    if(AVAILABLE_DESKTOPS[i].name == name){
      id = i;
      break;
    }
  }
  return id;
}

int desktopIdByExecutable(string name){
  int id = -1;
  for(int i = 0; i < AVAILABLE_DESKTOPS.size(); i++){
    if(AVAILABLE_DESKTOPS[i].executable == name){
      id = i;
      break;
    }
  }
  return id;
}

vector<string> detectDesktops(){
	cout << endl << "Searching for installed supported desktops" << endl;
  vector<string> found = {};
  int counter = 0;
	filesystem::path dePath;
	for(DE desktop : AVAILABLE_DESKTOPS){
		dePath = desktop.executable;
		if(filesystem::exists(dePath)){
      found.push_back(desktop.executable);
		}
	}
  return found;
}

int processOtherTasks(vector<pair<actions,string>> tasks, State state){
  ExecResult whoami = exec("whoami",noProcessing);
  if(whoami.outerr != "root\n"){
    cout << endl << "ERROR: these tasks will perform package installation/removal, so it's expected that root priveleges granted. Execute them with sudo or from root user!" << endl;
    return 1;
  }else{
    bool validId;
    int deId = -1;
    int result = 0;
    cout << "Amount of tasks: " << tasks.size() << endl;
    for(pair<actions,string> task : tasks){
      cout << endl << "Task: " << taskName(task.first) << endl;
      if((task.first == addDesktop)||(task.first == removeDesktop)||(task.first == switchDesktop)){
        cout << "Target: " << task.second << endl;
      }

      validId = (desktopIdByName(task.second) != -1);
      
      switch(task.first){
        case installVnc:
          result = installVncServer(state.pmInstall);
          break;
        case addDesktop:
          if(validId){
            deId = desktopIdByName(task.second);
            result = installDE(state.pmInstall,deId);
          }else{
            cout << "Incorrect desktop environment specified!" << endl;
          }
          break;
        case removeDesktop:
          if(validId){
            deId = desktopIdByName(task.second);
            result = removeDE(state.pmDelete,deId);
          }else{
            cout << "Incorrect desktop environment specified!" << endl;
          }
          break;
        case switchDesktop:
          if(validId){
            deId = desktopIdByName(task.second);
            switchVncDesktop(deId);
          }else{
            cout << "Incorrect desktop environment specified!" << endl;
          }
          break;
        default:
          cout << "Something went wrong, these task shouldn't be there..." << endl;
          break;
      }
    }
    return result;
  }
}

int switchVncDesktop(int deId){
  filesystem::path folder = "/root/.vnc";
  if(!filesystem::exists(folder)){
    filesystem::create_directory(folder);
  }
  filesystem::copy("/root/.vnc/xstartup","/root/.vnc/xstartup.bkp",filesystem::copy_options::overwrite_existing);
  ofstream xstartup;
  xstartup.open("/root/.vnc/xstartup");
  if(xstartup.is_open()){
    xstartup << AVAILABLE_DESKTOPS[deId].xstartup <<endl;
    xstartup.close();
    filesystem::path file = "/root/.vnc/xstartup";
    filesystem::permissions(file, 
      filesystem::perms::owner_all | 
      filesystem::perms::group_read | 
      filesystem::perms::group_exec | 
      filesystem::perms::others_read | 
      filesystem::perms::others_exec 
    );
    cout << "Xstartup written for root user, permission are set." << endl;
  }else{
    cout << "Failed to write xstartup!" << endl;
    return 1;
  }
  return 0;
}

int installDE(string installCommand, int id){
  string packages = "";
  for(string package : AVAILABLE_DESKTOPS[id].packages){
    packages += package + " ";
  }
  ExecResult result = packageManagement(true, installCommand,"",packages,true);

  if(result.time < 1000){
    cout << "Finished in " << result.time << "ms" << endl;
  }else if(result.time < 60000){
    cout << "Finished in " << result.time/1000 << "sec" << endl;
  }else if(result.time < 3600000){
    cout << "Finished in " << result.time/60000 << "min" << endl;
  }
  
  if(result.exitCode == 0){
    cout << desktopNameById(id) << " (packages \"" + packages + "\") successfully installed" << endl;
  }else{
    cout << "Installation failed with exit code " << result.exitCode << endl;
    cout << "Execution output:\n" << result.outerr << endl;
    return 1;
  }

  return 0;
}

int removeDE(string removeCommand, int id){
  string packages = "";
  for(string package : AVAILABLE_DESKTOPS[id].packages){
    packages += package + " ";
  }
  ExecResult result = packageManagement(false, "", removeCommand, packages, true);

  if(result.time < 1000){
    cout << "Finished in " << result.time << "ms" << endl;
  }else if(result.time < 60000){
    cout << "Finished in " << result.time/1000 << "sec" << endl;
  }else if(result.time < 3600000){
    cout << "Finished in " << result.time/60000 << "min" << endl;
  }
  
  if(result.exitCode == 0){
    cout << desktopNameById(id) << " (packages \"" + packages + "\") successfully removed" << endl;
  }else{
    cout << "Installation failed with exit code " << result.exitCode << endl;
    cout << "Execution output:\n" << result.outerr << endl;
    return 1;
  }
  return 0;
}

int installVncServer(string installCommand){

  ExecResult result = packageManagement(true, installCommand, "", "tightvncserver",false);

  if(result.time < 1000){
    cout << "Finished in " << result.time << "ms" << endl;
  }else if(result.time < 60000){
    cout << "Finished in " << result.time/1000 << "sec" << endl;
  }else if(result.time < 3600000){
    cout << "Finished in " << result.time/60000 << "min" << endl;
  }
  
  if(result.exitCode == 0){
    cout << "TightVNC server (package \"tightvncserver\") successfully installed" << endl;

    cout << "Writing start/stop scripts..." << endl;

    string start = "/bin/vncstart";
    string stop = "/bin/vncstop";

    if(!filesystem::exists(start)){
      ofstream vncstart(start);
      if(vncstart.is_open()){
        vncstart << "export USER=root" << endl
          << "export HOME=/root" << endl
          << "vncserver -geometry 1024x768 -depth 24 -name remote-desktop :1" << endl;
        vncstart.close();
        filesystem::permissions(start, 
          filesystem::perms::owner_all | 
          filesystem::perms::group_read | 
          filesystem::perms::group_exec | 
          filesystem::perms::others_read | 
          filesystem::perms::others_exec 
        );
      }else{
        cout << "Failed to write start script!" << endl;
      }
    }

    if(!filesystem::exists(stop)){
      ofstream vncstop(stop);
      if(vncstop.is_open()){
        vncstop << "export USER=root" << endl
          << "export HOME=/root" << endl
          << "vncserver -kill :1" << endl
          << "rm -rf /tmp/.X1-lock" << endl
          << "rm -rf /tmp/.X11-unix/X1" << endl;
        vncstop.close();
        filesystem::permissions(stop, 
          filesystem::perms::owner_all | 
          filesystem::perms::group_read | 
          filesystem::perms::group_exec | 
          filesystem::perms::others_read | 
          filesystem::perms::others_exec 
        );
      }else{
        cout << "Failed to write stop script!" << endl;
      }
    }

    cout << "Scritps written, now you can use:" << endl
      << "sudo vncstart \t-\t to start vnc server" << endl
      << "sudo vncstop \t-\t to stop vnc server" << endl;

  }else{
    cout << "Installation failed with exit code " << result.exitCode << endl;
    cout << "Execution output:\n" << result.outerr << endl;
    return 1;
  }
  return 0;
}
