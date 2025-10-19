
#!/usr/bin/env bash

# if [ "$(type -t ./build/bin/mol)" = "file" ]; then
if [ -f ./build/bin/app ]; then
    echo "[INFO]: RUNNING...\n"
    
    cd ./build/bin/
    
    ./app
    
    cd ..
else
    echo "[ERROR]: COULD NOT RUN ENGINE: EXECUTABLE DOES NOT EXIST OR HAS SOME ERROR. \n"
fi
