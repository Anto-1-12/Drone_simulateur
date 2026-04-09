# Rappel Coordonnées (X,Y,Z) = index[0,1,2] centregravité==0 alors explosion
# Rappel Orientation:
#https://www.drone-normandie.com/forces-aerodynamiques/
#https://dronetech-18.webself.net/les-forces

#Cravité:
G=9.8
P=G*0.8
#pas sûr de ça



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
    Momentum=[1,
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

    def cravité(self):
        self.centregravité = [centre_elt + grav_elt for grav_elt, centre_elt in zip(self.Gravité, self.centregravité)]
        print(self.centregravité)
    def momentum(self):
        self.centregravité = [centre_elt + mome_elt for mome_elt, centre_elt in zip(self.Momentum, self.centregravité)]
        print(self.centregravité)


class Moteur:
    #N=4?
    def __init__(self,position,orientation):
        self.vecteurdirection=[]
        self.position=position
        self.orientation=orientation

    def ON(Haut,Devant,Derrière,Gauche,Droite):
        pass

    def update_position_moteurs():
        pass

#tests
D=Drone()
D.cravité()