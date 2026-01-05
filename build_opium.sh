make clean; compiledb make -j$(proc)

echo "OUTPUT:"

./project/build/bin/project -h

echo "OUTPUT END!"
