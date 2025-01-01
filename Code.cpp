#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

struct exercisedata {
    string name;
    int stabilitydemand;
    int cooperatingandcompounddemand;
    int abilitytoreachfailure;
};

enum class Unit {
    tbsp,
    liter,
    quantity,
    hundred_grams,
};
enum class GoalType {
    Hypertrophy,
    Sports,
    Hybrid,
    Powerlifting,
    EnduranceSports
};

struct Exercise {
    string name;
    int sets;
    int reps;
};
struct FoodGoal {
    int calories;
    int protein;
    int carbohydrated;
    int fats;
};

struct Food {
    string name;
    int index;
    Unit unit;
    int calories;
    int protein;
    int carbohydrates;
    int fats;
};

struct Uservariables
{
    int leveloftraining;
    GoalType goal;
    bool gender;
    int weightinkg;
    int heightincm;
    int age;
};

string GoalToString(GoalType goal) {
    switch (goal) {
    case GoalType::Hypertrophy: return "Hypertrophy";
    case GoalType::Sports: return "Sports";
    case GoalType::Hybrid: return "Hybrid";
    case GoalType::Powerlifting: return "Powerlifting";
    case GoalType::EnduranceSports: return "Endurance Sports";
    default:
        return "Unknown Goal";
    }
}

GoalType stringToGoal(const std::string& goalStr) {
    if (goalStr == "Hypertrophy") return GoalType::Hypertrophy;
    if (goalStr == "Sports") return GoalType::Sports;
    if (goalStr == "Hybrid") return GoalType::Hybrid;
    if (goalStr == "Powerlifting") return GoalType::Powerlifting;
    if (goalStr == "Endurance Sports") return GoalType::EnduranceSports;
    throw std::invalid_argument("Unknown goal string");
}

string unitToString(Unit unit) {
    switch (unit) {
    case Unit::hundred_grams: return "100g";
    case Unit::tbsp: return "tbsp";
    case Unit::liter: return "liter";
    case Unit::quantity: return "quantity";
    default: return "unknown";
    }
}
Unit stringToUnit(const string& unitStr) {
    if (unitStr == "100g") return Unit::hundred_grams;
    if (unitStr == "tbsp") return Unit::tbsp;
    if (unitStr == "liter") return Unit::liter;
    if (unitStr == "quantity") return Unit::quantity;
    throw invalid_argument("Unknown unit string");
}

Food foodlist[50] = {
    // Meats
    {"Chicken Breast", 1, Unit::hundred_grams, 165, 31, 0, 3.6},
    {"Beef", 2, Unit::hundred_grams, 250, 26, 0, 17},
    {"Pork", 3, Unit::hundred_grams, 242, 27, 0, 14},
    {"Salmon", 4, Unit::hundred_grams, 208, 22, 0, 13},
    {"Turkey", 5, Unit::hundred_grams, 135, 30, 0, 1.5},

    // Grains
    {"Rice", 6, Unit::hundred_grams, 130, 2.7, 28, 0.3},
    {"Oats", 7, Unit::hundred_grams, 389, 16.9, 66.3, 6.9},
    {"Quinoa", 8, Unit::hundred_grams, 120, 4.1, 21.3, 1.9},
    {"Barley", 9, Unit::hundred_grams, 354, 12, 73.5, 2.3},
    {"Wheat", 10, Unit::hundred_grams, 339, 13, 71, 2.5},

    // Fruits
    {"Apple", 11, Unit::quantity, 95, 0.5, 25, 0.3},
    {"Banana", 12, Unit::quantity, 105, 1.3, 27, 0.3},
    {"Orange", 13, Unit::quantity, 62, 1.2, 15.4, 0.2},
    {"Strawberries", 14, Unit::hundred_grams, 32, 0.8, 7.7, 0.3},
    {"Blueberries", 15, Unit::hundred_grams, 57, 0.7, 14.5, 0.3},

    // Dry Fruits
    {"Almonds", 16, Unit::hundred_grams, 579, 21.2, 21.6, 49.9},
    {"Cashews", 17, Unit::hundred_grams, 553, 18.2, 30.2, 43.8},
    {"Walnuts", 18, Unit::hundred_grams, 654, 15.2, 13.7, 65.2},
    {"Pistachios", 19, Unit::hundred_grams, 562, 20.2, 28, 45},
    {"Dates", 20, Unit::hundred_grams, 277, 1.8, 75, 0.2},

    // Fast Foods
    {"Burger", 21, Unit::quantity, 354, 17, 30, 20},
    {"Pizza", 22, Unit::quantity, 285, 12, 36, 10},
    {"Fries", 23, Unit::hundred_grams, 312, 3.4, 41.4, 15},
    {"Fried Chicken", 24, Unit::quantity, 400, 28, 12, 24},
    {"Hot Dog", 25, Unit::quantity, 150, 5, 1, 13},

    // Vegetables
    {"Broccoli", 26, Unit::hundred_grams, 34, 2.8, 6.6, 0.4},
    {"Spinach", 27, Unit::hundred_grams, 23, 2.9, 3.6, 0.4},
    {"Carrot", 28, Unit::hundred_grams, 41, 0.9, 9.6, 0.2},
    {"Potato", 29, Unit::hundred_grams, 77, 2, 17, 0.1},
    {"Tomato", 30, Unit::hundred_grams, 18, 0.9, 3.9, 0.2},

    // Dairy
    {"Milk", 31, Unit::liter, 42, 3.4, 4.8, 1},
    {"Cheese", 32, Unit::hundred_grams, 402, 25, 1.3, 33},
    {"Yogurt", 33, Unit::hundred_grams, 59, 3.5, 4.1, 3.3},
    {"Butter", 34, Unit::hundred_grams, 717, 0.9, 0.1, 81},
    {"Ice Cream", 35, Unit::hundred_grams, 207, 3.5, 24, 11},

    // Miscellaneous
    {"Eggs", 36, Unit::quantity, 68, 6, 0.6, 4.8},
    {"Tofu", 37, Unit::hundred_grams, 144, 15.7, 1.9, 8.0},
    {"Peanut Butter", 38, Unit::tbsp, 94, 3.6, 3.2, 8.0},
    {"Honey", 39, Unit::tbsp, 64, 0.1, 17.3, 0},
    {"Olive Oil", 40, Unit::tbsp, 119, 0, 0, 13.5},

    // Beans & Legumes
    {"Black Beans", 41, Unit::hundred_grams, 339, 21.6, 62.4, 0.9},
    {"Lentils", 42, Unit::hundred_grams, 353, 25.8, 63.3, 1.1},
    {"Chickpeas", 43, Unit::hundred_grams, 364, 19.3, 60.6, 6.0},
    {"Kidney Beans", 44, Unit::hundred_grams, 333, 23.6, 60.4, 0.8},
    {"Soybeans", 45, Unit::hundred_grams, 446, 36.5, 30.2, 19.9},

    // Beverages
    {"Orange Juice", 46, Unit::liter, 45, 1, 10.4, 0.2},
    {"Apple Juice", 47, Unit::liter, 46, 0.2, 11.4, 0.1},
    {"Coffee", 48, Unit::liter, 2, 0.3, 0, 0},
    {"Tea", 49, Unit::liter, 1, 0.1, 0.3, 0},
    {"Lemonade", 50, Unit::liter, 40, 0.1, 10, 0.1}
};

vector<exercisedata> Chest = {
    {"Barbell Bench Press", 3, 5, 2},
    {"Dumbbell Bench Press", 4, 5, 2},
    {"Machine Chest Press", 1, 3, 5},
    {"Cable Chest Fly", 2, 4, 3},
    {"Push-ups", 3, 4, 2},
    {"Incline Dumbbell Press", 4, 5, 2},
    {"Cable Chest Press", 2, 3, 3},
    {"Pec Deck Machine", 1, 2, 5},
    {"Dips", 3, 5, 2},
    {"Incline Barbell Press", 3, 5, 2},
    {"Chest Press Machine", 1, 3, 5},
    {"Cable Low-to-High Fly", 2, 4, 3}
};

vector<exercisedata> Shoulders = {
    {"Barbell Overhead Press", 3, 5, 2},
    {"Dumbbell Lateral Raise", 4, 2, 3},
    {"Machine Shoulder Press", 1, 3, 5},
    {"Cable Lateral Raise", 2, 2, 3},
    {"Arnold Press", 4, 5, 2},
    {"Dumbbell Front Raise", 4, 2, 3},
    {"Machine Lateral Raise", 1, 2, 5},
    {"Push Press", 3, 5, 2},
    {"Cable Front Raise", 2, 2, 3},
    {"Face Pulls", 2, 3, 4},
    {"Overhead Dumbbell Press", 4, 5, 2},
    {"Seated Shoulder Press Machine", 1, 3, 5}
};

vector<exercisedata> Triceps = {
    {"Tricep Dips", 3, 5, 2},
    {"Close-Grip Bench Press", 3, 5, 2},
    {"Tricep Pushdowns", 2, 2, 4},
    {"Dumbbell Overhead Tricep Extension", 4, 2, 3},
    {"Skull Crushers", 4, 5, 2},
    {"Cable Overhead Tricep Extension", 2, 2, 3},
    {"Machine Tricep Press", 1, 2, 5},
    {"Diamond Push-ups", 3, 5, 2},
    {"Kickbacks", 4, 2, 3},
    {"Overhead Rope Extension", 2, 2, 4},
    {"Seated Machine Dip", 1, 3, 5},
    {"One-Arm Dumbbell Kickback", 4, 2, 3}
};

vector<exercisedata> Lats = {
    {"Pull-ups", 3, 5, 2},
    {"Lat Pulldown", 2, 3, 4},
    {"Seated Cable Rows", 2, 3, 4},
    {"Barbell Rows", 3, 5, 2},
    {"Dumbbell Rows", 4, 5, 2},
    {"T-Bar Rows", 3, 5, 2},
    {"One-Arm Dumbbell Row", 4, 5, 2},
    {"Inverted Rows", 3, 4, 2},
    {"Machine Pulldown", 1, 3, 5},
    {"Straight Arm Pulldown", 2, 2, 4},
    {"Assisted Pull-ups", 1, 3, 5},
    {"Chest-Supported Row Machine", 1, 3, 5}
};

vector<exercisedata> MidBack = {
    {"Barbell Rows", 3, 5, 2},
    {"Seated Cable Rows", 2, 3, 4},
    {"T-Bar Rows", 3, 5, 2},
    {"Dumbbell Rows", 4, 5, 2},
    {"Machine Rows", 1, 3, 5},
    {"Chest-Supported Rows", 1, 3, 5},
    {"Inverted Rows", 3, 4, 2},
    {"Landmine Rows", 3, 5, 2},
    {"Reverse Pec Deck", 1, 2, 5},
    {"Single-Arm Cable Rows", 2, 3, 4},
    {"Low Pulley Rows", 2, 3, 4},
    {"Smith Machine Rows", 1, 3, 5}
};

vector<exercisedata> Biceps = {
    {"Barbell Curl", 4, 2, 3},
    {"Dumbbell Curl", 4, 2, 3},
    {"Preacher Curl", 4, 2, 3},
    {"Hammer Curl", 4, 2, 3},
    {"Cable Bicep Curl", 2, 2, 4},
    {"Concentration Curl", 4, 2, 3},
    {"Machine Bicep Curl", 1, 2, 5},
    {"Incline Dumbbell Curl", 4, 2, 3},
    {"EZ Bar Curl", 4, 2, 3},
    {"Spider Curl", 4, 2, 3},
    {"Seated Cable Curl", 2, 2, 4},
    {"Single-Arm Preacher Curl Machine", 1, 2, 5}
};

vector<exercisedata> Quads = {
    {"Barbell Back Squat", 3, 5, 2},
    {"Leg Press", 1, 5, 5},
    {"Lunges", 3, 5, 2},
    {"Bulgarian Split Squat", 4, 5, 2},
    {"Leg Extension", 1, 2, 5},
    {"Hack Squat", 3, 5, 2},
    {"Dumbbell Step-ups", 4, 5, 2},
    {"Smith Machine Squats", 1, 5, 5},
    {"Front Squats", 3, 5, 2},
    {"Goblet Squat", 4, 4, 3},
    {"Cable Step-Ups", 2, 3, 4},
    {"Split Squat Machine", 1, 3, 5}
};

vector<exercisedata> Hamstring = {
    {"Romanian Deadlift", 3, 5, 2},
    {"Leg Curls", 1, 2, 5},
    {"Glute-Ham Raise", 4, 5, 2},
    {"Dumbbell Deadlift", 4, 5, 2},
    {"Kettlebell Swings", 4, 5, 2},
    {"Sumo Deadlift", 3, 5, 2},
    {"Machine Leg Curl", 1, 2, 5},
    {"Stiff-Legged Deadlift", 3, 5, 2},
    {"Cable Leg Curls", 2, 2, 4},
    {"Seated Leg Curl Machine", 1, 2, 5},
    {"Single-Leg Deadlift", 4, 5, 2},
    {"Hamstring Curl (Stability Ball)", 2, 2, 4}
};

vector<exercisedata> Glutes = {
    {"Hip Thrust", 1, 5, 5},
    {"Barbell Squat", 3, 5, 2},
    {"Bulgarian Split Squat", 4, 5, 2},
    {"Lunges", 3, 5, 2},
    {"Glute Kickback", 2, 2, 4},
    {"Deadlift", 3, 5, 2},
    {"Step-ups", 4, 5, 2},
    {"Kettlebell Swings", 4, 5, 2},
    {"Leg Press", 1, 5, 5},
    {"Glute Bridge", 1, 3, 5},
    {"Cable Glute Kickback", 2, 2, 4},
    {"Sumo Squat", 3, 5, 2}
};


bool compareExercises(const exercisedata& a, const exercisedata& b, GoalType goal) {
    switch (goal) {
    case GoalType::Hypertrophy:
        // Prioritize highest ability to reach failure, then cooperation, then stability
        if (a.abilitytoreachfailure != b.abilitytoreachfailure) return a.abilitytoreachfailure > b.abilitytoreachfailure;
        if (a.cooperatingandcompounddemand != b.cooperatingandcompounddemand) return a.cooperatingandcompounddemand > b.cooperatingandcompounddemand;
        return a.stabilitydemand > b.stabilitydemand;

    case GoalType::Sports:
        // Prioritize stability, then cooperation, then ability to reach failure
        if (a.stabilitydemand != b.stabilitydemand) return a.stabilitydemand > b.stabilitydemand;
        if (a.cooperatingandcompounddemand != b.cooperatingandcompounddemand) return a.cooperatingandcompounddemand > b.cooperatingandcompounddemand;
        return a.abilitytoreachfailure > b.abilitytoreachfailure;

    case GoalType::Hybrid:
        // Balance between cooperation, stability, and ability to reach failure
        if (a.cooperatingandcompounddemand != b.cooperatingandcompounddemand) return a.cooperatingandcompounddemand > b.cooperatingandcompounddemand;
        if (a.stabilitydemand != b.stabilitydemand) return a.stabilitydemand > b.stabilitydemand;
        return a.abilitytoreachfailure > b.abilitytoreachfailure;

    case GoalType::Powerlifting:
        // Prioritize stability, then ability to reach failure, then cooperation
        if (a.stabilitydemand != b.stabilitydemand) return a.stabilitydemand > b.stabilitydemand;
        if (a.abilitytoreachfailure != b.abilitytoreachfailure) return a.abilitytoreachfailure > b.abilitytoreachfailure;
        return a.cooperatingandcompounddemand > b.cooperatingandcompounddemand;

    case GoalType::EnduranceSports:
        // Focus on lower ability to reach failure, then cooperation, then stability
        if (a.abilitytoreachfailure != b.abilitytoreachfailure) return a.abilitytoreachfailure < b.abilitytoreachfailure;
        if (a.cooperatingandcompounddemand != b.cooperatingandcompounddemand) return a.cooperatingandcompounddemand > b.cooperatingandcompounddemand;
        return a.stabilitydemand > b.stabilitydemand;

    default:
        return false; // In case of an invalid goal type
    }
}

vector<exercisedata> sortExercisesByGoal(GoalType goal, vector<exercisedata>& exercises) {
    sort(exercises.begin(), exercises.end(), [&goal](const exercisedata& a, const exercisedata& b) {
        return compareExercises(a, b, goal);
        });
    return exercises;
}

void pushBackElements(vector<exercisedata>& vec, const vector<exercisedata>& temp, int i) {
    if (i == 1 && temp.size() >= 2) {
        vec.push_back(temp.at(0));
        vec.push_back(temp.at(3));
    }
    else if (i == 2 && temp.size() >= 4) {
        vec.push_back(temp.at(1));
        vec.push_back(temp.at(4));
    }
    else if (i == 3 && temp.size() >= 6) {
        vec.push_back(temp.at(2));
        vec.push_back(temp.at(5));
    }
}

class User {
public:
    string name;
    int id;
    Uservariables user;
    int dayincycle;
    FoodGoal foodtoday;

    void updateandcreatedatafile() {
        string filename = to_string(id) + ".txt";
        ofstream file(filename);
        if (file.is_open()) {
            file << name << endl;
            file << id << endl;
            file << dayincycle << endl;
            file << user.age << endl;
            file << user.gender << endl;
            file << user.heightincm << endl;
            file << user.weightinkg << endl;
            file << GoalToString(user.goal) << endl;
            file << user.leveloftraining << endl;
            file << foodtoday.calories << endl;
            file << foodtoday.carbohydrated << endl;
            file << foodtoday.fats << endl;
            file << foodtoday.protein << endl;

            cout << "File updated or created" << endl;
        }

    }

    User(string n, int i, int l, GoalType g, int d,bool gen,int weigh,int heigh,int a) {
        name = n;
        id = i;
        user.leveloftraining = l;
        user.goal = g;
        dayincycle = d;
        user.gender = gen;
        user.weightinkg = weigh;
        user.heightincm = heigh;
        user.age = a;
        foodtoday.calories = 0;
        foodtoday.carbohydrated = 0;
        foodtoday.fats = 0;
        foodtoday.protein = 0;
        
        updateandcreatedatafile();
        
    }
    
    vector<exercisedata> createworkout() {
        vector<exercisedata> returnvector;
        vector<exercisedata> temp;

        if (dayincycle == 1 || dayincycle == 4 || dayincycle == 7) {
            int j;
            if (dayincycle == 1) j = 1;
            else if (dayincycle == 4) j = 2;
            else if (dayincycle == 7) j = 3;


            temp = (sortExercisesByGoal(user.goal, Chest));
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, Shoulders);
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, Triceps);
            pushBackElements(returnvector, temp, j);
        }
        else if (dayincycle == 2 || dayincycle == 5 || dayincycle == 8) {
            int j;
            if (dayincycle == 2) j = 1;
            else if (dayincycle == 5) j = 2;
            else if (dayincycle == 8) j = 3;


            temp = (sortExercisesByGoal(user.goal, Lats));
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, MidBack);
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, Biceps);
            pushBackElements(returnvector, temp, j);
        }
        else if (dayincycle == 3 || dayincycle == 6 || dayincycle == 9) {
            int j;
            if (dayincycle == 3) j = 1;
            else if (dayincycle == 6) j = 2;
            else if (dayincycle == 9) j = 3;


            temp = (sortExercisesByGoal(user.goal, Quads));
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, Hamstring);
            pushBackElements(returnvector, temp, j);

            temp = sortExercisesByGoal(user.goal, Glutes);
            pushBackElements(returnvector, temp, j);
        }

        return returnvector;

    }
    vector<Exercise> createeworkout() {
        vector<exercisedata> data = createworkout();
        vector<Exercise> today;
        for (int i = 0; i < data.size(); i++) {
            today.push_back(Exercise{
                data[i].name,
                user.leveloftraining,
                (12 / data[i].stabilitydemand) +
                (12 / data[i].cooperatingandcompounddemand) +
                static_cast<int>(1.5 * data[i].stabilitydemand)
                });
        }

        return today;

    };

    FoodGoal calculatinggoals() {
        FoodGoal foodcalculation;
        foodcalculation.calories = (15 * user.weightinkg) + (6 * user.heightincm) - (5 * user.age);
        if (!user.gender) foodcalculation.calories -= 200;
        switch (user.goal)
        {
        case GoalType::Hypertrophy:
            foodcalculation.protein = (0.25 * (foodcalculation.calories / 4));
            foodcalculation.carbohydrated = (0.55 * (foodcalculation.calories / 4));
            foodcalculation.fats = (0.30 * (foodcalculation.calories / 8));
            break;
        case GoalType::Powerlifting:
            foodcalculation.calories *= 1.5;
            foodcalculation.protein = (0.25 * (foodcalculation.calories / 4));
            foodcalculation.carbohydrated = (0.65 * (foodcalculation.calories / 4));
            foodcalculation.fats = (0.20 * (foodcalculation.calories / 8));

            break;
        case GoalType::Hybrid:
            foodcalculation.protein = (0.2 * (foodcalculation.calories / 4));
            foodcalculation.carbohydrated = (0.6 * (foodcalculation.calories / 4));
            foodcalculation.fats = (0.30 * (foodcalculation.calories / 8));
            break;
        case GoalType::EnduranceSports:
            foodcalculation.calories *= 1.3;
            foodcalculation.protein = (0.25 * (foodcalculation.calories / 4));
            foodcalculation.carbohydrated = (0.65 * (foodcalculation.calories / 4));
            foodcalculation.fats = (0.20 * (foodcalculation.calories / 8));
            break;
        case GoalType::Sports:
            foodcalculation.calories *= 1.2;
            foodcalculation.protein = (0.25 * (foodcalculation.calories / 4));
            foodcalculation.carbohydrated = (0.65 * (foodcalculation.calories / 4));
            foodcalculation.fats = (0.20 * (foodcalculation.calories / 8));

            break;
        default:
            break;
        }
        return foodcalculation;

    }
    void updatecalories(int n, int q) {
        
        foodtoday.calories += (foodlist[n].calories * q);
        foodtoday.protein += (foodlist[n].protein * q);
        foodtoday.carbohydrated += (foodlist[n].carbohydrates * q);
        foodtoday.fats += (foodlist[n].fats * q);

    }
   
};

void frontendfunction(User& user) {
    system("cls");
    char choice;
    FoodGoal goal = user.calculatinggoals();
    cout << "Food Data for today" << endl;
    cout << "Calories: " << user.foodtoday.calories << "/" << goal.calories << endl;
    cout << "Protein: " << user.foodtoday.protein << "/" << goal.protein << endl;
    cout << "Carbohydrates: " << user.foodtoday.carbohydrated << "/" << goal.carbohydrated << endl;
    cout << "Fats: " << user.foodtoday.fats << "/" << goal.fats << endl << endl << endl;

    cout << "Press W for your next workout, F to add to your food eaten today, X to close the app" << endl;
    cin >> choice;
    switch (choice)
    {
    case 'w': {
        char key;
        system("cls");
        vector <Exercise> workouttoday = user.createeworkout();
        for (const auto& exercise : workouttoday) {
            cout << exercise.name << exercise.sets << "*" << exercise.reps << endl;
        }
        user.dayincycle++;
        user.updateandcreatedatafile();
        cout << "Press any key leave at anypoint" << endl;
        cin >> key;
        return;
    }
    case 'f': {
        int eaten, quantity;
        system("cls");
        cout << "Here is the list of foods,Write number of one you ate" << endl;
        
        for (int i = 0; i < 50; ++i) {
            cout << i + 1<< "-" << foodlist[i].name << "  ";
            if (i % 5 == 0) {
                cout << endl;
            }
        }
        cin >> eaten;
        system("cls");
        cout << "How many " << unitToString(foodlist[eaten-1].unit) << " you ate";
        cin >> quantity;
        if (eaten > 0 && eaten < 51) {
            user.updatecalories(eaten - 1, quantity);
            user.updateandcreatedatafile();
        }
        else {
            return;
        }


    }
    case 'x':
        return;

    default:
        break;
    } 
}

int main() {
    int choice;
    cout << "DO you want to login or register? choose 1 for Register, 2 for login" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1: {
        string name;
        int id, leveloftraining, dayincycle, weightinkg, heightincm, age, goalOption;
        bool gender;
        GoalType goal;

        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your ID: ";
        cin >> id;
        cout << "Enter your level of training (1 to 10): ";
        cin >> leveloftraining;
        cout << "Enter your day in cycle: ";
        cin >> dayincycle;
        cout << "Enter your gender (1 for Male, 0 for Female): ";
        cin >> gender;
        cout << "Enter your weight in kg: ";
        cin >> weightinkg;
        cout << "Enter your height in cm: ";
        cin >> heightincm;
        cout << "Enter your age: ";
        cin >> age;

        cout << "Choose your goal:\n";
        cout << "1. Hypertrophy\n";
        cout << "2. Sports\n";
        cout << "3. Hybrid\n";
        cout << "4. Powerlifting\n";
        cout << "5. EnduranceSports\n";
        cout << "Enter your choice (1-5): ";
        cin >> goalOption;

        switch (goalOption) {
        case 1: goal = GoalType::Hypertrophy; break;
        case 2: goal = GoalType::Sports; break;
        case 3: goal = GoalType::Hybrid; break;
        case 4: goal = GoalType::Powerlifting; break;
        case 5: goal = GoalType::EnduranceSports; break;
        default:
            cout << "Invalid choice, defaulting to Hypertrophy.\n";
            goal = GoalType::Hypertrophy;
            break;
        }

        User user(name, id, leveloftraining, goal, dayincycle, gender, weightinkg, heightincm, age);

        cout << "User object created successfully!\n";
        return 0;
    }
    case 2: {
        int id;
        cout << "Give your id: " << endl;
        cin >> id;
        string filename = to_string(id) + ".txt";
        ifstream file(filename);
        if (file.good()) {
            string name;
            int id, dayincycle, age, heightincm, weightinkg, leveloftraining;
            bool gender;
            string goal;
            float calories, carbohydrates, fats, protein;

            // Read values from the file
            file >> name;
            file >> id;
            file >> dayincycle;
            file >> age;
            file >> gender;
            file >> heightincm;
            file >> weightinkg;
            file >> goal;  // assuming you have a way to convert the string to GoalType
            file >> leveloftraining;
            file >> calories;
            file >> carbohydrates;
            file >> fats;
            file >> protein;
            // Create a new User object using the data from the file
            User user(name, id, leveloftraining, stringToGoal(goal), dayincycle, gender, weightinkg, heightincm, age);

            // Update the foodtoday struct
            user.foodtoday.calories = calories;
            user.foodtoday.carbohydrated = carbohydrates;
            user.foodtoday.fats = fats;
            user.foodtoday.protein = protein;

            frontendfunction(user);
            break;
        }
        else if (file.fail()) {
            return 0;
        }
    }
    
    default:
        break;
    }


    return 0;
}





