#include <iostream>
#include <string>

// Создание класса Голубь
class Pigeon {
  // Объявляем приватные переменные
  private:
    int healthPoint;  // Здоровье
    float moveSpeed;  // Скорость движения
    std::string livingEnv;  // Среда обитания

  // Объявляем публичные методы для доступа к приватным переменным и реализации поведения животного
  public:
    // Создаем конструктор класса
    Pigeon(int hp, float speed, std::string env) : healthPoint(hp), moveSpeed(speed), livingEnv(env) {}
    /*
      В данном примере такой конструктор реализует список инициализации:

      <className> (<var1>, ..., <varN>) : <classValue1>(<var1>), ..., <classValueN>(<varN>)

      Данная реализация позволяет более эффективно инициализировать перменные класса, иначе делалось так:

      Pigeon(int hp, float speed, std::string env) {
        this->healthPoint = hp;
        this->moveSpeed = speed;
        this->livingEnv = env;
      }

      При записи выше healthPoint и другие переменные создавались пустыми, а потом им бы присваивалось бы значение.

      Данную запись следует реализовывать, если в конструкторе сложно придумать альтернативное название перменным: 

      Pigeon(int healthPoint, float moveSpeed, std::string livingEnv) {
        this->healthPoint = hp;
        this->moveSpeed = speed;
        this->livingEnv = env;
      }
    */

    int getHealth() const { return healthPoint; }  // Getter для здоровья
    void setHealth(int health) { healthPoint = health; }  // Setter для здоровья

    float getSpeed() const { return moveSpeed; }  // Getter для скорости
    void setSpeed(float speed) { moveSpeed = speed; }  // Setter для скорости

    // Просто метод для класса(выводит информацию, где живет животное)
    void animalInfo() {
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    static void titlePrint() {
      std::cout << "\tPIGEON INFO:" << std::endl;
    }
};

// Для других классов аналогично

class Dog {
  private:
    int healthPoint; 
    float moveSpeed; 
    std::string livingEnv; 

  public:
    Dog(int hp, float speed, std::string env) : healthPoint(hp), moveSpeed(speed), livingEnv(env) {}
    
    int getHealth() const { return healthPoint; }  
    void setHealth(int health) { healthPoint = health; } 

    float getSpeed() const { return moveSpeed; } 
    void setSpeed(float speed) { moveSpeed = speed; } 

    void animalInfo() {
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    static void titlePrint() {
      std::cout << "\tDOG INFO:" << std::endl;
    }
};

class Dolphin {
  private:
    int healthPoint;
    float moveSpeed; 
    std::string livingEnv; 

  public:
    Dolphin(int hp, float speed, std::string env) : healthPoint(hp), moveSpeed(speed), livingEnv(env) {}
    
    int getHealth() const { return healthPoint; } 
    void setHealth(int health) { healthPoint = health; }

    float getSpeed() const { return moveSpeed; }
    void setSpeed(float speed) { moveSpeed = speed; }

    void animalInfo() {
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    static void titlePrint() {
      std::cout << "\tDOLPHIN INFO:" << std::endl;
    }
};

int main() {
  // Создаем экземпляры классов
  Pigeon pigeon = Pigeon(100, 40, "Air");
  Dog dog = Dog(90, 25, "Earth");
  Dolphin dolphin = Dolphin(65, 70, "Water");

  // Выводим информацию о голубе
  Pigeon::titlePrint();  // Используем статический метод
  std::cout << "Pigeon health: " << pigeon.getHealth() << std::endl;
  std::cout << "Pigeon speed: " << pigeon.getSpeed() << std::endl;
  pigeon.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о собаке
  Dog::titlePrint();  // Используем статический метод
  std::cout << "Dog health: " << dog.getHealth() << std::endl;
  std::cout << "Dog speed: " << dog.getSpeed() << std::endl;
  dog.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о дельфине
  Dolphin::titlePrint();  // Используем статический метод
  std::cout << "Dolphin health: " << dolphin.getHealth() << std::endl;
  std::cout << "Dolphin speed: " << dolphin.getSpeed() << std::endl;
  dolphin.animalInfo();
  std::cout << std::endl;

  return 0;
}