#include <iostream>
#include <vector>
#include <memory>

class Garniture {
public:
    Garniture(const std::string& nom, double cout) : nom(nom), cout(cout) {}

    // Getters
    std::string getNom() const { return nom; }
    double getCout() const { return cout; }

private:
    std::string nom;
    double cout;
};

class Pizza {
public:
    Pizza(const std::string& nom, double diametre, double prixBase)
        : nom(nom), diametre(diametre), prixBase(prixBase) {}

    virtual double calculerCout() const {
        double coutTotal = prixBase;
        for (const auto& garniture : garnitures) {
            coutTotal += garniture.getCout();
        }
        return coutTotal;
    }

    void ajouterGarniture(const Garniture& garniture) {
        garnitures.push_back(garniture);
    }

    // Getters
    std::string getNom() const { return nom; }
    double getDiametre() const { return diametre; }
    double getPrixBase() const { return prixBase; }
    const std::vector<Garniture>& getGarnitures() const { return garnitures; }

private:
    std::string nom;
    double diametre;
    double prixBase;
    std::vector<Garniture> garnitures;
};

class PetitePizza : public Pizza {
public:
    PetitePizza(const std::string& nom)
        : Pizza(nom, 10.0, 8.0) {} // Valeurs par défaut pour une petite pizza
};

class MoyennePizza : public Pizza {
public:
    MoyennePizza(const std::string& nom)
        : Pizza(nom, 13.0, 11.0) {} // Valeurs par défaut pour une pizza moyenne
};

class GrandePizza : public Pizza {
public:
    GrandePizza(const std::string& nom)
        : Pizza(nom, 16.0, 14.0) {} // Valeurs par défaut pour une grande pizza
};

class Commande {
public:
    void ajouterPizza(const Pizza& pizza) {
        pizzas.push_back(std::make_shared<Pizza>(pizza));
    }

    double calculerCoutTotal() const {
        double coutTotal = 0.0;
        for (const auto& pizza : pizzas) {
            coutTotal += pizza->calculerCout();
        }
        return coutTotal;
    }

    void afficherResume() const {
        std::cout << "Résumé :\n";
        for (const auto& pizza : pizzas) {
            std::cout << "Pizza: " << pizza->getNom() << ", Coût: " << pizza->calculerCout() << "\n";
            const auto& garnitures = pizza->getGarnitures();
            if (!garnitures.empty()) {
                std::cout << "  Garnitures:";
                for (const auto& garniture : garnitures) {
                    std::cout << " " << garniture.getNom() << " (+" << garniture.getCout() << "),";
                }
                std::cout << "\n";
            }
        }
        std::cout << "Coût total : " << calculerCoutTotal() << "\n";
    }

private:
    std::vector<std::shared_ptr<Pizza>> pizzas;
};

void ajouterGarnitures(Pizza* pizza) {
    std::string reponse;
    int nombreGarnituresAjoutees = 0;

    do {
        if (nombreGarnituresAjoutees >= 3) {
            std::cout << "Nombre maximal de garnitures atteint pour cette pizza.\n";
            break;
        }

        std::cout << "Choisissez une garniture (3 max) :\n";
        std::cout << "1. Fromage\n2. Ananas\n3. Steak\n4. Oeuf\n5. Jambon\n6. Champignon\n";

        int choixGarniture;
        std::cout << "Entrez le numéro de votre choix : ";
        std::cin >> choixGarniture;

        std::string nomGarniture;
        double coutGarniture = 0.0;

        switch (choixGarniture) {
            case 1:
                nomGarniture = "Fromage";
                coutGarniture = 2.0;
                break;
            case 2:
                nomGarniture = "Ananas";
                coutGarniture = 4.0;
                break;
            case 3:
                nomGarniture = "Steak";
                coutGarniture = 3.0;
                break;
            case 4:
                nomGarniture = "Oeuf";
                coutGarniture = 2.5;
                break;
            case 5:
                nomGarniture = "Jambon";
                coutGarniture = 2.0;
                break;
            case 6:
                nomGarniture = "Champignon";
                coutGarniture = 1.5;
                break;
            default:
                std::cout << "Choix invalide.\n";
                break;
        }

        Garniture garniture(nomGarniture, coutGarniture);
        pizza->ajouterGarniture(garniture);
        nombreGarnituresAjoutees++;

        std::cout << "Voulez-vous ajouter une autre garniture? (Oui/Non): ";
        std::cin >> reponse;
    } while (reponse == "Oui" || reponse == "oui");
}


int main() {
    Commande commande;

    std::cout << "Bienvenue dans le système de commande de pizzas!\n";

    do {
        std::cout << "Choisissez votre pizza :\n";
        std::cout << "1. Margherita (petite, 8€)\n2. Pepperoni (moyenne, 11€)\n3. Napolitaine (grande, 14€)\n4. Hawaienne (petite, 8€)\n5. Savoyarde (moyenne, 11€)\n";

        int choixPizza;
        std::cout << "Entrez le numéro de votre choix : ";
        std::cin >> choixPizza;

        Pizza* nouvellePizza = nullptr;

        switch (choixPizza) {
            case 1:
                nouvellePizza = new PetitePizza("Margherita");
                break;
            case 2:
                nouvellePizza = new MoyennePizza("Pepperoni");
                break;
            case 3:
                nouvellePizza = new GrandePizza("Napolitaine");
                break;
            case 4:
                nouvellePizza = new PetitePizza("Hawaienne");
                break;
            case 5:
                nouvellePizza = new MoyennePizza("Savoyarde");
                break;
            default:
                std::cout << "Choix invalide.\n";
                break;
        }

        if (nouvellePizza != nullptr) {
            // Ajout de garnitures
            ajouterGarnitures(nouvellePizza);

            // Ajout de la pizza à la commande
            commande.ajouterPizza(*nouvellePizza);

            // Libération de la mémoire allouée dynamiquement
            delete nouvellePizza;
        }

        std::cout << "Voulez-vous ajouter une autre pizza à la commande? (Oui/Non): ";
        std::string reponse;
        std::cin >> reponse;

        if (reponse != "Oui" && reponse != "oui") {
            break;
        }

    } while (true);

    // Affichage du résumé de la commande
    commande.afficherResume();

    return 0;
}
