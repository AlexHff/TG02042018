#include "Differe.h"

bool isInt(std::string s) {
    int firstZeroes = 0;
    bool firstOtherThanZeroFound = false;
    for (unsigned int i = 0; i < s.size(); i++) {
        // si on a un carac diff de 0 et qu'on n'en avait pas trouve avant, on sait qu'on a trouve le premier carac diff de 0
        if (s[i] != '0' && !firstOtherThanZeroFound) {
            firstOtherThanZeroFound = true;
        }
        // si carac est 0 et qu'on n'a pas encore lu autre chose que des zeros on incremente le compteur de zeros en debut
        if (s[i] == '0' && !firstOtherThanZeroFound) {
            firstZeroes++;
        }
        if (s[i] > '9' || s[i] < '0') {
            return false;
        }
    }

    return (firstZeroes == 0);
}

void preparePlot(BITMAP * graphique, int maxVal, int duree) {
    // dessin des axes
    line(graphique, 100, graphique->h - 100, graphique->w - 100, graphique->h - 100, makecol(0, 0, 0));
    line(graphique, graphique->w - 100, graphique->h - 100, graphique->w - 110, graphique->h - 110, makecol(0, 0, 0));
    line(graphique, graphique->w - 100, graphique->h - 100, graphique->w - 110, graphique->h - 90, makecol(0, 0, 0));
    textout_ex(graphique, font, "Temps", graphique->w - 90, graphique->h - 100, NOIR, BLANC);

    line(graphique, 100, graphique->h - 100, 100, 100, makecol(0, 0, 0));
    line(graphique, 100, 100, 110, 110, makecol(0, 0, 0));
    line(graphique, 100, 100, 90, 110, makecol(0, 0, 0));
    textout_centre_ex(graphique, font, "Quantite", 100, 90, NOIR, BLANC);

    // legendes
    /// horizontales
    int divUnit = 0;
    if (duree <= 10) divUnit = 1;
    if (duree > 10 && duree < 200) divUnit = 10;
    if (duree >= 200 && duree < 500) divUnit = 50;
    if (duree >= 500) divUnit = 100;
    int lar = graphique->w - 200;
    int unitW = (int)((float)lar / ((float)duree / (float)divUnit));

    for (unsigned int i = 0; i * unitW < lar; i++) {
        line(graphique, 100 + i * unitW, graphique->h - 100, 100 + i * unitW, graphique->h - 90, makecol(0, 0, 0));
        textout_centre_ex(graphique, font, std::to_string(i * divUnit).c_str(), 100 + i * unitW, graphique->h - 80, NOIR, BLANC);
    }

    /// verticales
    if (maxVal <= 10) divUnit = 1;
    if (maxVal > 10 && maxVal < 200) divUnit = 10;
    if (maxVal >= 200 && maxVal < 500) divUnit = 50;
    if (maxVal >= 500) divUnit = 100;
    int haut = graphique->h - 200;
    int unitH = (int)((float)haut / ((float)maxVal / (float)divUnit));

    for (unsigned int i = 0; i * unitH < haut; i++) {
        line(graphique, 100, graphique->h - 100 - i * unitH, 90, graphique->h - 100 - i * unitH, makecol(0, 0, 0));
        textout_centre_ex(graphique, font, std::to_string(i * divUnit).c_str(), 80, graphique->h - 100 - i * unitH, NOIR, BLANC);
    }

}

void valsToCoords(BITMAP * graphique, int maxVal, int duree, int * x, int * y, int xval, int yval) {
    int lar = graphique->w - 200;
    int haut = graphique->h - 200;
    *x = 100 + (int)((float)lar / ((float)duree / (float)xval));
    *y = graphique->h - 100 - (int)((float)haut / ((float)maxVal / (float)yval));
}

void differe() {
    int duree = 0;
    int maxVal = 1000;
    BITMAP * graphique = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(graphique, makecol(255, 255, 255));
    while (duree == 0) {
        std::string res;
        std::cout << "Combien de temps doit durer la simulation ?" << std::endl;
        std::cin >> res;
        if (isInt(res)) duree = std::stoi(res);
    }
    std::cout << "Creation du graphique pour " << duree << " etapes..." << std::endl;

    preparePlot(graphique, maxVal, duree);

    /////////////////////////////////////////
    /// DESSIN DES POINTS DU GRAPHIQUE ///
    /////////////////////////////////////////



    /////////////////////////////////////////
    ///    FIN DU DESSIN DES POINTS    ///
    /////////////////////////////////////////

    // affichage du graphique final
    clear_to_color(screen, makecol(255, 255, 255));
    blit(graphique, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    std::cout << "Appuyer sur ENTREE pour continuer" << std::endl;
    while ( !key[KEY_ENTER] ) { }
    std::cout << "Retour a l'affichage classique" << std::endl;
}
