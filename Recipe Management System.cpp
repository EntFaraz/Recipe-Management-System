#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Recipe {
    string name;
    vector<string> ingredients;
    string instructions;
};

class RecipeManager {
private:
    vector<Recipe> recipes;

public:
    void addRecipe(const string name, const vector<string> ingredients, const string instructions) {
        Recipe r;
        r.name = name;
        r.ingredients = ingredients;
        r.instructions = instructions;
        recipes.push_back(r);
    }

    void viewRecipes() const {
        for (size_t i = 0; i < recipes.size(); ++i) {
            cout << "Recipe: " << recipes[i].name << "\nIngredients: ";
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                cout << recipes[i].ingredients[j];
                if (j < recipes[i].ingredients.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "\nInstructions: " << recipes[i].instructions << "\n\n";
        }
    }

    void saveToFile(const string filename) const {
        ofstream file(filename.c_str());
        if (file.is_open()) {
            for (size_t i = 0; i < recipes.size(); ++i) {
                file << recipes[i].name << "\n";
                for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                    file << recipes[i].ingredients[j];
                    if (j < recipes[i].ingredients.size() - 1) {
                        file << ",";
                    }
                }
                file << "\n" << recipes[i].instructions << "\n";
            }
            file.close();
        } else {
            cout << "Error opening file for writing." << endl;
        }
    }

    void loadFromFile(const string filename) {
        ifstream file(filename.c_str());
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string name = line;
                getline(file, line);
                vector<string> ingredients;
                size_t pos = 0;
                while ((pos = line.find(',')) != string::npos) {
                    ingredients.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                string instructions;
                getline(file, instructions);
                addRecipe(name, ingredients, instructions);
            }
            file.close();
        } else {
            cout << "Error opening file for reading." << endl;
        }
    }
};

int main() {
    RecipeManager manager;
    manager.loadFromFile("recipes.txt");

    int choice;
    do {
        cout << "1. Add Recipe\n2. View Recipes\n3. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, ingredient, instructions;
            vector<string> ingredients;
            cout << "Enter recipe name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter ingredients (comma separated): ";
            getline(cin, ingredient);
            size_t pos = 0;
            while ((pos = ingredient.find(',')) != string::npos) {
                ingredients.push_back(ingredient.substr(0, pos));
                ingredient.erase(0, pos + 1);
            }
            cout << "Enter instructions: ";
            getline(cin, instructions);
            manager.addRecipe(name, ingredients, instructions);
        } else if (choice == 2) {
            manager.viewRecipes();
        }
    } while (choice != 3);

    manager.saveToFile("recipes.txt");
    return 0;
}
