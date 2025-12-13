struct Position {
    float x;
    float y;
};

struct Velocity {
    float dx;
    float dy;
};

void move(Position *p, const Velocity *v, float dt) {
    p->x += v->dx * dt;
    p->y += v->dy * dt;
}

int main() {
    Position pos = {0.0f, 0.0f};
    Velocity vel = {1.0f, 0.5f};

    move(&pos, &vel, 1.0f);
}
