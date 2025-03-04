class Animal {
  private int health;
  private float speed;
  private String environment;

  public Animal(int health, float speed, String environment) {
    this.health = health;
    this.speed = speed;
    this.environment = environment;
  }

  public int getHealth() {
    return health;
  }

  public void setHealth(int health) {
    this.health = health;
  }

  public float getSpeed() {
    return speed;
  }

  public void setSpeed(float speed) {
    this.speed = speed;
  }

  public void animalInfo() {
    System.out.println("Animal lives in " + environment);
  }
}

class Pigeon extends Animal {
  public Pigeon(int health, float speed, String environment) {
    super(health, speed, environment);
  }

  public static void titlePrint() {
    System.out.println("\tPIGEON INFO:");
  }
}

class Dog extends Animal {
  public Dog(int health, float speed, String environment) {
    super(health, speed, environment);
  }

  public static void titlePrint() {
    System.out.println("\tDOG INFO:");
  }
}

class Dolphin extends Animal {
  public Dolphin(int health, float speed, String environment) {
    super(health, speed, environment);
  }

  public static void titlePrint() {
    System.out.println("\tDOLPHIN INFO:");
  }
}

public class Main {
  public static void main(String[] args) {
    Pigeon pigeon = new Pigeon(100, 40, "Air");
    Dog dog = new Dog(90, 25, "Earth");
    Dolphin dolphin = new Dolphin(65, 70, "Water");

    Pigeon.titlePrint();
    System.out.println("Pigeon health: " + pigeon.getHealth());
    System.out.println("Pigeon speed: " + pigeon.getSpeed());
    pigeon.animalInfo();
    System.out.println();

    Dog.titlePrint();
    System.out.println("Dog health: " + dog.getHealth());
    System.out.println("Dog speed: " + dog.getSpeed());
    dog.animalInfo();
    System.out.println();

    Dolphin.titlePrint();
    System.out.println("Dolphin health: " + dolphin.getHealth());
    System.out.println("Dolphin speed: " + dolphin.getSpeed());
    dolphin.animalInfo();
    System.out.println();
  }
}
