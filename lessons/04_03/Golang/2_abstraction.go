package main

import "fmt"

type Animal struct {
	health     int
	speed      float64
	environment string
}

func (a *Animal) GetHealth() int {
	return a.health
}

func (a *Animal) SetHealth(health int) {
	a.health = health
}

func (a *Animal) GetSpeed() float64 {
	return a.speed
}

func (a *Animal) SetSpeed(speed float64) {
	a.speed = speed
}

func (a *Animal) AnimalInfo() {
	fmt.Println("Animal lives in", a.environment)
}

func main() {
	animals := map[string]Animal{
		"Pigeon":  {100, 40, "Air"},
		"Dog":     {90, 25, "Earth"},
		"Dolphin": {65, 70, "Water"},
	}

	for name, animal := range animals {
		fmt.Printf("\t%s INFO:\n", name)
		fmt.Printf("%s health: %d\n", name, animal.GetHealth())
		fmt.Printf("%s speed: %.2f\n", name, animal.GetSpeed())
		animal.AnimalInfo()
		fmt.Println()
	}
}
