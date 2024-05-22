#ifndef _DISPLAY_H
#define _DISPLAY_H 

#include "ia.hpp"

/*
Pour faciliter l'affichage et simplifier certaines parties, nous créons différentes classes. 
Elles seront réparties de manière à avoir une partie Game et une partie Menu/Option.

Game:
- Player : pour tout ce qui concerne le joueur.
- Grid : pour la construction de la grille de jeu.
- Wall : pour les murs.
- Game : pour faire fonctionner l'ensemble.

Menu:
Pour rendre le menu simple et interactif, nous créons une classe Boutons et zones de Texte qui seront appelés dans la classe Menu.
*/

// Classe Player qui représente un joueur dans le jeu
class Player: public sf::Drawable {
	private:
        int taille_tile; // unité de distance en pixels
        sf::Vector2u size; // taille du joueur
        bool sp = false; // vrai si une image est chargée, sinon false
		sf::CircleShape cercle; // forme par défaut
		sf::Sprite sprite; // sprite pour le joueur
    	sf::Texture texture; // texture pour le sprite
        Coord coord; // coordonnées x et y du joueur

		// Méthode pour dessiner le joueur
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if(!sp)
                target.draw(cercle, states); // dessine un cercle si aucune image n'est chargée
            else
                target.draw(sprite, states); // sinon, dessine le sprite
        }

	public:
        int id, nbr_wall; // id pour identifier le joueur, nbr_wall pour le nombre de murs

		// Initialisation du joueur avec une image
		void init(int taille_tile, int id, string name);

		// Initialisation du joueur par default (le cercle)avec une couleur
		void init(int taille_tile, int id, sf::Color color);

        Coord getCoord() { return coord; } // Retourne les coordonnées du joueur
        void setCoord(int x, int y); // Définit les coordonnées du joueur
        void moveDir(int bit, int saute=1); // Déplace le joueur dans une direction
        void updatePosition(); // Met à jour la position du joueur
};

// Classe Grid qui représente la grille de jeu
class Grid: public sf::Drawable {
    private:
        sf::VertexArray hlines; // lignes horizontales de la grille
        sf::VertexArray vlines; // lignes verticales de la grille
        int taille_tile; // taille des tuiles de la grille

    public:
        void set(int taille, int hauteur, int largeur); // Définit les dimensions de la grille

		// Méthode pour dessiner la grille
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(hlines, states); // dessine les lignes horizontales
            target.draw(vlines, states); // dessine les lignes verticales
        }
};

// Classe Wall qui représente un mur dans le jeu
class Wall: public sf::Drawable {
    private:
        int epaisseur = 15; // épaisseur du mur
        sf::RectangleShape rectangle; // forme rectangulaire pour le mur
        sf::Vector2u size; // taille du mur
        bool sp = false; // vrai si une image est chargée, sinon false
        sf::Sprite sprite; // sprite pour le mur
    	sf::Texture texture; // texture pour le sprite

    public:
        // Constructeurs pour initialiser un mur
        Wall(int taille = 0, int x = 0, int y = 0, int dir = 0, string name = "");//avec image 
        Wall(int taille = 0, int x = 0, int y = 0, int dir = 0, sf::Color color = sf::Color::Red);//sans image 

		// Méthode pour dessiner le mur
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if(!sp)
                target.draw(rectangle, states); // dessine un rectangle si aucune image n'est chargée
            else
                target.draw(sprite, states); // sinon, dessine le sprite
        }
};

// Classe Fond qui représente le fond du jeu
class Fond: public sf::Drawable {
    private:
        sf::Texture back; // texture pour le fond
        sf::Sprite background; // sprite pour le fond

		// Méthode pour dessiner le fond
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(background, states);
        }

    public:
        void set(string name, int largeur, int hauteur); // Définit le fond avec une image
};

// Classe Texte pour gérer les textes affichés
class Texte: public sf::Drawable {
    private:
        sf::Text text; // texte affiché
        sf::Color color; // couleur du texte
        int xx, yy; // position du texte

		// Méthode pour dessiner le texte
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(text, states);
        }

    public:
        void set(string str, sf::Font& font, int z, int x, int y); // Définit le texte avec une police
        void set_text(string tex); // Met à jour le contenu du texte
        void set_Color(sf::Color color); // Change la couleur du texte
};

// Classe Game qui gère l'ensemble du jeu
class Game {
    private:
        // Fenêtre de jeu
        sf::RenderWindow window;
        sf::Vector2i position;
        Fond F_jeu;
        // Texte affiché
        int T_size = 30;
        Texte T_IA, T_Pl, T_fini;

        // Joueurs
        Player p1, robot;
        int p1_id = 0, robot_id = 1, difi;
        bool tour = false, finish = false;

        // Grille
        Grid grid;
        int taille_tile = 100;
        int largeur, hauteur;
        int largeur_px, hauteur_px;
        int x, y, nbr_wall_poser = 0, nbr_wall_ini;
        Board board;
        vector<Wall*> walls;

        // Fonctions internes
        void verif(int id);
        void actionIA();
        int calc_dir(int x, int y, double xx, double yy);
        int event();
        void display();
        void displayFini(int id);

    public:
        // Initialisation du jeu
        void set(sf::Font& font, int largeur = 5, int hauteur = 10, int nbr_wall = 5, int difi = 3);
        void Run(); // Démarre le jeu
        void Delete(); // Supprime les éléments du jeu
};

// Classe Bouton pour gérer les boutons dans le menu
class Bouton : public sf::Drawable {
    private:
        sf::Text text; // texte du bouton
        sf::RectangleShape rec; // forme rectangulaire du bouton
        sf::Color cool, surcool, select; // couleurs pour les différents états du bouton
        static int cocher; // état coché
        int id; // identifiant du bouton

		// Méthode pour dessiner le bouton
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rec, states);
            target.draw(text, states);
        }

    public:
        Bouton();
        void setId(int id = -2); // Définit l'id du bouton
        int getCocher(); // Retourne l'état coché
        void set_bouton(const std::string& str, sf::Font& font, int largeur, int hauteur, float x, float y); // Initialise un bouton
        void set_fleche(const std::string& str, sf::Font& font, int size, float x, float y); // Initialise une flèche
        bool isHover(const sf::RenderWindow& window); // Vérifie si la souris est sur le bouton
        bool isClick(const sf::RenderWindow& window, bool o = false); // Vérifie si le bouton est cliqué
        void update(const sf::RenderWindow& window); // Met à jour l'état du bouton
};

// Classe Menu pour gérer le menu principal et les options
class Menu {
    private:
        sf::RenderWindow window; // fenêtre du menu
        sf::VideoMode fenetre; // mode vidéo de la fenêtre

        Fond FondMenu, FondOption; // fonds pour le menu et les options

        Game* g; // pointeur vers le jeu
        int largeurmenu, hauteurmenu; // dimensions du menu
        int taille_fleche = 40; // taille des flèches
        int hauteur_bouton = 50, largeur_bouton = 200; // dimensions des boutons
        bool option = false; // état des options
        sf::Font font; // police de caractère

        // Pour le menu
        Texte T_Titre_Jeu; // titre du jeu
        Bouton playButton, optionsButton, quitButton; // boutons du menu principal

        // Pour les paramètres
        Bouton flecheup, flechedown, retourButton; // boutons pour les options
        Bouton B_Largeur, B_Hauteur, B_nbrMur, B_dific; // boutons pour les paramètres
        Texte T_Titre_Params, T_Largeur, T_Hauteur, T_nbrMur, T_dific; // textes pour les paramètres

        int largeur = 5, hauteur = 5, nbrMur = int(10/144 *(largeur+hauteur+0.5)), dific = 4; // paramètres par défaut
        void updateOption(); // Met à jour les options
        void isClickiOption(); // Gère les clics dans les options
        void updateMenu(); // Met à jour le menu
        void isClickiMenu(); // Gère les clics dans le menu
        void creerwindow(); // Crée la fenêtre
        void displayMenu(); // Affiche le menu
        void displayOption(); // Affiche les options

    public:
        Menu(int largeurmenu = 800, int hauteurmenu = 600); // Constructeur/initialisation du menu
        int start(); // Démarre
};

#endif
