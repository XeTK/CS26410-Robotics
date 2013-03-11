echo "Compiling Please WAIT!!!"
g++ -o simulator `pkg-config --cflags playerc++` simple.cpp Mapt.cpp Mapt.h `pkg-config --libs playerc++`
echo "Running Simulator"
./simulator 
