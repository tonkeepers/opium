cd project 

make clean; bear -- make -j$(proc)

mv project/compile_commands.json . 

echo "OUTPUT:"

cd ..

./build/bin/project -h

echo "OUTPUT END!"
