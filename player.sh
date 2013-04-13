echo "Compiling Please WAIT!!!"
g++ -o simulator `pkg-config --cflags playerc++` *.cpp *.h `pkg-config --libs playerc++`
echo "Running Simulator"
./simulator 
