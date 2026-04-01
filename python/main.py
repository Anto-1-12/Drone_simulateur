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
    def __init__(self):
        self.centregravité=[0,0,0]
        self.orientation=[[1,0,0],
                          [0,1,0],
                          [0,0,1]]
        #positions des coins dans la liste
        # 0     1
        #   | |
        #   | |
        # 2     3
        self.coins[[-10,10,0],[10,10,0],[-10,-10,0],[10,-10,0]]
        self.moteurs=[]*(4)
        for x in range(len(self.moteurs)):
            self.moteurs[x]=Moteur.__init__(self.coins[x],self.orientation)


class Moteur:
    def __init__(self,position,orientation):
        pass