class Animal {
  constructor(protected health: number, protected speed: number, protected environment: string) {}

  getHealth(): number {
      return this.health;
  }

  setHealth(health: number): void {
      this.health = health;
  }

  getSpeed(): number {
      return this.speed;
  }

  setSpeed(speed: number): void {
      this.speed = speed;
  }

  animalInfo(): void {
      console.log(`Animal lives in ${this.environment}`);
  }
}

class Pigeon extends Animal {
  static titlePrint(): void {
      console.log("\tPIGEON INFO:");
  }
}

class Dog extends Animal {
  static titlePrint(): void {
      console.log("\tDOG INFO:");
  }
}

class Dolphin extends Animal {
  static titlePrint(): void {
      console.log("\tDOLPHIN INFO:");
  }
}

const animals = [
  { name: "Pigeon", instance: new Pigeon(100, 40, "Air") },
  { name: "Dog", instance: new Dog(90, 25, "Earth") },
  { name: "Dolphin", instance: new Dolphin(65, 70, "Water") }
];

animals.forEach(({ name, instance }) => {
  (instance.constructor as any).titlePrint();
  console.log(`${name} health: ${instance.getHealth()}`);
  console.log(`${name} speed: ${instance.getSpeed()}`);
  instance.animalInfo();
  console.log();
});
