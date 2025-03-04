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

const animals: { name: string; instance: Animal }[] = [
  { name: "Pigeon", instance: new Animal(100, 40, "Air") },
  { name: "Dog", instance: new Animal(90, 25, "Earth") },
  { name: "Dolphin", instance: new Animal(65, 70, "Water") },
];

animals.forEach(({ name, instance }) => {
  console.log(`\t${name.toUpperCase()} INFO:`);
  console.log(`${name} health: ${instance.getHealth()}`);
  console.log(`${name} speed: ${instance.getSpeed()}`);
  instance.animalInfo();
  console.log();
});
