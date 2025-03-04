using System;

class Animal {
    protected int health;
    protected float speed;
    protected string environment;

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

class Pigeon : Animal {
    public Pigeon(int health, float speed, string environment) : base(health, speed, environment) {}

    public static void TitlePrint() {
        Console.WriteLine("\tPIGEON INFO:");
    }
}

class Dog : Animal {
    public Dog(int health, float speed, string environment) : base(health, speed, environment) {}

    public static void TitlePrint() {
        Console.WriteLine("\tDOG INFO:");
    }
}

class Dolphin : Animal {
    public Dolphin(int health, float speed, string environment) : base(health, speed, environment) {}

    public static void TitlePrint() {
        Console.WriteLine("\tDOLPHIN INFO:");
    }
}

class Program {
    static void Main() {
        Animal[] animals = { new Pigeon(100, 40, "Air"), new Dog(90, 25, "Earth"), new Dolphin(65, 70, "Water") };
        foreach (var animal in animals) {
            if (animal is Pigeon) Pigeon.TitlePrint();
            if (animal is Dog) Dog.TitlePrint();
            if (animal is Dolphin) Dolphin.TitlePrint();
            Console.WriteLine($"Health: {animal.GetHealth()}");
            Console.WriteLine($"Speed: {animal.GetSpeed()}");
            animal.AnimalInfo();
            Console.WriteLine();
        }
    }
}
