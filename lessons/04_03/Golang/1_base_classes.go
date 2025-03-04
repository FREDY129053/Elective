// В Golang нет ООП как во всех ЯП
// В Go есть структруы и возможность задавать определенные функции определенным структурам
// Наследование реализуется путем вложения структур друг в друга

package main

import "fmt"

type Animal struct {
	health      int
	speed       float64
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

type Pigeon struct {
	Animal
}

func NewPigeon(health int, speed float64, environment string) *Pigeon {
	return &Pigeon{Animal{health, speed, environment}}
}

func (p *Pigeon) TitlePrint() {
	fmt.Println("\tPIGEON INFO:")
}

type Dog struct {
	Animal
}

func NewDog(health int, speed float64, environment string) *Dog {
	return &Dog{Animal{health, speed, environment}}
}

func (d *Dog) TitlePrint() {
	fmt.Println("\tDOG INFO:")
}

type Dolphin struct {
	Animal
}

func NewDolphin(health int, speed float64, environment string) *Dolphin {
	return &Dolphin{Animal{health, speed, environment}}
}

func (d *Dolphin) TitlePrint() {
	fmt.Println("\tDOLPHIN INFO:")
}

func main() {
	pigeon := NewPigeon(100, 40, "Air")
	dog := NewDog(90, 25, "Earth")
	dolphin := NewDolphin(65, 70, "Water")

	pigeon.TitlePrint()
	fmt.Println("Pigeon health:", pigeon.GetHealth())
	fmt.Println("Pigeon speed:", pigeon.GetSpeed())
	pigeon.AnimalInfo()
	fmt.Println()

	dog.TitlePrint()
	fmt.Println("Dog health:", dog.GetHealth())
	fmt.Println("Dog speed:", dog.GetSpeed())
	dog.AnimalInfo()
	fmt.Println()

	dolphin.TitlePrint()
	fmt.Println("Dolphin health:", dolphin.GetHealth())
	fmt.Println("Dolphin speed:", dolphin.GetSpeed())
	dolphin.AnimalInfo()
	fmt.Println()
}
