# CECS-326-Project-4
1. Open up MinGW64 Terminal
2. Make sure that MinGW64 is updated using the below commands
   pacman -Syu
   pacman -Su
   pacman -S mingw-w64-x86_64-toolchain
3. Navigate to Project Folder using Bash commands cd
4. Use the following commands for First-Come-First-Serve
   make fcfs
   ./fcfs <text file containing tasks>
5. Use the following commands for Priority
   make priority
   ./priority <text file containing tasks>
6. Use the following commands for Round Robin
   make rr
   ./rr <text file containing tasks>
