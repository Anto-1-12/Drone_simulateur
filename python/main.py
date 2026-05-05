from Espace import Drone
from Communication import InitialisationConnection,Canalouvert,Transmission,FermetureCanal
import time
import json

class Camera:
    def __init__(self):
        pass

class Game :
    sceau=time.time()
    tpsmax=100
    def __init__(self):
        print("Lancement simulation")
        self.drone=Drone()
        InitialisationConnection()
        self.run=True

    def inputs(self):
        #reçoit click
        #if reçoit click :
        
        pass

    def loop(self):
        while self.run:
            if time.time()-self.sceau >= 1/60 :
                print('tic')
                self.sceau=time.time()
                self.inputs()
                cmdreçu=Canalouvert()
                self.drone.tickdemouvement(cmdreçu)
                Transmission(json.dumps({"cmd":"Hellow"})+ "\n")
                
        
    
game = Game()
game.loop()
FermetureCanal()
print("Fermeture Simulation")