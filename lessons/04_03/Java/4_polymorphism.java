abstract class Animal {
    int healthPoint;
    float moveSpeed;
    String livingEnv;

    Animal(int hp, float speed, String env) {
        this.healthPoint = hp;
        this.moveSpeed = speed;
        this.livingEnv = env;
    }

    abstract int getHealth();
    abstract void setHealth(int health);
    abstract int getSpeed();
    abstract void setSpeed(int speed);
    abstract void animalInfo();
    abstract void saySomething();
}

class Pigeon extends Animal {
    Pigeon(int hp, float speed, String env) {
        super(hp, speed, env);
    }

    int getHealth() {
        return healthPoint * 100;
    }

    void setHealth(int health) {
        healthPoint = health / 100;
    }

    int getSpeed() {
        return (int) (moveSpeed * 10);
    }

    void setSpeed(int speed) {
        moveSpeed = speed / 10.0f;
    }

    void animalInfo() {
        System.out.println("Animal lives in " + livingEnv);
    }

    void saySomething() {
        System.out.println("Pigeon says: Cock-a-doodle-doo!");
    }
}

class Dog extends Animal {
    Dog(int hp, float speed, String env) {
        super(hp, speed, env);
    }

    int getHealth() {
        return healthPoint * 2;
    }

    void setHealth(int health) {
        healthPoint = health / 2;
    }

    int getSpeed() {
        return (int) (moveSpeed * 15);
    }

    void setSpeed(int speed) {
        moveSpeed = speed / 15.0f;
    }

    void animalInfo() {
        System.out.println("Animal lives in " + livingEnv);
    }

    void saySomething() {
        System.out.println("Dog says: Gav-gav-no!");
    }
}

class Dolphin extends Animal {
    Dolphin(int hp, float speed, String env) {
        super(hp, speed, env);
    }

    int getHealth() {
        return healthPoint * 3;
    }

    void setHealth(int health) {
        healthPoint = health / 3;
    }

    int getSpeed() {
        return (int) (moveSpeed * 2345678);
    }

    void setSpeed(int speed) {
        moveSpeed = speed / 2345678.0f;
    }

    void animalInfo() {
        System.out.println("Animal lives in " + livingEnv);
    }

    void saySomething() {
        System.out.println("Dolphin says: F*ck Microsoft!");
    }
}

public class Main {
    public static void main(String[] args) {
        Animal[] animals = {
            new Pigeon(100, 23.5f, "Air"),
            new Dog(20, 12.2f, "Earth"),
            new Dolphin(300, 45.6f, "Water")
        };

        for (Animal animal : animals) {
            animal.animalInfo();
            animal.saySomething();
            System.out.println("Health: " + animal.getHealth());
            System.out.println("Speed: " + animal.getSpeed());
            System.out.println();
        }
    }
}
