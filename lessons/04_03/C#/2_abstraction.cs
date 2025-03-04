using System;

class Animal {
    private int health;
    private float speed;
    private string environment;

    public Animal(int health, float speed, string environment) {
        this.health = health;
        this.speed = speed;
        this.environment = environment;
    }

    public int GetHealth() {
        return health;
    }

    public void SetHealth(int health) {
        this.health = health;
    }

    public float GetSpeed() {
        return speed;
    }

    public void SetSpeed(float speed) {
        this.speed = speed;
    }

    public void AnimalInfo() {
        Console.WriteLine($"Animal lives in {environment}");
    }
}

class Program {
    static void Main() {
        (string name, Animal instance)[] animals = {
            ("Pigeon", new Animal(100, 40, "Air")),
            ("Dog", new Animal(90, 25, "Earth")),
            ("Dolphin", new Animal(65, 70, "Water"))
        };

        foreach (var (name, instance) in animals) {
            Console.WriteLine($"\t{name.ToUpper()} INFO:");
            Console.WriteLine($"{name} health: {instance.GetHealth()}");
            Console.WriteLine($"{name} speed: {instance.GetSpeed()}");
            instance.AnimalInfo();
            Console.WriteLine();
        }
    }
}
