abstract class Animal {
  healthPoint: number;
  moveSpeed: number;
  livingEnv: string;

  constructor(healthPoint: number, moveSpeed: number, livingEnv: string) {
    this.healthPoint = healthPoint;
    this.moveSpeed = moveSpeed;
    this.livingEnv = livingEnv;
  }

  abstract getHealth(): number;
  abstract setHealth(health: number): void;
  abstract getSpeed(): number;
  abstract setSpeed(speed: number): void;
  abstract animalInfo(): void;
  abstract saySomething(): void;
}

class Pigeon extends Animal {
  constructor(healthPoint: number, moveSpeed: number, livingEnv: string) {
    super(healthPoint, moveSpeed, livingEnv);
  }

  getHealth(): number {
    return this.healthPoint * 100;
  }

  setHealth(health: number): void {
    this.healthPoint = health / 100;
  }

  getSpeed(): number {
    return this.moveSpeed * 10;
  }

  setSpeed(speed: number): void {
    this.moveSpeed = speed / 10;
  }

  animalInfo(): void {
    console.log(`Animal lives in ${this.livingEnv}`);
  }

  saySomething(): void {
    console.log("Pigeon says: Cock-a-doodle-doo!");
  }
}

class Dog extends Animal {
  constructor(healthPoint: number, moveSpeed: number, livingEnv: string) {
    super(healthPoint, moveSpeed, livingEnv);
  }

  getHealth(): number {
    return this.healthPoint * 2;
  }

  setHealth(health: number): void {
    this.healthPoint = health / 2;
  }

  getSpeed(): number {
    return this.moveSpeed * 15;
  }

  setSpeed(speed: number): void {
    this.moveSpeed = speed / 15;
  }

  animalInfo(): void {
    console.log(`Animal lives in ${this.livingEnv}`);
  }

  saySomething(): void {
    console.log("Dog says: Gav-gav-no!");
  }
}

class Dolphin extends Animal {
  constructor(healthPoint: number, moveSpeed: number, livingEnv: string) {
    super(healthPoint, moveSpeed, livingEnv);
  }

  getHealth(): number {
    return this.healthPoint * 3;
  }

  setHealth(health: number): void {
    this.healthPoint = health / 3;
  }

  getSpeed(): number {
    return this.moveSpeed * 2345678;
  }

  setSpeed(speed: number): void {
    this.moveSpeed = speed / 2345678;
  }

  animalInfo(): void {
    console.log(`Animal lives in ${this.livingEnv}`);
  }

  saySomething(): void {
    console.log("Dolphin says: F*ck Microsoft!");
  }
}

const animals: Animal[] = [
  new Pigeon(100, 23.5, "Air"),
  new Dog(20, 12.2, "Earth"),
  new Dolphin(300, 45.6, "Water"),
];

animals.forEach((animal) => {
  animal.animalInfo();
  animal.saySomething();
  console.log(`Health: ${animal.getHealth()}`);
  console.log(`Speed: ${animal.getSpeed()}\n`);
});
