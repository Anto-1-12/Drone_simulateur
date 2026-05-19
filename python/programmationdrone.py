#ici code pour programmer le robot
COMMANDEexemple=[
    {"cmd":"avancer","temps":300},
    {"cmd":"reculer","temps":300},
    {"cmd":"rolldroite","temps":300},
    {"cmd":"rollgauche","temps":300},
    {"cmd":"rollgauche","temps":300},
    {"cmd":"rollgauche","temps":300},
    {"cmd":"tourneràdroite","temps":300},
    {"cmd":"tourneràgauche","temps":300},
    {"cmd":"augmenter puissance moteur","temps":300},
    {"cmd":"hover","temps":"300"},
    {"cmd":"diminuer puissance moteur","temps":300}]


class Palantir:
    def __init__(self):
        self.listecommande=COMMANDEexemple

    def chatgptquidoisjeviser(self):
        if self.listecommande[0]['temps']>0:
            self.listecommande[0]['temps']-=1
            return self.listecommande[0]
        else:
            self.listecommande.pop(0)
            self.listecommande[0]['temps']-=1
            return self.listecommande[0]
