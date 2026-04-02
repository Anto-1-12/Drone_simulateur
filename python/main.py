from Espace import *

class Camera:
    def __init__(self):
        pass

class Game :
    def __init__(self):
        print("Lancement simulation")
        self.run=True

    def inputs(self):
        pass

    def loop(self):
        while self.run:
            self.inputs()
        
    
game = Game()
game.loop()
print("Fermeture Simulation")