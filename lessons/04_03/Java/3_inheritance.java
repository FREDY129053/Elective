class Animal {
    protected int health;
    protected float speed;
    protected String environment;

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
        Animal[] animals = {
            new Pigeon(100, 40, "Air"),
            new Dog(90, 25, "Earth"),
            new Dolphin(65, 70, "Water")
        };

        String[] names = {"Pigeon", "Dog", "Dolphin"};

        for (int i = 0; i < animals.length; i++) {
            if (animals[i] instanceof Pigeon) Pigeon.titlePrint();
            if (animals[i] instanceof Dog) Dog.titlePrint();
            if (animals[i] instanceof Dolphin) Dolphin.titlePrint();
            System.out.println(names[i] + " health: " + animals[i].getHealth());
            System.out.println(names[i] + " speed: " + animals[i].getSpeed());
            animals[i].animalInfo();
            System.out.println();
        }
    }
}
