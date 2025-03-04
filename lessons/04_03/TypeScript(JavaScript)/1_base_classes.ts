class Animal {
  constructor(private health: number, private speed: number, private environment: string) {}

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

const pigeon = new Pigeon(100, 40, "Air");
const dog = new Dog(90, 25, "Earth");
const dolphin = new Dolphin(65, 70, "Water");

Pigeon.titlePrint();
console.log(`Pigeon health: ${pigeon.getHealth()}`);
console.log(`Pigeon speed: ${pigeon.getSpeed()}`);
pigeon.animalInfo();
console.log();

Dog.titlePrint();
console.log(`Dog health: ${dog.getHealth()}`);
console.log(`Dog speed: ${dog.getSpeed()}`);
dog.animalInfo();
console.log();

Dolphin.titlePrint();
console.log(`Dolphin health: ${dolphin.getHealth()}`);
console.log(`Dolphin speed: ${dolphin.getSpeed()}`);
dolphin.animalInfo();
console.log();
