The example:
    - Player entity
    - Enemy entity
    - Gravity + platform collision
    - Left and right movement + jump
    - Simple punch attack
    - Enemy knockback + health
    - Basic platform

Intall:
    sudo apt update
    sudo apt install -y build-essential cmake git libraylib-dev

Get Flecs
    git clone https:://github.com/SanderMertens/flecs.git
    cd flecs
    mkdir build && cd build
    cmake ..
    make
    sudo make install

    # installs flecs.h and libflecs.so 

