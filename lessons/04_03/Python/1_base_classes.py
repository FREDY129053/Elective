# В Python нет типизации как в C++, но есть аннотаиця типов, чтобы указывать где какой тип передается и возвращается
# Так же, нет protected как такого, есть договоренность, что _val - это переменная protected
# За то есть private, который обозначается __val
# Все переменные указываются в конструкторе(__init__)
# Статичсные переменные указываются вне конструктора

class Animal:
    def __init__(self, health: int, speed: float, environment: str) -> None:
        self.__health = health
        self.__speed = speed
        self.__environment = environment

    @property
    def health(self) -> int:
        return self.__health

    @health.setter
    def health(self, health: int) -> None:
        self.__health = health

    @property
    def speed(self) -> float:
        return self.__speed

    @speed.setter
    def set_speed(self, speed: float) -> None:
        self.__speed = speed

    def animal_info(self) -> None:
        print(f"Animal lives in {self.__environment}")


class Pigeon(Animal):
    @staticmethod
    def title_print() -> None:
        print("\tPIGEON INFO:")


class Dog(Animal):
    @staticmethod
    def title_print() -> None:
        print("\tDOG INFO:")


class Dolphin(Animal):
    @staticmethod
    def title_print() -> None:
        print("\tDOLPHIN INFO:")


pigeon = Pigeon(100, 40, "Air")
dog = Dog(90, 25, "Earth")
dolphin = Dolphin(65, 70, "Water")

Pigeon.title_print()
print(f"Pigeon health: {pigeon.health}")
print(f"Pigeon speed: {pigeon.speed}")
pigeon.animal_info()
print()

Dog.title_print()
print(f"Dog health: {dog.health}")
print(f"Dog speed: {dog.speed}")
dog.animal_info()
print()

Dolphin.title_print()
print(f"Dolphin health: {dolphin.health}")
print(f"Dolphin speed: {dolphin.speed}")
dolphin.animal_info()
print()
