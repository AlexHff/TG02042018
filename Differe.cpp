#include "Differe.h"

int findMaxVal(Graph workg, int duree) {
    clear_to_color(screen, BLANC);
    Graph g = workg;
    int maxVal = 0;
    std::cout << "Recherche de la population maximale sur l'intervalle de temps." << std::endl;
    for (unsigned int i = 0; i < duree; i++) {
        for(auto &e : g.getVertices()) {
            int nb = e.second.getPopulation();
            if (nb > maxVal) {
                maxVal = nb;
            }
        }
        g.update_pop();
        if (i % 100 == 0) rectfill(screen, 0, 0, mapInt(i, 0, duree, 0, SCREEN_W), 10, ORANGE);
    }
    std::cout << "\tValeur max : " << maxVal << std::endl;
    return maxVal;
}

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
    clear_to_color(screen, BLANC);
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
    if (duree >= 500 && duree < 2000) divUnit = 100;
    if (duree >= 2000 && duree < 5000) divUnit = 500;
    if (duree >= 5000 && duree < 20000) divUnit = 1000;
    if (duree >= 20000 && duree < 50000) divUnit = 5000;
    if (duree >= 50000 && duree < 200000) divUnit = 10000;
    if (duree >= 200000 && duree < 500000) divUnit = 50000;
    if (duree >= 500000) divUnit = 100000;
    int lar = graphique->w - 200;
    int unitW = (int)((float)lar / ((float)duree / (float)divUnit));

    for (unsigned int i = 0; i * unitW < lar; i++) {
        line(graphique, 100 + i * unitW, graphique->h - 100, 100 + i * unitW, graphique->h - 90, makecol(0, 0, 0));
        line(graphique, 100 + i * unitW, graphique->h - 100, 100 + i * unitW, 100, 0xEEEEEE);
        textout_centre_ex(graphique, font, std::to_string(i * divUnit).c_str(), 100 + i * unitW, graphique->h - 80, NOIR, BLANC);
    }

    /// verticales
    if (maxVal <= 10) divUnit = 1;
    if (maxVal > 10 && maxVal < 200) divUnit = 10;
    if (maxVal >= 200 && maxVal < 500) divUnit = 50;
    if (maxVal >= 500 && maxVal < 2000) divUnit = 100;
    if (maxVal >= 2000 && maxVal < 5000) divUnit = 500;
    if (maxVal >= 5000 && maxVal < 20000) divUnit = 1000;
    if (maxVal >= 20000) divUnit = 5000;
    int haut = graphique->h - 200;
    int unitH = (int)((float)haut / ((float)maxVal / (float)divUnit));

    for (unsigned int i = 0; i * unitH < haut; i++) {
        line(graphique, 100, graphique->h - 100 - i * unitH, 90, graphique->h - 100 - i * unitH, makecol(0, 0, 0));
        line(graphique, 100, graphique->h - 100 - i * unitH, graphique->w - 100, graphique->h - 100 - i * unitH, 0xEEEEEE);
        textout_centre_ex(graphique, font, std::to_string(i * divUnit).c_str(), 80, graphique->h - 100 - i * unitH, NOIR, BLANC);
    }
    blit(graphique, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

int mapInt(int val, int minval, int maxval, int minres, int maxres) {
    return (int)(   ((float)val - (float)minval) / ((float)maxval - (float)minval) * ((float)maxres - (float)minres) + (float)minres   );
}

void valsToCoords(BITMAP * graphique, int maxVal, int duree, int * x, int * y, int xval, int yval) {
    int lar = graphique->w - 200;
    int haut = graphique->h - 200;
    *x = 100 + mapInt(xval, 0, duree, 0, lar);
    *y = graphique->h - 100 - mapInt(yval, 0, maxVal, 0, haut);
}

void dessinerCourbes(BITMAP * graphique, Graph workg, int maxVal, int duree) {
    Graph g = workg;
    std::vector<int> colors = {0x00FF00,0x0000FF,0xFF0000,0x01FFFE,0xFFA6FE,0xFFDB66,0x006401,0x010067,0x95003A,0x007DB5,0xFF00F6,0xFFEEE8,0x774D00,0x90FB92,0x0076FF,0xD5FF00,0xFF937E,0x6A826C,0xFF029D,0xFE8900,0x7A4782,0x7E2DD2,0x85A900,0xFF0056,0xA42400,0x00AE7E,0x683D3B,0xBDC6FF,0x263400,0xBDD393,0x00B917,0x9E008E,0x001544,0xC28C9F,0xFF74A3};
    for (unsigned int i = 0; i < duree; i++) {
        std::vector<std::pair<int, int>> depart;
        std::vector<std::pair<int, int>> arrivee;
        for(auto &e : g.getVertices()) {
            int x, y;
            valsToCoords(graphique, maxVal, duree, &x, &y, i, e.second.getPopulation());
            std::pair<int, int> temp(x, y);
            depart.push_back(temp);
        }
        g.update_pop();
        for(auto &e : g.getVertices()) {
            int x, y;
            valsToCoords(graphique, maxVal, duree, &x, &y, i + 1, e.second.getPopulation());
            std::pair<int, int> temp(x, y);
            arrivee.push_back(temp);
        }

        for (unsigned int i = 0; i < depart.size(); i++) {
            line(graphique, depart[i].first, depart[i].second, arrivee[i].first, arrivee[i].second, colors[i % colors.size()]);
        }

        if (i % 100 == 0) rectfill(screen, 0, 0, mapInt(i, 0, duree, 0, SCREEN_W), 10, VERT);
    }
}

void differe(Graph workg) {
    int duree = 0;
    int maxVal = 0;
    BITMAP * graphique = create_bitmap(SCREEN_W, SCREEN_H);
    clear_to_color(graphique, makecol(255, 255, 255));
    while (duree == 0) {
        std::string res;
        std::cout << "Combien de temps doit durer la simulation ?" << std::endl;
        std::cin >> res;
        if (isInt(res)) duree = std::stoi(res);
    }
    std::cout << "Creation du graphique pour " << duree << " etapes..." << std::endl;

    maxVal = findMaxVal(workg, duree);

    preparePlot(graphique, maxVal, duree);

    dessinerCourbes(graphique, workg, maxVal, duree);

    // affichage du graphique final
    clear_to_color(screen, makecol(255, 255, 255));
    blit(graphique, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    std::cout << "Appuyer sur ENTREE pour continuer" << std::endl;
    while ( !key[KEY_ENTER] ) { }

    std::cout << "Sauvegarde du graphique obtenu..." << std::endl;
    save_bitmap("simu_differee.bmp", graphique, NULL);

    std::cout << "Retour a l'affichage classique" << std::endl;
}
