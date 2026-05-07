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
                #Tic de 1/60 de seconde
                print('tic')
                #Update Time
                self.sceau=time.time()
                #Tous les inputs
                self.inputs()
                cmdreçu=Canalouvert()
                self.drone.tickdemouvement(cmdreçu)
                #Test Transmission
                Transmission(json.dumps({"cmd":"Hellow"})+ "\n")
                #Transmission et synchronisation coordonnées Drone
                Transmission(json.dumps(Drone.getcoordonnées())+"\n")
                
        
    
game = Game()
game.loop()
FermetureCanal()
print("Fermeture Simulation")