#include <iostream>
#include <windows.h>
using namespace std;

string exec(string command) {
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
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



/* reference
https://stackoverflow.com/questions/15141536/c-alternative-to-os-walk
https://ss64.com/nt/dir.html
http://www.davismol.net/2012/04/07/dos-list-and-filter-files-in-a-folder-with-dir-and-findstr-commands/
https://www.shellhacks.com/windows-grep-equivalent-cmd-powershell/#:~:text=The%20grep%20command%20in%20Linux,is%20the%20Select%2DString%20command.
https://stackoverflow.com/questions/1488775/c-remove-new-line-from-multiline-string
*/