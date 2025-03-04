using System;

class Animal
{
  private int health;
  private float speed;
  private string environment;

  public Animal(int health, float speed, string environment)
  {
    this.health = health;
    this.speed = speed;
    this.environment = environment;
  }

  public int GetHealth() => health;
  public void SetHealth(int health) => this.health = health;

  public float GetSpeed() => speed;
  public void SetSpeed(float speed) => this.speed = speed;

  public void AnimalInfo()
  {
    Console.WriteLine($"Animal lives in {environment}");
  }
}

class Pigeon : Animal
{
  public Pigeon(int health, float speed, string environment) : base(health, speed, environment) { }

  public static void TitlePrint() => Console.WriteLine("\tPIGEON INFO:");
}

class Dog : Animal
{
  public Dog(int health, float speed, string environment) : base(health, speed, environment) { }

  public static void TitlePrint() => Console.WriteLine("\tDOG INFO:");
}

class Dolphin : Animal
{
  public Dolphin(int health, float speed, string environment) : base(health, speed, environment) { }

  public static void TitlePrint() => Console.WriteLine("\tDOLPHIN INFO:");
}

class Program
{
  static void Main()
  {
    Pigeon pigeon = new Pigeon(100, 40, "Air");
    Dog dog = new Dog(90, 25, "Earth");
    Dolphin dolphin = new Dolphin(65, 70, "Water");

    Pigeon.TitlePrint();
    Console.WriteLine($"Pigeon health: {pigeon.GetHealth()}");
    Console.WriteLine($"Pigeon speed: {pigeon.GetSpeed()}");
    pigeon.AnimalInfo();
    Console.WriteLine();

    Dog.TitlePrint();
    Console.WriteLine($"Dog health: {dog.GetHealth()}");
    Console.WriteLine($"Dog speed: {dog.GetSpeed()}");
    dog.AnimalInfo();
    Console.WriteLine();

    Dolphin.TitlePrint();
    Console.WriteLine($"Dolphin health: {dolphin.GetHealth()}");
    Console.WriteLine($"Dolphin speed: {dolphin.GetSpeed()}");
    dolphin.AnimalInfo();
    Console.WriteLine();
  }
}
