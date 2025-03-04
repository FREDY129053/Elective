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

public class Main {
    public static void main(String[] args) {
      Animal[] animals = {
        new Animal(100, 40, "Air"),
        new Animal(90, 25, "Earth"),
        new Animal(65, 70, "Water")
      };

      String[] names = {"Pigeon", "Dog", "Dolphin"};

      for (int i = 0; i < animals.length; i++) {
        System.out.println("\t" + names[i].toUpperCase() + " INFO:");
        System.out.println(names[i] + " health: " + animals[i].getHealth());
        System.out.println(names[i] + " speed: " + animals[i].getSpeed());
        animals[i].animalInfo();
        System.out.println();
      }
  }
}
