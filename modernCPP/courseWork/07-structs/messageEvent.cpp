struct DamageEvent {
    int targetId;
    float amount;
};

struct Health {
    float hp;
};

void apply_damage(Health *h, const DamageEvent *e) {
    h->hp -= e->amount;
    if (h->hp < 0.0f) {
        h->hp = 0.0f;
    }
}

// communication through data not calls
int main() {
    Health enemy = {100.0f};
    DamageEvent hit = {42, 25.0f};

    apply_damage(&enemy, &hit);
}
