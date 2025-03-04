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
  def speed(self, speed: float) -> None:
    self.__speed = speed

  def animal_info(self) -> None:
    print(f"Animal lives in {self.__environment}")

animals = [
  ("Pigeon", Animal(100, 40, "Air")),
  ("Dog", Animal(90, 25, "Earth")),
  ("Dolphin", Animal(65, 70, "Water"))
]

for name, animal in animals:
  print(f"\t{name.upper()} INFO:")
  print(f"{name} health: {animal.health}")
  print(f"{name} speed: {animal.speed}")
  animal.animal_info()
  print()
