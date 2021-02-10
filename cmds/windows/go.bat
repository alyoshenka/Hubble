ECHO "go.bat"

mkdir build
cd build && cmake ..
cmake --build . 

ECHO "running exe"
"./Debug/HubbleExe.exe"
