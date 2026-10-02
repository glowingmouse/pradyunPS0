#include <iostream>
#include <utility> //for pair
#include <string> //for string
#include <array> //for arrays
#include <cmath> //for round

 class Bender{
    public:
        std::string Name;
        std::string Element;
        int Hp;
        int MaxHp;
        int Attack;
        int Defense;
        int Speed;
        bool is_fainted = false;
        std::array<std::pair<std::string, int>, 4> Moves;

        void display_stats(){
            std::cout << Name << " (" << Element << ") - HP: " << Hp << "/" << MaxHp << ", Attack: " << Attack << ", Defense: " << Defense << ", Speed: " << Speed << std::endl;
            std::cout << "Moves:";
            for (int i = 0; i < (Moves.size() - 1); i++){
                std::cout << " " << Moves[i].first << " (" << Moves[i].second << "),";
            }
            std::cout << " " << Moves[3].first << " (" << Moves[3].second << ")" << std::endl;
        }

        void attk(Bender &bender, int i){
            int damage = round((Attack * Moves[i].second) / bender.Defense);
            bender.Hp -= damage;
            if (bender.Hp < 0){
                bender.Hp = 0;
                bender.is_fainted = true;
            }
        }

        Bender(std::string name, std::string element, int hp, int attack, int defense, int speed, std::array<std::pair<std::string, int>, 4> moves){
            Name = name;
            Element = element;
            Hp = hp;
            MaxHp = hp;
            Attack = attack;
            Defense = defense;
            Speed = speed;
            Moves = moves;
        }
 };

 int main(){
    
    Bender bender1 = Bender("Kael", "Fire", 100, 58, 38, 88, std::array<std::pair<std::string, int>, 4>{{{"Ember Slash", 40}, {"Quick Jab", 30}, {"Focus", 0}, {"Flame Surge", 70}}});
    Bender bender2 = Bender("Mira", "Water", 92, 50, 45, 60, std::array<std::pair<std::string, int>, 4>{{{"Water Whip", 35}, {"Tide Push", 25}, {"Mist Veil", 0}, {"Tidal Wave", 60}}});
    
    bender1.display_stats();
    std::cout << std::endl;
    bender2.display_stats();
    std::cout << std::endl;
    
    Bender &first_bender = (bender1.Speed >= bender2.Speed) ? bender1 : bender2;
    Bender &second_bender = (bender1.Speed >= bender2.Speed) ? bender2 : bender1;
    int Hp1_before = first_bender.Hp;
    int Hp2_before = second_bender.Hp;

    first_bender.attk(second_bender, 0);
    int damage = Hp2_before - second_bender.Hp;


    std::cout << first_bender.Name << " used " << first_bender.Moves[0].first << "!" << std::endl;
    std::cout << second_bender.Name << " took " << damage << " damage!" << std::endl;
    std::cout << std::endl;
    
    second_bender.display_stats();
    std::cout << std::endl;
    
    std::cout << second_bender.Name << " fainted: " << (second_bender.is_fainted ? "True" : "False") << std::endl;
    
    return 0;
 }