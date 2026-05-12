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
        pass

    def loop(self):

        while self.run:

            if time.time()-self.sceau >= 1/60 :

                #Tic de 1/60 de seconde
                print('tic')

                #Update Time
                self.sceau=time.time()

                #Tous les inputs serveur
                self.inputs()

                #Réceptions commandes client
                cmdreçu=Canalouvert()
                print(cmdreçu) 

                #Tick de mouvement drone
                self.drone.tickdemouvement(cmdreçu)

                #Test Transmission
                Transmission(json.dumps({"cmd":"Hellow"})+ "\n")

                #Synchronisation Coordonnées Drone
                Transmission(json.dumps(self.drone.getcoordonnées())+"\n")

                #Synchronisation Angle Drone
                #Transmission(json.dumps(self.drone.getcoordonnées())+"\n")
                
game = Game()
game.loop()
FermetureCanal()
print("Fermeture Simulation")
input()