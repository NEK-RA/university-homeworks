#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>
using namespace std;

#ifndef UTILS_DEFINED
#define UTILS_DEFINED 1

enum packman {apt, apk, unknownPackageManager};
enum actions {showHelp, showVersion, listDesktops, installVnc, addDesktop, removeDesktop, switchDesktop};

struct State {
	packman pm;
	string pmInstall;
	string pmDelete;
  vector<string> installed;
};

struct DE{
  string name;
  vector<string> packages;
  string xstartup;
  string executable;
};

struct ExecResult{
  int exitCode;
  string outerr;
  double time;
};

const string VERSION = "UDI version 0.0.1";
const string HELP = "Usage:\n\
udi [option] value\n\
\n\
Examples:\n\
udi --help \t-\t to see this help message.\n\
\
udi --version \t-\t to see the version.\n\
\
udi --list \t-\t to see available desktops.\n\
\
udi --add|--remove|--switch desktopname \t-\t install/delete/switch to specified desktop environment. \n\
Require to be root or executed with sudo, since package installation will be performed\n\
\
udi --vnc \t-\t install vnc server (tightvnc), may be combined with desktop installation. \
By default is disabled, since this app intended to be used with UserLAnd app on android, where VNC server is already installed.\n\
Require to be root or executed with sudo, since package installation will be performed\n\
";

const string pkgPlaceholder = "PACKAGES_HERE";

const DE ICEWM = {
  "icewm",
  {"icewm","icewm-common"},
"#!/bin/bash\n\
xrdb $HOME/.Xresources\n\
icewm-session &",
  "/bin/icewm-session"
};

const DE XFCE = {
  "xfce",
  {"xfce4", "xfce4-terminal"},
"#!/bin/sh\n\
xrdb $HOME/.Xresources\n\
startxfce4 &",
  "/bin/startxfce4"
};

const vector<DE> AVAILABLE_DESKTOPS = {ICEWM, XFCE};

#endif

string taskName(actions act);
int searchVectorStr(vector<string> data, string query);
void noProcessing(string line);
void printLine(string line);
ExecResult exec(string command, void processLine(string));
string strReplace(string original, string placeholder, string content);
ExecResult packageManagement(bool install, string installCommand, string removeCommand, string packages, bool detailed);