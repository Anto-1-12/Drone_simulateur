# Rappel Coordonnées (X,Y,Z)
# Rappel Orientation:
#


class Obstacle:
    def __init__(self):
        pass

class Eclairage:
    def __init__(self):
        pass

class Drone:
    #gravité à mettre ici
    Gravité=[0,
             -1,
             0]
    #Vecteur momentum :
    Momentum=[0,
              0,
              0]

    def __init__(self):
        self.centregravité=[1,1,1]
        self.orientation=[[1,0,0],
                          [0,1,0],
                          [0,0,1]]
        #positions des coins dans la liste
        # 0     1
        #   | |
        #   | |
        # 2     3
        self.coins=[[-10,0,10],[10,0,10],[-10,-0,10],[10,-0,10]]
        self.moteurs=[]*(4)
        for x in range(len(self.moteurs)):
            self.moteurs[x]=Moteur.__init__(self.coins[x],self.orientation)

    def tickdemouvement(self):
        self.cravité()
        self.momentum()
        self.MinHauteur()

    def cravité(self):
        self.centregravité = [centre_elt + grav_elt for grav_elt, centre_elt in zip(self.Gravité, self.centregravité)]
        print(self.centregravité)
    def momentum(self):
        self.centregravité = [centre_elt + mome_elt for mome_elt, centre_elt in zip(self.Momentum, self.centregravité)]
        print(self.centregravité)
    def MinHauteur(self):
        if self.centregravité[1]<0:
            self.centregravité[1] += 10 
            


class Moteur:
    def __init__(self,position,orientation):
        pass

#tests
D=Drone()
D.cravité()