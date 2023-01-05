#include <iostream>
#include <filesystem>
#include <vector>
#include "utils.h"
#include "arguments.h"
#include "desktops.h"
using namespace std;

packman getManager(string spath);
void detectPackageManager(State &state);
string installationCommand(string spath);
string deletionCommand(string spath);

int main(int argc, char **argv){
	cout << "WARNING: ALPHA-VERSION >>> INTENDED TO BE USED UNDER ROOT USER ONLY OR WITH SUDO" << endl;
	State state;
	detectPackageManager(state);
	state.installed = detectDesktops();
  vector<pair<actions,string>> tasks = parseArguments(argc,argv);
  // cout << "Received " << tasks.size() << " arguments" << endl;
	switch(tasks[0].first){
		case showHelp:
			cout << HELP << endl;
			break;
		case showVersion:
			cout << VERSION << endl;
			break;
		case listDesktops:
			printAvailableDesktops(state.installed);
			break;
		default:
      processOtherTasks(tasks,state);
			break;
	}
}

packman getManager(string spath){
	if(spath == "/bin/apt"){
		return apt;
	}else if(spath == "/sbin/apk"){
		return apk;
	}else{
		return unknownPackageManager;
	}
}

void detectPackageManager(State &curstate){
	string managers[] = {
		"/sbin/apk",
		"/bin/apt"
	};
	cout << endl << "Searching for package managers..." << endl;
	filesystem::path pmPath;
	for(string spath : managers){
		pmPath = spath;
		cout << "Cheking " << spath << " ... ";
		if(filesystem::exists(pmPath)){
			cout << "Detected!" << endl;
			curstate.pmInstall = installationCommand(spath);
			curstate.pmDelete = deletionCommand(spath);
			break;
		}else{
			cout << "Not found" << endl;
		}
	}
}

string installationCommand(string spath){
	packman pm = getManager(spath);
	string command = spath + " ";
	switch(pm){
		case apt:
			command += "install --no-install-recommends PACKAGES_HERE -y";
			break;
		case apk:
			command += "add --no-cache PACKAGES_HERE";
			break;
		default:
			command = "";
			break;
	}
	return command;
}

string deletionCommand(string spath){
	packman pm = getManager(spath);
	string command = spath + " ";
	switch(pm){
		case apt:
			command += "purge PACKAGES_HERE -y && "+spath+ " autoremove -y";
			break;
		case apk:
			command += "del PACKAGES_HERE";
			break;
		default:
			command = "";
			break;
	}
	return command;
}
