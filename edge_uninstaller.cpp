#include <iostream>
#include <windows.h>
using namespace std;

string exec(string command) {
   char buffer[128];
   string result = "";

   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}

int main(){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    string dir = exec("c: && cd \"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\" && dir /B /S | findstr \"setup\"");
    dir = "\""+dir.substr(0,dir.length()-1)+"\"";
    cout<<dir;
    if(dir.length() == 2) MessageBox(NULL,"Uninstall not available","Microsoft Edge",MB_ICONEXCLAMATION);
      else {
         exec(dir + " --uninstall -system-level --verbose-logging");
    }
    return 0;
}
