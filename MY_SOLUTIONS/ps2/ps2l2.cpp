#include <iostream>
#include <utility> //for pair
#include <string> //for string
#include <array> //for arrays
#include <cmath> //for round
#include <random> //for random choosing
#include <algorithm> //for max

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
        std::string attack_strength;
        bool is_critical;

        void display_stats(){
            std::cout << Name << " (" << Element << ") - HP: " << Hp << "/" << MaxHp << ", Attack: " << Attack << ", Defense: " << Defense << ", Speed: " << Speed << std::endl;
            std::cout << "Moves:";
            for (int i = 0; i < (Moves.size() - 1); i++){
                std::cout << " " << Moves[i].first << " (" << Moves[i].second << "),";
            }
            std::cout << " " << Moves[3].first << " (" << Moves[3].second << ")" << std::endl;
        }

        void attk(Bender &bender, int i){
            float base_damage = (((static_cast<float>(Attack)) * Moves[i].second) / bender.Defense);
            float critical_chance = 0.10;
            std::random_device rd;
            std::uniform_real_distribution<double> dist(0.0,1.0);
            is_critical = (dist(rd) <= critical_chance) ? true : false;
            float type_multiplier;
            if ((Element == "Water" && bender.Element == "Fire") || (Element == "Fire" && bender.Element == "Air") || (Element == "Air" && bender.Element == "Earth") || (Element == "Earth" && bender.Element == "Water")){
                type_multiplier = 2.0;
                attack_strength = "Super Effective";
            }
            else if ((Element == "Fire" && bender.Element == "Water") || (Element == "Air" && bender.Element == "Fire") || (Element == "Earth" && bender.Element == "Air") || (Element == "Water" && bender.Element == "Earth")){
                type_multiplier = 0.5;
                attack_strength = "Weak";
            }
            else{
                type_multiplier = 1.0;
                attack_strength = "Neutral";
            }    
            float critical_multiplier = (is_critical) ? 2.0 : 1.0;
            int final_damage = std::max(1, static_cast<int>(round(base_damage * type_multiplier * critical_multiplier)));
            bender.Hp -= final_damage;
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

 class Duel{
    public:
        Bender* Bender1 = nullptr;
        Bender* Bender2 = nullptr;

        void set_bender_order(Bender& bender1, Bender& bender2, Bender*& first_bender, Bender*& second_bender){
            if (bender1.Speed > bender2.Speed){
                first_bender = &bender1;
                Bender1 = &bender1;
                second_bender = &bender2;
                Bender2 = &bender2;
            }
            else if (bender2.Speed > bender1.Speed){
                first_bender = &bender2;
                Bender1 = &bender2;
                second_bender = &bender1;
                Bender2 = &bender1;
            }
            else{
                std::random_device rd;
                std::uniform_int_distribution<int> dist(0,1);
                first_bender = (dist(rd) == 0) ? &bender1 : &bender2;
                if (first_bender == &bender1){
                    second_bender = &bender2;
                    Bender1 = &bender1;
                    Bender2 = &bender2;
                }
                else{
                    second_bender = &bender1;
                    Bender1 = &bender2;
                    Bender2 = &bender1;
                }
            }
        }

        void start_duel(Bender*& bender_no1, Bender*& bender_no2, int &c, int &s){
            std::cout << "=== DUEL BEGINS! ===" << std::endl;
            std::cout << (*bender_no1).Name << " (" << (*bender_no1).Element << ", HP: " << (*bender_no1).MaxHp << "/" << (*bender_no1).MaxHp << ") VS " << (*bender_no2).Name << " (" << (*bender_no2).Element << ", HP: " << (*bender_no2).MaxHp << "/" << (*bender_no2).MaxHp << ")" << std::endl << std::endl;
            std::cout << "Turn 1: " << (*bender_no1).Name << " goes first! (Speed: " << (*bender_no1).Speed << " vs " << (*bender_no2).Speed << ")" << std::endl;
            int Hp2_before = (*bender_no2).Hp;
            (*bender_no1).attk(*bender_no2, 0);
            int damage = Hp2_before - (*bender_no2).Hp;
            std::cout << (*bender_no1).Name << " used " << (*bender_no1).Moves[0].first << "!" << std::endl;
            if ((*bender_no1).attack_strength == "Super Effective"){
                std::cout << "Super Effective! (" << (*bender_no1).Element << " is strong against " << (*bender_no2).Element << ")" << std::endl;
                s++;
            }
            else if ((*bender_no1).attack_strength == "Weak"){
                std::cout << "Not very effective... (" << (*bender_no1).Element << " is weak against " << (*bender_no2).Element << ")" << std::endl;
            }
            if ((*bender_no1).is_critical){
                std::cout << "Critical Hit!" << std::endl;
                c++;
            }
            std::cout << (*bender_no2).Name << " took " << damage << " damage!" << std::endl;
            std::cout << (*bender_no2).Name << "HP: " << (*bender_no2).Hp << "/" << (*bender_no2).MaxHp << std::endl;   
        }
        void regular_first_strike(Bender*& bender_no1, Bender*& bender_no2, int k, int &c, int &s){
            std::cout << "Turn " << (2*k - 1) << ": " << (*bender_no1).Name << " goes first!" << std::endl;
            int Hp2_before = (*bender_no2).Hp;
            (*bender_no1).attk(*bender_no2, ((k - 1) % 4));
            int damage = Hp2_before - (*bender_no2).Hp;

            std::cout << (*bender_no1).Name << " used " << (*bender_no1).Moves[(k % 4)].first << "!" << std::endl;
            if ((*bender_no1).attack_strength == "Super Effective"){
                std::cout << "Super Effective! (" << (*bender_no1).Element << " is strong against " << (*bender_no2).Element << ")" << std::endl;
                s++;
            }
            else if ((*bender_no1).attack_strength == "Weak"){
                std::cout << "Not very effective... (" << (*bender_no1).Element << " is weak against " << (*bender_no2).Element << ")" << std::endl;
            }
            if ((*bender_no1).is_critical){
                std::cout << "Critical Hit!" << std::endl;
                c++;
            }
            std::cout << (*bender_no2).Name << " took " << damage << " damage!" << std::endl;
            std::cout << (*bender_no2).Name << "HP: " << (*bender_no2).Hp << "/" << (*bender_no2).MaxHp << std::endl;
        }
        void strike_back(Bender*& bender_no1, Bender*& bender_no2, int k, int &c, int &s){
            std::cout << "Turn " << (2*k) << ": " << (*bender_no2).Name << " strikes back!" << std::endl;
            int Hp1_before = (*bender_no1).Hp;
            (*bender_no2).attk(*bender_no1, (k % 4));
            int damage = Hp1_before - (*bender_no1).Hp;

            std::cout << (*bender_no2).Name << " used " << (*bender_no2).Moves[((k - 1) % 4)].first << "!" << std::endl;
            if ((*bender_no2).attack_strength == "Super Effective"){
                std::cout << "Super Effective! (" << (*bender_no2).Element << " is strong against " << (*bender_no1).Element << ")" << std::endl;
                s++;
            }
            else if ((*bender_no2).attack_strength == "Weak"){
                std::cout << "Not very effective... (" << (*bender_no2).Element << " is weak against " << (*bender_no1).Element << ")" << std::endl;
            }
            if ((*bender_no2).is_critical){
                std::cout << "Critical Hit!" << std::endl;
                c++;
            }
            std::cout << (*bender_no1).Name << " took " << damage << " damage!" << std::endl;
            std::cout << (*bender_no1).Name << "HP: " << (*bender_no1).Hp << "/" << (*bender_no1).MaxHp << std::endl;
        }

        Duel(Bender& bender1, Bender& bender2){
            Bender1 = &bender1;
            Bender2 = &bender2;
        }
 };
 

 int main(){
    
    //Bender bender1 = Bender("Kael", "Fire", 100, 58, 38, 88, std::array<std::pair<std::string, int>, 4>{{{"Ember Slash", 40}, {"Quick Jab", 30}, {"Focus", 0}, {"Flame Surge", 70}}});
    //Bender bender2 = Bender("Mira", "Water", 92, 50, 45, 60, std::array<std::pair<std::string, int>, 4>{{{"Water Whip", 35}, {"Tide Push", 25}, {"Mist Veil", 0}, {"Tidal Wave", 60}}});
    Bender bender1 = Bender("Nadia", "Water", 85, 48, 60, 72, std::array<std::pair<std::string, int>, 4>{{{"Wave Crash", 35}, {"Splash Kick", 25}, {"Guard", 0}, {"Riptide", 50}}});
    Bender bender2 = Bender("Talon", "Air", 90, 52, 55, 72, std::array<std::pair<std::string, int>, 4>{{{"Gale Strike", 38}, {"Wind Cutter", 28}, {"Updraft", 0}, {"Cyclone Blast", 48}}});
    //Bender bender1 = Bender("Sable", "Air", 95, 60, 58, 85, std::array<std::pair<std::string, int>, 4>{{{"Arctic Gust", 0}, {"Wind Blade", 52}, {"Tailwind", 0}, {"Cyclone Fang", 58}}});
    //Bender bender2 = Bender("Boran", "Earth", 110, 68, 62, 50, std::array<std::pair<std::string, int>, 4>{{{"Rockslide", 55}, {"Quicksand Trap", 0}, {"Stone Wall", 0}, {"Seismic Slam", 70}}});
    Duel duel = Duel(bender1, bender2);

    Bender* first_bender = nullptr;
    Bender* second_bender = nullptr;
    duel.set_bender_order(bender1, bender2, first_bender, second_bender);
    int c = 0; int s = 0;
    duel.start_duel(first_bender, second_bender, c, s);
    int counter = 1;
    std::string fainted_bender;
    std::string winner_bender;
    while (true){
        if ((*second_bender).is_fainted == true){
            fainted_bender = (*second_bender).Name;
            winner_bender =  (*first_bender).Name;
            counter = counter * 2;
            break;
        }
        std::cout << std::endl;
        duel.strike_back(first_bender, second_bender, counter, c, s);
        counter++;
        if ((*first_bender).is_fainted == true){
            fainted_bender = (*first_bender).Name;
            winner_bender = (*second_bender).Name;
            counter = 2 * counter - 2;
            break;
        }
        std::cout << std::endl;
        duel.regular_first_strike(first_bender, second_bender, counter, c, s);
    }
    std::cout << std::endl;
    std::cout << fainted_bender << " fainted!" << std::endl;
    std::cout << winner_bender << " wins the duel!" << std::endl << std::endl;
    
    std::cout << "Duel Summary:" << std::endl;
    std::cout << "- Winner: " << winner_bender << std::endl;
    std::cout << "- Turns: " << counter << std::endl;
    std::cout << "- Critical Hits: " << c << std::endl;
    std::cout << "- Super Effective Hits: " << s << std::endl;
    
    return 0;
 }
