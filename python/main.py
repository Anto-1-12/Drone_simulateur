from Espace import Drone
import time

class Camera:
    def __init__(self):
        pass

class Game :
    sceau=time.time()
    tpsmax=100
    def __init__(self):
        print("Lancement simulation")
        self.drone=Drone()
        self.run=True

    def inputs(self):
        pass

    def loop(self):
        while self.run:
            if time.time()-self.sceau >= 1/60 :
                self.sceau=time.time()
                self.inputs()
                self.drone.tickdemouvement()
                
        
    
game = Game()
game.loop()
print("Fermeture Simulation")