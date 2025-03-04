from abc import ABC, abstractmethod
from typing import List

# Абстрактный класс Animal
class Animal(ABC):
    def __init__(self, hp: int, speed: float, env: str):
        self.__health_point = hp
        self.__move_speed = speed
        self.__living_env = env

    @property
    @abstractmethod
    def health(self) -> int:
        pass

    @health.setter
    @abstractmethod
    def health(self, value: int):
        pass

    @property
    @abstractmethod
    def speed(self) -> float:
        pass

    @speed.setter
    @abstractmethod
    def speed(self, value: float):
        pass

    @abstractmethod
    def animal_info(self):
        pass

    @abstractmethod
    def say_something(self):
        pass

    @property
    def living_env(self) -> str:
        return self.__living_env

    @living_env.setter
    def living_env(self, value: str):
        self.__living_env = value

# Класс Pigeon
class Pigeon(Animal):
    @property
    def health(self) -> int:
        return self._Animal__health_point * 100

    @health.setter
    def health(self, value: int):
        self._Animal__health_point = value // 100

    @property
    def speed(self) -> float:
        return self._Animal__move_speed * 10

    @speed.setter
    def speed(self, value: float):
        self._Animal__move_speed = value / 10

    def animal_info(self):
        print(f"Animal lives in {self.living_env}")

    def say_something(self):
        print("Pigeon says: Cock-a-doodle-doo!")

# Класс Dog
class Dog(Animal):
    @property
    def health(self) -> int:
        return self._Animal__health_point * 2

    @health.setter
    def health(self, value: int):
        self._Animal__health_point = value // 2

    @property
    def speed(self) -> float:
        return self._Animal__move_speed * 15

    @speed.setter
    def speed(self, value: float):
        self._Animal__move_speed = value / 15

    def animal_info(self):
        print(f"Animal lives in {self.living_env}")

    def say_something(self):
        print("Dog says: Gav-gav-no!")

# Класс Dolphin
class Dolphin(Animal):
    @property
    def health(self) -> int:
        return self._Animal__health_point * 3

    @health.setter
    def health(self, value: int):
        self._Animal__health_point = value // 3

    @property
    def speed(self) -> float:
        return self._Animal__move_speed * 2345678

    @speed.setter
    def speed(self, value: float):
        self._Animal__move_speed = value / 2345678

    def animal_info(self):
        print(f"Animal lives in {self.living_env}")

    def say_something(self):
        print("Dolphin says: F*ck Microsoft!")

# Основная программа
def main():
    animals: List[Animal] = [
        Pigeon(100, 23.5, "Air"),
        Dog(20, 12.2, "Earth"),
        Dolphin(300, 45.6, "Water")
    ]

    for animal in animals:
        animal.animal_info()
        animal.say_something()
        print(f"Health: {animal.health}")
        print(f"Speed: {animal.speed}")
        print()

if __name__ == "__main__":
    main()