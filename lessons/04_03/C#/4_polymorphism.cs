using System;
using System.Collections.Generic;

abstract class Animal {
    protected int healthPoint;
    protected float moveSpeed;
    protected string livingEnv;

    protected Animal(int hp, float speed, string env) {
        healthPoint = hp;
        moveSpeed = speed;
        livingEnv = env;
    }

    public abstract int GetHealth();
    public abstract void SetHealth(int health);
    public abstract int GetSpeed();
    public abstract void SetSpeed(int speed);
    public abstract void AnimalInfo();
    public abstract void SaySomething();
}

class Pigeon : Animal {
    public Pigeon(int hp, float speed, string env) : base(hp, speed, env) {}

    public override int GetHealth() {
        return healthPoint * 100;
    }

    public override void SetHealth(int health) {
        healthPoint = health / 100;
    }

    public override int GetSpeed() {
        return (int)(moveSpeed * 10);
    }

    public override void SetSpeed(int speed) {
        moveSpeed = speed / 10.0f;
    }

    public override void AnimalInfo() {
        Console.WriteLine($"Animal lives in {livingEnv}");
    }

    public override void SaySomething() {
        Console.WriteLine("Pigeon says: Cock-a-doodle-doo!");
    }
}

class Dog : Animal {
    public Dog(int hp, float speed, string env) : base(hp, speed, env) {}

    public override int GetHealth() {
        return healthPoint * 2;
    }

    public override void SetHealth(int health) {
        healthPoint = health / 2;
    }

    public override int GetSpeed() {
        return (int)(moveSpeed * 15);
    }

    public override void SetSpeed(int speed) {
        moveSpeed = speed / 15.0f;
    }

    public override void AnimalInfo() {
        Console.WriteLine($"Animal lives in {livingEnv}");
    }

    public override void SaySomething() {
        Console.WriteLine("Dog says: Gav-gav-no!");
    }
}

class Dolphin : Animal {
    public Dolphin(int hp, float speed, string env) : base(hp, speed, env) {}

    public override int GetHealth() {
        return healthPoint * 3;
    }

    public override void SetHealth(int health) {
        healthPoint = health / 3;
    }

    public override int GetSpeed() {
        return (int)(moveSpeed * 2345678);
    }

    public override void SetSpeed(int speed) {
        moveSpeed = speed / 2345678.0f;
    }

    public override void AnimalInfo() {
        Console.WriteLine($"Animal lives in {livingEnv}");
    }

    public override void SaySomething() {
        Console.WriteLine("Dolphin says: F*ck Microsoft!");
    }
}

class Program {
    static void Main() {
        List<Animal> animals = new List<Animal> {
            new Pigeon(100, 23.5f, "Air"),
            new Dog(20, 12.2f, "Earth"),
            new Dolphin(300, 45.6f, "Water")
        };

        foreach (var animal in animals) {
            animal.AnimalInfo();
            animal.SaySomething();
            Console.WriteLine($"Health: {animal.GetHealth()}");
            Console.WriteLine($"Speed: {animal.GetSpeed()}\n");
        }
    }
}
