compiler=g++
file=main.cpp
libs="-lsfml-graphics -lsfml-window -lsfml-system"
flags="-O1"
out="tetris"
if $compiler $file $libs $flags -o $out; then
    echo "Compilation Successful"
    chmod +x $out
    ./$out
else 
    "Compilation Failed"
fi